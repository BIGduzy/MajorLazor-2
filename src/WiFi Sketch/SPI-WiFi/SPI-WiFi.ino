#include <hspi_slave.h>
#include <SPISlave.h>

#include <SPI.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

const char* ssid        = "";
const char* password    = "";

const char* host        = "";
const int httpPort = 1337;

int       valueId       = 1;
const int defaultId     = 1;
const int defaultLives  = 40;

int ackPin  = 3;
int conPin  = 1;
int bitPin0 = 2; // 1
int bitPin1 = 0; // 2
int bitPin2 = 4; // 3
int bitPin3 = 5; // 4
int bitPin4 = 15;// 5
int bitPin5 = 13;// 6
int bitPin6 = 12;// 7
int bitPin7 = 14;// 8

int commandId = 0;
int playerId  = 0;
int playerData = 0;

DynamicJsonBuffer jsonBuffer;

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  //registerPlayer(valueId, defaultLives);
  //registerPlayer(valueId + 1, defaultLives);
  //registerPlayer(valueId + 2, defaultLives);

  pinMode(bitPin0, INPUT);
  pinMode(bitPin1, INPUT);
  pinMode(bitPin2, INPUT);
  pinMode(bitPin3, INPUT);
  pinMode(bitPin4, INPUT);
  pinMode(bitPin5, INPUT);
  pinMode(bitPin6, INPUT);
  pinMode(bitPin7, INPUT);
  
  pinMode(ackPin, INPUT);
  //pinMode(conPin, OUTPUT);
}

void loop() {
  delay(1000);

  while(digitalRead(ackPin) != HIGH){delay(1);};

  commandId = readDataPins();

  Serial.println("---------");
  Serial.println(commandId);
  
  while(digitalRead(ackPin) != HIGH){delay(1);};

  playerId = readDataPins();

  Serial.println("---------");
  Serial.println(playerId);
  
  while(digitalRead(ackPin) != HIGH){delay(1);};

  playerData = readDataPins();

  Serial.println("---------");
  Serial.println(playerData);

  if (commandId == 0) {
    registerPlayer(playerId, playerData);
  } else {
    sendHitData(playerId, playerData);
  }

  commandId = 0;
  playerId = 0;
  playerData = 0;
  
  //sendHitData(2, 1);
  //registerPlayer(valueId, defaultLives);
}

int sendHitData(int playerId, int damage) {
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return 1;
  }

  JsonObject& jsonMessage = jsonBuffer.createObject();

  JsonArray& messageId = jsonMessage.createNestedArray("ID");
  messageId.add(1);

  JsonArray& data = jsonMessage.createNestedArray("data");
  data.add(playerId);
  data.add(damage);

  char jsonRequest[200];
  jsonMessage.printTo(jsonRequest, sizeof(jsonRequest));
  client.println(jsonRequest);

   while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  return 0;
}

int registerPlayer(int playerId, int lives) {
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return 1;
  }

  JsonObject& jsonMessage = jsonBuffer.createObject();

  JsonArray& messageId = jsonMessage.createNestedArray("ID");
  messageId.add(0);
  
  JsonArray& data = jsonMessage.createNestedArray("data");
  data.add(playerId);
  data.add(lives);

  char jsonRequest[200];
  jsonMessage.printTo(jsonRequest, sizeof(jsonRequest));
  client.println(jsonRequest);

   while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  return 0;
}

uint8_t readDataPins() {
  uint8_t temp = 0;
  temp |= (((digitalRead(bitPin0) == HIGH) ? 1 : 0) << 7);
  temp |= (((digitalRead(bitPin1) == HIGH) ? 1 : 0) << 6);
  temp |= (((digitalRead(bitPin2) == HIGH) ? 1 : 0) << 5);
  temp |= (((digitalRead(bitPin3) == HIGH) ? 1 : 0) << 4);
  temp |= (((digitalRead(bitPin4) == HIGH) ? 1 : 0) << 3);
  temp |= (((digitalRead(bitPin5) == HIGH) ? 1 : 0) << 2);
  temp |= (((digitalRead(bitPin6) == HIGH) ? 1 : 0) << 1);
  temp |= (((digitalRead(bitPin7) == HIGH) ? 1 : 0) << 0);
  //digitalWrite(conPin, HIGH);
  //delay(100);
  //digitalWrite(conPin, LOW);
  return temp;
}



