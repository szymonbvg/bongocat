#include "scenes.h"
#include "settings/settings.h"
#include "bongocat/bongocat.h"
#include <stdlib.h>

ui_scenesManager* ui_scenesManager_create()
{
  ui_scenesManager* manager = malloc(sizeof *manager);
  if (!manager)
  {
    return NULL;
  }

  manager->scenes = (struct ui_scene**)malloc(UI_SCENE_COUNT * sizeof(struct ui_scene));
  if (!manager->scenes)
  {
    free(manager);
    return NULL;
  }
  manager->curr_scene = -1;
  for (int i = 0; i < UI_SCENE_COUNT; i++)
  {
    manager->scenes[i] = NULL;
  }

  return manager;
}

void ui_scenesManager_setCurrentScene(ui_scenesManager* manager, ui_scene_e scene)
{
  manager->curr_scene = scene;
  for (int i = 0; i < UI_SCENE_BONGOCAT; i++)
  {
    struct ui_scene* scene = manager->scenes[i];
    if (i == manager->curr_scene || !scene)
    {
      continue;
    }

    scene->destroy(scene);
    manager->scenes[i] = NULL;
  }
  if (manager->scenes[scene])
  {
    return;
  }

  switch (scene)
  {
    case UI_SCENE_SETTINGS:
      manager->scenes[scene] = ui_scene_settings_create();
      break;
    case UI_SCENE_BONGOCAT:
      manager->scenes[scene] = ui_scene_bongocat_create();
      break;
    default:
      break;
  }
}

void ui_scenesManager_showCurrentScene(ui_scenesManager* manager)
{
  struct ui_scene* scene = manager->scenes[manager->curr_scene];
  if (!scene)
  {
    return;
  }

  sfRenderWindow_clear(gWindow, scene->bg_color);
  if (scene->update)
  {
    scene->update(scene);
  }
  scene->show(scene);

}

void ui_scenesManager_handleCurrentScene(ui_scenesManager* manager)
{
  struct ui_scene* scene = manager->scenes[manager->curr_scene];
  if (scene && scene->handleEvent)
  {
    scene->handleEvent(scene);
  }
}

void ui_scenesManager_destroy(ui_scenesManager* manager)
{
  for (int i = 0; i < UI_SCENE_COUNT; i++)
  {
    struct ui_scene* scene = manager->scenes[i];
    if (!scene)
    {
      continue;
    }
    scene->destroy(scene);
    manager->scenes[i] = NULL;
  }

  free(manager->scenes);
  free(manager);
}