#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
 int sock, tam, n;
 socklen_t origenTam;
 struct sockaddr_in origen[10];
 int numClientes = 0;
 struct sockaddr_in servidor;
 char buffer[1024];
 char usuario[10];
 
 if(argc < 2){
  printf("Error en la cantidad de parametros, se requiere establecer un puerto \n");
  exit(0);
  return 0;
 }
 
 sock = socket(AF_INET, SOCK_DGRAM, 0);
 tam = sizeof(servidor);
 bzero(&servidor,tam);
 servidor.sin_family = AF_INET;
 servidor.sin_addr.s_addr = INADDR_ANY;
 servidor.sin_port = htons(atoi(argv[1]));
 if(bind(sock,(struct sockaddr *)&servidor, tam) < 0){
  printf("Error de Conexion \n");
  return 0;
 }
 origenTam = sizeof(struct sockaddr_in);
 printf("SERVIDOR ACTIVO ------- ESPERA A RECIBIR MENSAJES--------\n");
 while(1){
     strcpy(usuario,"");
     strcpy(buffer,"");
    int u = recvfrom(sock,usuario,10,0,(struct sockaddr *)&origen,&origenTam);
  if(u < 0){
   printf("error recibir datos \n");
   exit(0);
  }else{
      n = recvfrom(sock,buffer,1024,0,(struct sockaddr *)&origen,&origenTam);
  }
  write(1,usuario,10);
  write(1,": ",2);
  write(1,buffer,n);

  n = sendto(sock,usuario,strlen(usuario),0, (struct sockaddr *)&origen, origenTam);
  u = sendto(sock,buffer,strlen(buffer),0, (struct sockaddr *)&origen, origenTam);
  if(n < 0){
   printf("error al enviar  datos \n");
   exit(0);   
  }
  
 }
 return 0;
}

