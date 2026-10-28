//
// Created by Nicola on 28/10/2026.
//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFO "/tmp/mia_fifo2"
#define BUFFER 256

int main(void) {
    char buffer[BUFFER];

    if (mkfifo(FIFO, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    printf("[SERVER] Attendo i messaggi...\n");

    int fd = open(FIFO, O_RDONLY);
    if (fd == -1) {
        perror("open");
        unlink(FIFO);
        return 1;
    }

    while (1) {
        size_t pos = 0;
        char c;
        ssize_t n;

        // legge una riga
        while (pos < BUFFER - 1) {
            n = read(fd, &c, 1);

            if (n == -1) {
                if (errno == EINTR)
                    continue;

                perror("read");
                close(fd);
                unlink(FIFO);
                return 1;
            }

            if (n == 0) {
                close(fd);
                unlink(FIFO);
                return 0;
            }

            if (c == '\n')
                break;

            buffer[pos++] = c;
        }

        buffer[pos] = '\0';

        if (strcmp(buffer, "QUIT") == 0) {
            printf("[SERVER] Arrivederci!\n");
            break;
        }

        printf("[SERVER] %s\n", buffer);
    }

    close(fd);
    unlink(FIFO);

    return 0;
}

