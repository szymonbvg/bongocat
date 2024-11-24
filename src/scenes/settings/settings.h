#ifndef UI_SCENE_SETTINGS_H
#define UI_SCENE_SETTINGS_H

#include <SFML/Graphics.h>
#include "scenes/scenes.h"

extern ui_scenesManager* gSc_manager;
extern sfFont* gFont;
extern sfEvent gEvent;
extern unsigned int gUse_microphone;

struct ui_scene_settings
{
  sfText* mic_text;
  sfText* btn_text;
  sfRectangleShape* checkbox;
  sfRectangleShape* btn;
};

typedef struct ui_scene ui_scene_settings_t;

ui_scene_settings_t* ui_scene_settings_create();
void ui_scene_settings_show(ui_scene_settings_t* scene);
void ui_scene_settings_handleEvent(ui_scene_settings_t* scene);
void ui_scene_settings_destroy(ui_scene_settings_t* scene);

#endif