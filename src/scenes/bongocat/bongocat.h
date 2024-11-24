#ifndef UI_SCENE_BONGOCAT_H
#define UI_SCENE_BONGOCAT_H

#include <SFML/Graphics.h>
#include "../scenes.h"
#include "mouse_arm/mouse_arm.h"
#include "keyboard_arm/keyboard_arm.h"
#include "texture/texture.h"
#include "mouse/mouse.h"
#include "head/head.h"
#include "sprite/sprite.h"

struct ui_scene_bongocat
{
  bongo_sprite* desk;
  bongo_sprite* body;
  bongo_head* head;
  bongo_mouse_arm* mouse_arm;
  bongo_kb_arm* kb_arm;
  bongo_mouse* mouse;
};

typedef struct ui_scene ui_scene_bongocat_t;

ui_scene_bongocat_t* ui_scene_bongocat_create();
void ui_scene_bongocat_show(ui_scene_bongocat_t* scene);
void ui_scene_bongocat_update(ui_scene_bongocat_t* scene);
void ui_scene_bongocat_destroy(ui_scene_bongocat_t* scene);

#endif