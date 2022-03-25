//gcc 7.4.0
/*          0  
    a       m          d
  o   l             U     n
  h                 
*/
#include  <stdio.h>
#include  <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pA,pO,pH,pL,pM,pU,pD,pN;
    int fd[2];
    char buffer[20];
    char resultado[20];
    
    //write(fd[1],buffer,strlen(buffer));
    //read(fd[0],buffer,20);

    pipe(fd);

    if((pA=fork()) == 0){ //proceso a
        if((pO=fork()) == 0){ //proceso o
            if((pH=fork()) == 0){ //proceso h
                strcat(buffer, "H");
                write(fd[1],buffer,strlen(buffer));
            }else{ //proceso o
                waitpid(pH,NULL,0);
                strcat(buffer, "O");
                write(fd[1],buffer,strlen(buffer));
            }
        }else{ //proceso a

            waitpid(pO,NULL,0);

            if((pL=fork()) == 0){ //proceso l
                strcat(buffer, "L");
                write(fd[1],buffer,strlen(buffer));
            }else{ //proceso a
                waitpid(pL,NULL,0);
                strcat(buffer, "A");
                write(fd[1],buffer,strlen(buffer));
            }
        }
        read(fd[0],buffer,20);
        printf("%s",buffer);
    }else{ //proceso 0

        waitpid(pA,NULL,0);

        if((pM=fork()) == 0){ //proceso m
            strcat(buffer, " M");
            write(fd[1],buffer,strlen(buffer));
        }else{ //proceso 0

            waitpid(pM,NULL,0);

            if((pD=fork()) == 0){ //proceso d
                if((pU=fork()) == 0){ //proceso u
                    strcat(buffer, "U");
                    write(fd[1],buffer,strlen(buffer));
                }else{ //proceso d

                    waitpid(pN,NULL,0);

                    if((pN=fork()) == 0){ //proceso n
                        strcat(buffer, "N");
                        write(fd[1],buffer,strlen(buffer));
                    }else{ //proceso d
                    
                        waitpid(pN,NULL,0);
                        strcat(buffer, "D");
                        write(fd[1],buffer,strlen(buffer));

                    }
                }
            }else{ //proceso 0
            
                waitpid(pD,NULL,0);
                strcat(buffer, "O\n");
                write(fd[1],buffer,strlen(buffer)+1);

            }
        }
        read(fd[0],buffer,20);
        printf("%s",buffer);
    }           
    
    return 0;
}