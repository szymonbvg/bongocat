#ifndef BONGO_KEYBOARD_ARM_H
#define BONGO_KEYBOARD_ARM_H

#include <SFML/Graphics.h>
#include "texture/texture.h"
#include "sprite/sprite.h"

extern sfRenderWindow* gWindow;
extern sfClock* gClock;

typedef struct
{
  unsigned int is_pressed;
  int rotation;

  bongo_sprite* base;
  bongo_texture* texture_d;
} bongo_kb_arm;

bongo_kb_arm* bongo_kb_arm_create();
void bongo_kb_arm_update(bongo_kb_arm* arm);
void bongo_kb_arm_handleClick(bongo_kb_arm* arm);
void bongo_kb_arm_destroy(bongo_kb_arm* arm);

#define bongo_kb_arm_draw(arm) bongo_sprite_draw(arm->base)

#endif