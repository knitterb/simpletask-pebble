# Simpletask Pebble
This is a Pebble watch app that integrates with the [Simpletask](https://play.google.com/store/apps/details?id=nl.mpcjanssen.todotxtholo) Android app.  Because there is a learning curve to implementing this watch, the plan is as follows.

Current Version: *Not Released!*

|Version |Description                                                              |
|--------|-------------------------------------------------------------------------|
|v0.1   d|List 15 tasks on the watch (no sort/filter)                              |
|v0.2    |List all tasks from the watch (follow sort/filter from phone view)       |
|v0.3    |Complete tasks from the watch                                            |
|v1.0    |View full task details in a card                                         |
|v2.0    |Minimal editing of existing tasks (change context/list & project/tag)    |
|v2.1    |Add new tasks (this requires speech-to-text)                             |
*d = developing*
*r = released*

list up to 15 tasks on the watch without any sort/filter (this is me learning)
list all tasks on watch following simpletask default filter/sort (what's on the main screen)
mark tasks as complete from watch
minimal editing of tasks on watch (priority, context, etc.) -- also may include a better view of tasks in a card view layout
entry of new tasks from watch

# Communications
All messages sent from the Pebble watch to the phone, and vice versa, are passed as a [Dictionary](https://developer.pebble.com/docs/c/Foundation/Dictionary/) (key-value pair).  Because there are a number of different message types that are passed between the two devices a message type has to be included to identify the action requested.

##Watch to Phone:

|Message Type       |Message Type ID (value)|
|-------------------|-----------------------|
|Request Tasks (all)|0                      |

###Request Tasks
This requests that the phone send all tasks.  There are no values that accompany this message.

|ID |Description      |
|---|-----------------|
|0  |Message Type ID  |

##Phone to Watch

|Message Type       |Message Type ID (value)|
|-------------------|-----------------------|
|Task               |0                      |

###Task
This represents a single task that is sent.  The following is the structure of the message.

|ID |Description      |
|---|-----------------|
|0  |Message Type ID  |
|1  |Task Line Number |

