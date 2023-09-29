#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

WiFiClientSecure ESP32Client;
PubSubClient client(ESP32Client);

int var = 0;
char datos[40];
String resultS = "";
String Topic = "";

const int pin_S1 = 34;
int valor_S1 = 0;

const int CLK = 18;
const int DIN = 23;
const int D_C = 04;
const int CE  = 15;
const int RST = 02;
Adafruit_PCD8544 display = Adafruit_PCD8544(CLK,DIN,D_C,CE,RST);

void setup()
{
  Serial.begin(115200);
  delay(10);
  connectAWS();
  
  display.begin();
  display.setContrast(50);
  display.clearDisplay();

  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.setCursor(0,15);
  display.println("              ");
  display.setCursor(0,23);
  display.println("              ");
  display.setCursor(12,19);
  display.println("BIENVENIDO");
  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();
  delay(200);
}

void loop()
{
  valor_S1 = leer_sensor(pin_S1);

  Serial.print("Potenciometro: ");
  Serial.println(valor_S1);
  
  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(10,3);
  display.print("MENSAJE DE");
  display.setCursor(22,12);
  display.print("ENTRADA");
  display.drawFastHLine(0,21,84,BLACK);
  display.display();

  display.setCursor(1,23);
  display.print("VALOR SENSOR:");
  display.setCursor(30,34);
  display.setTextSize(2);
  display.print(resultS);
  display.display();
  
  sprintf(datos, "%d ", valor_S1);

  publishMessage();
  client.loop();
  delay(1000);
}


int leer_sensor(int pin){
  int lectura = analogRead(pin);
  int valor = map(lectura, 0, 4095, 0, 100);
  delay(200);
  return valor;
}

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println("Connecting to Wi-Fi");
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
 
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  ESP32Client.setCACert(AWS_CERT_CA);
  ESP32Client.setCertificate(AWS_CERT_CRT);
  ESP32Client.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(callback);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
  Serial.println("AWS IoT Connected!");
}

void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["numeric"] = valor_S1;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
 
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Mensaje recibido [");
  Serial.print(topic);
  Serial.print("] ");
  char payload_string[length + 1];
  int resultI;
  memcpy(payload_string, payload, length);
  payload_string[length] = '\0';
  resultI = atoi(payload_string);
  var = resultI;
  resultS = "";
  for (int i=0;i<length;i++){
    resultS = resultS + (char)payload[i];
  }
  Serial.println();
}
