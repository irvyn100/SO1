#include  <stdio.h>
#include  <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    int x,y,z;
    pid_t pA,pD,pS,pM;

    printf("ingresa x: ");
    scanf("%d",&x);
    printf("ingresa y: ");
    scanf("%d",&y);
    printf("ingresa z: ");
    scanf("%d",&z);
    printf("pid: %d\n\n",getpid());
    if(((pA=fork()))==0){ // proceso ordenar ascendente
        int ordenar[3];
        ordenar[0]=x;
        ordenar[1]=y;
        ordenar[2]=z;
        int temp;
        for(int i=0;i<2;i++){
            if(ordenar[i]>ordenar[i+1]){
                temp=ordenar[i];
                ordenar[i]=ordenar[i+1];
                ordenar[i+1]=temp;
                i=0;
            }
        }
        printf("orden ascendente: ");
            for(int i=0;i<3;i++){
                printf("%d ,",ordenar[i]);
            }   
        printf("padre: %d",getppid());
        printf("\n");
    }else{ // padre
        waitpid(pA,NULL,0);


        if((pD=fork())==0){ // proceso ordenar descendente
            //sleep(10);
            int ordenar[3];
            ordenar[0]=x;
            ordenar[1]=y;
            ordenar[2]=z;
            int temp;
            for(int i=0;i<2;i++){
                if(ordenar[i]<ordenar[i+1]){
                    temp=ordenar[i];
                    ordenar[i]=ordenar[i+1];
                    ordenar[i+1]=temp;
                    i=0;
                }
            }
            printf("orden descendente: ");
            for(int i=0;i<3;i++){
                printf("%d ,",ordenar[i]);
            }  
            printf("padre: %d",getppid()); 
            printf("\n");
        }else{ // padre
            waitpid(pD,NULL,0);


            if((pS=fork())==0){ // proceso sumar
                //sleep(10);
                int sum=x+y+z;
                printf("la suma es: %d ,",sum);
                printf("padre: %d",getppid());
                printf("\n");
            }else{ // padre
                waitpid(pS,NULL,0);
        
                if((pM=fork())==0){ // proceso multiplicar
                    //sleep(10);
                    int mul=x*y*z;
                    printf("la multiplicacion es: %d ,",mul);
                    printf("padre: %d",getppid());
                    printf("\n");
                }else{ // padre
                    waitpid(pM,NULL,0);
                }
            }
        }
    }
    
    return 0;
}