#include "head.h"
#include <stdlib.h>
#include <stdio.h>

static sfBool recorder_onProcess(const sfInt16* samples, size_t count, void* arg)
{
  float avg_amp = 0.0f;
  for (int i = 0; i < count; i++)
  {
    avg_amp += abs(samples[i]);
  }
  avg_amp = avg_amp / count;
  
#if defined (_WIN32)
  volatile LONG* voice_detected = (volatile LONG*)arg;
  InterlockedExchange(voice_detected, FALSE);

  if (avg_amp > 100.0f)
  {
    InterlockedExchange(voice_detected, TRUE);
  }
#else
  atomic_uint* voice_detected = (atomic_uint*)arg;
  atomic_store(voice_detected, 0);

  if (avg_amp > 100.0f)
  {
    atomic_store(voice_detected, 1);
  }
#endif

  sfSleep(sfMilliseconds(100));
  return sfTrue;
}

bongo_head* bongo_head_create()
{
  bongo_head* head = malloc(sizeof *head);
  if (!head)
  {
    return NULL;
  }

  head->base = bongo_sprite_create("assets/head.png");
  if (!head->base)
  {
    free(head);
    return NULL;
  }
  bongo_sprite_setScale(head->base, (sfVector2f) {
    head->base->texture->scale.y * 1.6f, head->base->texture->scale.y * 1.6f
  });
  bongo_sprite_setPosition(
    head->base,
    sfRenderWindow_getSize(gWindow).x / 2.0f - 15, 
    bongo_sprite_getGlobalBounds(head->base).height / 2 - 25
  );

  head->is_txt_updated = 0;
#if defined (_WIN32)
  head->voice_detected = FALSE;
#else
  head->voice_detected = ATOMIC_VAR_INIT(0);
#endif

  head->recorder = NULL;
  head->texture_mic = NULL;
  if (gUse_microphone)
  {
    head->texture_mic = bongo_texture_create("assets/head_speak.png");
    if (!head->texture_mic)
    {
      bongo_sprite_destroy(head->base);
      free(head);
      return NULL;
    }

    head->recorder = sfSoundRecorder_create(NULL, recorder_onProcess, NULL, (void*)&head->voice_detected);
    if (!head->recorder)
    {
      bongo_texture_destroy(head->texture_mic);
      bongo_sprite_destroy(head->base);
      free(head);
      return NULL;
    }
    sfSoundRecorder_start(head->recorder, 44100);
  }

  return head;
}

void bongo_head_update(bongo_head* head)
{
  if (!gUse_microphone)
  {
    return;
  }

  if (head->is_txt_updated)
  {
    bongo_sprite_setTexture(head->base, NULL, sfTrue);
    bongo_sprite_setScale(head->base, (sfVector2f) {
      head->base->texture->scale.y * 1.6f, head->base->texture->scale.y * 1.6f
    });
    head->is_txt_updated = 0;
  }

#if defined (_WIN32)
  #define BONGO_VOICE_CONDITION (InterlockedCompareExchange(&head->voice_detected, 0, 0))
#else
  #define BONGO_VOICE_CONDITION (atomic_load(&head->voice_detected))
#endif
  if (BONGO_VOICE_CONDITION)
  {
    bongo_sprite_setTexture(head->base, head->texture_mic, sfTrue);
    bongo_sprite_setScale(head->base, (sfVector2f) {
      head->texture_mic->scale.y * 1.6f, head->texture_mic->scale.y * 1.6f
    });
    head->is_txt_updated = 1;
  }

  bongo_sprite_setPosition(
    head->base,
    sfRenderWindow_getSize(gWindow).x / 2.0f - 15,
    bongo_sprite_getGlobalBounds(head->base).height / 2 - 25
  );
}

void bongo_head_destroy(bongo_head* head)
{
  bongo_sprite_destroy(head->base);
  if (gUse_microphone)
  {
    bongo_texture_destroy(head->texture_mic);
    sfSoundRecorder_stop(head->recorder);
    sfSoundRecorder_destroy(head->recorder);
  }
  free(head);
}