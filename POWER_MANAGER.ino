#include "PINS.h"
#include "FLUX_MANAGER.h"
#include "POWER_MANAGER.h"


void gestionePower(bool)
{
  if (digitalRead(START_STOP_BTN_PIN) == 0 && digitalRead(FLUX_ENABLER_SWITCH_PIN) != 0 && powerMode == 0)
  {
    powerMode = 1; //lo stato del sistema diventa attivo se era disattivo, se viene premutlo lo S&S btn e se l'enable è disattivato
  }
  else if (digitalRead(START_STOP_BTN_PIN) == 0 && digitalRead(FLUX_ENABLER_SWITCH_PIN) !=0 && powerMode == 1)
  {
    powerMode = 0; //lo stato del sistema diventa disattivo se era attivo, se viene premutlo lo S&S btn e se l'enable è disattivato
  }
}

void gestioneIlluminazione(bool)
{
if (powerMode == 0)
  {
    digitalWrite(ILLUMINATION_RELAY_PIN, LOW);
  }
  else
  {
    digitalWrite(ILLUMINATION_RELAY_PIN, HIGH);
  }
}