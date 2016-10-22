#include <pebble.h>
#include "display.h"
#include "clicks.h"
#include "timer.h"
#include "fgbattery.h"
#include "fgmessage.h"
#include "bgworker.h"


static const GRect BATTERY_POSITIONS =  { { 0,  0 }, { /* width: */ 144, /* height: */  16} };
static const GRect TIME_POSITIONS =     { { 0, 32 }, { /* width: */ 144, /* height: */  56} };
static const GRect DATE_POSITIONS =     { { 0,104 }, { /* width: */ 144, /* height: */  56} };
// total dimension: 176 (row) x 144 (col)



static Window *s_main_window;
static ActionBarLayer *s_action_bar_layer;
TextLayer *s_battery_layer;
TextLayer *s_date_layer;
TextLayer *s_time_layer;


void main_window_load(Window *window) {  
 
  // Create ActionBar
  s_action_bar_layer = action_bar_layer_create();
  action_bar_layer_add_to_window(s_action_bar_layer, window);
  action_bar_layer_set_click_config_provider(s_action_bar_layer, config_provider);
  
  // Create TextLayer for Battery
  s_battery_layer = text_layer_create(BATTERY_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_battery_layer));
  text_layer_set_background_color(s_battery_layer, GColorBlack);
  text_layer_set_text_color(s_battery_layer, GColorWhite);
  text_layer_set_text_alignment(s_battery_layer, GTextAlignmentRight);
  text_layer_set_font(s_battery_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  
  // Create TextLayer for Time
  s_time_layer = text_layer_create(TIME_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_background_color(s_time_layer, GColorBlack);
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49)); //FONT_KEY_ROBOTO_BOLD_SUBSET_49

  // Create TextLayer for Date
  s_date_layer = text_layer_create(DATE_POSITIONS);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_layer));
  text_layer_set_text(s_date_layer, "XXXDay\n00/00/0000");
  text_layer_set_background_color(s_date_layer, GColorBlack);
  text_layer_set_text_color(s_date_layer, GColorWhite);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
  text_layer_set_font(s_date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  
}



void main_window_unload(Window *window) {
  action_bar_layer_destroy(s_action_bar_layer);
  text_layer_destroy(s_battery_layer);
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_time_layer);
}



void display_subscribe(){
  s_main_window = window_create();
  window_set_background_color(s_main_window, GColorBlack);
  
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}



void display_unsubscribe(){
  window_destroy(s_main_window);
}