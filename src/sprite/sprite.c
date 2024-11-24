#include "sprite.h"
#include <stdlib.h>

bongo_sprite* bongo_sprite_create(const char* texture_file)
{
  bongo_sprite* sprite = malloc(sizeof *sprite);
  if (!sprite)
  {
    return NULL;
  }

  sprite->texture = bongo_texture_create(texture_file);
  if (!sprite->texture)
  {
    free(sprite);
    return NULL;
  }

  sprite->base = sfSprite_create();
  if (!sprite->base)
  {
    bongo_texture_destroy(sprite->texture);
    free(sprite);
    return NULL;
  }
  sfSprite_setTexture(sprite->base, sprite->texture->base, sfFalse);

  return sprite;
}

void bongo_sprite_setTexture(bongo_sprite* sprite, bongo_texture* texture, sfBool resetRect)
{
  if (!texture)
  {
    sfSprite_setTexture(sprite->base, sprite->texture->base, resetRect);
    return;
  }

  sfSprite_setTexture(sprite->base, texture->base, resetRect);
}

void bongo_sprite_setScale(bongo_sprite* sprite, sfVector2f scale)
{
  sfSprite_setScale(sprite->base, (sfVector2f) { 1 / scale.x, 1 / scale.y });
  sfFloatRect size = sfSprite_getGlobalBounds(sprite->base);
  sfSprite_setOrigin(sprite->base, (sfVector2f) { size.width / 2, size.height / 2 });
}

void bongo_sprite_destroy(bongo_sprite* sprite)
{
  sfSprite_destroy(sprite->base);
  bongo_texture_destroy(sprite->texture);
  free(sprite);
}