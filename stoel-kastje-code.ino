#include <ChainableLED.h>
ChainableLED leds(6,7, 1);
void setup()
{
  Serial.begin(9600);
  delay(1000);

  // RGB Led opzetten
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  String response = "";
  if (Serial.available()) {
    while (Serial.available()) {
      char c = Serial.read();
      response += c;
    }
    if (response.indexOf("OK+CONN") >= 0) {
      Serial.println("Er is verbinding");
    }
    if (response.indexOf("COLOR1") >= 0) {
      Serial.println("Kleur 1");
      leds.setColorRGB(0, 0, 255, 0); 
    }
    else if (response.indexOf("COLOR2") >= 0) {
            Serial.println("Kleur 2");
      leds.setColorRGB(0, 255, 0, 0);
    }
    else if (response.indexOf("COLOR3") >= 0) {
            Serial.println("Kleur 3");
      leds.setColorRGB(0, 255, 127, 0); 
    }
  }
  delay(1000);
}
