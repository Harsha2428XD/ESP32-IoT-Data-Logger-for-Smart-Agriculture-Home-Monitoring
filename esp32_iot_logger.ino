#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Replace with your server endpoint URL (e.g., local server IP or domain)
const char* serverUrl = "http://YOUR_SERVER_IP/smart_agri/save_data.php";

// Sensor Pins & Type
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int soilMoisturePin = 34;
const int relayPin = 26;

// Configuration Thresholds
const int moistureThreshold = 40; // Percentage below which irrigation triggers

void setup() {
  Serial.begin(115200);
  
  pinMode(soilMoisturePin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Pump OFF initially

  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Read Sensors
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    int rawMoisture = analogRead(soilMoisturePin);
    
    // Convert raw ADC (0-4095) to moisture percentage (0-100%)
    int moisturePercent = map(rawMoisture, 4095, 0, 0, 100);
    moisturePercent = constrain(moisturePercent, 0, 100);

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Automated Irrigation Logic
    if (moisturePercent < moistureThreshold) {
      digitalWrite(relayPin, HIGH); // Turn Pump ON
      Serial.println("Soil dry! Irrigation pump activated.");
    } else {
      digitalWrite(relayPin, LOW); // Turn Pump OFF
      Serial.println("Soil moisture optimal. Pump off.");
    }

    // Prepare HTTP POST Request
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String httpRequestData = "temperature=" + String(temperature) + 
                             "&humidity=" + String(humidity) + 
                             "&moisture=" + String(moisturePercent);

    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Server Response: " + response);
    } else {
      Serial.println("Error sending POST: " + String(httpResponseCode));
    }
    
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  // Send data every 10 seconds
  delay(10000);
}
