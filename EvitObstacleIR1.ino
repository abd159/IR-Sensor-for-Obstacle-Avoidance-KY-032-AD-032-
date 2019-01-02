int Led = 13 ;// define LED Interface
int buttonpin = 2; // define the obstacle avoidance sensor interface
int pinSpeaker = 10;           //Set up a speaker on a PWM pin (digital 9, 10, or 11)

int pirState = LOW;             // we start, assuming no motion detected


//I2C LCD:
#include <Wire.h> // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>

// Set the LCD I2C address
LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x3F for a 16 chars and 2 line display


void setup ()
{
   lcd.begin(16, 2);
  lcd.init(); // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Capteur 20cm max");
  lcd.setCursor(1, 1);
  lcd.print("> Obstacles <");
  // *******************************************************************
     pinMode (Led, OUTPUT) ;// define LED as output interface
     pinMode (buttonpin, INPUT) ;// define the obstacle avoidance sensor output interface
     pinMode (pinSpeaker, OUTPUT);
}
void loop ()
{
  pirState = LOW;
       playTone(0, 0);
       
     if (digitalRead (buttonpin) == HIGH) // When the obstacle avoidance sensor detects a signal, LED goes on.
     {
     //-----------------------------------------------
      lcd.clear();
      // set the cursor to (0,0):
      lcd.setCursor(0, 0);
      lcd.print("Pas d'Obstacle");
      lcd.setCursor(0, 1);
      lcd.print("buttonpin=  ");
      lcd.print(digitalRead (buttonpin));
      //lcd.print(" sec");
      //-----------------------------------------------

      
       digitalWrite (Led, LOW);
       pirState = LOW;
       playTone(0, 0);
       
     }
     else
     {
     //-----------------------------------------------
      lcd.clear();
      // set the cursor to (0,0):
      lcd.setCursor(0, 0);
      lcd.print("Obstacle Detected");
      lcd.setCursor(0, 1);
      lcd.print("buttonpin=  ");
      lcd.print(digitalRead (buttonpin));
      //lcd.print(" sec");
      //-----------------------------------------------
      
     digitalWrite (Led, HIGH);
       pirState = HIGH;
       playTone(400, 190);

       
     }
}

// duration in mSecs, frequency in hertz
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}
