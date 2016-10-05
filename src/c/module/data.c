#include <pebble.h>
#include "data.h"

static task s_tasks[NUM_MAX_TASK_ITEMS];

// Largest expected inbox and outbox message sizes
const uint32_t outbox_size = 64 ;
const uint32_t inbox_size = 64 ;

const uint32_t MESSAGE_KEY_RequestData = 0;
const uint32_t MESSAGE_KEY_ReceiveLine = 0;
const uint32_t MESSAGE_KEY_ReceiveName = 1;


static int state_recv=0;
static int state_sent=0;
static int nextval=-1;
static MenuLayer *s_menu_layer;

void data_init(MenuLayer *m) {
  s_menu_layer=m;
  nextval=0;
  
  // Need to wait for JS to be ready, probably need a better facility than this
  // https://developer.pebble.com/docs/pebblekit-js/Pebble/#addEventListener (although this is JS not C)
  //psleep(1000);

  // get tasks from phone
  data_request_bind();


  //data_request_tasks();
    
  // make a fake set of tasks for now
  s_tasks[0].id=0;
  strncpy(s_tasks[0].name, "zeroth task this is really long", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[1].id=1;
  strncpy(s_tasks[1].name, "first task", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[2].id=2;
  strncpy(s_tasks[2].name, "second task", NUM_TASK_DESCRIPTION_LENGTH-1);
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
  data_request_unbind();
}

int data_get_task_count() {
  return NUM_MAX_TASK_ITEMS;
}

task data_get_task(int index) {
  return s_tasks[index];
}

void data_request_tasks() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Requesting line: %d", nextval);
  
  if (!(state_recv==0 && state_sent==0)) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Still processing another line");
    return;
  }
            
  state_recv=1;
  state_sent=1;  

  // Declare the dictionary's iterator
  DictionaryIterator *out_iter;
  
  // Prepare the outbox buffer for this message
  AppMessageResult result = app_message_outbox_begin(&out_iter);
  if(result == APP_MSG_OK) {
    // Add an item to ask for weather data
    dict_write_int(out_iter, MESSAGE_KEY_RequestData, &nextval, sizeof(int), true);
  
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

void data_request_bind() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Binding receivers");

  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
 
  // Open AppMessage
  int res=app_message_open(inbox_size, outbox_size);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Message open result: %d", res);

}

void data_request_unbind() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Unbinding receivers");
  app_message_deregister_callbacks();
}

static void inbox_received_callback(DictionaryIterator *iter, void *context) {
  // A new message has been successfully received
  APP_LOG(APP_LOG_LEVEL_INFO, "Message received");

  state_recv=0;

  // Is this an appReady alert?
  Tuple *app_ready_tuple = dict_find(iter, MESSAGE_KEY_AppReady);
  if(app_ready_tuple) {
      APP_LOG(APP_LOG_LEVEL_INFO, "App is ready");
      data_request_tasks();
      return;
  }

  
  int32_t line=-1;
  Tuple *line_tuple = dict_find(iter, MESSAGE_KEY_ReceiveLine);
  if(line_tuple) {
    // This value was stored as JS Number, which is stored here as int32_t
    line = line_tuple->value->int32;
  }
  
  char name[NUM_TASK_DESCRIPTION_LENGTH];
  Tuple *name_tuple = dict_find(iter, MESSAGE_KEY_ReceiveName);
  if(name_tuple) {
    // This value was stored as JS String, which is stored here as char*
    char *t_name = name_tuple->value->cstring;
    strncpy(name, t_name, NUM_TASK_DESCRIPTION_LENGTH-1);
  }
  
  if (line>=0 && line<NUM_MAX_TASK_ITEMS) {
    APP_LOG(APP_LOG_LEVEL_INFO, "Message received line: %d", (int)line);
    s_tasks[line].id=line;
    strncpy(s_tasks[line].name, name, NUM_TASK_DESCRIPTION_LENGTH-1);
    nextval++;
  }
  menu_layer_reload_data(s_menu_layer);
  data_request_tasks();
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  // A message was received, but had to be dropped
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped. Reason: %d", (int)reason);
}

static void outbox_sent_callback(DictionaryIterator *iter, void *context) {
  // The message just sent has been successfully delivered
  APP_LOG(APP_LOG_LEVEL_INFO, "Message sent.");
  state_sent=0;
  data_request_tasks();
}

static void outbox_failed_callback(DictionaryIterator *iter,
                                      AppMessageResult reason, void *context) {
  // The message just sent failed to be delivered
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message send failed. Reason: %d", (int)reason);
}

