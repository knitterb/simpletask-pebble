#pragma once

#include <pebble.h>  // Pebble SDK symbols

#define NUM_MAX_TASK_ITEMS 15
#define NUM_TASK_DESCRIPTION_LENGTH 25

typedef struct task
{
  int id;
  char name[NUM_TASK_DESCRIPTION_LENGTH];
} task;

void data_init(int array_length);

void data_deinit();

int data_get_task_count();

task data_get_task(int index); 

