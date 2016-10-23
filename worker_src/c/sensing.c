#include <pebble_worker.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "worker.h"
#include "connectivity.h"
#include "logging.h"
#include "sensing.h"
#include "battery.h"
#include "bgmessage.h"


static uint8_t TOTAL_SAMPLE_LOG = 25; // since using ACCEL_SAMPLING_50HZ

static uint8_t accel_samples_per_update;
static uint8_t k;
static uint64_t packet_start_time;
  
uint32_t data_pointer[52]; // size = (TOTAL_SAMPLE_LOG + 1) * 2;

void print_screen(void){    
  
  int16_t x = 0;
  int16_t y = 0;
  int16_t z = 0;
  char s_buffer[64];
  
  z = data_pointer[2];
  y = data_pointer[2]>>16;
  x = data_pointer[3];

  snprintf (s_buffer, 64, "%d\n%d\n%d\n",x,y,z);
  //text_layer_set_text(acc_text_layer, "Sampling!");
  APP_LOG(APP_LOG_LEVEL_INFO, "%s", s_buffer);
  
}

// accelerometer data logging handler
void accel_data_handler(AccelData * data, uint32_t num_samples) {
  
  uint64_t packet_current_time;
  uint64_t packet_time;
  
  for (uint32_t i = 0; i < num_samples; i++) {    
    if (!(data[i].did_vibrate)){
      if (k==0){
        packet_start_time = data[i].timestamp;
        data_pointer[0] = data[i].timestamp >> 0;
        data_pointer[1] = data[i].timestamp >> 32;        
        ////APP_LOG(APP_LOG_LEVEL_INFO, "data[%u] = %lu, data[%u] = %lu", k*2+0, data_pointer[k*2+0], k*2+1, data_pointer[k*2+1]);    
        k++;
      }      
      
      packet_current_time = data[i].timestamp;
      packet_time = packet_current_time - packet_start_time;
      data_pointer[k*2+0] = data[i].y;
      data_pointer[k*2+0] = data_pointer[k*2+0]<<16;
      data_pointer[k*2+0] = data_pointer[k*2+0] | (data[i].z & 0x0000ffff);
      data_pointer[k*2+1] = packet_time;
      data_pointer[k*2+1] = data_pointer[k*2+1]<<16;
      data_pointer[k*2+1] = data_pointer[k*2+1] | (data[i].x & 0x0000ffff);
      ////APP_LOG(APP_LOG_LEVEL_INFO, "data[%u] = %lu, data[%u] = %lu",k*2+0, data_pointer[k*2+0],k*2+1, data_pointer[k*2+1]);
      k++;

      if (k==TOTAL_SAMPLE_LOG + 1){
        ////APP_LOG(APP_LOG_LEVEL_INFO, "k = %u, data size = %u", k, sizeof(data_pointer));        
        if (battery_flag){
          log_data(k*2);
          print_screen();
        }
        k = 0;
      }
    }
  }

}



void sensing_subscribe(void){
  accel_samples_per_update = 5;
  // Register acceleration event handler with a 5 sample buffer
  accel_data_service_subscribe(accel_samples_per_update, accel_data_handler);
  // Adjust sampling rate
  accel_service_set_sampling_rate(ACCEL_SAMPLING_50HZ);  
}


void sensing_unsubscribe(void){
  accel_data_service_unsubscribe();
  //APP_LOG(APP_LOG_LEVEL_ERROR,"Sensor Unsubscribe, Clear Data!");
  k = 0;
}

