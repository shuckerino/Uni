#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


int signalSIGTERM; // zählt die Anzahl der eingegangenen SIGTERM-Signale
int signalSIGINT; // zählt die Anzahl der eingegangenen SIGINT-Signale

// Signal-Handler für das SIGTERM-Signal
void sigtermhandler(int sig) {
    printf("Diese Loesung wurde erstellt von Lukas Scheler \n");
    signalSIGTERM = signalSIGTERM + 1; 
    if(signalSIGTERM == 3) { 
        printf("Beendet durch 3 SIGTERM \n\n"); 
        exit(5);
    }
}

// Signal-Handler für das SIGINT-Signal
void siginthandler(int sig) {
    printf("Ein SIGINT Signal ist eingegangen mit: %d \n", sig); 
    signalSIGINT = signalSIGINT + 1; 
    if(signalSIGINT == 3) { 
        printf("Beendet durch 3 SIGTERM \n\n"); 
        exit(5); 
    }
}

int main() {
	printf("Diese Lösung wurde erstellt von Lukas Scheler \n");
    // Hier werden die Signal-Handler für SIGINT und SIGTERM gesetzt
    signal(SIGINT, siginthandler);
    signal(SIGTERM, sigtermhandler);
    printf("Das Programm ist gestartet \n");

    while(1) {
    }   
}
