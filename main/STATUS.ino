#include "STATUS.h"
#include "PINS.h"

unsigned long liquid_1_time = 0;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long lastDebounceTime = 0;

int poti = 0;
int percentage_L2 = 0;
int mappedValue = 0;
int debounceDelaymin = 100; // Tempo massimo di debounce in millisecondi
int debounceDelayMAX = 700; // Tempo massimo di debounce in millisecondi

int buttonState = 1;            // Stato corrente del pulsante
int lastButtonState = 1;   // Stato precedente del pulsante
int minPercentage = 2;     //percentuale minima di alcool

enum state{
    OFF,
    ON,
    EROG_L1,
    EROG_L2
}currentState;

bool pulsantePremuto() {
    bool reading = digitalRead(START_STOP_BTN_PIN); // Leggi il pulsante

    // Controllo il cambiamento nello stato del pulsante
    if (reading != lastButtonState) {
        lastDebounceTime = millis(); // Aggiorna il tempo dell'ultimo cambiamento
    }

    // Se il tempo di debounce è trascorso
    if ((millis() - lastDebounceTime) > debounceDelaymin) {
        // Rileva transizione da HIGH a LOW
        if (reading == LOW && buttonState == HIGH) {
            buttonState = reading; // Aggiorna lo stato
            lastButtonState = reading; // Aggiorna lo stato precedente
            return true; // Rilevata una singola pressione
        }
        buttonState = reading; // Aggiorna lo stato
    }

    lastButtonState = reading; // Aggiorna lo stato precedente
    return false; // Nessuna pressione rilevata
}


void Led_Display_ON(){
  digitalWrite(ILLUMINATION_RELAY_PIN, HIGH); //accendo striscia LED
  //aggiungere accensione illuminazione display
}

void Led_Display_OFF(){
  digitalWrite(ILLUMINATION_RELAY_PIN, LOW); //spengo striscia LED
  //aggiungere spegnimento illuminazione display
}

void initStateMachine(){
  currentState = OFF;
};

int setRelay2Timer(void)
{
  poti = analogRead(POTI_PIN);
  mappedValue = map(poti, 0, 1023, 0, 100);

  return mappedValue;
}//settiamo il timer del rele analcolico come percentuale del tempo di erogazione della bevanda alcolica (Liquid_1)

void runStateMachine()
{
  switch (currentState)
  {

    case OFF: //siamo in ON, possiamo andare all'erogazione di L1 oppure spegnere, dipende dallo stato del selettore

      Led_Display_OFF();
      digitalWrite(LIQUID_1_RELAY_PIN, LOW);
      digitalWrite(LIQUID_2_RELAY_PIN, LOW);

      if (pulsantePremuto())
      {
        currentState = (ON);
        Serial.println("OFF to ON");
      }
    break;

    case ON: //siamo in ON, possiamo andare all'erogazione di L1 oppure spegnere, dipende dallo stato del selettore
      Led_Display_ON();

      if (pulsantePremuto() && digitalRead(FLUX_ENABLER_SWITCH_PIN) == LOW)
      {
        currentState = (OFF);
        Serial.println("ON to OFF");
      }
      else if (pulsantePremuto() && digitalRead(FLUX_ENABLER_SWITCH_PIN) == HIGH)
      {
        currentState = (EROG_L1);
      }
    break;

    case EROG_L1:
      Led_Display_ON();

      // Avvia l'erogazione se il relè non è già acceso
      if (digitalRead(LIQUID_1_RELAY_PIN) == LOW) {
          digitalWrite(LIQUID_1_RELAY_PIN, HIGH);
          currentMillis = millis(); // Salva il tempo iniziale
      }

      // Controlla se il pulsante è premuto per fermare l'erogazione
      if (pulsantePremuto()) {
          digitalWrite(LIQUID_1_RELAY_PIN, LOW);
          liquid_1_time = millis() - currentMillis; // Calcola il tempo di erogazione

          // Debug
          Serial.print("Tempo di erogazione: ");
          Serial.println(liquid_1_time);

          // Passa allo stato successivo
          percentage_L2 = setRelay2Timer();
          currentState = EROG_L2;
      }
    break;


    case EROG_L2:
      Led_Display_ON();

      float tTot = 0;
      if(percentage_L2 > 0)
      {
        tTot = (liquid_1_time * 100) / percentage_L2;

        Serial.print("Tempo di erogazione L1: "); Serial.println(liquid_1_time);
        Serial.print("percentage_L2: "); Serial.println(percentage_L2);
        Serial.print("Tempo di erogazione L2: "); Serial.println(tTot-liquid_1_time);
        digitalWrite(LIQUID_2_RELAY_PIN, HIGH);
        delay(round(tTot)-liquid_1_time);
        digitalWrite(LIQUID_2_RELAY_PIN, LOW);
      }
      else 
      {
        Serial.println("Errore: percentage_L2 è 0!");
      }
      currentState = (ON);
    break;
  }
}
