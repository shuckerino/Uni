#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/signal.h>
#include <string.h>

int signal_counter = 0;

void sigint_handler(){
	// use write instead of print, because printf is not async safe
	// printf("Reacting to received SIGINT!\n");
	char* msg = "Reacting to received SIGINT!\n";
	write(STDOUT_FILENO, msg, strlen(msg));
	signal_counter++;
}

void sigterm_handler(){
	// printf("Reacting to received SIGTERM!\n");
	char* msg = "Reacting to received SIGTERM!\n";
	write(STDOUT_FILENO, msg, strlen(msg));
	signal_counter++;
}

int main(){
	printf("This solution was created by Rinaldo Schuster\n");

	printf("Program got started!\n");

	struct sigaction sigint_handl;
	struct sigaction sigterm_handl;
	sigint_handl.sa_handler = sigint_handler;
	sigterm_handl.sa_handler = sigterm_handler;
	
	// register handlers
	sigaction(SIGINT, &sigint_handl,NULL);
	sigaction(SIGTERM, &sigterm_handl,NULL);
	
	// using sigaction is actually preferred
	// signal(SIGINT, sigint_handler);
	// signal(SIGTERM, sigterm_handler);


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
