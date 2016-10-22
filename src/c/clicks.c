#include <pebble.h>
#include "display.h"
#include "clicks.h"
#include "timer.h"
#include "fgbattery.h"
#include "fgmessage.h"
#include "bgworker.h"


void single_click_handler(ClickRecognizerRef recognizer, void *context) {
  delay_time();
}

void back_click_handler(ClickRecognizerRef recognizer, void *context) {
  delay_time();
}

void long_click_handler(ClickRecognizerRef recognizer, void *context) {
  delay_time();
}

void multi_click_handler(ClickRecognizerRef recognizer, void *context) {
  delay_time();
}

void config_provider(void *ctx) {
  window_single_click_subscribe(BUTTON_ID_SELECT, single_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, single_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, single_click_handler);
  window_single_click_subscribe(BUTTON_ID_BACK, back_click_handler);
  window_long_click_subscribe(BUTTON_ID_UP, 1000, long_click_handler, NULL);
  window_long_click_subscribe(BUTTON_ID_DOWN, 1000, long_click_handler, NULL);
  window_long_click_subscribe(BUTTON_ID_SELECT, 1000, long_click_handler, NULL);
  window_multi_click_subscribe(BUTTON_ID_UP, 2, 3, 1000, true, multi_click_handler);
  window_multi_click_subscribe(BUTTON_ID_DOWN, 2, 3, 1000, true, multi_click_handler);
  window_multi_click_subscribe(BUTTON_ID_SELECT, 2, 3, 1000, true, multi_click_handler);
  window_multi_click_subscribe(BUTTON_ID_BACK, 2, 3, 1000, true, multi_click_handler);
}