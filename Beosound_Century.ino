#include <LiquidCrystal_I2C.h>
#include <SimpleRotary.h>

#include "Events.h"
#include "FeedbackController.h"
#include "VolumeController.h"
#include "ButtonController.h"
#include "RadioController.h"
#include "MenuController.h"

///////////////////////////////////
//////// LCD STUFF    /////////////
///////////////////////////////////

//LiquidCrystal_I2C lcd(0x27,16,2); /// address, cols, rows
LiquidCrystal_I2C* lcd = new LiquidCrystal_I2C(0x27,16,2); /// address, cols, rows

FeedbackController feedbackController(lcd);

Menu menu;

PlayerState playerState(&feedbackController, &menu);

///////////////////////////////////
//////// INPUT STUFF  /////////////
///////////////////////////////////

event buttons[6] = {
  mode_cd,
  mode_radio,
  mode_aux,
  mode_tape,
  open_cd,
  power
};

// Pin A, Pin B, Button Pin
SimpleRotary rotaryEncoderVolume(A1,A0,A2);
SimpleRotary rotaryEncoderMenu(11,12,A3);
SimpleRotary rotaryEncoderRadio(8,9,10);

VolumeController  volumeController(&playerState, &rotaryEncoderVolume);
MenuController    menuController(&playerState, &rotaryEncoderMenu);
RadioController   radioController(&playerState, &rotaryEncoderRadio);
ButtonController  buttonController(&playerState, buttons);

unsigned long currentMillis;

void setup() {
  Serial.begin(9600);
  Serial.println("Sketch start.");
  feedbackController.initialise();
  buttonController.initialise();
}

void loop() {
  currentMillis = millis();
  
  volumeController.listenForEvent();
  buttonController.listenForEvent();
  radioController.listenForEvent();
  menuController.listenForEvent();
  feedbackController.updateFeedback(currentMillis);
}
