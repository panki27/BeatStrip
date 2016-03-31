#include <Adafruit_NeoPixel.h>

#define PIN 3 // LED Digital In PIN

int analogPin = 1;
int val = 0;
int peak = 0;
int loopCount = 0;
int activeColor = 0;
int lastPeak = 0;
byte wheelCol = byte(160);
unsigned long lastChange = millis();
unsigned long lastChangeRainbow = millis();
const long interval = 5000;
const long rainbowInterval = 100;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

uint32_t ColorCombos[6] = {strip.Color(0, 0, 255), strip.Color(200, 0, 255), //different colors to rotate through
                            strip.Color(0, 0, 255), strip.Color(0, 255, 0),
                            strip.Color(255, 255, 255), strip.Color(0, 255, 0)};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Useful to print debug information, such as peak 
  strip.begin();
  strip.show();
   
}

void loop() {
  unsigned long currentTime = millis();
  // if(currentTime - lastChange >= interval){ // every 5 seconds change colors
  //   colorChange();
  // }
  centerBarFade();
}

void centerBar(){
  val = analogRead(analogPin); // read in the voltage coming through the lowpass filter
  peak = round(val/20); // maximum value is ~600, max of LEDs being driven per side is 30

  if(peak < lastPeak){
    lastPeak = lastPeak -3; // if the new voltage is lower, reduce the 'amplitude' of the bar by 3 per side
  }
  else lastPeak = peak;
 
  for(int i2 = 0; i2<(30-lastPeak); i2++){ //OFF STATE 
    strip.setPixelColor(i2, ColorCombos[activeColor+1]);
    strip.setPixelColor((60-i2), ColorCombos[activeColor+1]); 
  }
  strip.show();
    for(int i = 0; i<lastPeak; i++){ // ON State
    strip.setPixelColor(i+30, ColorCombos[activeColor]);
    strip.setPixelColor((30-i), ColorCombos[activeColor]);
  }
 strip.show();
}


void centerBarFade(){  // WIP: Rotating, contrasting colors
  val = analogRead(analogPin);
  peak = round(val/20);
  unsigned long now = millis();
  
  if(now - lastChangeRainbow >= rainbowInterval){ // every 0.1 seconds change colors
    wheelCol++;
    lastChangeRainbow = now;
  }

  if(peak < lastPeak){ 
    lastPeak = lastPeak -2;
  }

  else lastPeak = peak;

  for(int n = 0; n<60; n++){

    if( (n < 30-lastPeak) || (n > (60-n+2*lastPeak)) ){
      strip.setPixelColor(n, Wheel(wheelCol));
    }
    else {
      strip.setPixelColor(n, Wheel(wheelCol-128));
    }
  }

  if(wheelCol == byte(255)){
     wheelCol = byte(0);
   }
   strip.show();
}

void colorChange(){
  if(activeColor < 6){
    activeColor = activeColor + 2;
      lastChange = millis();
    }
    else activeColor = 0;
  }
  
void vuMeter(){
  val = analogRead(analogPin);
  peak = round(val/10); 
  for(int i = 0; i<peak; i++){
  //  strip.setPixelColor(i, 255, 125, 0);
  }
    for(int i = peak; i<60; i++){
//    strip.setPixelColor(i, 0, 0, 0);
  }
  //strip.show();
}

uint32_t Wheel(byte WheelPos) { // Generate colors from a value of 0-255
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

