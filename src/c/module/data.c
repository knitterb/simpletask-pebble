#include <pebble.h>
#include "data.h"

static task s_tasks[NUM_MAX_TASK_ITEMS];

void data_init(int array_length) {
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

int data_get_task_count() {
  return NUM_MAX_TASK_ITEMS;
}

task data_get_task(int index) {
  return s_tasks[index];
}
