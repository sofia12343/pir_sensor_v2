unsigned long motionDelay = 10000; // Motion Delay Timer
unsigned long motionTimer; // Motion Trigger Timer

void PIR_read() {

// First off check the PIR pin, if it HIGH then we need to read the sensor if there is 10sec delay
// between the last motion reading and the current time
if (digitalRead(pirPin) == HIGH && !inMotion)
  {
    Serial.println("Motion Detected");

    // Send notification to pubnub
     pubnub_execute( "\"Someone_is_outside_the_door\"");
     
//     takePhoto(); // Takes photo and sends to pubnub
//     SnapAndSave(); // takes photo and save it to SD card
    
    motionTimer = millis();
    inMotion = true;
  }
  else if (millis() - motionTimer >= motionDelay) {
    // If there is no motion for motionDelay seconds (10sec for now), 
    //then get ready for reading the pin for any new motion
    inMotion = false;
  }
}
