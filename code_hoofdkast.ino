  #include "Arduino.h"
  #define LED_MODE 1
  #include <ChainableLED.h>

  // RGB Led, 1 is voor 1 ledje
  ChainableLED leds(6,7, 1);

  // Button 1
  const int ledPin = 2;  
  const int buttonPin = 3;

  // Button 2
  const int ledPin2 = 8;
  const int buttonPin2 = 9;

  // Button 3
  const int ledPin3 = 4; 
  const int buttonPin3 = 5;

  // Ledjes uit
  int ledState = LOW;
  int ledState2 = LOW;
  int ledState3 = LOW;
  int ledState4 = LOW;

  // Status van het knopje initaliseren
  int buttonState1; 
  int buttonState2; 
  int buttonState3;
  int buttonState4;

  // Laatste button state in loop
  int lastButtonState1 = HIGH;
  int lastButtonState2 = HIGH; 
  int lastButtonState3 = HIGH;
  int lastButtonState4 = HIGH;

  // Debouncetime zodat niet meerdere keren wordt geregistreerd
  unsigned long lastDebounceTime1 = 100;
  unsigned long lastDebounceTime2 = 100;
  unsigned long lastDebounceTime3 = 100;
  unsigned long lastDebounceTime4 = 100; 

  unsigned long debounceDelay = 50;

  // Loudness sensor
  int loudnessPin = A0;

  // Bijhouden hoelang de overlast er is en bijhouden of het over de 20seconden gaat
  unsigned long startTime;
  bool loudnessExceedsThreshold = false;

  void setup() {

    // Pins klaarzetten voor de buttons en leds
    pinMode(buttonPin, INPUT);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, ledState);

    pinMode(buttonPin2, INPUT);
    pinMode(ledPin2, OUTPUT);
    digitalWrite(ledPin2, ledState2);

    pinMode(buttonPin3, INPUT);  
    pinMode(ledPin3, OUTPUT);
    digitalWrite(ledPin3, ledState3);

    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(loudnessPin, INPUT);


    // Serial Monitor op port 9600
    Serial.begin(9600);

    // Verbinding klaarzetten
    delay(2000);
    Serial.println("AT+ROLE1");
    delay(2000);
    Serial.println("AT+CON341513D9161E");
  }

  void loop(){
    // Verbinding maken met andere Aduino
    String response = "";
    if (Serial.available()) {
      while (Serial.available()) {
        char c = Serial.read();
        response += c;
      }
      if (response.indexOf("OK+CONN") >= 0) {
        Serial.println("Er is verbinding");
      }
    }
    // Loudness meter
    int loudness = analogRead(loudnessPin);
    // Status van knopje lezen
    int reading1 = digitalRead(buttonPin);
    int reading2 = digitalRead(buttonPin2);
    int reading3 = digitalRead(buttonPin3);

    if (reading1 != lastButtonState1) {
      lastDebounceTime1 = millis(); // Millis voor het bijhouden wanneer een knopje is ingedrukt
    }

    if (reading2 != lastButtonState2) {
      lastDebounceTime2 = millis(); // Millis voor het bijhouden wanneer een knopje is ingedrukt
    }

    if (reading3 != lastButtonState3) {
      lastDebounceTime3 = millis(); // Millis voor het bijhouden wanneer een knopje is ingedrukt
    }
    // Button states koppelen
  buttonState1 = reading1;
  buttonState2 = reading2;
  buttonState3 = reading3;

  // De eerste if is om te voorkomen dat het meerdere keren wordt geregistreerd 
  if ((millis() - lastDebounceTime1) > debounceDelay) { 
    if (buttonState1 == LOW) {
      ledState = HIGH;
      ledState2 = LOW;
      ledState3 = LOW;
      Serial.println("Button 1 selected");
      Serial.println("COLOR1");
      leds.setColorRGB(0, 0, 255, 0);
    }
    lastDebounceTime1 = millis(); 
  }

  if ((millis() - lastDebounceTime2) > debounceDelay) { 
    if (buttonState2 == LOW) {
      ledState = LOW;
      ledState2 = HIGH;
      ledState3 = LOW;
      Serial.println("Button 2 selected");
      Serial.println("COLOR2");
      leds.setColorRGB(0, 255, 0, 0);
    }
    lastDebounceTime2 = millis(); 
  }

  if ((millis() - lastDebounceTime3) > debounceDelay) { 
    if (buttonState3 == LOW) {
      ledState = LOW;
      ledState2 = LOW;
      ledState3 = HIGH;
      Serial.println("Button 3 selected");
      Serial.println("COLOR3");
      leds.setColorRGB(0, 255, 127, 0); 
    }
    lastDebounceTime3 = millis();
  }
    if (loudness > 30 && !loudnessExceedsThreshold) {
      startTime = millis();
      loudnessExceedsThreshold = true;
    } else if (loudness <= 30) { 
      loudnessExceedsThreshold = false;
    }
    if (loudnessExceedsThreshold && millis() - startTime >= 1000) {
      Serial.println("COLOR2");  
      leds.setColorRGB(0, 255, 0, 0); 
      loudnessExceedsThreshold = false; 
    }
    digitalWrite(ledPin, ledState);
    digitalWrite(ledPin2, ledState2);
    digitalWrite(ledPin3, ledState3);
    

    lastButtonState1 = reading1;
    lastButtonState2 = reading2;
    lastButtonState3 = reading3;
  }
