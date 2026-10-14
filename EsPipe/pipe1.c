//
// Created by Nicola on 14/10/2026.
//
//Esercizio 1: Scambio dati semplice tramite Pipe (Padre e Figlio)
//Scrivere un programma C in cui il processo padre crea una pipe anonima tramite pipe(fd) e genera un processo figlio tramite fork().
//Il figlio calcola la somma di tutti i numeri pari contenuti in un array di 10 interi e invia il risultato al padre scrivendolo nella pipe.
//Il padre, nel frattempo, calcola la somma dei numeri dispari dello stesso array, legge il risultato inviato dal figlio tramite read(),
//attende la terminazione del figlio con wait(NULL) e stampa a schermo le due somme parziali e la somma totale complessiva.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    int n[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int somma_pari = 0;
    int somma_dispari = 0;
    int i;
    // Creazione della pipe
    if (pipe(fd) == -1) {
        perror("errore pipe()");
        exit(1);
    }
    // Creazione del processo figlio
    pid_t pid = fork();

    if (pid == -1) {
        perror("errore fork()");
        exit(1);
    }

    if (pid == 0) {
        // PROCESSO FIGLIO

        close(fd[0]); // Il figlio non legge dalla pipe

        // Calcolo della somma dei numeri pari
        for (i = 0; i < 10; i++) {
            if (n[i] % 2 == 0) {
                somma_pari += n[i];
            }
        }

        // Invio del risultato al padre
        if (write(fd[1], &somma_pari,
                  sizeof(somma_pari)) == -1) {
            perror("errore write()");
            close(fd[1]);
            exit(1);
                  }

        close(fd[1]);
        exit(0);
    } else {
        // PROCESSO PADRE

        close(fd[1]); // Il padre non scrive nella pipe

        // Calcolo della somma dei numeri dispari
        for (i = 0; i < 10; i++) {
            if (n[i] % 2 != 0) {
                somma_dispari += n[i];
            }
        }

        // Lettura del risultato inviato dal figlio
        if (read(fd[0], &somma_pari,
                 sizeof(somma_pari)) == -1) {
            perror("Errore nella read");
            close(fd[0]);
            wait(NULL);
            exit(1);
                 }

        close(fd[0]);

        // Attesa della terminazione del figlio
        wait(NULL);

        // Stampa dei risultati
        printf("somma numeri pari: %d\n", somma_pari);
        printf("somma numeri dispari: %d\n", somma_dispari);
        printf("somma totale: %d\n",
               somma_pari + somma_dispari);
    }

    return 0;
}

