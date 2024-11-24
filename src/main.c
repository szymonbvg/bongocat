#include <SFML/Graphics.h>
#include "scenes/scenes.h"

sfFont* gFont;
sfRenderWindow* gWindow;
sfEvent gEvent;
sfClock* gClock;
ui_scenesManager* gSc_manager;

unsigned int gUse_microphone;

int main(void)
{
  gWindow = sfRenderWindow_create((sfVideoMode) { 520, 350 }, "bongocat", sfClose, NULL);
  if (!gWindow)
  {
    return 1;
  }
  sfRenderWindow_setFramerateLimit(gWindow, 60);

  sfImage* icon = sfImage_createFromFile("assets/icon.png");
  if (!icon)
  {
    sfRenderWindow_destroy(gWindow);
    return 1;
  }
  sfVector2u icon_size = sfImage_getSize(icon);
  sfRenderWindow_setIcon(gWindow, icon_size.x, icon_size.y, sfImage_getPixelsPtr(icon));

  gFont = sfFont_createFromFile("assets/consola.ttf");

  gSc_manager = ui_scenesManager_create();
  if (!gSc_manager)
  {
    sfFont_destroy(gFont);
    sfImage_destroy(icon);
    sfRenderWindow_destroy(gWindow);
    return 1;
  }
  ui_scenesManager_setCurrentScene(gSc_manager, UI_SCENE_SETTINGS);

  gUse_microphone = 0;

  gClock = sfClock_create();
  if (!gClock)
  {
    ui_scenesManager_destroy(gSc_manager);
    sfFont_destroy(gFont);
    sfImage_destroy(icon);
    sfRenderWindow_destroy(gWindow);
    return 1;
  }

  while (sfRenderWindow_isOpen(gWindow))
  {
    while (sfRenderWindow_pollEvent(gWindow, &gEvent))
    {
      if (gEvent.type == sfEvtClosed)
      {
        sfRenderWindow_close(gWindow);
      }

      ui_scenesManager_handleCurrentScene(gSc_manager);
    }

    ui_scenesManager_showCurrentScene(gSc_manager);
    sfRenderWindow_display(gWindow);
  }

  ui_scenesManager_destroy(gSc_manager);
  sfClock_destroy(gClock);
  sfFont_destroy(gFont);
  sfImage_destroy(icon);
  sfRenderWindow_destroy(gWindow);

  return 0;
}