// LED will blink when in config mode

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <FastLED.h>

//for LED status
#include <Ticker.h>
Ticker ticker;


//FastLed Setup

#define REDPIN   D3
#define GREENPIN D2
#define BLUEPIN  D1

#define SERIAL_BAUD 115200

// Time period of fading in millisecs
#define PERIOD 13000
// Angular Frequency by definition
#define OMEGA 2*PI/PERIOD
// No Phase
#define PHASE 0
// Offset of the sine wave
#define OFFSET 127
// Amplitude of the sine wave
#define AMPLITUDE 150

int update_led_timer = 25;


void showAnalogR( const CRGB& rgb)
{
  analogWrite(REDPIN,   rgb.r );
  analogWrite(GREENPIN, 0 );
  analogWrite(BLUEPIN,  0 );
}

void callback_Red_led()
{

  float ledValue = millis()/1000.0;
  int value = 128.0 + 128 * sin( ledValue * 2.0 * PI  );
  showAnalogR(CHSV( 0, 255, checkValue(value)));
}

void showAnalogG( const CRGB& rgb)
{
  analogWrite(REDPIN,  0  );
  analogWrite(GREENPIN, rgb.g );
  analogWrite(BLUEPIN,  0 );
}
void callback_Green_led()
{
  float ledValue = OFFSET + AMPLITUDE * (cos((OMEGA * millis()) + PHASE));

  showAnalogG(CHSV( 100, 255, checkValue(ledValue)));
}

void showAnalogB( const CRGB& rgb)
{
  analogWrite(REDPIN,  0  );
  analogWrite(GREENPIN, 0 );
  analogWrite(BLUEPIN,  rgb.b );
}



void callback_Blue_led()
{
  int ledValue = OFFSET + AMPLITUDE * (cos((OMEGA * millis()) + PHASE));
  showAnalogB(CHSV( 225, 255, checkValue(ledValue)));
}

int checkValue(int val) {
  if (val > 255)
    val = 255;
  else if (val < 0)
    val = 0;
  return val;
}

void tickRed()
{
  callback_Red_led();
}
void tickGreen()
{
  callback_Green_led();
}
void tickBlue()
{
  callback_Blue_led();
}
//gets called when WiFiManager enters configuration mode

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  //entered config mode, make led toggle faster
  ticker.attach(0.03, tickRed);
}

void setup() {

  pinMode(REDPIN,   OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN,  OUTPUT);

  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BAUD);

  // start ticker with 0.5 because we start in AP mode and try to connect
  
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
  ticker.detach();
  ticker.attach(0.03, tickBlue);
  //ticker.detach();
}

void loop() {
  // put your main code here, to run repeatedly:

}
