//
// Created by Nicola on 28/10/2026.
//
//Esercizio 1 — Echo server
//Scrivi due programmi: client.c e server.c. Il client legge una riga da tastiera con fgets, la invia al server attraverso una FIFO,
//e il server la riceve e la stampa preceduta da [SERVER] . Usa una sola FIFO — la comunicazione è in una direzione sola.
//Il server rimuove la FIFO al termine.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FIFO "/tmp/mia_fifo"
#define BUFFER 256

int main(void) {
    char buffer[BUFFER];

    printf("Inserisci un messaggio: ");

    if (fgets(buffer, BUFFER, stdin) == NULL)
        return 1;

    // apro la FIFO in scrittura
    int fd = open(FIFO, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // invia il messaggio
    size_t len = strlen(buffer);

    if (write(fd, buffer, len) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}

