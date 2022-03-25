//gcc 7.4.0
/*       0  
    4           7
  2   3     5   6   9
  1                 8
*/
#include  <stdio.h>
#include  <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    pid_t p1,p2,p3,p4,p5,p6,p7,p8,p9;

    if((p4 = fork()) == 0){ // proceso 4
        if((p2 = fork() == 0)){ //proceso 2
            if((p1 = fork() == 0)){ //proceso 1
                printf("1 -> PID: %d, PPID: %d\n",getpid(), getppid());
            }else{ // proceso 2

                waitpid(p1,NULL,0);

                printf("2 -> PID: %d, PPID: %d\n",getpid(), getppid());
            }
        }else{ //proceso 4

            waitpid(p2,NULL,0);

            if((p3 = fork()) == 0) { //proceso 3
                printf("3 -> PID: %d, PPID: %d\n",getpid(), getppid());
            }else{ //proceso 4

                waitpid(p3,NULL,0);

                printf("4 -> PID: %d, PPID: %d\n",getpid(), getppid());
            }
        }
    }else{ // proceso 0

        waitpid(p4,NULL,0);

        if((p7 = fork()) == 0) { //proceso 7
            if((p5 = fork()) == 0) { //proceso 5
                printf("5 -> PID: %d, PPID: %d\n",getpid(), getppid());
            }else{ //proceso 7

                waitpid(p5,NULL,0);

                if((p6 = fork()) == 0) { //proceso 6
                    printf("6 -> PID: %d, PPID: %d\n",getpid(), getppid());
                }else{ //proceso 7

                    waitpid(p6,NULL,0);

                    printf("7 -> PID: %d, PPID: %d\n",getpid(), getppid());
                    if((p9 = fork()) == 0) { //proceso 9
                        if((p8 = fork()) == 0) { //proceso 8
                            printf("8 -> PID: %d, PPID: %d\n",getpid(), getppid());
                        }else{ //proceso 9

                            waitpid(p8,NULL,0);

                            printf("9 -> PID: %d, PPID: %d\n",getpid(), getppid());
                        }
                    }else{ //proceso 7
                    
                        waitpid(p9,NULL,0);

                    }
                }
            }
        }else{ //proceso 0

            waitpid(p7,NULL,0);
            printf("@ -> PID: %d, PPID: %d\n",getpid(), getppid());
        }
    }
    return 0;
}