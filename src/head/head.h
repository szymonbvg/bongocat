#ifndef BONGO_HEAD_H
#define BONGO_HEAD_H

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "texture/texture.h"
#include "sprite/sprite.h"

// Either I've been living under a rock,
// or there's no support for stdatomic.h in MSVC XD?
#if defined (_WIN32)
  #include <windows.h>
#else
  #include <stdatomic.h>
#endif

extern unsigned int gUse_microphone;
extern unsigned int gThreshold;

typedef struct
{
#if defined (_WIN32)
  volatile LONG voice_detected;
  volatile LONG threshold;
#else
  atomic_uint voice_detected;
  atomic_uint threshold;
#endif
} mic_thrd_data;

typedef struct
{
  unsigned int is_txt_updated;

  bongo_sprite* base;
  bongo_texture* texture_mic;

  mic_thrd_data thrd_data;
  sfSoundRecorder* recorder;
} bongo_head;

bongo_head* bongo_head_create();
void bongo_head_update(bongo_head* head);
void bongo_head_destroy(bongo_head* head);

#define bongo_head_draw(head) bongo_sprite_draw(head->base)

#endif