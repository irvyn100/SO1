//gcc 7.4.0
/*          0  
    a       m          d
  o   l             v     n
  h                 
*/
#include  <stdio.h>
#include  <stdlib.h>

int main(void)
{
    int pA,pO,pH,pL,pM,pV,pD,pN;

    if((pD=fork())==0){//hijo d
        if((pV=fork())==0){//hijo v
            printf("V -> PID: %d, PPID: %d\n",getpid(), getppid());
        }else{//padre de v(d)
            if((pN=fork())==0){//hijo n
                printf("N -> PID: %d, PPID: %d\n",getpid(), getppid());
            }else{//padre de n (d)
                sleep(1);
                printf("D -> PID: %d, PPID: %d\n",getpid(), getppid());
            }
        }
    }else{//padre de d (0)
        if((pM=fork())==0){//hijo m
            printf("M -> PID: %d, PPID: %d\n",getpid(), getppid());
        }else{//padre de m (0)
            if((pA=fork())==0){//hijo a
                if((pL=fork())==0){//hijo l
                    printf("L -> PID: %d, PPID: %d\n",getpid(), getppid());
                }else{//padre de l (a)
                    if((pO=fork())==0){//hijo o
                        if((pH=fork())==0){//hijo h
                            printf("H -> PID: %d, PPID: %d\n",getpid(), getppid());
                        }
                        else{//padre de h (o)
                            sleep(1);
                            printf("O -> PID: %d, PPID: %d\n",getpid(), getppid());
                        }
                    }else{//padre de o (a)
                        sleep(2);
                        printf("A -> PID: %d, PPID: %d\n",getpid(), getppid());
                    }
                }
            }else{//padre de a (0)
                sleep(4);
                printf("0 -> PID: %d, PPID: %d\n",getpid(), getppid());
            }
        }
    }
    
    
    return 0;
}