/*
 Entwickeln Sie ein C-Programm "Starten", das einen Kindprozess erzeugt, der dann sofort mit einem exec-Systemaufruf ein komplett anderes Programm P-neu (etwa eine einfache „Hallo Welt!“-Anwendung) ausführt, während der Elternprozess auf das Ende des Kindprozesses wartet. Nach Ende des Kindprozesses soll der Elternprozess die PID des Kindprozesses und dessen Endestatus ausgeben. Testen Sie Ihr Programm mit a. einem existierenden P-neu, welches keine Aufrufparameter benötigt. b. einem nicht existierenden P-neu. c. einem existierenden P-neu, welches Aufrufparameter verarbeitet. Die Aufrufparameter von P-neu sollen dabei die Aufrufparameter vom Programm "Starten" sein. Behandeln Sie entsprechende Fehlermeldungen des exec-Systemaufrufs.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]){
	
	if (argc < 2){
		printf("Please pass some arguments to pass two the new process...\n");
		return -1;
	}

	int child_pid = fork();

	if (child_pid < 0){
		printf("Error forking child process, aborting execution...\n");
		return -1;
	}
	else if (child_pid == 0){ // code for child process
		
		execv("/home/rino/Desktop/Uni/Shup/Lab02/A24/P-neu", argv);

		// check for errors
		printf("Fehlernummer ist %d\n", errno);
		perror("Fehlermeldung");
		// printf("Fehlermeldung in Klartext: %s", perror(("Fehlermeldung")))
		printf("Der Aufruf des Programms P-Neu ist fehlgeschlagen...\n");

	}
	else{ // code for parent process
		int status;
		wait(&status);

		printf("Exit status of child process with PID %d is %d\n", child_pid , WEXITSTATUS(status));

	}


}
