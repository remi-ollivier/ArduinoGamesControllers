#include "Keyboard.h"

//joystick pins
#define X_JOYSTICK_AXIS A1 // joystick X axis
#define Y_JOYSTICK_AXIS A2 // joystick Y axis

//joystick const
#define LEFT_THRESHOLD 480 //value to be under to go left
#define LEFT_MAX 15 //value to be under to go left max
#define RIGHT_THRESHOLD 520 //value to be over to go right
#define RIGHT_MAX 980 //value to be over to go right max
#define UP_THRESHOLD 480 //value to be under to go up
#define UP_MAX 15 //value to be under to go up max
#define DOWN_THRESHOLD 520 //value to be over to go down
#define DOWN_MAX 980 //value to be over to go down max
#define KEYBOARD_SPACE_BAR 0x20 //space bar keyboard signal

// voice const
#define VOICE_THRESHOLD 50 //sound level to be over to make the space bar associated action
#define VOICE_SENSOR A0 //voice sensor pin

bool holdVert = false; //var to remember if the joystick is less than 25% in one vertical direction
bool holdHori = false; //var to remember if the joystick is less than 25% in one horizontal direction

//init method
void setup() {
  Keyboard.begin(); //init keyboard to send keyboard's signals to the computer
  Serial.begin(115200); //open serial port for debug
}

//loop method
void loop() {
  int xReading = readAxis(X_JOYSTICK_AXIS); //read horizontal joystick value
  int yReading = readAxis(Y_JOYSTICK_AXIS); //read vertical joystick value
  int voiceReading = readVoiceCapture(VOICE_SENSOR); //read voice sensor value

  //debug prints
  Serial.print("X : ");
  Serial.println(xReading);
  Serial.print("Y : ");
  Serial.println(yReading);

  if (xReading < LEFT_THRESHOLD) { //if the value is left
    if (xReading > LEFT_MAX) { //if the joystick is 25% pushed
      if (holdHori == false) { //if the joystick was not pushed or over 25%
        holdHori = true; //save the 25% state
        Keyboard.press(KEY_LEFT_ARROW); //send left arrow signal to the computer
        delay(100); //delay 100 milliseconds
        Keyboard.release(KEY_LEFT_ARROW); //release left arrow signal
      } else //if the joystick is more than 25% pushed
        Keyboard.release(KEY_LEFT_ARROW); //if the joystick is in 25% and the signal has already been sent
    } else { //if the joystick is more than 25% pushed
      Keyboard.press(KEY_LEFT_ARROW); //send left arrow signal to the computer without releasing it
      holdHori = false; //save that we are not in 25% state
    }
  } else if (xReading > RIGHT_THRESHOLD) { //if the value is right
    if (xReading < RIGHT_MAX) { //if the joystick is 25% pushed
      if (holdHori == false) { //if the joystick was not pushed or over 25%
        holdHori = true; //save the 25% state
        Keyboard.press(KEY_RIGHT_ARROW); //send right arrow signal to the computer
        delay(100); //delay 100 milliseconds
        Keyboard.release(KEY_RIGHT_ARROW); //release right arrow signal
      } else //if the joystick is more than 25% pushed
        Keyboard.release(KEY_RIGHT_ARROW); //if the joystick is in 25% and the signal has already been sent
    } else { //if the joystick is more than 25% pushed
      Keyboard.press(KEY_RIGHT_ARROW); //send right arrow signal to the computer without releasing it
      holdHori = false; //save that we are not in 25% state
    }
  } else { //if the value is middle
    holdHori = false; //save that we are not in 25% state
  }

  if (yReading < UP_THRESHOLD) {
    if (yReading > UP_MAX) { //if the joystick is 25% pushed
      if (holdVert == false) { //if the joystick was not pushed or over 25%
        holdVert = true; //save the 25% state
        Keyboard.press(KEY_UP_ARROW); //send up arrow signal to the computer
        delay(100); //delay 100 milliseconds
        Keyboard.release(KEY_UP_ARROW); //release up arrow signal
      } else //if the joystick is more than 25% pushed
        Keyboard.release(KEY_UP_ARROW); //if the joystick is in 25% and the signal has already been sent
    } else { //if the joystick is more than 25% pushed
      Keyboard.press(KEY_UP_ARROW); //send up arrow signal to the computer without releasing it
      holdVert = false; //save that we are not in 25% state
    }
  } else if (yReading > DOWN_THRESHOLD) {
    if (yReading < DOWN_MAX) { //if the joystick is 25% pushed
      if (holdVert == false) { //if the joystick was not pushed or over 25%
        holdVert = true; //save the 25% state
        Keyboard.press(KEY_DOWN_ARROW); //send down arrow signal to the computer
        delay(100); //delay 100 milliseconds
        Keyboard.release(KEY_DOWN_ARROW); //release down arrow signal
      } else //if the joystick is more than 25% pushed
        Keyboard.release(KEY_DOWN_ARROW); //if the joystick is in 25% and the signal has already been sent
    } else { //if the joystick is more than 25% pushed
      Keyboard.press(KEY_DOWN_ARROW); //send down arrow signal to the computer without releasing it
      holdVert = false; //save that we are not in 25% state
    }
  } else { //if the value is middle
    holdVert = false; //save that we are not in 25% state
  }

  if (voiceReading > VOICE_THRESHOLD) { //if the voice is over the minimum value
    Keyboard.press(KEYBOARD_SPACE_BAR); //send signal to the computer
    Keyboard.releaseAll(); //release keyboard's signals
  }

}

int readAxis(int axisPin) {
  return analogRead(axisPin); //return the value read for the joystick axis
}

int readVoiceCapture(int voicePin) {
  return analogRead(voicePin); //return the value read for the micro sensor
}
