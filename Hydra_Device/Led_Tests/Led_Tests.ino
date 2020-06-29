#include <arduino-timer.h>
#include <FastLED.h>

#define REDPIN   D3
#define GREENPIN D2
#define BLUEPIN  D1

#define SERIAL_BAUD 115200

// Time period of fading in millisecs
#define PERIOD 2000
// Angular Frequency by definition
#define OMEGA 2*PI/PERIOD
// No Phase
#define PHASE 0
// Offset of the sine wave
#define OFFSET 128
// Amplitude of the sine wave
#define AMPLITUDE 127

int update_led_timer = 25;


void showAnalogRGB( const CRGB& rgb)
{
  analogWrite(REDPIN,   rgb.r );
  analogWrite(GREENPIN, rgb.g );//rgb.g
  analogWrite(BLUEPIN,  rgb.b );
}


void callback_led()
{
  float ledValue = OFFSET + AMPLITUDE * (cos((OMEGA * millis()) + PHASE));

  showAnalogRGB(CHSV( ledValue, 255, 255));

  Serial.println(ledValue);

}

void setup() {
  Serial.begin(SERIAL_BAUD);

  pinMode(REDPIN,   OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN,  OUTPUT);

  Serial.write("i am in setup");

}


void loop()
{
  if (millis() % update_led_timer == 0) callback_led();
}
