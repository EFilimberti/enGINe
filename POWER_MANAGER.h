#ifndef POWER_MANAGER
#define POWER_MANAGER

bool powerMode = 0; //stato corrente del sistema (sleep o attivo)

void gestionePower(bool); //funzione che gestisce lo stato del sistema

void gestioneIlluminazione(bool); //funzione che gestisce l'attivazione dei led

#endif