#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <Adafruit_NeoPixel.h>

int level = 1;
const unsigned long interval = 2000; // 1 second
unsigned long myTimer = 0;

// DFPlayer
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// Buttons
const int buttonPin1 = 9;
const int buttonPin2 = 7;
const int buttonPin3 = 5;
const int buttonPin4 = 2;

// NeoPixel
#define LED_PIN     3
#define NUM_PIXELS  12  // άλλαξε ανάλογα με τα LEDs σου
Adafruit_NeoPixel pixels(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
 
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

  // DFPlayer
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("Σφάλμα: DFPlayer δεν ξεκίνησε");
    while (true);
  }
  Serial.println("DFPlayer ξεκίνησε σωστά.");
  myDFPlayer.volume(30);

  // NeoPixel
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void loop() {

if( level==1){
  
  myDFPlayer.play(1);
    Serial.println("Παίζει τραγούδι 2");
    fadeColor(0, 255, 0, 4000,11); //φαδε
    level=2;
}

  if (digitalRead(buttonPin1) == LOW && level==2) {
    pixels.clear();    // Καθαρίζει όλα τα LED (θέτει χρώμα = 0)
    pixels.show(); 
    myDFPlayer.play(2);
    Serial.println("Παίζει το αρχείο 2");
    fadeColor(30, 155, 90, 6700,10);

    myDFPlayer.play(3);
    Serial.println("Παίζει το αρχείο 3");
    delay(2500);
    breatheRing(2000, 5500, 3000);

    myDFPlayer.play(4);
    delay(4000);
    breatheRing(4000, 5500, 3000);

    myDFPlayer.play(5);
    delay(6000);
    breatheRing(3000, 6000, 3000);

    delay(5000);

    myDFPlayer.play(6);
    fadeColor(180, 180, 100, 3000,6);

    level=3;


    waitForButtonRelease(buttonPin1);


    
  }

   if (digitalRead(buttonPin2) == LOW && level==3) {
      pixels.clear();    // Καθαρίζει όλα τα LED (θέτει χρώμα = 0)
    pixels.show(); 
    myDFPlayer.play(7);
    Serial.println("Παίζει το αρχείο 7");
    level=4;
    waitForButtonRelease(buttonPin2);
    delay(9000);

     Serial.println("Περίμενε 2 δευτερόλεπτα για κουμπί...");
  myTimer = millis();      // ξεκινάμε χρονόμετρο
  level = 4;   




   }


   if (level == 4) {
  if (digitalRead(buttonPin2) == LOW ) {
    Serial.println("Πάτησες το κουμπί!");
    myDFPlayer.play(8);
    fadeColor(223, 105, 105, 3160,6);
    level = 5;
    //delay(19000);
      pixels.clear();
  pixels.show();
    waitForButtonRelease(buttonPin2);

    
  } else if (millis() - myTimer >= 4000) {
    Serial.println("Δεν πάτησες το κουμπί!");
    myDFPlayer.play(9);
    setColor(150,180,60);
    delay(9000);
    level = 5;
  }
  
}

if(level==5){
myDFPlayer.play(10);
level=6;
}


if (digitalRead(buttonPin3) == LOW && level==6) {
  myDFPlayer.play(11);
    fadeColor(30, 155, 90, 5000,10); //φαδε
    myDFPlayer.play(13);
    fadeColor(90, 55, 150, 3000,5); //φαδε
    level = 7;



waitForButtonRelease(buttonPin3);
}


if (digitalRead(buttonPin4) == LOW && level==7) {
  myDFPlayer.play(12);
    fadeColor(30, 155, 90, 5000,8); //φαδε
    delay(2000);
waitForButtonRelease(buttonPin4);
Serial.println("ksekinaei xronos");
level = 8; 
    myTimer = millis();      // ξεκινάμε χρονόμετρο
    





}

   if (level == 8) {
  if (digitalRead(buttonPin4) == LOW ) {
    Serial.println("Πάτησες το κουμπί!");
    myDFPlayer.play(14);
    setColor(82,201,69);
    delay(9000);
    // for(int i=0;i<8;i++){
    //  heartPulse(255, 0, 0, 1000);
    // delay(200);}

    
      pixels.clear();
  pixels.show();
    waitForButtonRelease(buttonPin4);

    level = 9;
  } else if (millis() - myTimer >= 5000) {
    Serial.println("Δεν πάτησες το κουμπί!");
    myDFPlayer.play(15);
    setColor(150,180,60);
    delay(12000);
    level = 9;
  }

  
}

if(level==9){
Serial.println("telos");
  myDFPlayer.play(16);
  rainbowCycle(100);
      pixels.clear();
  pixels.show();
  level=10;
}

if(level==10){
  pixels.clear();
  pixels.show();
}

}





void setColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();
}

void waitForButtonRelease(int pin) {
  while (digitalRead(pin) == LOW);
  delay(200);
}





void fadeColor(uint8_t r, uint8_t g, uint8_t b, int duration, int repeats) {
  int steps = 50; // Αριθμός βημάτων για ομαλό fade
  int delayTime = duration / (steps * 2); // Χρόνος μεταξύ βημάτων

  for (int rep = 0; rep < repeats; rep++) {
    // Fade in
    for (int i = 0; i <= steps; i++) {
      float factor = (float)i / steps;
      setColor(r * factor, g * factor, b * factor);
      delay(delayTime);
    }

    // Fade out
    for (int i = steps; i >= 0; i--) {
      float factor = (float)i / steps;
      setColor(r * factor, g * factor, b * factor);
      delay(delayTime);
    }
  }
  setColor(r , g , b );
}


void breatheRing(int inhaleTime, int holdTime, int exhaleTime) {
  int inhaleDelay = inhaleTime / NUM_PIXELS;
  int exhaleDelay = exhaleTime / NUM_PIXELS;

  // Εισπνοή - άναμμα LED ένα-ένα
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 255)); // π.χ. μπλε
    pixels.show();
    delay(inhaleDelay);
  }

  // Κράτημα αναπνοής - όλα αναμμένα
  delay(holdTime);

  // Εκπνοή - σβήσιμο LED ένα-ένα
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, 0); // σβήσιμο
    pixels.show();
    delay(exhaleDelay);
  }
}


void heartPulse(uint8_t r, uint8_t g, uint8_t b, int pulseDelay) {
  // Πρώτος παλμός (μικρός)
  setColor(r, g, b);
  delay(100);
  setColor(0, 0, 0);
  delay(100);

  // Δεύτερος παλμός (πιο μεγάλος)
  setColor(r, g, b);
  delay(200);
  setColor(0, 0, 0);

  delay(pulseDelay); // Χρόνος μέχρι τον επόμενο παλμό
}


void rainbowCycle(int wait) {
  for (int j = 0; j < 256; j++) { // Ένα πλήρες ουράνιο τόξο
    for (int i = 0; i < NUM_PIXELS; i++) {
      pixels.setPixelColor(i, Wheel((i + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

// Βοηθητική για τα χρώματα του ουράνιου τόξου
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}



bool isTimePassed(unsigned long &previous, unsigned long interval) {
  unsigned long current = millis();
  if (current - previous >= interval) {
    previous = current;
    return true;
  }
  return false;
}


