#include <Adafruit_NeoPixel.h>

#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs_4_15 = CapacitiveSensor(4,0);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_16 = CapacitiveSensor(3,16);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_4_18 = CapacitiveSensor(4,18);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil
#define LED_PIN    12
#define LED_COUNT 24
#define LED_PIN2   11
#define LED_PIN3   14

String readString;

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip1(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, LED_PIN2, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip3(LED_COUNT, LED_PIN3, NEO_RGBW + NEO_KHZ800);


void setup()                    
{
  strip1.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip1.show();            // Turn OFF all pixels ASAP
  strip1.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip2.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip2.show();            // Turn OFF all pixels ASAP
  strip2.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  
  strip3.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip3.show();            // Turn OFF all pixels ASAP
  strip3.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.begin(9600);
}

void loop()                    
{
    if (Serial.available()) {
      while (Serial.available()) {
        if (Serial.available() >0) {
          char c = Serial.read();  //gets one byte from serial buffer
          readString += c; //makes the string readString
        }
     }
     Serial.print("Received: ");
     Serial.println(readString);
     String part01 = getValue(readString,'@',1); // (T)otal number of hosts
     String part02 = getValue(readString,'@',2); // number of (E)vents
     String part03 = getValue(readString,'@',3); // status of (M)onitor
     
     for(int i=0; i<part01.remove(0,1).toInt(); i++) {
        strip1.setPixelColor(i, strip1.Color(  0, 255,   0)); // Green
        strip1.show();          
     }
     if (part02.remove(0,1).toInt() > 0) {
        theaterChaseRainbow(50);
     }

     if (part03.remove(0,1).toInt() > 0) {
       colorWipe3(strip3.Color(  0, 255,   0), 50); // Green
       colorWipe3(strip3.Color(  255, 0,   0), 50); // Green
     }
     readString = "";
    }

    
    long start = millis();
    long total1 =  cs_4_15.capacitiveSensor(60);
    long total2 =  cs_4_16.capacitiveSensor(60);
    long total3 =  cs_4_18.capacitiveSensor(60);

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing

    Serial.print(total1);                  // print sensor output 1
    Serial.print("\t");
    Serial.print(total2);                  // print sensor output 2
    Serial.print("\t");
    Serial.println(total3);                // print sensor output 3

    /*
    colorWipe(strip1.Color(255,   0,   0), 50); // Red
    //theaterChaseRainbow(40); // Rainbow-enhanced theaterChase variant
    colorWipe(strip1.Color( 255, 255,   0), 50); // Green

    //theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant

    colorWipe2(strip2.Color( 0, 0, 255), 50);
    colorWipe2(strip2.Color( 255, 0, 255), 50);
    
    colorWipe3(strip3.Color(  0, 255,   0), 50); // Green
    colorWipe3(strip3.Color(  0, 255,   255), 50); // Green

    colorWipe(strip1.Color(  0, 0,   0), 50); // Green
    colorWipe2(strip2.Color(  0, 0,   0), 50); // Green
    colorWipe3(strip3.Color(  0, 0,   0), 50); // Green
    */
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}



void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip1.numPixels(); i++) { // For each pixel in strip...
    strip1.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip1.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void colorWipe2(uint32_t color, int wait) {
  for(int i=0; i<strip2.numPixels(); i++) { // For each pixel in strip...
    strip2.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip2.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void colorWipe3(uint32_t color, int wait) {
  for(int i=0; i<strip1.numPixels(); i++) { // For each pixel in strip...
    strip3.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip3.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip2.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip2.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip2.numPixels();
        uint32_t color = strip2.gamma32(strip2.ColorHSV(hue)); // hue -> RGB
        strip2.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip2.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
