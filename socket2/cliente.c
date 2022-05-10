#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
 int sock, tam, n, aux, aux2;
 char x[2];
 char y[2];
 socklen_t origenTam;
 struct hostent *huesped;
 struct sockaddr_in origen, servidor;
 char buffer[1024];
 
 if(argc < 3){
  printf("Error en la cantidad de parametros, se requiere establecer un puerto \n");
  printf("Sintaxis: ./prog servidor puerto\n");
  exit(0);
  return 0;
 }
 
 sock = socket(AF_INET, SOCK_DGRAM, 0);
 tam = sizeof(struct sockaddr_in);
 bzero(&servidor,tam);
 huesped = gethostbyname(argv[1]);
 if( huesped <= 0){
  printf("El servidor no existe\n");
  return 0;
 }
 bzero(buffer,1024);
 bcopy((char *)huesped->h_addr,(char *)&servidor.sin_addr,huesped->h_length);
 servidor.sin_family = AF_INET;
 servidor.sin_port = htons(atoi(argv[2]));

char entrada[1024];
int cmp = 1;
while(cmp != 10 ){
 aux = 0;
 printf("Ingresa una cadena: \n");
 fgets(buffer,1024,stdin);
 strcpy(entrada,buffer);

 cmp = strcmp(entrada,"adios");
 //printf("Buffer: %sEntrada:%s CMP: %d \n",buffer,entrada,cmp);
 if(strcmp(entrada,"suma")==10){
  aux = 1;
    printf("ingresa x (1-9)");
    scanf("%s", &x);
    printf("ingresa y (1-9)");
    scanf("%s", &y);
 }
 else if(strcmp(entrada,"resta")==10){
    aux =1;
     printf("ingresa x (1-9)");
    scanf("%s", &x);
    printf("ingresa y (1-9)");
    scanf("%s", &y);
 } 
 else if(strcmp(entrada,"fibo")==10){
    aux =1;
    printf("ingresa x (1-9)");
    scanf("%s", &x);
 } 


 n = sendto(sock, buffer,strlen(buffer),0, (struct sockaddr *)&servidor, tam);
  if(n < 0){
   printf("error al enviar el mensaje \n");
   exit(0);  
  } 
  n = sendto(sock, x,strlen(x),0, (struct sockaddr *)&servidor, tam);
  if(n < 0){
   printf("error al enviar el mensaje \n");
   exit(0);  
  }
  n = sendto(sock, y,strlen(y),0, (struct sockaddr *)&servidor, tam);
  if(n < 0){
   printf("error al enviar el mensaje \n");
   exit(0);  
  }

 origenTam = sizeof(struct sockaddr_in);
  /*n = recvfrom(sock,buffer,1024,0,(struct sockaddr *)&origen,&tam);
  if(n < 0){
   printf("error recibir datos \n");
   exit(0);
  }*/
 char msg[100]= "Se ha enviado un mensaje\n";
 buffer[n] = '\n';
 strcat(msg,buffer);
 aux2 = strlen(msg);
  //printf("%s \n",msg);
  //write(1, msg ,aux);
  //write(1,buffer,n);
 if(aux == 1){
   n = recvfrom(sock,buffer,1024,0,(struct sockaddr *)&origen,&tam);
   char msg[100]= "Se ha enviado un mensaje";
   buffer[n] = '\0';
   strcat(msg,buffer);
   aux2 = strlen(msg);
   printf("%s \n",buffer);
  }
  if(n < 0){
   printf("error recibir datos \n");
   exit(0);
  }
 
}
  close(sock);
 
 return 0;
}

