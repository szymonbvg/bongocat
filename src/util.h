#ifndef BONGO_UTIL_H
#define BONGO_UTIL_H

#include <SFML/Graphics.h>

int bongo_collision_pintri(sfVector2f p, sfVector2f a, sfVector2f b, sfVector2f c);
int bongo_collision_pinarea(sfVector2f p, sfVertexArray* area);

#endif