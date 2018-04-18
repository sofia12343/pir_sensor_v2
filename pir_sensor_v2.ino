#include <SPI.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>  
#include <PubNub.h>

//#include <Adafruit_VC0706.h>
//#include <SD.h>   

// SD chip select is set to be pin 4 on arduino. (Pin 10 is chip select for ethernet)
#define chipSelect 4

// Camera interdace: Camera TX on arduino pin2 and camera RX on arduino pin3
#define tx 5
#define rx 6

//PIR sensor gives a HIGH when there is some motion It is connected to pin 3 on Arduino board.
const int pirPin = 3; 

// User push button is connected to pin on the Arduino board.
const int buttonPin = 2;  

// Motion sensor need to be read or not flag - Based on this flag we read the motion sensor (and sometimes we don't)
// This helps us not catching every frequent movement 
boolean inMotion = false; 

//the IP address is dependent on your network - It is only used when DHCP is not working 
//(i.e. assigning IP to ethernet shield automatically
//IPAddress ip(192, 168, 137, 120);


// Current state of the user push button
boolean btnIsPressed = false;

//Internal variables required to debounce user push button
long currentBtnTime = 0;
long oldBtnTime = 0;

// Debounce time in millisecond. This means if there is a change in button state in last 200ms of last change
// just ignore that change because that would be because of button bounce
const double debounceTime = 200;

void btnPressed(){
  // This is an Interrupt Service Routine (ISR) called on button press
  // User push button debouncing. Changes button state only if an actual change by user and not button bounce
  currentBtnTime = millis(); 
  
  if(currentBtnTime - oldBtnTime > debounceTime) 
  {
    btnIsPressed = true;
  }
  
  oldBtnTime = currentBtnTime;
}

void setup() {

  // Ethernet shield mac number. Only necessary when there are multiple ethernet shields on the same 
  // network. An arbitrary mac number is used here.
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

  //PIR sensor pin is made input so that it can be read in the Arduino
  pinMode(pirPin, INPUT); // Prepare the pin as Input pin

  //Button pin is made input so that it can be read in the Arduino
  pinMode(buttonPin, INPUT_PULLUP);
  
  //Button is read as an interrupt so that it doesn't get missed in any case
  attachInterrupt(digitalPinToInterrupt(buttonPin), btnPressed, LOW);  

  Serial.begin(9600);
  Serial.println("Serial set up");

  // Starting the ethernet connection using the MAC number only
  while (!Ethernet.begin(mac)) {
    Serial.println("Ethernet setup error using DHCP");
    delay(1000);
  }

  // We try to start an ethernet connectio using DHCP server first (above lines of code)
  //If that doesn't work, we then try to give a manual IP to start connection
//  if(!Ethernet.begin(mac))
//  {
//      Serial.println("Ethernet setup error using DHCP");
//
//    // initialize the ethernet device
//    Ethernet.begin(mac); //ip
//
//    //print out the IP address
//    Serial.print("IP = ");
//    Serial.println(Ethernet.localIP());
//  }

  // This functions 
//  printIPAddress();

  Serial.println("Ethernet set up");

  //PubNub channel info and publish and suscribe keys
  char pubkey[] = "pub-c-9f65251b-0280-4504-8bc4-ccf128ca47ca";
  //Your keys here
  char subkey[] = "sub-c-231999f6-40f4-11e8-8ce7-1294c71dad07";
  //channel
  char channel[] = "iotchannel";

  // Conencting with the associated pubnub account using the above given publish and suscribe keys
  PubNub.begin(pubkey, subkey);
  
  Serial.println("PubNub set up");
  
}

void loop() {
  
  // Read the PIR motion pin 
  PIR_read();

  // Based on the current button state (updated in ISR which is called when button is pressed), 
  // we take appropriate action such as sending notification to pubnub etc
  if(btnIsPressed){
    // Making the button state to false, so that it can be set again on next button press
    btnIsPressed = false;
    Serial.println("Button Pressed!");

    //Sending notification messgae to pubnub
    pubnub_execute("\"Someone_has_rang_the_door_bell\"");
  }
  
}
