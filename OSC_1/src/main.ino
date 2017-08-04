#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>


const char * networkName = "A303";
const char * networkPswd = "Ijnition420";

//IP address to send UDP data to:
const char * udpAddress = "192.168.1.255";
const int udpPort = 3333;

//Are we currently connected?
boolean connected = false;

int ledPin = 5;

//The udp library class
WiFiUDP udp;


void setup(void){

  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  //Connect to the WiFi network
  connectToWiFi(networkName, networkPswd);

  //set in sta mode
  WiFi.mode(WIFI_STA);
  delay(100);

  //register event handler
  WiFi.onEvent(WiFiEvent);
  delay(100);
}

void loop(void){

  if(connected){
    int value = random(250);

    digitalWrite(ledPin, !digitalRead(ledPin));

    OSCMessage msg("/bno");
    msg.add((int) millis());
    msg.add((int) value);

    udp.beginPacket(udpAddress,udpPort);
    msg.send(udp);
    udp.endPacket();

  }else{
    for(int i = 0 ; i<5;i++){
      delay(2000);
      digitalWrite(ledPin, !digitalRead(ledPin));
    }
    if(!connected){
      connectToWiFi(networkName, networkPswd);
    }
  }
  //100 Hz
  delay(10);
}

void connectToWiFi(const char * ssid, const char * pwd){
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  delay(500);

  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}

//wifi event handler
void WiFiEvent(WiFiEvent_t event){
    switch(event) {
      case SYSTEM_EVENT_STA_GOT_IP:
          //When connected set
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());
          //initializes the UDP state
          //This initializes the transfer buffer
          udp.begin(WiFi.localIP(),udpPort);
          digitalWrite(ledPin, HIGH);
          connected = true;
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          digitalWrite(ledPin, LOW);
          break;
    }
}
