/************************************************************************************************************************************
 * ShiftPWM blocking RGB fades example, (c) Elco Jacobs, updated August 2012.
 *
 * ShiftPWM blocking RGB fades example. This example uses simple delay loops to create fades.
 * If you want to change the fading mode based on inputs (sensors, buttons, serial), use the non-blocking example as a starting point.
 * Please go to www.elcojacobs.com/shiftpwm for documentation, fuction reference and schematics.
 * If you want to use ShiftPWM with LED strips or high power LED's, visit the shop for boards.
 ************************************************************************************************************************************/
 

// This is the setup for the layers control
// You set the number of layers and the first controler pin, the others are following it
// BE CAREFULL and make sure all the pins are avaible
const char nbr_layers = 4;
const char layer_1_pin = 3;


// This potentiometer allows us to manually control the max intensity
// It must be plugged to an analog input
// For the change to be effective you need to reset the board
int potentiometer_pin = A5;

// ShiftPWM uses timer1 by default. To use a different timer, before '#include <ShiftPWM.h>', add
#define SHIFTPWM_USE_TIMER2  // for Arduino Uno and earlier (Atmega328)
// #define SHIFTPWM_USE_TIMER3  // for Arduino Micro/Leonardo (Atmega32u4)

// Clock and data pins are pins from the hardware SPI, you cannot choose them yourself if you use the hardware SPI.
// Data pin is MOSI (Uno and earlier: 11, Leonardo: ICSP 4, Mega: 51, Teensy 2.0: 2, Teensy 2.0++: 22) 
// Clock pin is SCK (Uno and earlier: 13, Leonardo: ICSP 3, Mega: 52, Teensy 2.0: 1, Teensy 2.0++: 21)

// You can choose the latch pin yourself.
const int ShiftPWM_latchPin=1;

// ** uncomment this part to NOT use the SPI port and change the pin numbers. This is 2.5x slower **
#define SHIFTPWM_NOSPI
const int ShiftPWM_dataPin = 0;
const int ShiftPWM_clockPin = 2;


// If your LED's turn on if the pin is low, set this to true, otherwise set it to false.
const bool ShiftPWM_invertOutputs = true; 

// If your layers controllers turn on if the pin is low, set this to true, otherwise set it to false.
const bool ShiftPWM_invertLayersCtrl = false; 

// You can enable the option below to shift the PWM phase of each shift register by 8 compared to the previous.
// This will slightly increase the interrupt load, but will prevent all PWM signals from becoming high at the same time.
// This will be a bit easier on your power supply, because the current peaks are distributed.
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!

// Here you set the number of brightness levels, the update frequency and the number of shift registers.
// These values affect the load of ShiftPWM.
// Choose them wisely and use the PrintInterruptLoad() function to verify your load.
// There is a calculator on my website to estimate the load.

unsigned char maxBrigthness = 255;
unsigned char pwmFrequency = 75;
int numRegisters = 1;
int numRGBleds = numRegisters*8/3;

void setup(){
  // Serial.begin(9600);

  // Sets the number of 8-bit registers that are used.
  ShiftPWM.SetAmountOfRegisters(numRegisters);


     ShiftPWM.Start(pwmFrequency,maxBrigthness,potentiometer_pin);

     for(int l=0; l<nbr_layers;l++){
    pinMode(layer_1_pin+l,OUTPUT);
    digitalWrite(layer_1_pin+l,HIGH);
  }


     ShiftPWM.SetAll(0);

   }



   void loop(){

    ShiftPWM.SetRGB(0,255,255,255);

    for(char l=0; l<nbr_layers;l++){
    digitalWrite(layer_1_pin+l,HIGH);
  }
  digitalWrite(layer_1_pin,LOW);

  }



// NEED TO MOVE THEM TO LIB !!

  void SetLayers(){
  for(int l=0; l<nbr_layers;l++){
    pinMode(layer_1_pin+l,OUTPUT);
    digitalWrite(layer_1_pin+l,LOW);
  }
}



void UseLayer(char layer){
  if(ShiftPWM_invertLayersCtrl){
  for(char l=0; l<nbr_layers;l++){
    digitalWrite(layer_1_pin+l,HIGH);
  }
  digitalWrite(layer,LOW);
}
    else{
  for(char l=0; l<nbr_layers;l++){
    digitalWrite(layer_1_pin+l,LOW);
  }
  digitalWrite(layer,HIGH);
}
}