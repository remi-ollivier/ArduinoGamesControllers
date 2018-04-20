#include <Keypad.h>
#include <Keyboard.h>

#define ROWS 4 //4 rows
#define COLS 4 //4 columns
#define KEYBOARD_SPACE_BAR 0x20//space bar key

//reference the characters on the keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '4', '7', '*'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '#'},
  {'A', 'B', 'C', 'D'}
};
byte rowPins[ROWS] = {3, 2, 1, 0}; //row pin of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //column pin of the keypad

//Keypad initialization, customKeypad will be used to get keypad's events
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//init method
void setup() {
  Serial.begin(9600);//init Serial to display debug messages
  Keyboard.begin();//init keyboard to send keyboard commands to the computer
  customKeypad.addEventListener(keypadEvent); //add a custom event listener for the keypad
  customKeypad.setDebounceTime(50);//set the long click duration
}

//program loop method
void loop() {
  char key = customKeypad.getKey();//get the pressed key if any, non-blocking method so it can return an empty char
}

//the event listener for the keypad
void keypadEvent(KeypadEvent key) {
  switch (customKeypad.getState()) { //get the state associated to the event
    case PRESSED://if the state is pressed
      switch (key) { //send the correct signal depending on the key pressed
        case '2': //if the key is 2 meaning up
          Serial.println("PRESSED 2");
          Keyboard.press(KEY_UP_ARROW);
          break;
        case '8': //if the key is 8 meaning down
          Serial.println("PRESSED 8");
          Keyboard.press(KEY_DOWN_ARROW);
          break;
        case '4': //if the key is 4 meaning left
          Serial.println("PRESSED 4");
          Keyboard.press(KEY_LEFT_ARROW);
          break;
        case '6': //if the key is 6 meaning right
          Serial.println("PRESSED 6");
          Keyboard.press(KEY_RIGHT_ARROW);
          break;
        case '5': //if the key is 5 meaning action, we send a space bar signal
          Serial.println("PRESSED 5");
          Keyboard.press(KEYBOARD_SPACE_BAR);
          Keyboard.release(KEYBOARD_SPACE_BAR);//release signal after sending it (the action must be sent once)
          break;
      }
      break;
    case HOLD://if the state is hold
      switch (key) {
        case '2':
          Serial.println("Hold 2");
          Keyboard.press(KEY_UP_ARROW);
          break;
        case '8':
          Serial.println("Hold 8");
          Keyboard.press(KEY_DOWN_ARROW);
          break;
        case '4':
          Serial.println("Hold 4");
          Keyboard.press(KEY_LEFT_ARROW);
          break;
        case '6':
          Serial.println("Hold 6");
          Keyboard.press(KEY_RIGHT_ARROW);
          break;
      }
      break;
    case RELEASED://if the state is released
      Serial.println("RELEASED");
      Keyboard.releaseAll();//release all signals
      break;
  }
}


