#include <pebble.h>
#include "data.h"

static int* s_array;
static task s_tasks[NUM_MAX_TASK_ITEMS];

void data_init(int array_length) {
  if(!s_array) {
    s_array = (int*)malloc(array_length * sizeof(int));
  }
  
  // make a fake set of tasks for now
  s_tasks[0].id=0;
  strncpy(s_tasks[0].name, "first task this is really long", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[1].id=1;
  strncpy(s_tasks[1].name, "second task", NUM_TASK_DESCRIPTION_LENGTH-1);
  s_tasks[2].id=2;
  strncpy(s_tasks[2].name, "third task", NUM_TASK_DESCRIPTION_LENGTH-1);
  
}

void data_deinit() {
  if(s_array) {
    free(s_array);
    s_array = NULL;
  }
}

void data_set_array_value(int index, int new_value) {
  s_array[index] = new_value;
}

int data_get_array_value(int index) {
  return s_array[index];
}

int data_get_task_count() {
  return NUM_MAX_TASK_ITEMS;
}

task data_get_task(int index) {
  return s_tasks[index];
}
