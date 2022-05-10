#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
 int sock, tam, n, numClientes = 0;
 socklen_t origenTam[5], origenTamTemp;
 struct sockaddr_in origen[5], origenTemp;
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
 origenTamTemp = sizeof(struct sockaddr_in);
 printf("SERVIDOR ACTIVO ------- ESPERA A RECIBIR MENSAJES--------\n");
 while(1){
     strcpy(usuario,"");
     strcpy(buffer,"");
    int u = recvfrom(sock,usuario,10,0,(struct sockaddr *)&origen[numClientes],&origenTam[numClientes]);
  if(u < 0){
   printf("error recibir datos \n");
   exit(0);
  }else{
      n = recvfrom(sock,buffer,1024,0,(struct sockaddr *)&origen[numClientes],&origenTam[numClientes]);
  }
  if(numClientes != 3){
  numClientes++;
  }

  write(1,usuario,u);
  write(1,": ",2);
  write(1,buffer,n);
  
  for (int i = 0; i < numClientes; i++)
  {
        n = sendto(sock,usuario,strlen(usuario),0, (struct sockaddr *)&origen[i], origenTam[i]);
        u = sendto(sock,buffer,strlen(buffer),0, (struct sockaddr *)&origen[i], origenTam[i]);
        if(n < 0){
        printf("error al enviar  datos %d, %d\n",numClientes,i);
        exit(0);   
        } else{
            printf("buffer: %d, usuario: %d",n,u);
        }
  }
  strcpy(usuario,"");
strcpy(buffer,"");
  
 }
 return 0;
}

