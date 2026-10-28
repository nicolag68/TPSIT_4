//
// Created by Nicola on 28/10/2026.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define FIFO "/tmp/mia_fifo2"
#define BUFFER 256

int main(void) {
    char buffer[BUFFER];

    // Ignora SIGPIPE
    signal(SIGPIPE, SIG_IGN);

    int fd = open(FIFO, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    while (1) {
        printf("Messaggio (QUIT per uscire): ");
        fflush(stdout);

        if (fgets(buffer, BUFFER, stdin) == NULL)
            break;

        size_t len = strlen(buffer);
        size_t sent = 0;

        // invia tutto il messaggio
        while (sent < len) {
            ssize_t n = write(fd, buffer + sent, len - sent);

            if (n == -1) {
                if (errno == EINTR)
                    continue;

                if (errno == EPIPE)
                    fprintf(stderr, "[CLIENT] Nessun reader: canale chiuso.\n");
                else
                    perror("write");

                close(fd);
                return 1;
            }

            sent += (size_t)n;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "QUIT") == 0)
            break;
    }

    close(fd);
    return 0;
}

