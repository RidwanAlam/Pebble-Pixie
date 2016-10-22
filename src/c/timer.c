#include <pebble.h>
#include "display.h"
#include "clicks.h"
#include "timer.h"
#include "fgbattery.h"
#include "fgmessage.h"
#include "bgworker.h"
#include <time.h>


void delay_time(void){
  uint16_t t = (2 ^ 16) - 1;
  while(t>0){t--;}
}


void tick_handler(struct tm *tick_time, TimeUnits units_changed) {  
  time_t temp = time(NULL); 
  struct tm *temp_time = localtime(&temp);
  
  static char s_buffer_1[32];
  strftime(s_buffer_1, sizeof(s_buffer_1), "%I:%M", temp_time); //clock_is_24h_style()?"%H:%M":"%I:%M %p"
  text_layer_set_text(s_time_layer,s_buffer_1+((s_buffer_1[0]=='0')?1:0));
  
  static char s_buffer_2[32];
  strftime(s_buffer_2, sizeof(s_buffer_2), "%B %d\n%A", temp_time); 
  text_layer_set_text(s_date_layer, s_buffer_2);
  
}

void timer_subscribe(){
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

void timer_unsubscribe(){
  tick_timer_service_unsubscribe();
}
