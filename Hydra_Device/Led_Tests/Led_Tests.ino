
#include <FastLED.h>

#define REDPIN   D3
#define GREENPIN D2
#define BLUEPIN  D1

#define SERIAL_BAUD 115200

// Time period of fading in millisecs
#define PERIOD 10000
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
  Serial.println(ledValue);
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
  Serial.print(ledValue);
  Serial.print("    ");
  Serial.println(checkValue(ledValue));


}

int checkValue(int val) {
  if (val > 255)
    val = 255;
  else if (val < 0)
    val = 0;
  return val;
}

void setup() {
  Serial.begin(SERIAL_BAUD);
  pinMode(REDPIN,   OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN,  OUTPUT);
}


void loop()
{
  if (millis() % update_led_timer == 0) callback_Blue_led();
}
