#include <UTFT.h>
#include <SdFat.h>
#include <UTFT_SdRaw.h>
#include "wifi_icon.h"

// Fonts
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

// TFT Display
UTFT myGLCD(CTE40, 38, 39, 40, 41);

// Draw header (time, date, wifi)
void drawHeader() {
  myGLCD.setFont(SmallFont);
  myGLCD.print("8:46 A.M.", CENTER, 20);
  myGLCD.print("03/27/2025", LEFT, 20);
  myGLCD.drawBitmap(460 - 16, 20, 16, 16, wifi_icon); // Adjust RIGHT manually for 480 width
}

void resetScreen() {
  myGLCD.clrScr();
  myGLCD.fillScr(255, 255, 255);           // White background
  myGLCD.setColor(0, 0, 0);                // Text color: black
  myGLCD.setBackColor(255, 255, 255);      // Match background
}

void setup() {
  Serial.begin(9600);
  myGLCD.InitLCD(0);
  resetScreen();

  // Welcome Screen
  drawHeader();
  myGLCD.setFont(BigFont);
  myGLCD.print("Welcome Jane", CENTER, 150);
  myGLCD.print("First, a few questions", CENTER, 170);
  myGLCD.print("will be asked to", CENTER, 190);
  myGLCD.print("confirm background.", CENTER, 210);
  delay(2000);
}

void loop() {
  // Simulated progression through screens — in practice, use button input to trigger these

  // Question 1: Age
  resetScreen();
  drawHeader();
  myGLCD.setFont(BigFont);
  myGLCD.print("How old are you?", CENTER, 150);
  myGLCD.print("Please answer using number keypad.", CENTER, 190);
  myGLCD.print("Press Y to confirm.", CENTER, 210);

  delay(2000); // Wait for demonstration

  // Question 2: Gender
  resetScreen();
  drawHeader();
  myGLCD.setFont(BigFont);
  myGLCD.print("What gender were you", CENTER, 150);
  myGLCD.print("assigned at birth?", CENTER, 170);
  myGLCD.print("Select 'M' for male and 'F' for female.", CENTER, 210);
  myGLCD.print("Press Y to confirm.", CENTER, 230);

  delay(2000);

  // Sample Collection Instructions
  resetScreen();
  drawHeader();
  myGLCD.setFont(BigFont);
  myGLCD.print("Please clean finger tip and", CENTER, 150);
  myGLCD.print("then use sterile lancet.", CENTER, 170);
  myGLCD.print("Transfer blood to cartridge", CENTER, 190);
  myGLCD.print("then insert into device slot.", CENTER, 210);

  delay(2000);

  // Calculating Screen
  resetScreen();
  drawHeader();
  myGLCD.setFont(BigFont);
  myGLCD.print("Please wait while eGFR", CENTER, 150);
  myGLCD.print("is being calculated.", CENTER, 170);

  delay(2000);

  // Delivering eGFR
  resetScreen();
  drawHeader();

  myGLCD.setFont(BigFont);
  myGLCD.print("eGFR:", LEFT, 150);

  myGLCD.setFont(SevenSegNumFont);
  myGLCD.print("34", LEFT + 100, 180);

  myGLCD.setFont(BigFont);
  myGLCD.print("Sending eGFR", CENTER, 300);
  myGLCD.print("to Provider ...", CENTER, 320);
  myGLCD.print("Select 'Y'", CENTER, 350);
  myGLCD.print("to Confirm", CENTER, 370);

  while (1); // Stop loop from repeating
}
