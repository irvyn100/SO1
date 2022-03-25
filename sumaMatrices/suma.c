#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
    pid_t c11,c12,c21,c22;
    int a[4],b[4],fd[2];
    char salida[20];
    pipe(fd);

    //write(fd[1],buffer,strlen(buffer));
    //read(fd[0],buffer,20);

    printf("Matriz A:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("ingresa el dato %d: ",i+1);
        scanf("%d",&a[i]);
    }

    printf("Matriz B:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("ingresa el dato %d: ",i+1);
        scanf("%d",&b[i]);
    }
    
    printf("\n|%d %d|    +    |%d %d|\n|%d %d|    +    |%d %d|\n\n",a[0],a[1],b[0],b[1],a[2],a[3],b[2],b[3]);
    

    if((c11 = fork()) == 0){ //prceso c11
        int aux = a[0] + b[0];
        sprintf(salida, "%d", aux);
        strcat(salida, "A");


        write(fd[1],salida,strlen(salida));
    }else{ // padre
        if((c12 = fork()) == 0){ //prceso c12
            int aux = a[1] + b[1];
            sprintf(salida, "%d", aux);
            strcat(salida, "B");


            write(fd[1],salida,strlen(salida));
        }else{ //padre
            if((c21 = fork()) == 0){ //prceso c21
                int aux = a[2] + b[2];
                sprintf(salida, "%d", aux);
                strcat(salida, "C");


                write(fd[1],salida,strlen(salida));
            }else{//padre
                if((c22 = fork()) == 0){ //prceso c22
                    int aux = a[3] + b[3];
                    sprintf(salida, "%d", aux);
                    strcat(salida, "D");


                    write(fd[1],salida,strlen(salida));     
                }else{//padre
                    waitpid(c11,NULL,0);
                    waitpid(c12,NULL,0);
                    waitpid(c21,NULL,0);
                    waitpid(c22,NULL,0);
                    char r11[20],r12[20],r21[20],r22[20],aux[20] = "",letra[20];
                    int todo = 0;

                    while (todo != 4)
                    {
                        read(fd[0],letra,1);
                        printf("%s", letra);
                        if(strcmp(letra, "A") == 0){
                            strcpy(r11,aux);
                            strcpy(aux,"");
                            todo++;
                        }else{
                            if (strcmp(letra, "B") == 0)
                            {
                                strcpy(r12,aux);
                                strcpy(aux,"");
                                todo++;
                            }else{
                                if (strcmp(letra, "C") == 0)
                                {
                                    strcpy(r21,aux);
                                    strcpy(aux,"");
                                    todo++;
                                }else{
                                    if (strcmp(letra, "D") == 0)
                                    {
                                        strcpy(r22,aux);
                                        strcpy(aux,"");
                                        todo++;
                                    }else{
                                        strcat(aux, letra);
                                    }
                                }
                            }
                        }
                    }
                    printf("\n\n=    |%s %s|\n=    |%s %s|\n\n",r11,r12,r21,r22);
                    
                }
            }
        }
    }

    return 0;
}