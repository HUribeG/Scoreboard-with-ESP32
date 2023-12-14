#include <LEDMatrixDriver.hpp>
#include <ESP32Time.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>


//Tablero Basquet Gimnasio universitario 
//
//

//RED2.4Infinitum
//18FloYRose08

//INFINITUM1558_2.4
//2d3vxLW9ts

//const char* ssid = "INFINITUM1558_2.4";
//const char* password = "2d3vxLW9ts";

const char* ssid = "RED2.4Infinitum";
const char* password = "18FloYRose08";


const char *ssid_AP = "red no segura";
const char *password_AP = "Contraseña_Segura32";

WebServer server(80);


const int led = 4; //2 led_builtin
const int Chicharra = 2;


// Other pins are Arduino specific SPI pins (MOSI=DIN, SCK=CLK of the LEDMatrix) see https://www.arduino.cc/en/Reference/SPI
const uint8_t LEDMATRIXA_CS_PIN = 15;
const uint8_t LEDMATRIXB_CS_PIN = 22;

// Number of 8x8 segments you are connecting
const int LEDMATRIX_SEGMENTS = 1;
const int LEDMATRIX_WIDTH    = LEDMATRIX_SEGMENTS * 8;

DynamicJsonDocument doc(2048);

bool strComplete =0;
String inputStr="";

int MarVis=0;
int MarLoc=0;
bool stateT=0;
bool TimeStop=0;
int TimeAct=0;
///CS == LOAD
  
LEDMatrixDriver lmd1(LEDMATRIX_SEGMENTS, LEDMATRIXA_CS_PIN); //Marcador y periodo
LEDMatrixDriver lmd2(LEDMATRIX_SEGMENTS, LEDMATRIXB_CS_PIN); //Crono y fault




int Loc; 
int Vis; 
int TimeSet;
bool Stop;
bool TimeSetState;
bool Bonus;
bool Pos;
int FaultL;
int FaultV;
int Periodo;
bool Chicha;
bool Tablero;
int Activate=0;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //pinMode(21, INPUT_PULLDOWN);

  pinMode(led, OUTPUT);
  pinMode(Chicharra, OUTPUT);
  digitalWrite(led, 1);
//  WiFi.mode(WIFI_STA);
//  WiFi.begin(ssid, password);
//  Serial.println("");
//
//  // Wait for connection
//  while (WiFi.status() != WL_CONNECTED) {
//    digitalWrite(led,LOW);
//    delay(500);
//    Serial.print(".");
//  }

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid_AP, password_AP);
  //WiFi.softAPConfig(ip, gateway, subnet);
  
  
  Serial.println("");
  
  WiFi.printDiag(Serial);
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  //Serial.println(WiFi.localIP());
  Serial.println(WiFi.softAPIP()); 
//
//  if (MDNS.begin("esp32")) {
//    Serial.println("MDNS responder started");
//  }

  server.on("/", handleRoot);
  server.on("/app", HTTP_POST, handlePost);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  
  lmd1.setEnabled(true);
  lmd1.setIntensity(15);   // 0 = low, 10 = high
  lmd1.setDecode(0xFF);
  
  lmd2.setEnabled(true);
  lmd2.setIntensity(15);   // 0 = low, 10 = high
  lmd2.setDecode(0xFF);
  
  lmd1.clear();
  lmd2.clear();
//  MarcadorLoc(0);
//  MarcadorVis(0);
}
int btn =0;
bool inicio=1;


long Time1=0;
long Time2=0;
long anterior=0;
long actual=0;
int MinutosIniciales=0;
int minu=0;
int secs=0;

void loop() {
  // put your main code here, to run repeatedly:
  
  server.handleClient();
  delay(5);//allow the cpu to switch to other tasks

  UpdateTime();
  
}
