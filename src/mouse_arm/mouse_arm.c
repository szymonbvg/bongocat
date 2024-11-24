#include "mouse_arm.h"
#include <stdlib.h>

bongo_mouse_arm* bongo_mouse_arm_create()
{
  bongo_mouse_arm* arm = malloc(sizeof *arm);
  if (!arm)
  {
    return NULL;
  }

  arm->texture = bongo_texture_create("assets/mouse_arm.png");
  if (!arm->texture)
  {
    free(arm);
    return NULL;
  }
  
  arm->base = sfVertexArray_create();
  if (!arm->base)
  {
    bongo_texture_destroy(arm->texture);
    free(arm);
    return NULL;
  }
  sfVertexArray_setPrimitiveType(arm->base, sfQuads);

  sfVertexArray_append(arm->base, (sfVertex) {
    .position = { 105, 120 },
    .texCoords = { 0, 0 },
    .color = sfWhite
  });
  sfVertexArray_append(arm->base, (sfVertex) {
    .position = { 230, 120 },
    .texCoords = { arm->texture->size.x,0 },
    .color = sfWhite
  });
  sfVertexArray_append(arm->base, (sfVertex) {
    .position = { 180, 250 },
    .texCoords = { arm->texture->size.x, arm->texture->size.y },
    .color = sfWhite
  });
  sfVertexArray_append(arm->base, (sfVertex) {
    .position = { 80, 250 },
    .texCoords = { 0, arm->texture->size.y },
    .color = sfWhite
  });

  return arm;
}

void bongo_mouse_arm_draw(bongo_mouse_arm* arm)
{
  sfRenderStates states = sfRenderStates_default();
  states.texture = arm->texture->base;
  sfRenderWindow_drawVertexArray(gWindow, arm->base, &states);
}

// I'm too lazy to implement bezier
// Maybe someday
void bongo_mouse_arm_handleMove(bongo_mouse_arm* arm, bongo_mouse* parent)
{
  sfVertex* v2 = sfVertexArray_getVertex(arm->base, 2);
  v2->position = (sfVector2f){ parent->curr_pos.x + 90, parent->curr_pos.y };

  sfVertex* v3 = sfVertexArray_getVertex(arm->base, 3);
  v3->position = (sfVector2f){ parent->curr_pos.x - 20, parent->curr_pos.y - 10 };
}

void bongo_mouse_arm_destroy(bongo_mouse_arm* arm)
{
  sfVertexArray_destroy(arm->base);
  bongo_texture_destroy(arm->texture);
  free(arm);
}