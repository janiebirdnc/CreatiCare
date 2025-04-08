#include <UTFT.h>
#include <Keypad.h>

//Initialize Keypad
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'M'},
  {'4', '5', '6', 'F'},
  {'7', '8', '9', 'Y'},
  {'#', '0', '*', 'N'} // Assuming '*' as the "Enter" button
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//Set up LCD screen + displays

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

UTFT myGLCD(CTE40, 38, 39, 40, 41); // TFT Display

void drawHeader() { // Draw header (time, date)
  myGLCD.setFont(SmallFont);
  myGLCD.print("8:46 A.M.", CENTER, 20);
  myGLCD.print("03/27/2025", 20, 20);
}

void welcomeScreen(){// Welcome Screen
  drawHeader();
  myGLCD.setFont(BigFont);
  myGLCD.print("Welcome User", CENTER, 150);
  myGLCD.print("A few questions", CENTER, 170);
  myGLCD.print("will be asked to", CENTER, 190);
  myGLCD.print("confirm background.", CENTER, 210);
  myGLCD.print("Select checkmark", CENTER, 250);
  myGLCD.print("to continue.", CENTER, 270);
}

void ageScreen() { // ask for age
  resetScreen();
  drawHeader();
  myGLCD.setFont(BigFont);
  myGLCD.print("How old are you?", CENTER, 150);
  myGLCD.print("Please answer", CENTER, 170);
  myGLCD.print("using keypad.", CENTER, 190);

  myGLCD.setFont(SmallFont);
  myGLCD.print("Select checkmark to continue", CENTER, 290);
  myGLCD.print("Select X to clear response", CENTER, 310);
  
}

void genderScreen() { // ask for gender
  resetScreen();
  drawHeader();
  myGLCD.setFont(BigFont);
  myGLCD.print("What was", CENTER, 130);
  myGLCD.print("your assigned", CENTER, 150);
  myGLCD.print("gender at birth?", CENTER, 170);
  myGLCD.print("Select M for Male", CENTER, 200);
  myGLCD.print("or F for Female", CENTER, 220);

  myGLCD.setFont(SmallFont);
  myGLCD.print("Select checkmark to continue", CENTER, 290);
  myGLCD.print("Select X to clear response", CENTER, 310);
}

void raceScreen() {
  resetScreen();
  drawHeader();
  myGLCD.setFont(BigFont);
  myGLCD.print("Are you Black or", CENTER, 150);
  myGLCD.print("African-American?", CENTER, 170);
  myGLCD.print("Select Y for Yes", CENTER, 200);
  myGLCD.print("or N for No", CENTER, 220);

  myGLCD.setFont(SmallFont);
  myGLCD.print("Select checkmark to continue", CENTER, 290);
  myGLCD.print("Select X to clear response", CENTER, 310);
}

void sampleCollectionScreen() {
  resetScreen();
  drawHeader();
  myGLCD.setFont(BigFont);

  myGLCD.print("Clean fingertip", CENTER, 120);
  myGLCD.print("with alcohol pad.", CENTER, 140);
  myGLCD.print("Use sterile lancet", CENTER, 170);
  myGLCD.print("to collect a drop.", CENTER, 190);
  myGLCD.print("Place blood in", CENTER, 220);
  myGLCD.print("cartridge", CENTER, 240);
  myGLCD.print("and insert.", CENTER, 260);

  myGLCD.setFont(SmallFont);
  myGLCD.print("Press checkmark to", CENTER, 280);
  myGLCD.print("continue when finished", CENTER, 290);

  // Wait for '*' to continue
  char customKey;
  while (true) {
    customKey = customKeypad.getKey();
    if (customKey == '*') {
      break;
    }
  }
}

void calculatingEGFRScreen() {
  resetScreen();
  drawHeader();
  myGLCD.setFont(BigFont);

  myGLCD.print("Please wait", CENTER, 150);
  myGLCD.print("while eGFR", CENTER, 170);
  myGLCD.print("is being", CENTER, 190);
  myGLCD.print("calculated.", CENTER, 210);

  delay(3000); // Simulate 3 second calculation time
} 

void deliverEGFRScreen(float egfr) {
  resetScreen();
  drawHeader();

  myGLCD.setFont(BigFont);
  myGLCD.print("eGFR:", LEFT, 150);

  myGLCD.setFont(SevenSegNumFont);
  myGLCD.print(String(egfr, 0), LEFT + 100, 180); // no decimals

  myGLCD.setFont(BigFont);
  myGLCD.print("Sending eGFR", CENTER, 300);
  myGLCD.print("to Provider ...", CENTER, 320);
  myGLCD.print("Select checkmark", CENTER, 350);
  myGLCD.print("to confirm", CENTER, 370);

  // Wait for 'Y' to confirm
  char customKey;
  while (true) {
    customKey = customKeypad.getKey();
    if (customKey == '*') {
      break;
    }
  }

  // Optional: Show a final confirmation or reset
  myGLCD.fillScr(255, 255, 255);
  myGLCD.setColor(0, 0, 0);
  myGLCD.setFont(BigFont);
  myGLCD.print("eGFR Sent!", CENTER, 160);
}


void displayAgeInput(int age) {
  myGLCD.setColor(255, 255, 255); // White background
  myGLCD.fillRect(0, 230, 200, 280); // Clear only the age display area

  myGLCD.setColor(0, 0, 0); // Black text
  myGLCD.setFont(BigFont);
  String ageStr = String(age);
  myGLCD.print(ageStr, CENTER, 230);
}

void displayString(String entString) {
  myGLCD.setColor(255, 255, 255); // White background
  myGLCD.fillRect(0, 240, 319, 280); // Clear previous display area

  myGLCD.setColor(0, 0, 0); // Black text
  myGLCD.setFont(BigFont);
  myGLCD.print(entString, CENTER, 250);
}

void resetScreen() {
  myGLCD.clrScr();
  myGLCD.fillScr(255, 255, 255);           // White background
  myGLCD.setColor(0, 0, 0);                // Text color: black
  myGLCD.setBackColor(255, 255, 255);      // Match background
}

// Screen Logic
void waitForContinue() {
  char customKey = NO_KEY;

  while (true){
    customKey = customKeypad.getKey();
    if (customKey == '*') {
      break;
    }
  }
}

// Store Variables
int enteredAge = 0; // Variable to store age
String enteredGender = ""; // Variable to store gender
String enteredEthnicity = ""; // Variable to store ethnicity

bool ageEntered = false;
bool genderEntered = false;

void resetInputs() { // Function to reset variables
  enteredAge = 0;
  enteredGender = "";
  enteredEthnicity = "";
  ageEntered = false;
  genderEntered = false;
}

bool askAge() {
  resetInputs();
  ageScreen();
  enteredAge = 0;

  char customKey;
  while (true) {
    customKey = customKeypad.getKey();

    if (customKey != NO_KEY) {
      if (isDigit(customKey)) {
        if (enteredAge < 1000) {
          enteredAge = enteredAge * 10 + (customKey - '0');
          displayAgeInput(enteredAge);
        }
      } else if (customKey == '#') { // 'X' clear
        enteredAge = 0;
        displayAgeInput(enteredAge);
      } else if (customKey == '*') { // Confirm
        if (enteredAge > 0) {
          return true;
        }
      }
    }
  }
}

bool askGender() {
  enteredGender = "";
  genderScreen();

  String genderSelection = "";
  char customKey;

  while (true) {
    customKey = customKeypad.getKey();

    if (customKey == 'F') {
      genderSelection = "Female";
      displayString(genderSelection);
    } else if (customKey == 'M') {
      genderSelection = "Male";
      displayString(genderSelection);
    } else if (customKey == '#') {
      genderSelection = "";
      displayString("");
    } else if (customKey == '*' && genderSelection != "") {
      enteredGender = genderSelection;
      return true;
    }
  }
}

bool askRace() {
  enteredEthnicity = "";
  raceScreen();

  String raceSelection = "";
  char customKey;

  while (true) {
    customKey = customKeypad.getKey();
    if (customKey == 'N') {
      raceSelection = "Not Black";
      displayString("No");
    } else if (customKey == 'Y') {
      raceSelection = "Black";
      displayString("Yes");
    } else if (customKey == '#') {
      raceSelection = "";
      displayString("");
    } else if (customKey == '*' && raceSelection != "") {
      enteredEthnicity = raceSelection;
      return true;
    }
  }
}


//Store eGFR Equations
float calculate_BSA(int age, float height, float weight) {
  // Calculate body surface area using Du Bois formula
  float BSA = 0.007184 * pow(height, 0.725) * pow(weight, 0.425);
  return BSA;
}

float calculate_eGFR(int age, String gender, String ethnicity, float Scr) {
  const float k = gender.equals("Female") ? 0.7 : 0.9;
  const float a = gender.equals("Black") ? 1.159 : 1.0;

  float eGFR = 141 * pow(min(Scr / k, 1), a) * pow(max(Scr / k, 1), -1.209) * pow(0.993, age);

  return eGFR;
}

void setup() {
  Serial.begin(9600);
  myGLCD.InitLCD(0);
  resetScreen();

  welcomeScreen();
  waitForContinue();
}

void loop() {
  if (askAge()) {
    if (askGender()) {
      if (askRace()){
        sampleCollectionScreen();
        calculatingEGFRScreen();

        // Generate fake creatinine
        float Scr = (enteredGender == "Female") ? random(5, 11) / 10.0 : random(7, 13) / 10.0;
        float egfr = calculate_eGFR(enteredAge, enteredGender, enteredEthnicity, Scr);

        deliverEGFRScreen(egfr);

        // Optionally stop or reset:
        while (1); // stop repeating
      }
    }
  }
  

}
