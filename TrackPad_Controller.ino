#include "Keyboard.h"
#include <ps2.h>
#define PS2_DATA 10
#define PS2_CLK 9
#define POSITIVE_THRESHOLD 10
#define NEGATIVE_THRESHOLD -10
#define PS2_RESET_CODE 0xff
#define PS2_REMOTE_MODE 0xf0
#define PS2_DATA_ACTIVATED 0xeb
#define DELAY_PRESS_BUTTON 100
byte mx;
byte mz;
uint16_t msval[3];
uint16_t repeatCnt;

PS2 mouse(PS2_CLK, PS2_DATA); //Pin 10 is the mouse data & pin 9 is the clock.

void mouse_init(PS2 *mouse)
{
  mouse->write(PS2_RESET_CODE);  // reset
  mouse->read();  // ack byte
  mouse->read();  // blank */
  mouse->read();  // blank */
  mouse->write(PS2_REMOTE_MODE);  // remote mode
  mouse->read();  // ack
  delayMicroseconds(100);
}

void setup() {
  Serial.begin(9600);
  Keyboard.begin(); // Enable access to keyboard
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Initialisation...");

  mouse_init(&mouse);
  Serial.println("Setup done");
}

void loop() {
  char mstat;
  char mx;
  char my;
  delay(10);
  /* get a reading from the mouse */
  mouse.write(PS2_DATA_ACTIVATED);  // give me data!
  mouse.read();      // ignore ack
  mstat = mouse.read();
  mx = mouse.read();

  if (mx > POSITIVE_THRESHOLD) {
    int presses = Keyboard.press(KEY_RIGHT_ARROW); // create keyboard event and return all current event 
    delay(DELAY_PRESS_BUTTON);
    if (presses > 1) {
      Keyboard.releaseAll(); // release multplie keyboard event 
    }
  } else if (mx < NEGATIVE_THRESHOLD) {
    int presses = Keyboard.press(KEY_LEFT_ARROW);
    delay(DELAY_PRESS_BUTTON);
    if (presses > 1) {
      Keyboard.releaseAll();
    }
  }

  Keyboard.releaseAll();
}
