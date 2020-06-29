// LED will blink when in config mode

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <FastLED.h>

//for LED status
#include <Ticker.h>
Ticker ticker;

#ifndef LED_BUILTIN
#define LED_BUILTIN 13 // ESP32 DOES NOT DEFINE LED_BUILTIN
#endif

int LED = LED_BUILTIN;


//FastLed Setup

#define REDPIN   D3
#define GREENPIN D2
#define BLUEPIN  D1



// Time period of fading in millisecs
#define PERIOD 2000
// Angular Frequency by definition
#define OMEGA 2*PI/PERIOD
// No Phase
#define PHASE 0
// Offset of the sine wave
#define OFFSET 128.0
// Amplitude of the sine wave
#define AMPLITUDE 127.0

// Used to generate time for the cos wave
unsigned long timer = 0;

void showAnalogRGB( const CRGB& rgb)
{
  analogWrite(REDPIN,   rgb.r );
  analogWrite(GREENPIN, rgb.g ); //rgb.g
  analogWrite(BLUEPIN,  0 );
}



void tick()
{
  //toggle state
  //digitalWrite(LED, !digitalRead(LED));     // set pin to the opposite state


  float ledValue = OFFSET + AMPLITUDE * (cos((OMEGA * millis()) + PHASE));

  showAnalogRGB(CHSV( ledValue, 255, 255));

  Serial.println(ledValue);

}

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  //entered config mode, make led toggle faster
  ticker.attach(0.03, tick);
}

void setup() {

  pinMode(REDPIN,   OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN,  OUTPUT);

  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  // put your setup code here, to run once:
  Serial.begin(115200);

  // start ticker with 0.5 because we start in AP mode and try to connect
  //ticker.attach(0.6, tick);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;
  //reset settings - for testing
  // wm.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wm.setAPCallback(configModeCallback);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wm.autoConnect()) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(1000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  //ticker.detach();
}

void loop() {
  // put your main code here, to run repeatedly:

}
