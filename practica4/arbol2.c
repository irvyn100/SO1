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

    if((pA=fork()) == 0){ //proceso a
        if((pO=fork()) == 0){ //proceso o
            if((pH=fork()) == 0){ //proceso h
                printf("H -> PID: %d, PPID: %d\n",getpid(), getppid());
            }else{ //proceso o
                waitpid(pH,NULL,0);
                printf("O -> PID: %d, PPID: %d\n",getpid(), getppid());

            }
        }else{ //proceso a

            waitpid(pO,NULL,0);

            if((pL=fork()) == 0){ //proceso l
                printf("L -> PID: %d, PPID: %d\n",getpid(), getppid());
            }else{ //proceso a
                waitpid(pL,NULL,0);
                printf("A -> PID: %d, PPID: %d\n",getpid(), getppid());
            }
        }
    }else{ //proceso 0

        waitpid(pA,NULL,0);

        if((pM=fork()) == 0){ //proceso m
            printf("M -> PID: %d, PPID: %d\n",getpid(), getppid());
        }else{ //proceso 0

            waitpid(pM,NULL,0);

            if((pD=fork()) == 0){ //proceso d
                if((pU=fork()) == 0){ //proceso u
                    printf("U -> PID: %d, PPID: %d\n",getpid(), getppid());
                }else{ //proceso d

                    waitpid(pN,NULL,0);

                    if((pN=fork()) == 0){ //proceso n
                        printf("N -> PID: %d, PPID: %d\n",getpid(), getppid());
                    }else{ //proceso d
                    
                        waitpid(pN,NULL,0);
                        printf("D -> PID: %d, PPID: %d\n",getpid(), getppid());

                    }
                }
            }else{ //proceso 0
            
                waitpid(pD,NULL,0);
                printf("0 -> PID: %d, PPID: %d\n",getpid(), getppid());

            }
        }
    }
    
    return 0;
}