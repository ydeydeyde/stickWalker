#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h> 
#include <utility/imumaths.h> 

// Object constructed from class?
Adafruit_BNO055 bno = Adafruit_BNO055(55); 

#define LED_PIN D7
#define POT_PIN A0 
#define NUMPIXELS 60

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup(void) {

  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  pixels.begin(); // This initializes the NeoPixel library.
  
// if BNO was found
    if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);
}

void loop(void) {
  /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);
  
  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
    for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(event.orientation.x,event.orientation.y,event.orientation.z)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
}


