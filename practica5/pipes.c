#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

/*              padre
    fruta      vehiculo     ropa
*/

int main(void)
{
    pid_t pFruta,pVehiculo,pRopa;
    int color, fd[2];
    char buffer[20];

    printf("PID:%d",getpid());
    do
    {
        printf("\n1.-verde\n2.-rojo\n3.-azul\nelige un color: ");
        scanf("%d",&color);
    } while (color<1 || color>3);

    pipe(fd);
    if(color == 2 && (pFruta = fork()) == 0){ //prceso fruta
        printf("\n\nPADRE:%d",getppid());
        printf("\ningrsa una fruta: ");
        scanf("%s",&buffer);
        write(fd[1],buffer,strlen(buffer));
    }else{ // prceso padre
        waitpid(pFruta,NULL,0); //esperamos

        if(color == 3 && ((pVehiculo = fork()) == 0)){ //prceso Vehiculo
            printf("\n\nPADRE:%d",getppid());
            printf("\ningrsa un vehiculo: ");
            scanf("%s",&buffer);
            write(fd[1],buffer,strlen(buffer));
        }else{ // prceso padre
            waitpid(pVehiculo,NULL,0); //esperamos

            if(color == 1 && (pRopa = fork()) == 0){ //prceso ropa
                printf("\n\nPADRE:%d",getppid());
                printf("\ningrsa un ropa: ");
                scanf("%s",&buffer);
                write(fd[1],buffer,strlen(buffer)+1);
            }else{ // prceso padre
                waitpid(pRopa,NULL,0); //esperamos

                printf("\n\nPID:%d",getpid());
                read(fd[0],buffer,20);
                switch (color)
                {
                case 1:
                    printf("\nVerde  ->  %s\n",buffer);
                    break;
                
                case 2:
                    printf("\nRojo  ->  %s\n",buffer);
                    break;

                case 3:
                    printf("\nAzul  ->  %s\n",buffer);
                    break;

                default:
                    break;
                }
            }
        }
    }
    
    return 0;
}