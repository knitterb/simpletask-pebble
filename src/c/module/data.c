#include <pebble.h>
#include "data.h"

static task s_tasks[NUM_MAX_TASK_ITEMS];

// Largest expected inbox and outbox message sizes
const uint32_t outbox_size = 64;
const uint32_t inbox_size = 256;

const uint32_t MESSAGE_KEY_RequestData = 0;


void data_init() {
  // get tasks from phone
  data_request_tasks();
    
  // make a fake set of tasks for now
  s_tasks[0].id=0;
  strncpy(s_tasks[0].name, "first task this is really long", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[1].id=1;
  strncpy(s_tasks[1].name, "second task", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[2].id=2;
  strncpy(s_tasks[2].name, "third task", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[3].id=3;
  strncpy(s_tasks[3].name, "third task", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[4].id=4;
  strncpy(s_tasks[4].name, "fourth task", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[5].id=5;
  strncpy(s_tasks[5].name, "fifth task", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[6].id=6;
  strncpy(s_tasks[6].name, "sixth task", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[7].id=7;
  strncpy(s_tasks[7].name, "seventh task", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[8].id=8;
  strncpy(s_tasks[8].name, "eighth task", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[9].id=9;
  strncpy(s_tasks[9].name, "nineth task", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[10].id=10;
  strncpy(s_tasks[10].name, "tenth task", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[11].id=11;
  strncpy(s_tasks[11].name, "eleventh task", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[12].id=12;
  strncpy(s_tasks[12].name, "tweleth task", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[13].id=13;
  strncpy(s_tasks[13].name, "thirteenth task", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[14].id=14;
  strncpy(s_tasks[14].name, "fourteenth task", NUM_TASK_DESCRIPTION_LENGTH-1);
}

void data_deinit() {
}

void data_request_tasks() {
  
  // Open AppMessage
  app_message_open(inbox_size, outbox_size);

  // Declare the dictionary's iterator
  DictionaryIterator *out_iter;
  
  // Prepare the outbox buffer for this message
  AppMessageResult result = app_message_outbox_begin(&out_iter);
  if(result == APP_MSG_OK) {
    // Add an item to ask for weather data
    int value = 0;
    dict_write_int(out_iter, MESSAGE_KEY_RequestData, &value, sizeof(int), true);
  
    // Send this message
    result = app_message_outbox_send();
    if(result != APP_MSG_OK) {
      APP_LOG(APP_LOG_LEVEL_ERROR, "Error sending the outbox: %d", (int)result);
    } else {
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Sent request to phone success: %d", (int)result);
    }
  } else {
    // The outbox cannot be used right now
    APP_LOG(APP_LOG_LEVEL_ERROR, "Error preparing the outbox: %d", (int)result);
  }
  
}

int data_get_task_count() {
  return NUM_MAX_TASK_ITEMS;
}

task data_get_task(int index) {
  return s_tasks[index];
}
