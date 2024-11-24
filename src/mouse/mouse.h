#ifndef BONGO_MOUSE_H
#define BONGO_MOUSE_H

#include <SFML/Graphics.h>
#include "texture/texture.h"
#include "sprite/sprite.h"

extern sfRenderWindow* gWindow;

typedef struct
{
  sfVector2f default_pos;
  sfVector2f curr_pos;

  sfVertexArray* area;
  bongo_sprite* base;
} bongo_mouse;

bongo_mouse* bongo_mouse_create();
void bongo_mouse_draw(bongo_mouse* mouse);
void bongo_mouse_handleMove(bongo_mouse* mouse);
void bongo_mouse_destroy(bongo_mouse* mouse);

#endif