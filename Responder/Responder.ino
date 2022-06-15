#include <esp_now.h>
#include <WiFi.h>
#include <FastLED.h>

#define DATA_PIN 23
#define NUM_LEDS 16
 
// Create a structured object
int myData = 0;

CRGB leds[NUM_LEDS];
 
void setup() {
  Serial.begin(115200);

  partner();

  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);

  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);

  FastLED.clear();
  FastLED.show();
}

// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  
  Serial.println(myData);
  
  for(int i = 0; i <= NUM_LEDS; i++){
    leds[i] = CHSV(myData, 255, 255);
  }
  FastLED.show();
}
 
void loop() {
}

void partner(){
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
}
