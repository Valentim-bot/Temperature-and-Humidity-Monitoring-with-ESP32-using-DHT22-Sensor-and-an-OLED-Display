#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h" // Include the DHT library

// DHT22 Configuration
#define DHTPIN 18    // Pin connected to the DHT sensor
#define DHTTYPE DHT22 // Specify DHT22 sensor
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT22 sensor

// OLED Display Configuration
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.println(F("DHT22 + OLED test!"));

  // Initialize the DHT sensor
  dht.begin();

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // Read humidity and temperature from DHT22 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any readings failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Display the readings on the OLED screen
  display.clearDisplay();

  // Display temperature
  display.setTextSize(1);
  display.setCursor(0, 7);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(0, 16);
  display.print(temperature);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true); // Enable extended ASCII for the degree symbol
  display.write(167);  // Degree symbol
  display.setTextSize(2);
  display.print("C");

  // Display humidity
  display.setTextSize(1);
  display.setCursor(0, 37);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(0, 50);
  display.print(humidity);
  display.print(" %");

  display.display();

  // Print values to Serial Monitor
  Serial.print(F("Temperature: "));
  Serial.print(temperature);
  Serial.print(F("°C  Humidity: "));
  Serial.print(humidity);
  Serial.println(F("%"));

  delay(2000); // Wait 2 seconds between readings
}
