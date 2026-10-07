//
// Created by Nicola on 07/10/2026.
//Esercizio 2: Gestione di N figli in parallelo
//Scrivere un programma C in cui il processo padre genera 3 processi figli simultanei.
//Ogni figlio deve stampare il proprio PID, attendere 2 secondi e poi terminare.
//Il padre deve attendere che tutti e 3 i figli abbiano completato l'esecuzione prima di stampare un messaggio finale e chiudersi.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {

    pid_t pid;

    for (int i = 0; i < 3; i++) {
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            printf("figlio: PID = %d\n", getpid());
            sleep(2);
            return 0;
        }

    }
    // Codice eseguito solo dal padre
    // Attende la terminazione di tutti e 3 i figli
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("tutti i figli hanno finito - padre finito.\n");

    return 0;

}

