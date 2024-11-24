#include "keyboard_arm.h"
#include <stdlib.h>

bongo_kb_arm* bongo_kb_arm_create()
{
  bongo_kb_arm* arm = malloc(sizeof *arm);
  if (!arm)
  {
    return NULL;
  }

  arm->is_pressed = 0;
  arm->rotation = 0;

  arm->texture_d = bongo_texture_create("assets/arm_down.png");
  if (!arm->texture_d)
  {
    free(arm);
    return NULL;
  }

  arm->base = bongo_sprite_create("assets/arm_up.png");
  if (!arm->base)
  {
    bongo_texture_destroy(arm->texture_d);
    free(arm);
    return NULL;
  }
  bongo_sprite_setScale(arm->base, (sfVector2f) { arm->base->texture->scale.y * 4, arm->base->texture->scale.y * 4 });
  bongo_sprite_setPosition(arm->base, 362, 180);

  return arm;
}

void bongo_kb_arm_update(bongo_kb_arm* arm)
{
  if (sfTime_asMilliseconds(sfClock_getElapsedTime(gClock)) >= 15 && arm->is_pressed)
  {
    if (arm->rotation > 0)
    {
      bongo_sprite_rotate(arm->base, -40);
    }
    else if (arm->rotation < 0)
    {
      bongo_sprite_rotate(arm->base, 30);
    }

    bongo_sprite_setTexture(arm->base, NULL, sfTrue);
    bongo_sprite_setScale(arm->base, (sfVector2f) { arm->base->texture->scale.y * 4, arm->base->texture->scale.y * 4 });
    bongo_sprite_setPosition(arm->base, 362, 180);

    arm->is_pressed = 0;
  }
}

void bongo_kb_arm_handleClick(bongo_kb_arm* arm)
{
  for (int i = 0; i < sfKeyCount; i++)
  {
    if (!sfKeyboard_isKeyPressed(i))
    {
      continue;
    }

    sfClock_restart(gClock);
    if (arm->is_pressed)
    {
      break;
    }

    bongo_sprite_setTexture(arm->base, arm->texture_d, sfTrue);
    bongo_sprite_setScale(arm->base, (sfVector2f) { arm->texture_d->scale.y * 4, arm->texture_d->scale.y * 4 });
    bongo_sprite_setPosition(arm->base, 367, 247);

    arm->rotation = 0;
    
    if ((i <= 6 && i != 1) || (i >= 16 && i <= 31 && i != 20 && i != 24 && i != 26))
    {
      bongo_sprite_setPosition(arm->base, 395, 235);
      bongo_sprite_rotate(arm->base, -30);

      arm->rotation = -1;
    }
    else if ((i >= 7 && i <= 15) || (i >= 32 && i <= 35) || i == 20 || i == 24 || i == 1 || i == 26)
    {
      bongo_sprite_setPosition(arm->base, 340, 235);
      bongo_sprite_rotate(arm->base, 40);

      arm->rotation = 1;
    }

    arm->is_pressed = 1;
    break;
  }
}

void bongo_kb_arm_destroy(bongo_kb_arm* arm)
{
  bongo_sprite_destroy(arm->base);
  bongo_texture_destroy(arm->texture_d);
  free(arm);
}