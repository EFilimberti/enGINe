#ifndef FLUX_MANAGER
#define FLUX_MANAGER

int poti = 0; //posizione del potenziometro, da 0 a 1023
bool liquidSelector = 1; //1 GIN, 0 TONICA
bool secureFlow = 0; // solo se secureFlow è a 1 è possibile versare la pozione

int ginTimer = 2000; //timer del gin di default 2s
int tonicaTimer = 6000; //timer del gin di default 6s

unsigned long mappedValueGin = 0; //variabile usata per mappare la posizione del poti nel tempo (per il gin --> 0->5s)
unsigned long mappedValueTonica = 0; //variabile usata per mappare la posizione del poti nel tempo (per la Tonica --> 0->15s) Teniamo 1/3 come rapporto gin tonica

bool getFluxEnablerStatus(void); //leggiamo lo stato del (secondo) enable di flusso

bool getLiquidSelectorStatus(void); //leggiamo l'impostazione del selettore di bevanda (se GIN o TONICA)

int setRelayTimer(void); //funzione che setta il timer dei relay di GIN e Tonica in funzione della posizione del poti

void secureFlowCheck(bool,bool); //permette il flusso solo se lo stato del sistema è attivo e se lo switch enable è attivato

void versaPozione(bool, unsigned long, unsigned long); //funzione che versa GIN e Tonica se secureFlowCheck ok


#endif