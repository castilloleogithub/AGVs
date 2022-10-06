#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include <esp_littlefs.h>
#include "FS.h"

#include <Arduino_JSON.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Replace with your network credentials
const char* ssid = "Fran_wifi";
const char* password = "00414716154";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "direction";
const char* PARAM_INPUT_2 = "steps";

//Variables to save values from HTML form
String direction;
String steps;

bool newRequest = false;

// Initialize SPIFFS
void initSPIFFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  else {
  Serial.println("SPIFFS mounted successfully");
  }
}

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}


void setup() 
{
  
  // Serial port for debugging purposes

  Serial.begin(115200);
  initWiFi();
  initSPIFFS();


  lcd.init();                      // initialize the lcd 
  lcd.backlight();
 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                                                              {
                                                                request->send(SPIFFS, "/index.html", "text/html");
                                                              });
  
  server.serveStatic("/", SPIFFS, "/");

  server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
                                                                  int params = request->params();
                                                                  for(int i=0;i<params;i++){
                                                                    AsyncWebParameter* p = request->getParam(i);
                                                                    if(p->isPost()){
                                                                      // HTTP POST input1 value
                                                                      if (p->name() == PARAM_INPUT_1) {
                                                                        direction = p->value().c_str();// acá es lo del opcion 1 o 2
                                                                        
                                                                      }
                                                                      // HTTP POST input2 value
                                                                      if (p->name() == PARAM_INPUT_2) {
                                                                        steps = p->value().c_str();//Acá pongo lo de valor por pantalla
                                                                        Serial.print("Number of steps set to: ");
                                                                        Serial.println(steps);
                                                                        lcd.setCursor(0,1);
                                                                        lcd.print(steps);
                                                                        // Write file to save value
                                                                      }
                                                                      newRequest = true;
                                                                      //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
                                                                    }
                                                                  }
                                                                  request->send(SPIFFS, "/index.html", "text/html");
                                                                });

  server.begin();
}

void loop() 
{
  if (newRequest)
  {
    lcd.home();
    if(direction == "CW")lcd.print("Opcion 1");
    else                 lcd.print("Opcion 2");
    Serial.print("Direction set to: ");
    Serial.println(direction);
    newRequest = false;
  }
}


/*
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
  lcd.setCursor(2,1);
  lcd.print("Ywrobot Arduino!");
   lcd.setCursor(0,2);
  lcd.print("Arduino LCM IIC 2004");
   lcd.setCursor(2,3);
  lcd.print("Power By Ec-yuan!");
}


void loop()
{
}*/
