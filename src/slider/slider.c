#include "slider.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

ui_slider* ui_slider_create()
{
  ui_slider* slider = malloc(sizeof *slider);
  if (!slider)
  {
    return NULL;
  }

  sfVector2u window_size = sfRenderWindow_getSize(gWindow);

  slider->track = sfRectangleShape_create();
  if (!slider->track)
  {
    free(slider);
    return NULL;
  }
  sfRectangleShape_setFillColor(slider->track, sfColor_fromRGB(35, 35, 35));
  sfRectangleShape_setSize(slider->track, (sfVector2f) { 200, 10 });
  sfRectangleShape_setPosition(slider->track, (sfVector2f) {
    window_size.x / 2.0f - sfRectangleShape_getSize(slider->track).x / 2,
    window_size.y / 2.5f
  });

  slider->label = sfText_create();
  if (!slider->label)
  {
    sfRectangleShape_destroy(slider->track);
    free(slider);
    return NULL;
  }
  sfText_setFont(slider->label, gFont);
  sfText_setCharacterSize(slider->label, 20);
  
  char threshold_str[15] = { 0 };
  snprintf(threshold_str, sizeof threshold_str, "threshold: %u", gThreshold);

  sfText_setString(slider->label, threshold_str);

  float label_text_size = (
    sfText_findCharacterPos(slider->label, strlen(sfText_getString(slider->label))).x
    - sfText_findCharacterPos(slider->label, 0).x
  );
  
  sfText_setPosition(slider->label, (sfVector2f) {
    window_size.x / 2.0f - label_text_size / 2,
    sfRectangleShape_getPosition(slider->track).y + 25
  });

  slider->thumb = sfRectangleShape_create();
  if (!slider->thumb)
  {
    sfText_destroy(slider->label);
    sfRectangleShape_destroy(slider->track);
    free(slider);
    return NULL;
  }

  sfRectangleShape_setFillColor(slider->thumb, sfColor_fromRGB(50, 50, 50));
  sfRectangleShape_setSize(slider->thumb, (sfVector2f) { 10, 20 });
  sfRectangleShape_setPosition(slider->thumb, (sfVector2f) {
    sfRectangleShape_getPosition(slider->track).x + 200 * (gThreshold * 1.0f / SLIDER_MAX_VALUE) - 5,
    sfRectangleShape_getPosition(slider->track).y - 5
  });

  return slider;
}

void ui_slider_draw(ui_slider* slider)
{
  sfRenderWindow_drawRectangleShape(gWindow, slider->track, NULL);
  sfRenderWindow_drawRectangleShape(gWindow, slider->thumb, NULL);
  sfRenderWindow_drawText(gWindow, slider->label, NULL);
}

void ui_slider_handleEvent(ui_slider* slider)
{
  sfVector2f mouse_pos = (sfVector2f)
  {
    sfMouse_getPositionRenderWindow(gWindow).x * 1.0f,
    sfMouse_getPositionRenderWindow(gWindow).y * 1.0f
  };

  sfFloatRect track_bounds = sfRectangleShape_getGlobalBounds(slider->track);
  sfFloatRect thumb_bounds = sfRectangleShape_getGlobalBounds(slider->thumb);
  track_bounds.width = track_bounds.width + 5;
  track_bounds.top = thumb_bounds.top;
  track_bounds.height = thumb_bounds.height;

  if (sfMouse_isButtonPressed(sfMouseLeft))
  {
    if (sfFloatRect_contains(&track_bounds, mouse_pos.x, mouse_pos.y))
    {
      sfRectangleShape_setPosition(slider->thumb, (sfVector2f) {
        mouse_pos.x - 5, sfRectangleShape_getPosition(slider->thumb).y
      });
      
      float val = (
        ((sfRectangleShape_getPosition(slider->thumb).x - sfRectangleShape_getPosition(slider->track).x) / 200)
        * SLIDER_MAX_VALUE
      );

      gThreshold = 0;
      if (val >= 0)
      {
        gThreshold = (unsigned int)roundf(val);
      }

      char threshold_str[15] = { 0 };
      snprintf(threshold_str, sizeof threshold_str, "threshold: %u", gThreshold);

      sfText_setString(slider->label, threshold_str);
    }
  }
}

void ui_slider_destroy(ui_slider* slider)
{
  sfRectangleShape_destroy(slider->thumb);
  sfRectangleShape_destroy(slider->track);
  sfText_destroy(slider->label);
  free(slider);
}