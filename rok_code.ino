#include <Adafruit_NeoPixel.h> //library laden
#ifdef __AVR__
#endif


#define BUTTON_PIN   A3 // pin van knopje

#define PIXEL_PIN    11 // pin waar de lampjes beginnen

#define PIXEL_COUNT 12 // aantal lampjes


Adafruit_NeoPixel strip(BUTTON_PIN, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

boolean oldState = HIGH; // wanneer de knopje "omhoog" is, staat de state op "oldstate"
int     mode     = 0;   // default mode

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin(); 
  strip.show();  
}


void loop() {
  boolean newState = digitalRead(BUTTON_PIN); // wanneer de knopje ingedrukt wordt, gaat het naar newstate

  if((newState == LOW) && (oldState == HIGH)) { // als knopje is ingedrukt
    delay(20);
    newState = digitalRead(BUTTON_PIN);
    if(newState == LOW) {      
      if(++mode > 7) mode = 0; // volgende in sequence, na 7 terug naar 0
      switch(mode) {          
        case 0:
          colorWipe(strip.Color(  0,   0,   0), 50);    // Black/off
          break;
        case 1:
          colorWipe(strip.Color(183,   19,   242), 50);    // purple
          break;
        case 2:
          colorWipe(strip.Color(  242, 19,   187), 50);    // pink
          break;
        case 3:
          colorWipe(strip.Color(  62,   116, 240), 50);    // Blue
          break;
        case 4:
          theaterChase(strip.Color(127, 127, 127), 50); // White
          break;
        case 5:
          rainbow(15); //regenboog!
          break;
        case 6:
          colorWipe(strip.Color(255,  255,   255), 100);    // white
          break;  
         case 7:
          colorWipe(strip.Color(240,  215,   149), 100);    // warm light
          break;  
    
      }
    }
  }

  
  oldState = newState; // de nieuwste state wordt de oude
}


void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);         
    strip.show();                          
    delay(wait);                           
  }
}


void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) { 
    for(int b=0; b<3; b++) {
      strip.clear();         
      for(int c=b; c<strip.numPixels(); c += 6) {
        strip.setPixelColor(c, color); 
      }
      strip.show(); 
      delay(wait);  
    }
  }
}



void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);  
  }
}
