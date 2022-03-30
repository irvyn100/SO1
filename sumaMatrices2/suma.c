#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int c11[2], c12[2], c21[2], c22[2];
    char matrizA[4][2], matrizB[4][2];
    char resultado[5];
    pid_t h00, h01, h10, h11;

    // Tuberias
    pipe(c11);
    pipe(c12);
    pipe(c21);
    pipe(c22);

    // ingresar datos
    matrizA[0][0] = 'a';
    matrizA[0][1] = '\0';

    matrizA[1][0] = 'b';
    matrizA[1][1] = '\0';

    matrizA[2][0] = 'c';
    matrizA[2][1] = '\0';

    matrizA[3][0] = 'd';
    matrizA[3][1] = '\0';

    matrizB[0][0] = 'e';
    matrizB[0][1] = '\0';

    matrizB[1][0] = 'f';
    matrizB[1][1] = '\0';

    matrizB[2][0] = 'g';
    matrizB[2][1] = '\0';

    matrizB[3][0] = 'h';
    matrizB[3][1] = '\0';

    printf("matriz A: \n [%s] \n [%s]\n", matrizA[0], matrizA[1]);
    printf("matriz B: \n [%s] \n [%s]\n", matrizB[0], matrizB[1]);
    // --.--
    write(c11[1], matrizA[0], 1);
    write(c11[1], matrizB[0], 1);

    write(c12[1], matrizA[1], 1);
    write(c12[1], matrizB[1], 1);

    write(c21[1], matrizA[2], 1);
    write(c21[1], matrizB[2], 1);

    write(c22[1], matrizA[3], 1);
    write(c22[1], matrizB[3], 1);

    if ((h00 = fork()) == 0)
    { // hijo
        char aux[2];
        read(c11[0], aux, 2);
        printf("HIJO 00: %s PID:%d, PPID:%d\n", aux, getpid(), getppid());
        write(c11[1], aux, 2);
    }
    else
    { // padre
        if ((h01 = fork()) == 0)
        { // hijo 01
            char aux[2];
            read(c12[0], aux, 2);
            printf("HIJO 01: %s PID:%d, PPID:%d\n", aux, getpid(), getppid());
            write(c12[1], aux, 2);
        }
        else
        { // padre
            if ((h10 = fork()) == 0)
            { // hijo
                char aux[2];
                read(c21[0], aux, 2);
                printf("HIJO 10: %s PID:%d, PPID:%d\n", aux, getpid(), getppid());
                write(c21[1], aux, 2);
            }
            else
            { // padre
                if ((h11 = fork()) == 0)
                { // hijo
                    char aux[2];
                    read(c22[0], aux, 2);
                    printf("HIJO 11: %s PID:%d, PPID:%d\n", aux, getpid(), getppid());
                    write(c22[1], aux, 2);
                }
                else
                {   // padre
                    // esperamos
                    waitpid(c11, NULL, 0);
                    waitpid(c12, NULL, 0);
                    waitpid(c21, NULL, 0);
                    waitpid(c22, NULL, 0);

                    printf("PADRE: -----");
                    read(c11[0], resultado, 2);
                    printf("Resultado:\n|%s  ", resultado);
                    read(c12[0], resultado, 2);
                    printf("%s|\n");
                    read(c21[0], resultado, 2);
                    printf("|%s  ");
                    read(c22[0], resultado, 2);
                    printf("%s|\n");
                }
            }
        }
    }
}