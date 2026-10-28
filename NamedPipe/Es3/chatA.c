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
#include <signal.h>

#define FIFO_AB "/tmp/fifo_a_to_b"
#define FIFO_BA "/tmp/fifo_b_to_a"
#define BUFFER 256

int main(void) {
    char buffer[BUFFER];

    signal(SIGPIPE, SIG_IGN);

    if (mkfifo(FIFO_AB, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    if (mkfifo(FIFO_BA, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    // A apre prima in scrittura
    int out = open(FIFO_AB, O_WRONLY);
    if (out == -1) {
        perror("open");
        return 1;
    }

    // Poi apre in lettura
    int in = open(FIFO_BA, O_RDONLY);
    if (in == -1) {
        perror("open");
        close(out);
        return 1;
    }

    while (1) {
        printf("[A] Messaggio (EXIT per uscire): ");
        fflush(stdout);

        if (fgets(buffer, BUFFER, stdin) == NULL)
            break;

        if (write(out, buffer, strlen(buffer)) == -1) {
            perror("write");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "EXIT") == 0)
            break;

        // Attende la risposta di B
        size_t pos = 0;
        char c;
        ssize_t n = 1;

        while (pos < BUFFER - 1) {
            n = read(in, &c, 1);

            if (n <= 0 || c == '\n')
                break;

            buffer[pos++] = c;
        }

        if (n <= 0)
            break;

        buffer[pos] = '\0';
        printf("[B] %s\n", buffer);

        if (strcmp(buffer, "EXIT") == 0)
            break;
    }

    close(in);
    close(out);

    unlink(FIFO_AB);
    unlink(FIFO_BA);

    printf("[A] Chat terminata.\n");
    return 0;
}

