#define FORCE_SENSOR_PIN A0 // the FSR and 10K pulldown are connected to A0
#include <Adafruit_NeoPixel.h>
#define PIN 2 
#define NUMPIXELS 20

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 200;

int redColor = 0;
int greenColor = 0;
int blueColor = 0;

void setup() {
  Serial.begin(9600);
  pixels.begin();
// Serial.begin(9600);
}

void loop(){
  
  double analogReading = analogRead(FORCE_SENSOR_PIN);

  Serial.print("Force sensor reading = ");
  Serial.println(analogReading); // print the raw analog reading
  setColor();
  
  double forca = analogReading/23.3;
  
  for(int i=0;i<forca;i++){
   Serial.println(i); 
   pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
   pixels.show();
   
   delay(delayval);
   
  pixels.setPixelColor(i, 0,0,0);
  delay(delayval);
// Serial.println(i);
  }
}
  
  void setColor(){
    redColor = random(0, 255);
    greenColor = random(0, 225);
    blueColor = random(0 ,255);
    Serial.print("red: ");
    Serial.println(redColor);
    Serial.print("green: ");
    Serial.println(greenColor);
    Serial.print("blue: ");
    Serial.println(blueColor);
    
}  
 