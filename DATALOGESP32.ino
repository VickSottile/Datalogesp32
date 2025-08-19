#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// URL de Google Apps Script
String GOOGLE_SCRIPT_URL= "tu url";
const char* ssid = "Nombre de tu red";
const char* password = "contraseña";

WiFiClientSecure client;

void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  client.setInsecure();
}

void loop() 
{
if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();   // Desactiva verificación SSL (es más simple, pero menos seguro)

    HTTPClient https;
    
    int sensor1 = random(20, 30);   // simula temperatura
    int sensor2 = random(50, 100);  // simula humedad

    String url = GOOGLE_SCRIPT_URL + "?sensor1=" + String(sensor1) + "&sensor2=" + String(sensor2);
    
    Serial.println("Enviando a: " + url);

    if (https.begin(client, url)) {  // usa WiFiClientSecure
      int httpCode = https.GET();

      if (httpCode > 0) {
        Serial.printf("Código HTTP: %d\n", httpCode);
        String payload = https.getString();
        Serial.println("Respuesta: " + payload);
      } else {
        Serial.printf("Error en GET: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    } else {
      Serial.println("Fallo en conexión HTTPS");
    }
  }
  delay(60000); // cada 1 minuto
}