/*
 Entwickeln Sie ein C-Programm, das auf die Signale SIGTERM und SIGINT reagiert. Das Programm soll nach dem Start eine Meldung auf stdout ausgeben, dass es gestartet wurde und wie es sich verhält, d.h. auf welche Signale es wie reagiert. Danach soll das Programm in einer Endlosschleife laufen. Das Programm soll bei Eintreffen eines der Signale SIGTERM oder SIGINT auf der Konsole ausgeben, dass das entsprechende Signal eingetroffen ist. Nachdem das dritte Mal ein Signal SIGTERM oder SIGINT eingetroffen ist, soll sich das Programm selbst beenden und als Endestatus den Wert 5 zurück geben.
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/signal.h>

int signal_counter = 0;

void sigint_handler(){
	// use write instead of print, because printf is not async safe
	printf("Reacting to received SIGINT!\n");
	signal_counter++;
	return;
}

void sigterm_handler(){
	printf("Reacting to received SIGTERM!\n");
	signal_counter++;
	return;
}

int main(){

	printf("Program got started!\n");
	
	// using sigaction is actually preferred
	signal(SIGINT, sigint_handler);
	signal(SIGTERM, sigterm_handler);


	while(1){
		sleep(1);
		if (signal_counter == 3){
			printf("Received 3 signals, now truly aborting this program!\n");
			return 5;
		}
		printf("Doing nothing...PID is %d\n", getpid());
	}

	return 0;
}
