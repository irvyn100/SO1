//gcc 7.4.0
/*       A  
    E           H
  C   D     F   G   J
  B                 I
*/
#include  <stdio.h>
#include  <stdlib.h>

int main(void)
{
    int B,C,D,E,F,G,H,I,J;

    if((E = fork())== 0){ //hijo E
        if((D = fork()) == 0){ // hijo D
            sleep(3);
            printf("D -> PID: %d, PPID: %d\n",getpid(), getppid());
        }else{ // padre de D (E)
           sleep(3);
            printf("E -> PID: %d, PPID: %d\n",getpid(), getppid());
            if((C = fork()) == 0){ // hijo C
                if((B = fork()) == 0){ //hijo B
                    //sleep(2);
                    printf("B -> PID: %d, PPID: %d\n",getpid(), getppid());
                }else{ // padre de B (C)
                    //sleep(1);
                    printf("C -> PID: %d, PPID: %d\n",getpid(), getppid());
                }
            }else{ // padre de C (E)   
            }
        }
    }else{ // padre de E (A)
        if((H = fork()) == 0){//hijo H
            if((F = fork()) == 0){//hijo F
                printf("F -> PID: %d, PPID: %d\n",getpid(), getppid());
            }else{//padre de F (H)
                if((G = fork()) == 0){//hijo G
                    printf("G -> PID: %d, PPID: %d\n",getpid(), getppid());
                }
                else{//padre de G (H)
                    if((J = fork()) == 0){//hijo J
                        if((I = fork()) == 0){//hijo I
                            printf("I -> PID: %d, PPID: %d\n",getpid(), getppid());
                        }else{ // padre de I (J)
                            sleep(1);
                            printf("J -> PID: %d, PPID: %d\n",getpid(), getppid());
                        }
                    }else{//padre de J (H)
                        sleep(2);
                        printf("H -> PID: %d, PPID: %d\n",getpid(), getppid());
                    }
                }
            }
        }else{ // padre de H (A)
            sleep(5);
            printf("A -> PID: %d, PPID: %d\n",getpid(), getppid());
        }
    }
    
    
    return 0;
}