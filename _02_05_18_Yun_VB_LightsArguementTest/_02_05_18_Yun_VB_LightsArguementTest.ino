/*
  Arduino Yun Bridge example
 This example for the Arduino Yun shows how to use the
 Bridge library to access the digital and analog pins
 on the board through REST calls. It demonstrates how
 you can create your own API when using REST style
 calls through the browser.
 Possible commands created in this shetch:
 * "/arduino/digital/13"     -> digitalRead(13)
 * "/arduino/digital/13/1"   -> digitalWrite(13, HIGH)
 * "/arduino/analog/2/123"   -> analogWrite(2, 123)
 * "/arduino/analog/2"       -> analogRead(2)
 * "/arduino/mode/13/input"  -> pinMode(13, INPUT)
 * "/arduino/mode/13/output" -> pinMode(13, OUTPUT)
 This example code is part of the public domain
 http://arduino.cc/en/Tutorial/Bridge
 */

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

// Listen on default port 5555, the webserver on the Yun
// will forward there all the HTTP requests for us.
YunServer server;

void setup() {
  // Bridge startup
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  Bridge.begin();

  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  // Get clients coming from server
  YunClient client = server.accept();

  // There is a new client?
  if (client) {
    // Process request
    process(client);

    // Close connection and free resources.
    client.stop();
  }

  delay(1); // Poll every 50ms
}

void process(YunClient client) {
  // read the command
  String command = client.readStringUntil('/');

  // is "digital" command?
  if (command == "digital") {
    digitalCommand(client);
  }
  if(command == "off"){
    off();
  }
}

void digitalCommand(YunClient client) {
  int Four, Five, Six, Seven, Eight, Nine, Ten, Eleven, Twelve, Thirteen;
  
  // Read pin number
  // If the next character is a '/' it means we have an URL
  // with a value like: "/digital/13/1"
  Four = client.parseInt();
  digitalWrite(4, Four);
  Five = client.parseInt();
  digitalWrite(5, Five);
  Six = client.parseInt();
  digitalWrite(6, Six);
  Seven = client.parseInt();
  digitalWrite(7, Seven);
  Eight = client.parseInt();
  digitalWrite(8, Eight);
  Nine = client.parseInt();
  digitalWrite(9, Nine);
  Ten = client.parseInt();
  digitalWrite(10, Ten);
  Eleven = client.parseInt();
  digitalWrite(11, Eleven);
  Twelve = client.parseInt();
  digitalWrite(12, Twelve);
  Thirteen = client.parseInt();
  digitalWrite(13, Thirteen);
}
void off(){
  for(int x = 4; x < 13; x++){
    digitalWrite(x, LOW);
  }
}

