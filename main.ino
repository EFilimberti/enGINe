#include "PINS.h"
#include "FLUX_MANAGER.h"
#include "POWER_MANAGER.h"

unsigned long previousMillis = 0;


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
  // Esecuzione di gestionePower e gestioneIlluminazione
  powerMode = gestionePower(powerMode);
  gestioneIlluminazione(powerMode);

/* debug per start&stop e stato sistema
  unsigned long currentMillis = millis(); // Ottieni il tempo corrente

  if (currentMillis - previousMillis >= 500) 
  {
      previousMillis = currentMillis; // Salva il tempo attuale

      // Stampa i valori di debug
      Serial.print("S_S_BTN:");
      Serial.println(digitalRead(START_STOP_BTN_PIN));
  }

*/
  // Altri controlli e funzioni
  getLiquidSelectorStatus();
  setRelayTimer();

  //secureFlowCheck(powerMode, getFluxEnablerStatus()); //trovare l'errore
  versaPozione(secureFlow, mappedValueTonica, mappedValueGin);
}
