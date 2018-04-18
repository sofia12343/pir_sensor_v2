//void takePhoto() {
//  
//  #if ARDUINO >= 100
//  //camera TX connected to pin 2, camera RX to pin 3:
//  SoftwareSerial cameraconnection = SoftwareSerial(tx, rx);
//  #else
//  NewSoftSerial cameraconnection = NewSoftSerial(tx, rx);
//  #endif
//  
//  Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);
//  
//  // Initialize the camera module
//  if (cam.begin()) 
//  {
//    Serial.println("Camera Found:");
//  }
//  else 
//  {
//    Serial.println("No camera found?");
//    return;
//  }
//
//  // Set the picture size that we want to acquire form the camera
//  cam.setImageSize(VC0706_320x240);        
//
//// Get image size form the camera. It would be the same as we set in the above line of code
//  uint8_t imgsize = cam.getImageSize();
//  
//  Serial.print("Image size: ");
//  if (imgsize == VC0706_320x240) Serial.println("320x240");
//
//  Serial.println("Taking a snap now");
//
//  // Take snap after 1000ms (1second)
//  delay(1000);
//
//  // Taking the picture and determining the success of the operation
//  if (! cam.takePicture()) 
//    Serial.println("Failed to snap!");
//  else 
//    Serial.println("Picture taken!");
//
//
//  // Get the size of the image (frame) taken  
//  uint16_t jpglen = cam.frameLength();
//  uint16_t ImageSize = jpglen; // to be used in base64 encoder
//  Serial.print("Storing ");
//  Serial.print(jpglen, DEC);
//  Serial.print(" byte image.");
//
//  pinMode(8, OUTPUT);
//  
//// For counting # of writes
//  byte wCount = 0; 
//  char imageData[ImageSize+1];
//  int pixel = 0;
//  
//  while (jpglen > 0) {
//    
//    // read 32 bytes at a time fromt he camera into arduino memory;
//    uint8_t *buffer;
//    uint8_t bytesToRead = min(32, jpglen); 
//    buffer = cam.readPicture(bytesToRead);
//
//    for(uint8_t j=0; j < bytesToRead; j++)
//    {
//      // Reading each pixel value and storing the value (for example 255 as a char in the imageData array)
//      imageData[pixel] = *(buffer+j);
//      pixel++;
//    }
//
//    Serial.println("");
//    
//    // "........................."
//    //Progress bar showing the bytes reading process fromt he camera.
//    if(++wCount >= 64) { 
//      Serial.print('.');
//      wCount = 0;
//    }
//    jpglen -= bytesToRead;
//  }
//       
//  // Sending image data to pubnub. Image size is more than 2Kb do it doesn't work for UNO board
////  pubnub_execute(imageData);
//  
//  Serial.println("done!");
//}

