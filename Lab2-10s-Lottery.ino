/* Rotary encoder test code printing to LCD screen
 * Modified from https://github.com/FAR-Lab/Developing-and-Designing-Interactive-Devices/wiki/Rotary-Encoder-test-Code by Jessica Faruque
 * Modified by Chris Brownell 9/9/2018
 * 
 */
 
#include <LiquidCrystal.h>
#include "pitches.h"
#define ENC_A 7 //these need to be digital input pins
#define ENC_B 8

// initialize variables used for the timer
long timer = 0;
long endMillis = 0;
long countDownFrom = 10;

// initialize variables used for the lottery draw and encoder
int counterMax = 10;
int winningDraw = 0;
static unsigned int counter4x = 0;      //the SparkFun encoders jump by 4 states from detent to detent
static unsigned int counter = 0;
static unsigned int prevCounter = 0;
int tmpdata;

// notes in the winning and losing melody
int melodyBAD[] = {NOTE_G3,NOTE_G3,0};
int melodyGOOD[] = {NOTE_G3,NOTE_G3,NOTE_G4,0};

// note durations for winning and losing tones
int noteDurationsBAD[] = {10,10};
int noteDurationsGOOD[] = {6,10,2};

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
void setup()
{
  /* Setup encoder pins as inputs */
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  lcd.begin(16, 2);
}
 
void loop()
{
  winningDraw = random(1,11);
  lcd.print("Your Guess: ");
  lcd.print(counter);
  // While the lotto is open, allow user to select their guess
  // Close the lotto (aka exit the while loop) after countDownFrom seconds
  while((countDownFrom*1000)-timer>0){
    // use encoder to pick a number between 0 and counterMax
    tmpdata = read_encoder();
    if( tmpdata) {
      counter4x += tmpdata;
      counter = counter4x/4;    // SparkFun encoders jump by 4 states from detent to detent
      if (prevCounter != counter){
        lcd.clear();
        lcd.print("Your Guess: ");
        if(counter > counterMax) {
          counter = counterMax;
        }
        lcd.print(counter);
      }
      prevCounter = counter;
    } 
    lcd.setCursor(0, 1);
    // print the number of seconds until the next drawing
    lcd.print("Drawing in ");
    lcd.print(countDownFrom-(timer/1000));
    lcd.print("   ");
    // record how much time has passed since the last loop finished
    timer = millis() - endMillis;
    
  }
  // display the winning draw number
  lcd.setCursor(0, 1);
  lcd.print("Winning Draw: ");
  lcd.print(winningDraw);
  delay(1000); 
  lcd.setCursor(0, 1);
  // if the contestant chose 0, do not print a message or make a sound
  if(counter == 0) {
  // if the contentant chose the winning number, play a happy sound and winning message
  } else if(counter == winningDraw){
    lcd.print("YOU JUST WON! :)");
      for (int thisNote = 0; thisNote < 3; thisNote++) {
    
        // to calculate the note duration, take one second divided by the note type.
        int noteDuration = 1000 / noteDurationsGOOD[thisNote];
        tone(9, melodyGOOD[thisNote], noteDuration);
    
        // note's duration + 30% silent time between notes
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(9);
      }
    // if the contentant chose a losing number, play a sad sound and losing message
    } else {
        lcd.print("YOU LOSE :(     ");
        for (int thisNote = 0; thisNote < 2; thisNote++) {
      
          // to calculate the note duration, take one second divided by the note type.
          int noteDuration = 1000 / noteDurationsBAD[thisNote];
          tone(9, melodyBAD[thisNote], noteDuration);
      
          // note's duration + 30% silent time between notes
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          noTone(9);
        }
      }
  // let the win/loss sink in for 2 seconds
  delay(2000);    
  // reset the clock for the next 10 second lottery
  endMillis = millis();
  timer = millis() - endMillis;
  lcd.clear();
}
 
/* returns change in encoder state (-1,0,1) */
int read_encoder()
{
  static int enc_states[] = {
    0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0  };
  static byte ABab = 0;
  ABab *= 4;                   //shift the old values over 2 bits
  ABab = ABab%16;      //keeps only bits 0-3
  ABab += 2*digitalRead(ENC_A)+digitalRead(ENC_B); //adds enc_a and enc_b values to bits 1 and 0
  return ( enc_states[ABab]);
 
 
}
