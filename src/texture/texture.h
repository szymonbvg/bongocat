#ifndef BONGO_TEXTURE_H
#define BONGO_TEXTURE_H

#include <SFML/Graphics.h>

extern sfRenderWindow* gWindow;

typedef struct
{
  sfTexture* base;
  sfVector2f size;
  sfVector2f scale;
} bongo_texture;

bongo_texture* bongo_texture_create(const char* texture_file);
void bongo_texture_destroy(bongo_texture* texture);

#endif