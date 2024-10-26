#include "PINS.h"
#include "FLUX_MANAGER.h"
#include "POWER_MANAGER.h"

bool getFluxEnablerStatus(void) 
{
  if (digitalRead(FLUX_ENABLER_SWITCH_PIN) == LOW)
  {
    return 1;  //flusso bloccato
  }
    else 
  {
    return 0;  //flusso concesso
  }
} //leggiamo lo stato del (secondo) enable di flusso

bool getLiquidSelectorStatus(void) 
{
    if (digitalRead(LIQUID_SELECTOR_PIN) == LOW)
    {
      return 1;  //selettore su GIN
    }
    else 
    {
      return 0;  //selettore su Tonica
    }
} //leggiamo l'impostazione del selettore di bevanda (se GIN o TONICA)

int setRelayTimer(void)
{
  poti = analogRead(DEBUG_POTI_PIN);

  if (getLiquidSelectorStatus == 1)
  {
    mappedValueGin = map(poti, 0, 1023, 0, 5000);
  }
  else 
  {
    mappedValueTonica = map(poti, 0, 1023, 0, 15000);
  }
}//settiamo i timer dei rele in base alla posizione del potenziometro e della bevanda selezionata dal selettore

void secureFlowCheck (bool powerMode, bool getFluxEnablerStatus()){
  if (powerMode == 1 && getFluxEnablerStatus()==0)
  {
    secureFlow = 1;
  }
  else
  {
    secureFlow = 0;
  }
} //permette il flusso solo se lo stato del sistema è attivo e se lo switch enable è attivato


void versaPozione(bool secureFlow, unsigned long mappedValueTonica, unsigned long mappedValueGin){
  if(secureFlow == 1 && (digitalRead(START_STOP_BTN_PIN) == LOW))
  {
    digitalWrite(GIN_RELAY_PIN, HIGH);
    delay(mappedValueGin);

    digitalWrite(TONIC_RELAY_PIN, HIGH);
    delay(mappedValueTonica);
  }
  else
  {
    digitalWrite(GIN_RELAY_PIN, LOW);
    delay(1000);

    digitalWrite(TONIC_RELAY_PIN, LOW);
    delay(1000);
  }
}