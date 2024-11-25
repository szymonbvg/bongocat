#ifndef UI_SLIDER
#define UI_SLIDER

#include <SFML/Graphics.h>

#define SLIDER_MAX_VALUE 300

extern sfRenderWindow* gWindow;
extern sfFont* gFont;
extern unsigned int gThreshold;

typedef struct
{
  sfText* label;
  sfRectangleShape* track;
  sfRectangleShape* thumb;
} ui_slider;

ui_slider* ui_slider_create();
void ui_slider_draw(ui_slider* slider);
void ui_slider_handleEvent(ui_slider* slider);
void ui_slider_destroy(ui_slider* slider);

#endif