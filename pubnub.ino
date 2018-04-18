void pubnub_execute(char myMsg[]){

  char channel[] = "pir"; //pir
  
  // In the the DHCP server changes IP, changes are updated
  Ethernet.maintain();
  
  EthernetClient *client;
  
  Serial.println("publishing a message");
  client = PubNub.publish(channel,myMsg);

  // If could not connect publish the message to pubnub, show error message
  if (!client) {
    Serial.println("publishing error");
    delay(10); 
    return;
  }
  while (client->connected()) {
    
    // wait for the client (pubub) to send acknowledge of our publication
    while (client->connected() && !client->available()) ; 

    //When client is connected and available, read the Acknowledgement
    char c = client->read();
    Serial.print(c);
  }
  // Stop the client, as publishing and receiving acknowledgement is done
  client->stop();
  
  Serial.println();
  
  Serial.println("waiting for a message (subscribe)");
  PubSubClient *pclient = PubNub.subscribe(channel);
  if (!pclient) {
    Serial.println("subscription error");
    delay(10); 
    return;
  }
  // Wait for pubnub to send any subscription notifications 
  while (pclient->wait_for_data()) {
    char c = pclient->read();
    Serial.print(c);
  }
  pclient->stop();
  
  Serial.println();
  
}

void printIPAddress(){
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();
}
