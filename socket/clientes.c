#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
  pid_t pA;
 int sock, tam, n, u, enviado;
 socklen_t origenTam;
 struct hostent *huesped;
 struct sockaddr_in origen, servidor;
 char buffer[1024];
 char usuario[10];
 if(argc < 4){
  printf("Error en la cantidad de parametros, se requiere establecer un puerto \n");
  printf("Sintaxis: ./prog servidor puerto usuario(maximo 10 caracteres)\n");
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
 servidor.sin_addr.s_addr = INADDR_ANY;
 servidor.sin_port = htons(atoi(argv[2]));

char entrada[1024];
char temp[1024];
int cmp = 1;
while(cmp != 10 ){
 //printf("Ingresa una cadena: \n");
 strcpy(usuario,"");
strcpy(buffer,"");
 fgets(buffer,1024,stdin);
  //printf("%s",temp);

 cmp = strcmp(entrada,"adios");
 //printf("Buffer: %sEntrada:%s CMP: %d \n",buffer,entrada,cmp);
 n = sendto(sock, argv[3],strlen(argv[3]),0, (struct sockaddr *)&servidor, tam);
 if(n < 0){
   printf("error al enviar el mensaje \n");
   exit(0);  
  } 
 n = sendto(sock, buffer,strlen(buffer),0, (struct sockaddr *)&servidor, tam);
  if(n < 0){
   printf("error al enviar el mensaje \n");
   exit(0);  
  }
  if(((pA=fork()))==0){
    while (1)
    {
      origenTam = sizeof(struct sockaddr_in);
      u = recvfrom(sock,usuario,10,0,(struct sockaddr *)&origen,&tam);
      if(u < 0){
      printf("error recibir datos \n");
      exit(0);
      }
      n = recvfrom(sock,buffer,1024,0,(struct sockaddr *)&origen,&tam);
      if(n < 0){
      printf("error recibir datos \n");
      exit(0);
      }
        /*write(1,usuario,u);
        write(1, ": ",2);
        write(1,buffer,n);*/
    }
    
  }
  
}
  close(sock);
 
 return 0;
}

