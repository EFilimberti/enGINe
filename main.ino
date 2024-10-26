#include "PINS.h"
#include "FLUX_MANAGER.h"
#include "POWER_MANAGER.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // inizializza la linea seriale

  //inputs
  pinMode(DEBUG_POTI_PIN, INPUT);
  pinMode(FLUX_ENABLER_SWITCH_PIN, INPUT_PULLUP); //enable switch chiude a massa
  pinMode(START_STOP_BTN_PIN, INPUT_PULLUP); //lo S&S btn chiude a massa
  pinMode(LIQUID_SELECTOR_PIN, INPUT_PULLUP); //il selettore di bevanda per la selezione dei timer chiude a massa

  //outputs
  pinMode(GIN_RELAY_PIN, OUTPUT);
  pinMode(TONIC_RELAY_PIN, OUTPUT);
  pinMode(ILLUMINATION_RELAY_PIN, OUTPUT);

}

void loop() 
{
  // put your main code here, to run repeatedly:

  //Illuminazione e stato sistema
  void gestionePower();
  void gestioneIlluminazione();


  //Impostazione timer relay GIN e TONICA
  bool getLiquidSelectorStatus();
  int setRelayTimer();
  
  //Check permesso flusso e rilascio pozione
  bool getFluxEnablerStatus();
  void secureFlowCheck();
  void versaPozione();
}