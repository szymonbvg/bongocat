#include "util.h"

int bongo_collision_pintri(sfVector2f p, sfVector2f a, sfVector2f b, sfVector2f c)
{
  float d1 = (p.x - b.x) * (a.y - b.y) - (a.x - b.x) * (p.y - b.y);
  float d2 = (p.x - c.x) * (b.y - c.y) - (b.x - c.x) * (p.y - c.y);
  float d3 = (p.x - a.x) * (c.y - a.y) - (c.x - a.x) * (p.y - a.y);
  return (d1 >= 0 && d2 >= 0 && d3 >= 0) || (d1 <= 0 && d2 <= 0 && d3 <= 0);
}

int bongo_collision_pinarea(sfVector2f p, sfVertexArray* area)
{
  sfVector2f v0_pos = sfVertexArray_getVertex(area, 0)->position;
  sfVector2f v1_pos = sfVertexArray_getVertex(area, 1)->position;
  sfVector2f v2_pos = sfVertexArray_getVertex(area, 2)->position;
  sfVector2f v3_pos = sfVertexArray_getVertex(area, 3)->position;

  return (int)(bongo_collision_pintri(p, v0_pos, v1_pos, v2_pos) || bongo_collision_pintri(p, v2_pos, v3_pos, v0_pos));
}