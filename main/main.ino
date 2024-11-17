#include "PINS.h"
#include "STATUS.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // inizializza la linea seriale

  //inputs
  pinMode(POTI_PIN, INPUT);
  pinMode(FLUX_ENABLER_SWITCH_PIN, INPUT); //enable switch
  pinMode(START_STOP_BTN_PIN, INPUT_PULLUP); //lo S&S btn chiude a massa

  //outputs
  pinMode(LIQUID_1_RELAY_PIN, OUTPUT);
  pinMode(LIQUID_2_RELAY_PIN, OUTPUT);
  pinMode(ILLUMINATION_RELAY_PIN, OUTPUT);
  initStateMachine(); // Inizializza la macchina a stati a ON
}

void loop() 
{
  benvenuto();
  runStateMachine();
}
