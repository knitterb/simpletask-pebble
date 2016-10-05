#pragma once

#include <pebble.h>  // Pebble SDK symbols

#define NUM_MAX_TASK_ITEMS 15
#define NUM_TASK_DESCRIPTION_LENGTH 25

typedef struct task
{
  int id;
  char name[NUM_TASK_DESCRIPTION_LENGTH];
} task;


void data_init();

void data_deinit();

int data_get_task_count();

task data_get_task(int index); 

void data_request_tasks();
void data_request_bind();
void data_request_unbind();
static void inbox_received_callback(DictionaryIterator *iter, void *context);
static void inbox_dropped_callback(AppMessageResult reason, void *context);
static void outbox_sent_callback(DictionaryIterator *iter, void *context);
static void outbox_failed_callback(DictionaryIterator *iter, AppMessageResult reason, void *context);