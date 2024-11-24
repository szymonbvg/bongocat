#ifndef BONGO_MOUSE_ARM_H
#define BONGO_MOUSE_ARM_H

#include <SFML/Graphics.h>
#include "texture/texture.h"
#include "mouse/mouse.h"

extern sfRenderWindow* gWindow;
extern sfEvent gEvent;

typedef struct
{
  bongo_texture* texture;
  sfVertexArray* base;
} bongo_mouse_arm;

bongo_mouse_arm* bongo_mouse_arm_create();
void bongo_mouse_arm_draw(bongo_mouse_arm* arm);
void bongo_mouse_arm_handleMove(bongo_mouse_arm* arm, bongo_mouse* parent);
void bongo_mouse_arm_destroy(bongo_mouse_arm* arm);

#endif