#include "mouse.h"
#include "util.h"
#include <stdlib.h>
#include <math.h>
#include <float.h>

bongo_mouse* bongo_mouse_create()
{
  bongo_mouse* mouse = malloc(sizeof *mouse);
  if (!mouse)
  {
    return NULL;
  }

  mouse->area = sfVertexArray_create();
  if (!mouse->area)
  {
    free(mouse);
    return NULL;
  }
  sfVertexArray_setPrimitiveType(mouse->area, sfQuads);

  sfVertexArray_append(mouse->area, (sfVertex) {
    .position = { 80, 195 },
    .color = sfTransparent
  });
  sfVertexArray_append(mouse->area, (sfVertex) {
    .position = { 185, 220 },
    .color = sfTransparent
  });
  sfVertexArray_append(mouse->area, (sfVertex) {
    .position = { 130, 275 },
    .color = sfTransparent
  });
  sfVertexArray_append(mouse->area, (sfVertex) {
    .position = { 35, 235 },
    .color = sfTransparent
  });

  mouse->base = bongo_sprite_create("assets/mouse.png");
  if (!mouse->base)
  {
    sfVertexArray_destroy(mouse->area);
    free(mouse);
    return NULL;
  }
  bongo_sprite_setScale(mouse->base, (sfVector2f) { mouse->base->texture->scale.y * 7, mouse->base->texture->scale.y * 7 });
  mouse->default_pos = (sfVector2f){ 105, 235 };
  bongo_sprite_setPosition(mouse->base, mouse->default_pos.x, mouse->default_pos.y);

  mouse->curr_pos = bongo_sprite_getPosition(mouse->base);

  return mouse;
}

void bongo_mouse_draw(bongo_mouse* mouse)
{
  sfRenderWindow_drawVertexArray(gWindow, mouse->area, NULL);
  bongo_sprite_draw(mouse->base);
}

void bongo_mouse_handleMove(bongo_mouse* mouse)
{
  sfVector2f center = (sfVector2f) { sfVideoMode_getDesktopMode().width / 2.0f, sfVideoMode_getDesktopMode().height / 2.0f };
  sfVector2f scale = (sfVector2f) { 60 / -center.x, 30 / -center.y };
  sfVector2f mouse_pos = (sfVector2f) { sfMouse_getPosition(NULL).x * 1.0f, sfMouse_getPosition(NULL).y * 1.0f };

  sfVector2f new_pos = (sfVector2f)
  {
    mouse->default_pos.x + (mouse_pos.x - center.x) * scale.x,
    mouse->default_pos.y + (mouse_pos.y - center.y) * scale.y
  };

  bongo_sprite_setPosition(mouse->base, new_pos.x, new_pos.y);

  int is_in_area = bongo_collision_pinarea(new_pos, mouse->area);
  if (!is_in_area)
  {
    sfVector2f nearest = new_pos;
    float min_d = FLT_MAX;
    for (int i = 0; i < 4; ++i)
    {
      int j = i + 1;
      sfVector2f a = sfVertexArray_getVertex(mouse->area, i)->position;
      sfVector2f b = sfVertexArray_getVertex(mouse->area, j % 4)->position;

      sfVector2f ab = { b.x - a.x, b.y - a.y };
      float t = ((new_pos.x - a.x) * ab.x + (new_pos.y - a.y) * ab.y) / (powf(ab.x, 2) + powf(ab.y, 2));

      if (t < 0.0f) t = 0.0f;
      if (t > 1.0f) t = 1.0f;

      sfVector2f interpolated_p = { a.x + ab.x * t, a.y + ab.y * t };
      float d = sqrtf(powf(new_pos.x - interpolated_p.x, 2) + powf(new_pos.y - interpolated_p.y, 2));

      if (d < min_d) {
        min_d = d;
        nearest = interpolated_p;
      }
    }

    bongo_sprite_setPosition(mouse->base, nearest.x, nearest.y);
  }

  mouse->curr_pos = bongo_sprite_getPosition(mouse->base);
}

void bongo_mouse_destroy(bongo_mouse* mouse)
{
  sfVertexArray_destroy(mouse->area);
  bongo_sprite_destroy(mouse->base);
  free(mouse);
}