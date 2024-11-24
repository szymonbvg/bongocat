#include "bongocat.h"
#include <stdlib.h>

ui_scene_bongocat_t* ui_scene_bongocat_create()
{
  ui_scene_bongocat_t* scene = malloc(sizeof *scene);
  if (!scene)
  {
    return NULL;
  }

  struct ui_scene_bongocat* data = malloc(sizeof *data);
  if (!data)
  {
    free(scene);
    return NULL;
  }

  data->desk = bongo_sprite_create("assets/desk.png");
  if (!data->desk)
  {
    free(data);
    free(scene);
    return NULL;
  }
  bongo_sprite_setScale(data->desk, (sfVector2f) { data->desk->texture->scale.x, data->desk->texture->scale.y });
  bongo_sprite_setPosition(data->desk, sfRenderWindow_getSize(gWindow).x / 2.0f, sfRenderWindow_getSize(gWindow).y / 2.0f);

  data->body = bongo_sprite_create("assets/body.png");
  if (!data->body)
  {
    bongo_sprite_destroy(data->desk);
    free(data);
    free(scene);
    return NULL;
  }
  bongo_sprite_setScale(data->body, (sfVector2f) { data->body->texture->scale.x * 1.75f, data->body->texture->scale.y * 1.75f });
  bongo_sprite_setPosition(data->body, sfRenderWindow_getSize(gWindow).x / 2.0f + 25, sfRenderWindow_getSize(gWindow).y / 2.0f - 35);

  data->head = bongo_head_create();
  if (!data->head)
  {
    bongo_sprite_destroy(data->body);
    bongo_sprite_destroy(data->desk);
    free(data);
    free(scene);
    return NULL;
  }

  data->mouse = bongo_mouse_create();
  if (!data->mouse)
  {
    bongo_head_destroy(data->head);
    bongo_sprite_destroy(data->body);
    bongo_sprite_destroy(data->desk);
    free(data);
    free(scene);
    return NULL;
  }

  data->mouse_arm = bongo_mouse_arm_create();
  if (!data->mouse_arm)
  {
    bongo_mouse_destroy(data->mouse);
    bongo_head_destroy(data->head);
    bongo_sprite_destroy(data->body);
    bongo_sprite_destroy(data->desk);
    free(data);
    free(scene);
    return NULL;
  }

  data->kb_arm = bongo_kb_arm_create();
  if (!data->kb_arm)
  {
    bongo_mouse_arm_destroy(data->mouse_arm);
    bongo_mouse_destroy(data->mouse);
    bongo_head_destroy(data->head);
    bongo_sprite_destroy(data->body);
    bongo_sprite_destroy(data->desk);
    free(data);
    free(scene);
    return NULL;
  }

  scene->bg_color = sfWhite;
  scene->scene_data = data;

  scene->show = ui_scene_bongocat_show;
  scene->update = ui_scene_bongocat_update;
  scene->destroy = ui_scene_bongocat_destroy;
  scene->handleEvent = NULL;

  return scene;
}

void ui_scene_bongocat_show(ui_scene_bongocat_t* scene)
{
  struct ui_scene_bongocat* data = scene->scene_data;

  bongo_sprite_draw(data->desk);
  bongo_mouse_draw(data->mouse);
  bongo_mouse_arm_draw(data->mouse_arm);
  bongo_sprite_draw(data->body);
  bongo_head_draw(data->head);
  bongo_kb_arm_draw(data->kb_arm);
}

void ui_scene_bongocat_update(ui_scene_bongocat_t* scene)
{
  struct ui_scene_bongocat* data = scene->scene_data;

  bongo_mouse_handleMove(data->mouse);
  bongo_mouse_arm_handleMove(data->mouse_arm, data->mouse);
  bongo_kb_arm_handleClick(data->kb_arm);
  bongo_kb_arm_update(data->kb_arm);
  bongo_head_update(data->head);
}

void ui_scene_bongocat_destroy(ui_scene_bongocat_t* scene)
{
  struct ui_scene_bongocat* data = scene->scene_data;

  bongo_sprite_destroy(data->desk);
  bongo_sprite_destroy(data->body);
  bongo_head_destroy(data->head);
  bongo_mouse_destroy(data->mouse);
  bongo_mouse_arm_destroy(data->mouse_arm);
  bongo_kb_arm_destroy(data->kb_arm);
  free(data);
  free(scene);
}