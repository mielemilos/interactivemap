//**************************************************************//
//  Name    : PoliceMap                                         //
//  Author  : Michiel Bodewes                                   //
//  Date    : 25 Oct, 2013                                      //
//  Version : 1.0                                               //
//  Notes   : A interactive police map                          //
//****************************************************************
// Used code examples from: shiftout, lcd, button and more

//////////////////////////////////////////////////////////////////
//  Libs
//////////////////////////////////////////////////////////////////
#include <LiquidCrystal.h>
#include "Button.h"
#include "Leds.h"

#include "MainState.h"
#include "PMController.h"

#include <avr/pgmspace.h>

const String _VERSION_ = "1.4";


//////////////////////////////////////////////////////////////////
//  Pin definitions                                             //
//////////////////////////////////////////////////////////////////

// free: none


// buttons
//const int buttons_pin1 = 16;    // Pushbutton pin a2
Button button1(16);
//const int buttons_pin2 = 14;    // Pushbutton pin a0
Button button2(14);
//const int buttons_pin3 = 15;    // Pushbutton pin a1
Button button3(15);
//const int buttons_pin4 = 9;     // Pushbutton pin 4
Button button4(9);

// speaker
const int speaker_pin = 10;

// lcdbuttons
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


// lights
Leds leds(5, 11, 12, 8);

// the controller
PMController pm_controller(4, &leds, &lcd, speaker_pin);

//////////////////////////////////////////////////////////////////
//  Variables
//////////////////////////////////////////////////////////////////

bool _isFirst = true;



void handle_buttons() {
  // update the state the buttons
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  
  // update button states
  pm_controller.setButton(0, button1.getState());
  pm_controller.setButton(1, button2.getState());
  pm_controller.setButton(2, button3.getState());
  pm_controller.setButton(3, button4.getState());
}

void print_init_text() {
  lcd.print(F("Police Map"));
  lcd.setCursor(0,1);
  lcd.print(F("Version: "));
  lcd.print(_VERSION_);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Hallo Teije"));

  delay(1000);

  lcd.setCursor(0,1);
  lcd.print(F("Hallo Wester")); 
}

// simple softreset by triggering the watchdog timer at 0
void softReset() {
  asm volatile ("  jmp 0");
}

// init the timer
void init_timer() {
  //timer
  cli();          // disable global interrupts
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B

  OCR1A = 15624/10;         // set compare match register to desired timer count:
  TCCR1B |= (1 << WGM12);   // turn on CTC mode:
  TCCR1B |= (1 << CS10);    // Set CS10 and CS12 bits for 1024 prescaler:
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt:
  sei();                    // enable global interrupts

}

// timer callback
ISR(TIMER1_COMPA_vect) {
 
}


////////////////////////////////////////////////////////////////////////
// Ardiuno setup and loop                                             //
////////////////////////////////////////////////////////////////////////

void setup() {
  // lcd
  lcd.begin(16, 2);
  // buttons
  pinMode(button1.getButtonPin(), INPUT);
  pinMode(button2.getButtonPin(), INPUT);
  pinMode(button3.getButtonPin(), INPUT);
  pinMode(button4.getButtonPin(), INPUT);
  // Leds
  leds.addPinLed(13); // add pin leds 13 to leds
  leds.init();
  
}

void loop() {
  if (_isFirst) {
    print_init_text();
    _isFirst = false;
  }

  handle_buttons();

  // check if reset was called: (long) hold buttons 1, 3 and 4 ;)
  if (button1.getState() == Button::BUTTON_STATE_HOLD_LONG && button2.getState()  == Button::BUTTON_STATE_HOLD_LONG && button4.getState() == Button::BUTTON_STATE_HOLD_LONG) {
    lcd.clear();
    lcd.print(F("  ## reset ##"));
    delay(1000);
    softReset();
    return;
  }

  pm_controller.doLoop();
}

