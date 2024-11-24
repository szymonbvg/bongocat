#ifndef UI_SCENES_H
#define UI_SCENES_H

#include <SFML/Graphics.h>

extern sfRenderWindow* gWindow;
extern unsigned int gUse_microphone;

typedef enum
{
  UI_SCENE_SETTINGS,
  UI_SCENE_BONGOCAT,
  UI_SCENE_COUNT
} ui_scene_e;

struct ui_scene
{
  sfColor bg_color;

  void (*show)(void*);
  void (*update)(void*);
  void (*handleEvent)(void*);
  void (*destroy)(void*);

  void* scene_data;
};

typedef struct
{
  int curr_scene;
  struct ui_scene** scenes;
} ui_scenesManager;

ui_scenesManager* ui_scenesManager_create();
void ui_scenesManager_setCurrentScene(ui_scenesManager* manager, ui_scene_e scene);
void ui_scenesManager_showCurrentScene(ui_scenesManager* manager);
void ui_scenesManager_handleCurrentScene(ui_scenesManager* manager);
void ui_scenesManager_destroy(ui_scenesManager* manager);

#endif