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
#include <sys/stat.h>
#include <errno.h>

#define FIFO "/tmp/mia_fifo"
#define BUFFER 256

int main(void) {
    char buffer[BUFFER];

    // creo la FIFO
    if (mkfifo(FIFO, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    printf("[SERVER] Attendo il client...\n");

    // apro la FIFO in lettura
    int fd = open(FIFO, O_RDONLY);
    if (fd == -1) {
        perror("open");
        unlink(FIFO);
        return 1;
    }

    // riceve il messaggio
    ssize_t n = read(fd, buffer, BUFFER - 1);

    if (n == -1) {
        perror("read");
    } else if (n > 0) {
        buffer[n] = '\0';
        printf("[SERVER] %s", buffer);

        if (buffer[n - 1] != '\n')
            printf("\n");
    }

    // chiudo e rimuovo la FIFO
    close(fd);
    unlink(FIFO);

    return n == -1 ? 1 : 0;
}

