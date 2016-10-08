# Simpletask Pebble
This is a Pebble watch app that integrates with the [Simpletask](https://play.google.com/store/apps/details?id=nl.mpcjanssen.todotxtholo) Android app.

# Communications
All messages sent from the Pebble watch to the phone, and vice versa, are passed as a [Dictionary](https://developer.pebble.com/docs/c/Foundation/Dictionary/) (key-value pair).  Because there are a number of different message types that are passed between the two devices a message type has to be included to identify the action requested.

