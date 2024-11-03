/*
Schreiben Sie ein C-Programm, das mittels des fork()-Systemaufrufs einen weiteren identi-
schen Prozess startet. Beide Prozesse sollen dann ihre Prozessnummer sowie die
Prozessnummer des Vaterprozesses ausgeben (getpid()- bzw. getppid()-
Systemaufrufe) und darauf in eine Endlosschleife laufen.
Starten Sie Ihr Programm im Hintergrund und beobachten Sie den Prozesszustand mit dem
ps-Kommando über die Kommando-Shell.
Beenden Sie dann die Prozesse mit dem kill-Kommando (kill -9 <pid>) von der
Shell aus, wobei Sie nach Beendigung des ersten Prozesses wiederum den Prozesszustand mit
ps beobachten.
Wiederholen Sie den Ablauf nochmals, wobei Sie nun die beiden Prozesse in umgekehrter
Reihenfolge beenden
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	
	printf("This solution was created by Rinaldo Schuster\n");

	// create child process
	int p_id = fork();

	// check if fork failed
	if (p_id < 0){
		printf("Creating child process failed, aborting execution...\n");
		return EXIT_FAILURE; // EXIT_FAILURE or 1, does not matter
	}
	else if (p_id == 0){ // code for child process
		while(1){
			printf("I am the child process with PID = %d and PPID = %d\n", getpid(), getppid());
			sleep(1);
		}
	}
	else{ // code for parent process
		while(1){
			printf("I am the father process with PID = %d and PPID = %d\n", getpid(), getppid());
			sleep(1);
		}
	}

	return EXIT_SUCCESS;
}
