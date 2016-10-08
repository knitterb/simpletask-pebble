# Simpletask Pebble
This is a Pebble watch app that integrates with the [Simpletask](https://play.google.com/store/apps/details?id=nl.mpcjanssen.todotxtholo) Android app.

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

