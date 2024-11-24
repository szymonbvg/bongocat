#include "settings.h"
#include <string.h>
#include <stdlib.h>

ui_scene_settings_t* ui_scene_settings_create()
{
  ui_scene_settings_t* scene = malloc(sizeof *scene);
  if (!scene)
  {
    return NULL;
  }

  struct ui_scene_settings* data = malloc(sizeof *data);
  if (!data)
  {
    free(scene);
    return NULL;
  }

  data->mic_text = sfText_create();
  if (!data->mic_text)
  {
    free(data);
    free(scene);
    return NULL;
  }

  data->btn_text = sfText_create();
  if (!data->btn_text)
  {
    sfText_destroy(data->mic_text);
    free(data);
    free(scene);
    return NULL;
  }

  data->checkbox = sfRectangleShape_create();
  if (!data->checkbox)
  {
    sfText_destroy(data->mic_text);
    sfText_destroy(data->btn_text);
    free(data);
    free(scene);
    return NULL;
  }

  data->btn = sfRectangleShape_create();
  if (!data->btn)
  {
    sfText_destroy(data->mic_text);
    sfText_destroy(data->btn_text);
    sfRectangleShape_destroy(data->checkbox);
    free(data);
    free(scene);
    return NULL;
  }

  sfVector2u window_size = sfRenderWindow_getSize(gWindow);
  
  sfText_setFont(data->mic_text, gFont);
  sfText_setCharacterSize(data->mic_text, 20);
  sfText_setString(data->mic_text, "use microphone?");

  float mic_text_size = (
    sfText_findCharacterPos(data->mic_text, strlen(sfText_getString(data->mic_text))).x
    - sfText_findCharacterPos(data->mic_text, 0).x
  );
  
  sfText_setPosition(data->mic_text, (sfVector2f) {
    (window_size.x / 2.0f - mic_text_size / 2) - (10 + sfRectangleShape_getSize(data->checkbox).x / 2),
    window_size.y / 3.5f
  });

  sfRectangleShape_setFillColor(data->checkbox, sfRed);
  sfRectangleShape_setSize(data->checkbox, (sfVector2f) { 15, 15 });
  sfRectangleShape_setPosition(data->checkbox, (sfVector2f) {
    sfText_getPosition(data->mic_text).x + mic_text_size + 10,
    window_size.y / 3.5f + 7
  });

  sfRectangleShape_setFillColor(data->btn, sfColor_fromRGB(35, 35, 35));
  sfRectangleShape_setSize(data->btn, (sfVector2f) { sfRenderWindow_getSize(gWindow).x / 3.0f, 45 });
  sfRectangleShape_setPosition(data->btn, (sfVector2f) {
    window_size.x / 2.0f - sfRectangleShape_getSize(data->btn).x / 2.0f,
    window_size.y / 2.0f
  });

  sfText_setFont(data->btn_text, gFont);
  sfText_setCharacterSize(data->btn_text, 20);
  sfText_setString(data->btn_text, "start");

  float btn_text_size = (
    sfText_findCharacterPos(data->btn_text, strlen(sfText_getString(data->btn_text))).x
    - sfText_findCharacterPos(data->btn_text, 0).x
  );

  sfText_setPosition(data->btn_text, (sfVector2f) {
    window_size.x / 2.0f - btn_text_size / 2,
      sfRectangleShape_getPosition(data->btn).y + 9
  });

  scene->bg_color = sfBlack;
  scene->scene_data = data;

  scene->show = ui_scene_settings_show;
  scene->handleEvent = ui_scene_settings_handleEvent;
  scene->destroy = ui_scene_settings_destroy;
  scene->update = NULL;

  return scene;
}

void ui_scene_settings_show(ui_scene_settings_t* scene)
{
  struct ui_scene_settings* data = scene->scene_data;

  sfRenderWindow_drawText(gWindow, data->mic_text, NULL);
  sfRenderWindow_drawRectangleShape(gWindow, data->checkbox, NULL);
  sfRenderWindow_drawRectangleShape(gWindow, data->btn, NULL);
  sfRenderWindow_drawText(gWindow, data->btn_text, NULL);
}

void ui_scene_settings_handleEvent(ui_scene_settings_t* scene)
{
  struct ui_scene_settings* data = scene->scene_data;

  sfVector2f mouse_pos = (sfVector2f)
  {
    sfMouse_getPositionRenderWindow(gWindow).x * 1.0f,
    sfMouse_getPositionRenderWindow(gWindow).y * 1.0f
  };

  sfFloatRect btn_bounds = sfRectangleShape_getGlobalBounds(data->btn);

  if (gEvent.type == sfEvtMouseButtonReleased)
  {
    if (gEvent.mouseButton.button == sfMouseLeft)
    {
      sfFloatRect checkbox_bounds = sfRectangleShape_getGlobalBounds(data->checkbox);
      if (sfFloatRect_contains(&checkbox_bounds, mouse_pos.x, mouse_pos.y))
      {
        sfRectangleShape_setFillColor(data->checkbox, sfRed);
        if (!gUse_microphone)
        {
          sfRectangleShape_setFillColor(data->checkbox, sfGreen);
        }
        gUse_microphone = !gUse_microphone;
      }

      if (sfFloatRect_contains(&btn_bounds, mouse_pos.x, mouse_pos.y))
      {
        ui_scenesManager_setCurrentScene(gSc_manager, UI_SCENE_BONGOCAT);
        return;
      }
    }
  }

  sfRectangleShape_setFillColor(data->btn, sfColor_fromRGB(35, 35, 35));
  if (sfFloatRect_contains(&btn_bounds, mouse_pos.x, mouse_pos.y))
  {
    sfRectangleShape_setFillColor(data->btn, sfColor_fromRGB(50, 50, 50));
  }
}

void ui_scene_settings_destroy(ui_scene_settings_t* scene)
{
  struct ui_scene_settings* data = scene->scene_data;

  sfText_destroy(data->mic_text);
  sfText_destroy(data->btn_text);
  sfRectangleShape_destroy(data->checkbox);
  sfRectangleShape_destroy(data->btn);
  free(data);
  free(scene);
}