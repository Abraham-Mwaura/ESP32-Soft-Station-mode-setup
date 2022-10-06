//for wifi connectivity
#include <WiFi.h>
//to help create a webserver

//To be able to use it, make sure you select the right board
#include <WebServer.h>

const char* ssid= "";
const char* password ="";

//windows>cmd>ipconfig


IPAddress local_ip(192,168,163,230);
IPAddress gateway (192,168,163,13);
IPAddress subnet(255,255,255,0);

//create the webserver object and declare the port
WebServer server(80);

uint8_t LEDPin1 =2;
//initial state
bool LED1status =LOW;
uint8_t LEDPin2 =5;
bool LED2status =LOW;


void setup() {
Serial.begin(115200);
pinMode(LEDPin1, OUTPUT);
pinMode(LEDPin2, OUTPUT);


WiFi.softAP(ssid, password);
WiFi.softAPConfig(local_ip,gateway,subnet);
//to stabilize everything
delay(100);

//opens the specified function when the specified url is hit
//192.168.163.230/led1on  
server.on("/", handle_OnConnect);
server.on("/led1on", handle_led1on);
server.on("/led1off", handle_led1off);
server.on("/led2on", handle_led2on);
server.on("/led2off", handle_led2off);
server.onNotFound(handle_NotFound);

//to start the server
server.begin();
Serial.println("https server has started");
}

void loop() {
  
  server.handleClient();
  
  if(LED1status) {
  digitalWrite(LEDPin1,HIGH);
  }
  else{
  digitalWrite(LEDPin1,LOW);
  }

  if(LED2status) {
  digitalWrite(LEDPin2,HIGH);
  }
  else{
  digitalWrite(LEDPin2,LOW);
  }
}


void handle_OnConnect(){
  //turns off the two LEDs
LED1status =  LOW;
LED2status = LOW;

Serial.println("GPIO 2: off and GPIO5: off");
//google on https codes and their meaning

server.send(200, "text/html", SendHTML(LED1status, LED2status));
}

void handle_led1on(){
LED1status =  HIGH;
Serial.println("GPIO 2: on");
server.send(200, "text/html", SendHTML(LED1status,true ));
}

void handle_led1off(){
LED1status = LOW;
Serial.println("GPIO 1: OFF");
server.send(200, "text/html", SendHTML(LED1status, false ));
}

void handle_led2on(){
LED2status =  HIGH;
Serial.println("GPIO 5: on");
server.send(200, "text/html", SendHTML(LED2status, true ));
}

void handle_led2off(){
LED2status = LOW;
Serial.println("GPIO 5: OFF");
server.send(200, "text/html", SendHTML(LED2status, false ));
}

void handle_NotFound(){

Serial.println("Not FOUND");
server.send(404, "text/html", "Not Found" );
}


String SendHTML (uint8_t led1stat, uint8_t led2stat)
{
  String ptr ="<!DOCTYPE html> <html>\n";
  ptr + = "<head><meta name=\ "viewport\" content=\"width=device-width, initial-scale=1.0 user-scalable=no\">\n"; 
}
