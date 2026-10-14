//
// Created by Nicola on 14/10/2026.
//
/**Esercizio 3: Pipeline a tre processi e due Pipe
Scrivere un programma C in cui il processo padre (A) genera due processi figli (B e C) e due pipe anonime (pipe1 e pipe2)
per collegare i tre processi in cascata. Il processo A genera 20 numeri interi casuali tra 1 e 100
e li invia uno alla volta al processo B tramite pipe1. Il processo B legge i numeri da pipe1, scarta quelli minori di 50,
calcola il quadrato dei rimanenti e li invia al processo C tramite pipe2. Il processo C legge i numeri da pipe2,
li stampa a schermo a mano a mano che arrivano e, al termine della ricezione dei dati, calcola e stampa la loro media aritmetica.
Il processo A attende il completamento di B e C tramite wait().
Ciascun processo deve chiudere i descrittori di pipe non usati per prevenire blocchi indefiniti in lettura**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define N 20

int main() {
    int pipe1[2];
    int pipe2[2];
    pid_t pidB, pidC;
    int numeri[N];
    int numero;

    // creazione delle due pipe
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("errore pipe()");
        exit(1);
    }
    // creazione del processo B
    pidB = fork();
    if (pidB == -1) {
        perror("errore fork() b");
        exit(1);
    }

    if (pidB == 0) {
        // PROCESSO B

        close(pipe1[1]); // B legge da pipe1
        close(pipe2[0]); // B scrive su pipe2

        // legge i numeri da A fino alla fine della pipe
        while (read(pipe1[0], &numero, sizeof(numero))
               == sizeof(numero)) {

            if (numero >= 50) {
                int quadrato = numero * numero;

                if (write(pipe2[1], &quadrato,
                          sizeof(quadrato)) != sizeof(quadrato)) {
                    perror("errore write() b");
                    close(pipe1[0]);
                    close(pipe2[1]);
                    exit(1);
                }
            }
        }

        close(pipe1[0]);
        close(pipe2[1]);

        exit(0);
    }

    // creazione del processo C
    pidC = fork();

    if (pidC == -1) {
        perror("errore fork() c");
        exit(1);
    }

    if (pidC == 0) {
        // PROCESSO C

        close(pipe1[0]); // C non legge da pipe1
        close(pipe1[1]); // C non scrive su pipe1
        close(pipe2[1]); // C legge da pipe2

        int somma = 0;
        int conteggio = 0;

        // riceve e stampa i quadrati fino alla fine della pipe
        while (read(pipe2[0], &numero, sizeof(numero))
               == sizeof(numero)) {

            printf("quadrato ricevuto: %d\n", numero);

            somma += numero;
            conteggio++;
        }

        close(pipe2[0]);

        // calcolo della media
        if (conteggio > 0) {
            printf("Media aritmetica: %.2f\n",
                   (double)somma / conteggio);
        } else {
            printf("Nessun numero ricevuto: media non calcolabile.\n");
        }

        exit(0);
    }

    // PROCESSO A (PADRE)

    close(pipe1[0]); // A scrive su pipe1
    close(pipe2[0]); // A non legge da pipe2
    close(pipe2[1]); // A non scrive su pipe2

    srand((unsigned int)time(NULL));

    printf("processo A: numeri generati\n");

    for (int i = 0; i < N; i++) {
        numeri[i] = rand() % 100 + 1;

        printf("%d ", numeri[i]);

        if (write(pipe1[1], &numeri[i],
                  sizeof(numeri[i])) != sizeof(numeri[i])) {
            perror("errore write() a");
            close(pipe1[1]);
            waitpid(pidB, NULL, 0);
            waitpid(pidC, NULL, 0);
            exit(1);
        }
    }

    printf("\n");

    // chiudendo pipe1, A segnala a B la fine dei dati
    close(pipe1[1]);

    // attesa dei processi figli
    waitpid(pidB, NULL, 0);
    waitpid(pidC, NULL, 0);

    printf("processi b e c terminati.\n");

    return 0;
}
