//Esercizio 3: Catena di processi (Gerarchia lineare)
//Scrivere un programma C che realizzi una catena a tre livelli di processi (Nonno -> Padre -> Nipote).
//Il processo originale crea un figlio, il quale crea a sua volta un proprio figlio.
//Ogni processo genitore deve attendere la terminazione del rispettivo figlio prima di stampare il proprio messaggio di chiusura.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    pid_t pid;

    // Il nonno crea il padre
    pid = fork();

    if (pid < 0) {
        perror("Errore nella fork");
        return 1;
    }

    if (pid == 0) {
        // PROCESSO PADRE
        // Il padre crea il nipote
        pid = fork();

        if (pid < 0) {
            perror("Errore nella fork");
            return 1;
        }

        if (pid == 0) {
            // PROCESSO NIPOTE
            printf("Nipote: chiusura\n");
            return 0;
        }
        // Il padre aspetta che termini il nipote
        wait(NULL);
        printf("Padre: il nipote è terminato\n");
        printf("Padre: chiusura\n");

        return 0;
    }
    // PROCESSO NONNO
    // Aspetta che termini il padre
    wait(NULL);
    printf("Nonno: il padre è terminato\n");
    printf("Nonno: chiusura\n");

    return 0;
}