# Make a Digital Timer!
Chris Brownell (ckb77)

## Part A. Solder your LCD panel

**Take a picture of your soldered panel and add it here!**
![lcdpanel](https://github.com/chrisbrownell/IDD-Fa18-Lab2/blob/master/IMG_1390.JPG)

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

For my multimeter I initially mapped the analogRead values (0 to 1023) to a smaller range (0 to 255) because I thought
I might be using analogWrite. So the video below shows the multimeter values from 0 to 255. 

In the video I connect the 5V pin, 3V pin, and the potentiometer used to vary LCD contrast to pin A0 to show varying 
voltages. 

[Video of Lowly Multimeter](https://drive.google.com/file/d/1yrSvN21JwVmIkKy-acdxyGuJmQ4WaSSJ/view?usp=sharing)

Lowly Multimeter Sketch:
```
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int analogIn = A0;
int inputValue = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
  inputValue = analogRead(analogIn);
  lcd.print(map(inputValue, 0, 1023, 0, 255));
  delay(500);
  lcd.clear();
}
```

## Part C. Using a time-based digital sensor

**Upload a video of your working rotary encoder here.**

[Rotary Encoder Video](https://drive.google.com/file/d/15SfUtqe1EwgN0s9-FLvbpygG3XojwMJP/view?usp=sharing)

I modified the test code to print the output value to the LCD. 
[Modified Encoder Test Code](https://github.com/chrisbrownell/IDD-Fa18-Lab2/blob/master/Lab2-Encoder-Test.ino)


## Part D. Make your Arduino sing!

**a. How would you change the code to make the song play twice as fast?**

Divide all the values in noteDurations[] by 2. Or to make things simpler, modify this line:
```
int noteDuration = 1000 / noteDurations[thisNote];
```
to instead be:
```
int noteDuration = 500 / noteDurations[thisNote];
```
 
**b. What song is playing?**

The main theme from Star Wars!

[Video of Star Wars Theme](https://drive.google.com/file/d/15Wi9Y_hL7v8CHbxh4iBOut4_U_3SvmUK/view?usp=sharing)

## Part E. Make your own timer

**a. Make a short video showing how your timer works, and what happens when time is up!**
Based on my idea #7 from the [pre-lab](https://github.com/chrisbrownell/IDD-Fa18-Lab2-Prep/blob/master/README.md) I made a ten second lottery.
Using the encoder, a lottery contestent can select a number between 0 and 10. The lottery is drawn every 10 seconds and 
if the contestant guesses correctly, they hear a happy sound and see a winning message on the LCD screen. If the contestant
guesses incorrectly, they hear a sad sound and see a losing message. If the contestant chooses 0, it is treated as 
a non-attempt and no sound or message are displayed.

[Video of 10 second lotto](https://drive.google.com/file/d/1rbYHCPNlthieoLMdHhPXIoVl1CIGcKNQ/view?usp=sharing)

[Arduino Sketch for 10 second lotto](https://github.com/chrisbrownell/IDD-Fa18-Lab2/blob/master/Lab2-10s-Lottery.ino)

**b. Post a link to the completed lab report your class hub GitHub repo.**
