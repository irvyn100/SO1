#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
    int edad;
    char color[6];
    pid_t pMenores,pAdultos,pMayores,pVideojuegos,pLectura,pEjercicios,pEstudia,pTrabaja,pAuto,pCasa;

    printf("ingresa tu edad: ");
    do
    {
        scanf("%d",&edad);
    } while (edad < 1);
    printf("1.-rojo\n2.-verde\n3.-azul\nescribe un color: ");
    do
    {
        scanf("%s",&color);
    } while (strcmp(color, "rojo") != 0 && strcmp(color, "verde") != 0 && strcmp(color, "azul") != 0);
    printf("PID: %d\n\n",getpid());

    if(edad<18 && (pMenores=fork())==0){ // proceso menores 
        int pasaTiempo;
        printf("1.-videojuegos\n2.-lectura\n3.-ejercicio\nselecciona tu pasatiempo: ");
        do
        {
            scanf("%d",&pasaTiempo);
        } while (pasaTiempo > 3 || pasaTiempo < 1);
        printf("PID: %d\nPADRE: %d\n\n",getpid(),getppid());

        if(pasaTiempo==1 && (pVideojuegos=fork())==0){ // proceso videojuegos
            printf("edad: %d\ncolor: %s\npasatiempo: videojuegos\n",edad,color);
            printf("PID: %d\nPADRE: %d\n\n",getpid(),getppid());

        } else{ //proceso menores

            waitpid(pVideojuegos,NULL,0); //esperamos el proceso videojuegos

            if(pasaTiempo==2 && (pLectura=fork())==0){ //proceso lectura
                printf("edad: %d\ncolor: %s\npasatiempo: lectura\n",edad,color);
                printf("PID: %d\nPADRE: %d\n\n",getpid(),getppid());
            }else{ //proceso menores

                waitpid(pLectura,NULL,0); //esperamos el proceso lectura

                if(pasaTiempo==3 && (pEjercicios=fork())==0){ //proceso ejercicio
                    printf("edad: %d\ncolor: %s\npasatiempo: lectura\n",edad,color);
                    printf("PID: %d\nPADRE: %d\n\n",getpid(),getppid());

                }else{ //proceso menores
                
                    waitpid(pEjercicios,NULL,0);

                }
            }
        }
    }else{ //proceso padre

        waitpid(pMenores,NULL,0); //esperamos al proceso menores

        if(edad>=18 && edad<=40 && (pAdultos=fork())==0){ //proceso adultos
            printf("PID: %d\nPADRE: %d\n\n",getpid(),getppid());
            if((strcmp(color,"verde")==0 || strcmp(color,"azul")==0) && (pEstudia=fork()==0) ){ //proceso estudia
                char estudia[50];
                printf("¿que estudias? ");
                scanf("%s",&estudia);
                printf("edad: %d\ncolor: %s\nestudias: %s\n",edad,color,estudia);
                printf("PID: %d\nPADRE: %d\n\n",getpid(),getppid());
            }else{ //proceso adulto

                waitpid(pAdultos,NULL,0); // esperamos proceso adultos

                if((strcmp(color,"rojo")==0) && (pTrabaja=fork()==0)){ //proceso trabaja
                    char trabajo[50];
                    printf("¿en que trabajas? ");
                    scanf("%s",&trabajo);
                    printf("edad: %d\ncolor: %s\nestudias: %s\n",edad,color,trabajo);
                    printf("PID: %d\nPADRE: %d\n\n",getpid(),getppid());
                }else{ //proceso adultos

                    waitpid(pTrabaja,NULL,0); //esperamos al proceso

                }
            }
        }else{ //proceso padre

            waitpid(pAdultos,NULL,0); //esperamos al proceso adultos

            if(edad>40 && (pMayores=fork())==0){ //proceso mayores
                printf("PID: %d\nPADRE: %d\n\n",getpid(),getppid());
                if(strcmp(color,"verde")==0 && (pAuto=fork())==0){ //proceso auto
                    int carro;
                    printf("¿tienes un auto?\n1.-si\n2.-no\n");
                    do {
                        scanf("%d",&carro);
                    }while(carro < 1 || carro > 2);
                    if(carro == 1){
                        printf("edad: %d\ncolor: %s\ntienes auto\n",edad,color);
                        printf("PID: %d\nPADRE: %d\n\n",getpid(),getppid());
                    }else{
                        printf("edad: %d\ncolor: %s\nno tienes auto\n",edad,color);
                        printf("PID: %d\nPADRE: %d\n\n",getpid(),getppid());
                    }
                }else{ //proceso mayores

                    waitpid(pAuto,NULL,0); //esperamos al proceso

                    if((strcmp(color,"rojo")==0 || strcmp(color,"azul")==0) && (pCasa=fork())==0){ //proceso casa
                        int casa;
                        printf("¿tienes casa?\n1.-si\n2.-no\n");
                        do {
                            scanf("%d",&casa);
                        }while(casa < 1 || casa > 2);
                        if(casa == 1){
                            printf("edad: %d\ncolor: %s\ntienes casa\n",edad,color);
                            printf("PID: %d\nPADRE: %d\n\n",getpid(),getppid());
                        }else{
                            printf("edad: %d\ncolor: %s\nno tienes casa\n",edad,color);
                            printf("PID: %d\nPADRE: %d\n\n",getpid(),getppid());
                        }
                    }else{ //proceso mayores

                        waitpid(pCasa,NULL,0); //esperamos el proceso

                    }
                }
            }else{ //proceso padre
            
                waitpid(pMayores,NULL,0); //esperamos al proceso mayores

            }
        }
    }
    
    return 0;
}