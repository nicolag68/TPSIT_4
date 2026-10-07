//Esercizio 4: Decisione del Padre in Base al Valore di Ritorno
//Scrivere un programma C in cui il processo figlio chiede all'utente di inserire un numero intero da tastiera.
//Il figlio analizza il numero ed esce restituendo un codice specifico:
//Codice 1: Se il numero è primo.
//Codice 2: Se il numero è pari (e non primo).
//Codice 3: Se il numero è dispari (e non primo).
//Il processo padre deve attendere che l'utente interagisca con il figlio tramite wait(&status) e, una volta letto il codice con WEXITSTATUS, eseguire un'azione diversa in base al risultato comunicato, ovvero stampare il risultato con una frase associata.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int primo(int n) {
    if (n < 2) {
        return 0;
    }

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("Errore nella fork");
        return 1;
    }

    if (pid == 0) {
        // PROCESSO FIGLIO
        int numero;

        printf("Inserisci un numero intero: ");
        scanf("%d", &numero);

        if (primo(numero)) {
            // Numero primo
            return 1;
        }
        else if (numero % 2 == 0) {
            // Numero pari ma non primo
            return 2;
        }
        else {
            // Numero dispari ma non primo
            return 3;
        }
    }

    // PROCESSO PADRE
    wait(&status);

    // Recupera il codice restituito dal figlio
    int codice = WEXITSTATUS(status);

    if (codice == 1) {
        printf("Il figlio comunica: il numero è primo.\n");
    }
    else if (codice == 2) {
        printf("Il figlio comunica: il numero è pari e non primo.\n");
    }
    else if (codice == 3) {
        printf("Il figlio comunica: il numero è dispari e non primo.\n");
    }

    return 0;
}