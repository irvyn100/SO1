#include <stdio.h>
#include <iostream>
#include <string.h>
#include "Registro.cpp"

int main(void){
    Registro registro = Registro();
    int opc, total, fecha, tmp=0, o1=0, o2=0;
    char vendedor[25];

    printf("\t BIENVENIDO UWU");
    do
    {
        printf("\n\n1.-Registrar venta \n2.-eliminar venta \n3.-ordenar\n4.-salir\n");
        scanf("%d",&opc);
        switch(opc){
            case 1: 
                printf("\n\ningresa el nombre del vendedor: ");
                scanf("%24s",vendedor);
                printf("ingresa el total vendido: ");
                scanf("%d",&total);
                printf("ingresar la fecha: ");
                scanf("%d",&fecha);
                registro.registrar(vendedor, total,fecha);
            break;
            case 2:
                registro.mostrar();
                printf("\n\ningresar el numero del registro que deseas eliminar");
                scanf("%d",&tmp);
                registro.eliminar(tmp);
                printf("\n");
            break;
            case 3:
                do
                {
                    printf("\n\n1.-ordenar por vendedor\n2.-ordenar por total\n3.-ordenar por fecha\n");
                    scanf("%d",&o1);
                } while (o1<1 || o1>3);
                do
                {
                    printf("\n\n1.-ascendente\n2.-descendente\n");
                    scanf("%d",&o2);
                } while (o2<1 || o2>2); 
                if (o1==1)
                {
                    registro.ordenarVendedor(o2);
                    registro.mostrar();
                }
                if (o1==2)
                {
                    registro.ordenarTotal(o2);
                    registro.mostrar();
                }
                if (o1==3)
                {
                    registro.ordenarFecha(o2);
                    registro.mostrar();
                }
            break;
        }
    } while (opc!=4);
    
    return 0;
}

