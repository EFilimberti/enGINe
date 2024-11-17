#ifndef STATUS
#define STATUS

#include "PINS.h"

void initStateMachine(); // Inizializza la macchina a stati
void runStateMachine();  // Esegue la macchina a stati
bool pulsantePremuto();

#define extern unsigned long liquid_1_time
#define extern unsigned long currentMillis
#define extern unsigned long previousMillis
#define extern int mappedValue
#define extern int poti
#define extern int percentage_L2
#define extern int debounceDelayminPercentage
#define extern int minPercentage
#define extern unsigned long lastDebounceTime

#define extern int buttonState    // Stato corrente del pulsante
#define extern int lastButtonState  // Stato precedente del pulsante

#endif
