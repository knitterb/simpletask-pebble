Pebble.addEventListener("ready", function() {
  
  console.log("My app has started - Doing stuff...");
  
  var dict = {
    'AppReady': 1
  }
  Pebble.sendAppMessage(dict, function() {
    console.log("notified app");
  }, function(e) {
    console.log("couldn't notifiy app: "+JSON.stringify(e));
  });
  
  
});
 