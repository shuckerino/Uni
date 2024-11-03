/**
Ändern Sie das Programm aus Aufgabe A21 so, dass
 Sie es mit vier verschiedenen Zeichenketten als Übergabeparametern starten.
Der Elternprozess soll
 seine Prozessnummer ausgeben, einmal das erste Übergabeargument ausgeben und
dann
 drei Kindprozesse starten, die ihrerseits das zweite, dritte bzw. vierte Übergabeargu-
ment und ihre Prozessnummer ausgeben.
Kindprozess 1 und 2 laufen wie in Aufgabe A21 in einer Endlosschleife.
Der dritte Kindprozess ist so abzuändern, dass er
 eine Sekunde wartet (sleep()-Systemaufruf benutzen),
 sich dann selbst regulär beendet (exit()-Systemaufruf oder verlassen der main()-
Funktion mit return) und
 als Returnwert 2 zurück gibt.
Der Elternprozess soll nach Starten aller Kindprozesse in der nachfolgend angegebenen
Reihenfolge tun:
1. mittels des sleep()-Systemaufrufs 2 Sekunden warten,
2. den ersten Kindprozess mit dem Signal SIGTERM (numerisch 15) beenden (kill()-
Systemaufruf benutzen),
3. den zweiten und dritten Prozess mit dem Signal SIGKILL (numerisch 9) beenden
1/3 b02-shup-cprog-2024ss.docx
© D. Wißmann, HS Coburg, Fak. Elektrotechnik und Informatik
Shell und Prozesse SoSe 2024
4. und dann erst den jeweiligen Endestatus der Kindprozesse abholen und ausgeben (ver-
wenden Sie dabei den wait()-Systemaufruf) und
5. sich abschließend selbst beenden.
Untersuchen und vergleichen Sie die Endestatuswerte der Kindprozesse
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("This solution was created by Rinaldo Schuster\n");

    if (argc != 5)
    {
        printf("The given command line arguments were not valid. Please make sure to pass 4 arguments that should be outputted...\n");
        return EXIT_FAILURE;
    }

    // output PID and first CL-Argument
    printf("I am the father process with PID %d\n", getpid());
    printf("The first argument is %s\n", argv[1]);

    int child_pid_1 = fork();

    if (child_pid_1 < 0)
    {
        printf("Creation of child process 1 was unsuccessful, aborting execution...\n");
        return EXIT_FAILURE;
    }
    else if (child_pid_1 == 0)
    { // code for first child process
        
        printf("I am the 1. child process with PID %d\n", getpid());
        printf("The second argument is %s\n", argv[2]);

        while (1)
        {
            sleep(1);
        }
    }
    else
    {
        int child_pid_2 = fork();

        if (child_pid_2 < 0)
        {
            printf("Creation of child process 2 was unsuccessful, aborting execution\n");
            return EXIT_FAILURE;
        }
        else if (child_pid_2 == 0)
        { // code for second child process
            printf("I am the 2. child process with PID %d\n", getpid());
            printf("The third argument is %s\n", argv[3]);
            while (1)
            {
                sleep(1);
            }
        }
        else
        {
            int child_pid_3 = fork();

            if (child_pid_3 < 0)
            {
                printf("Creation of child process 3 was unsuccessful, aborting execution\n");
                return EXIT_FAILURE;
            }
            else if (child_pid_3 == 0)
            { // code for third child process
                printf("I am the 3. child process with PID %d\n", getpid());
                printf("The fourth argument is %s\n", argv[4]);
                sleep(1);
                exit(2);
            }
            else
            { // final code for father process
                sleep(2);

                // send different signals to each child process
                kill(child_pid_1, SIGTERM);
                kill(child_pid_2, SIGKILL);
                kill(child_pid_3, SIGKILL);
               
                int exit_status;
                
                // get exit status of all child processes
                wait(&exit_status);
                printf("Normal exit status of one of the children: %d\n", exit_status);
                printf("Translated exit status of one of the children: %d\n", WEXITSTATUS(exit_status));
                wait(&exit_status);
                printf("Normal exit status of one of the children: %d\n", exit_status);
                printf("Translated exit status of one of the children: %d\n", WEXITSTATUS(exit_status));
                wait(&exit_status);
                printf("Normal exit status of one of the children: %d\n", exit_status);
                printf("Translated exit status of one of the children: %d\n", WEXITSTATUS(exit_status));

                return EXIT_SUCCESS;
            }
        }
    }

    return EXIT_SUCCESS;
}
