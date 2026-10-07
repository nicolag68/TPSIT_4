//
// Created by Nicola on 01/10
//Esercizio 1: Sincronizzazione sequenziale (Padre e Figlio)
// Scrivere un programma C in cui il processo padre crea un processo figlio tramite fork().
// Il figlio deve stampare a schermo i numeri da 1 a 5, con una pausa di 1 secondo tra ciascun numero.
// Il padre deve attendere che il figlio completi la propria esecuzione tramite wait(NULL) prima di iniziare a stampare i numeri da 6 a 10.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {

    pid_t pid;

    pid = fork(); // creazione processo figlio

    if (pid == -1) {
        // perror("fork");
        // exit(1);
    }
    if (pid == 0) { // figlio
        for (int i = 1; i <= 5; i++) {
            printf("%d\n", i);
            sleep(1); // aspetta 1 sec
        }
        printf("finito processo figlio!!\n");
    }

    else {
        // processo padre
        wait(NULL);
        for (int i = 6; i <= 10; i++) {
            printf("%d\n", i);
            sleep(1);
        }
        printf("finito processo padre!!\n");
    }
    return 0;
}
