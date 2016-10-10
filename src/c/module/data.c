#include <pebble.h>
#include "data.h"

#define MessageTypeRequestAllTasks 0

#define MessageTypeResponseTask 0
#define MessageTypeResponseTaskLine 1
#define MessageTypeResponseTaskHash 2
#define MessageTypeResponseTaskName 3

static task s_tasks[NUM_MAX_TASK_ITEMS];

// Largest expected inbox and outbox message sizes
const uint32_t outbox_size = 256 ;
const uint32_t inbox_size = 512 ;


static MenuLayer *s_menu_layer;

void data_init(MenuLayer *m) {
  s_menu_layer=m;
  
  // get tasks from phone
  data_request_bind();


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
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Requesting tasks");
  
  // Declare the dictionary's iterator
  DictionaryIterator *out_iter;
  
  // Prepare the outbox buffer for this message
  AppMessageResult result = app_message_outbox_begin(&out_iter);
  if(result == APP_MSG_OK) {
    // Add an item to ask for weather data
    int msgType=MessageTypeRequestAllTasks;
    dict_write_int(out_iter, 0,  &msgType, sizeof(int), true);
  
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

  // Is this an appReady alert?
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Looking for MESSAGE_KEY_AppReady=%d", (int)MESSAGE_KEY_AppReady);
  Tuple *app_ready_tuple = dict_find(iter, MESSAGE_KEY_AppReady);
  if(app_ready_tuple) {
      APP_LOG(APP_LOG_LEVEL_INFO, "App is ready");
      data_request_tasks();
      return;
  }


  Tuple *messageResponseTuple = dict_find(iter, 0);
  if (!messageResponseTuple) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Could not find a response control at position 0");
    return;
  }

  int messageResponseType=messageResponseTuple->value->int32;
  switch (messageResponseType) {
    case MessageTypeResponseTask: // task
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Found a task repsonse (MessageTypeResponseTask)");
        Tuple *task_line=dict_find(iter, MessageTypeResponseTaskLine);
        if (!task_line) {
          APP_LOG(APP_LOG_LEVEL_ERROR,"Cannot find task line (MessageTypeResponseTaskLine)");
          return;
        }
        Tuple *task_hash=dict_find(iter, MessageTypeResponseTaskHash);
        if (!task_hash) {
          APP_LOG(APP_LOG_LEVEL_ERROR,"Cannot find task hash (MessageTypeResponseTaskHash)");
          return;
        }
        Tuple *task_name=dict_find(iter, MessageTypeResponseTaskName);
        if (!task_name) {
          APP_LOG(APP_LOG_LEVEL_ERROR,"Cannot find task name (MessageTypeResponseTaskName)");
          return;
        }

        int32_t line=task_line->value->int32;
        s_tasks[line].id=line;
        strcpy(s_tasks[line].hash, task_hash->value->cstring);
        strncpy(s_tasks[line].name, task_name->value->cstring, NUM_TASK_DESCRIPTION_LENGTH-1);
        
        break;
    default: // unknown
        APP_LOG(APP_LOG_LEVEL_ERROR, "Unknown response control type: %d", (int)messageResponseTuple->value->int32);
  }

  menu_layer_reload_data(s_menu_layer);
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  // A message was received, but had to be dropped
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped. Reason: %d", (int)reason);
}

static void outbox_sent_callback(DictionaryIterator *iter, void *context) {
  // The message just sent has been successfully delivered
  APP_LOG(APP_LOG_LEVEL_INFO, "Message sent.");
}

static void outbox_failed_callback(DictionaryIterator *iter,
                                      AppMessageResult reason, void *context) {
  // The message just sent failed to be delivered
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message send failed. Reason: %d", (int)reason);
}

