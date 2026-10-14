#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

        int fd[2];

        if (pipe(fd) == -1) {
                perror("pipe error"); // fprintf(stderr, "errore pipe");
                exit(-1);
        }

        pid_t pid = fork();
        if (pid == -1) {
                perror("fork error");
                exit(-2);
        }

        //figlio !0 quindi 1
        if (!pid) {
                char msg[] = "ciao pollo";

                write(fd[1], msg, sizeof(msg));
        }
        //pipe crea buffer


        char buffer[100];
        int bytes_letti = read(fd[0], buffer, sizeof(buffer));
        printf("%s\n", buffer);


        return 0;
}