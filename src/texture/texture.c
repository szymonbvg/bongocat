#include "texture.h"
#include <stdlib.h>

bongo_texture* bongo_texture_create(const char* texture_file)
{
  bongo_texture* texture = malloc(sizeof *texture);
  if (!texture)
  {
    return NULL;
  }

  texture->base = sfTexture_createFromFile(texture_file, NULL);
  texture->size = (sfVector2f) { 0, 0 };

  if (texture->base)
  {
    texture->size = (sfVector2f) {
      sfTexture_getSize(texture->base).x * 1.0f,
      sfTexture_getSize(texture->base).y * 1.0f
    };
  }

  texture->scale = (sfVector2f)
  {
    texture->size.x / (sfRenderWindow_getSize(gWindow).x * 1.0f),
    texture->size.y / (sfRenderWindow_getSize(gWindow).y * 1.0f)
  };

  return texture;
}

void bongo_texture_destroy(bongo_texture* texture)
{
  sfTexture_destroy(texture->base);
  free(texture);
}