# Make a Digital Timer!
Chris Brownell (ckb77)

## Part A. Solder your LCD panel

**Take a picture of your soldered panel and add it here!**

## Part B. Writing to the LCD
 
**a. What voltage level do you need to power your display?**

5.0V +/- 0.2V

**b. What voltage level do you need to power the display backlight?**

3.2V +/- 0.15V
   
**c. What was one mistake you made when wiring up the display? How did you fix it?**

I didn't connect power and ground rails on the left and right halves of the long breadboard at first so the rails were not 
functioning as expected.

**d. What line of code do you need to change to make it flash your name instead of "Hello World"?**

lcd.print("hello, world!"); However I notice when I try my full name "Christopher Kirlin Brownell" (27 chars including spaces)
it cuts off at 16 chars and does not wrap to the next line. 

By modifying the "Scroll" sample code as follows, I can get the full name to slowly scroll across the LCD screen:
```
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String s = "Christopher Kirlin Brownell";

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(s);
  delay(1000);
}

void loop() {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    delay(500);
}
```
 
**e. Include a copy of your Lowly Multimeter code in your lab write-up.**


## Part C. Using a time-based digital sensor

**Upload a video of your working rotary encoder here.**


## Part D. Make your Arduino sing!

**a. How would you change the code to make the song play twice as fast?**
 
**b. What song is playing?**


## Part E. Make your own timer

**a. Make a short video showing how your timer works, and what happens when time is up!**

**b. Post a link to the completed lab report your class hub GitHub repo.**
