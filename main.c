#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Errore fork");
        return 1;
    } else if (pid == 0) {
        int n;
        printf("Inserisci un numero intero: ");
        if (scanf("%d", &n) != 1) {
            exit(0);
        }

        if (is_prime(n)) {
            exit(1);
        } else if (n % 2 == 0) {
            exit(2);
        } else {
            exit(3);
        }
    } else {
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            if (code == 1) {
                printf("Il numero inserito e primo.\n");
            } else if (code == 2) {
                printf("Il numero inserito e pari (e non primo).\n");
            } else if (code == 3) {
                printf("Il numero inserito e dispari (e non primo).\n");
            }
        }
    }

    return 0;
}