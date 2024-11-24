#ifndef BONGO_SPRITE_H
#define BONGO_SPRITE_H

#include <SFML/Graphics.h>
#include "texture/texture.h"

extern sfRenderWindow* gWindow;

typedef struct
{
  bongo_texture* texture;
  sfSprite* base;
} bongo_sprite;

bongo_sprite* bongo_sprite_create(const char* texture_file);
void bongo_sprite_setScale(bongo_sprite* sprite, sfVector2f scale);
void bongo_sprite_setTexture(bongo_sprite* sprite, bongo_texture* texture, sfBool resetRect);
void bongo_sprite_destroy(bongo_sprite* sprite);

#define bongo_sprite_setPosition(sprite, x, y) sfSprite_setPosition(sprite->base, (sfVector2f) {x, y})
#define bongo_sprite_draw(sprite) sfRenderWindow_drawSprite(gWindow, sprite->base, NULL)
#define bongo_sprite_getPosition(sprite) sfSprite_getPosition(sprite->base)
#define bongo_sprite_getGlobalBounds(sprite) sfSprite_getGlobalBounds(sprite->base)
#define bongo_sprite_rotate(sprite, angle) sfSprite_rotate(sprite->base, angle)

#endif