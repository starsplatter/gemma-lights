#include <Adafruit_NeoPixel.h>

#define PIN 1

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(100);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  rgbloop();
}

// enter pairs of color to change between, along with how long you want the change to take
// enter as many pairs as you want and it will go through them all
// do cheaty things like begin and end on the same color to pause somewhere for a while, etc.
// after you set the colors here you don't need worry about anything lower down unless you want to

void rgbloop() {
  rgbfade( 252,116,5,    73,4,138, 25);
    rgbfade( 73,4,138,    2,3,48, 75);
    rgbfade( 2,3,48,    2,3,48, 25);

  rgbfade( 2,3,48,  252,116,5,       75);
    rgbfade( 252,116,5,  250,225,0,       25);
 rgbfade( 250,225,0,        252,116,5, 25);
 // rgbfade( 0,0,255,  0,0,0,   20);
  delay(500);
}

#define STEPS 100
void rgbfade(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t wait) {
  /* fade from c1 to c2 */
  uint16_t i, j,k;
  int16_t rb,gb,bb;
  uint32_t cb;

  // The interpolation formula that Buddha likes is
  // a*t + b*(1-t) for t goes from 0 to 1
  // or 
  // a*t/STEPS + b*(STEPs-t)/STEPS for t goes from 0 to STEPS
  // (a*t + b*(STEPS-t))/STEPS
  //
  
  for(j=0; j<=STEPS; j++) {
    k = STEPS-j;
    rb = (r2*j + r1*k)/STEPS;
    gb = (g2*j + g1*k)/STEPS;
    bb = (b2*j + b1*k)/STEPS;
    cb = strip.Color(rb,gb,bb);    
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, cb);
    }
    strip.show();
    delay(wait);
  }
}


