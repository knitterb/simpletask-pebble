#pragma once

#include <pebble.h>  // Pebble SDK symbols

#define NUM_MAX_TASK_ITEMS 3
#define NUM_TASK_DESCRIPTION_LENGTH 15

typedef struct task
{
  int id;
  char name[NUM_TASK_DESCRIPTION_LENGTH];
} task;

void data_init(int array_length);

void data_deinit();

void data_set_array_value(int index, int new_value);

int data_get_array_value(int index);

int data_get_task_count();
task data_get_task(int index); 

