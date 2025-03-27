#include <Keypad.h>
#include <UTFT.h>
#include <UTFT_SdRaw.h>
#include <SdFat.h>
#include "wifi_icon.h"

// Fonts
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

// LCD Setup
UTFT myGLCD(CTE40, 38, 39, 40, 41);

// Keypad Setup
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '4', '7', '#'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '*'},
  {'A', 'B', 'C', 'D'}  // '*' is Enter, '#' is Clear
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Input variables
int enteredAge = 0;
String enteredGender = "";
String enteredEthnicity = "";

bool ageEntered = false;
bool genderEntered = false;

// Helper Functions
void resetScreen() {
  myGLCD.clrScr();
  myGLCD.fillScr(255, 255, 255);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255, 255, 255);
}

void drawHeader() {
  myGLCD.setFont(SmallFont);
  myGLCD.print("8:46 A.M.", CENTER, 20);
  myGLCD.print("03/27/2025", LEFT, 20);
  myGLCD.drawBitmap(460 - 16, 20, 16, 16, wifi_icon);
}

void showQuestion(String line1, String line2 = "", String line3 = "", String line4 = "") {
  resetScreen();
  drawHeader();
  myGLCD.setFont(BigFont);
  myGLCD.print(line1, CENTER, 150);
  if (line2 != "") myGLCD.print(line2, CENTER, 170);
  if (line3 != "") myGLCD.print(line3, CENTER, 190);
  if (line4 != "") myGLCD.print(line4, CENTER, 210);
}

void resetInputs() {
  enteredAge = 0;
  enteredGender = "";
  enteredEthnicity = "";
  ageEntered = false;
  genderEntered = false;
  showQuestion("How old are you?", "Use number keypad.", "Press * to confirm.");
}

float calculate_eGFR(int age, String gender, String ethnicity, float Scr) {
  const float k = gender.equals("Female") ? 0.7 : 0.9;
  const float a = ethnicity.equals("Yes") ? 1.159 : 1.0;

  float eGFR = 141 * pow(min(Scr / k, 1), a) * pow(max(Scr / k, 1), -1.209) * pow(0.993, age);
  return eGFR;
}

void setup() {
  Serial.begin(9600);
  myGLCD.InitLCD();
  resetInputs();
}

void loop() {
  char customKey = customKeypad.getKey();

  if (!ageEntered) {
    if (customKey != NO_KEY) {
      if (customKey == '*') {
        if (enteredAge > 0) {
          ageEntered = true;
          showQuestion("Gender at birth?", "'1' for Female", "'2' for Male");
        }
      } else if (customKey == '#') {
        enteredAge = 0;
        showQuestion("Cleared. Enter age:");
      } else if (isDigit(customKey)) {
        enteredAge = enteredAge * 10 + (customKey - '0');
        myGLCD.printNumI(enteredAge, CENTER, 270);
      }
    }
  } else if (!genderEntered) {
    if (customKey == '1') {
      enteredGender = "Female";
      genderEntered = true;
      showQuestion("Are you", "African-American?", "'1' for No", "'2' for Yes");
    } else if (customKey == '2') {
      enteredGender = "Male";
      genderEntered = true;
      showQuestion("Are you", "African-American?", "'1' for No", "'2' for Yes");
    }
  } else {
    if (customKey == '1' || customKey == '2') {
      enteredEthnicity = customKey == '1' ? "No" : "Yes";

      float Scr = (enteredGender == "Female") ? random(5, 11) / 10.0 : random(7, 13) / 10.0;
      float eGFR = calculate_eGFR(enteredAge, enteredGender, enteredEthnicity, Scr);

      resetScreen();
      drawHeader();
      myGLCD.setFont(BigFont);
      myGLCD.print("eGFR:", LEFT, 150);
      myGLCD.setFont(SevenSegNumFont);
      myGLCD.printNumF(eGFR, 1, LEFT + 100, 180);
      myGLCD.setFont(BigFont);
      myGLCD.print("Sending eGFR to provider...", CENTER, 300);

      delay(5000);  // Simulate delay
      resetInputs();
    }
  }
}
