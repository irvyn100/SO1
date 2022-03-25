#include <stdio.h>
#include <iostream>
#include <string.h>

class Registro{
    //atributos
    public:
    struct Venta{
        char vendedor[25];
        int total;
        int fecha;
        struct Venta *sig;
    }*ventas,*aux;

    // metodos
    Registro();
    void registrar(char[],int,int);
    void mostrar();
    void eliminar(int);
    void ordenarVendedor(int);
    void ordenarTotal(int);
    void ordenarFecha(int);

};

Registro::Registro(){
    ventas=NULL;
}

// registrar
void Registro::registrar(char ven[],int tot,int fech){
    Venta *nuevaVenta, *tmp; //se crean nodos auxiliares
    nuevaVenta=(Venta *) malloc(sizeof(Venta));//se asigna un espacio en memoria para el nodo

    //ingresa la informacion del nodo
    strcpy( nuevaVenta->vendedor, ven );
    nuevaVenta->total=tot;
    nuevaVenta->fecha=fech;
    nuevaVenta->sig=NULL;

    if(ventas==NULL){
        ventas=nuevaVenta;
    }else{
        tmp=ventas;
        while(tmp->sig != NULL){
            tmp=tmp->sig;
        }

        tmp->sig=nuevaVenta;
    }
}

// mostrar
void Registro::mostrar(){
    aux = ventas;
    printf("\n\n");
    int cont=1;
    while(aux != NULL){
        printf("%d.- vendedor: %s   total:%d   fecha:%d\n", cont,aux->vendedor,aux->total,aux->fecha);
        aux=aux->sig;
        cont++;
    }
}

// eliminar
void Registro::eliminar(int eliminar){
    Venta *nodoAnterior;
    aux = ventas;
    int cont=1;
    if(eliminar==1){
        ventas=ventas->sig;
        free(aux);
    }else{
        while(cont!=eliminar || aux==NULL){
            nodoAnterior=aux;
            aux=aux->sig;
            cont++;
        }
        if(aux!=NULL){
            nodoAnterior->sig=aux->sig;
            free(aux);
        }
    }
}


// ordenar por vendedores
void Registro::ordenarVendedor(int forma){
    char tmpV[10];
    int tmpT,tmpF;
    bool fin=true;
    aux=ventas;
    if(forma==1){
        // ascendente
        while (aux->sig!=NULL || fin==false){
            if (aux->sig==NULL)
            {
                fin=true;   
                aux=ventas;
            }
            if(strcmp(aux->vendedor,aux->sig->vendedor)>0){
                // guardamos en una variable temporal
                strcpy( tmpV, aux->sig->vendedor );
                tmpT = aux->sig->total;
                tmpF = aux->sig->fecha;

                // cambiamos los datos
                strcpy( aux->sig->vendedor,  aux->vendedor );
                aux->sig->total = aux->total;
                aux->sig->fecha = aux->fecha;

                strcpy( aux->vendedor, tmpV );
                aux->total = tmpT;
                aux->fecha = tmpF;

                fin=false;
            }
            aux=aux->sig;
        }
    }
    else{
        // descendente
        while (aux->sig!=NULL || fin==false){
            if (aux->sig==NULL)
            {
                fin=true;   
                aux=ventas;
            }
            if(strcmp(aux->vendedor,aux->sig->vendedor)<0){
                // guardamos en una variable temporal
                strcpy( tmpV, aux->sig->vendedor );
                tmpT = aux->sig->total;
                tmpF = aux->sig->fecha;

                // cambiamos los datos
                strcpy( aux->sig->vendedor,  aux->vendedor );
                aux->sig->total = aux->total;
                aux->sig->fecha = aux->fecha;

                strcpy( aux->vendedor, tmpV );
                aux->total = tmpT;
                aux->fecha = tmpF;

                fin=false;
            }
            aux=aux->sig;
        }
    }
}



// ordenar por total
void Registro::ordenarTotal(int forma){
    char tmpV[10];
    int tmpT,tmpF;
    bool fin=true;
    aux=ventas;
    if(forma==1){
        // ascendente
        while (aux->sig!=NULL || fin==false){
            if (aux->sig==NULL)
            {
                fin=true;   
                aux=ventas;
            }
            if(aux->total > aux->sig->total){
                // guardamos en una variable temporal
                strcpy( tmpV, aux->sig->vendedor );
                tmpT = aux->sig->total;
                tmpF = aux->sig->fecha;

                // cambiamos los datos
                strcpy( aux->sig->vendedor,  aux->vendedor );
                aux->sig->total = aux->total;
                aux->sig->fecha = aux->fecha;

                strcpy( aux->vendedor, tmpV );
                aux->total = tmpT;
                aux->fecha = tmpF;

                fin=false;
            }
            aux=aux->sig;
        }
    }
    else{
        // descendente
        while (aux->sig!=NULL || fin==false){
            if (aux->sig==NULL)
            {
                fin=true;   
                aux=ventas;
            }
            if(aux->total < aux->sig->total){
                // guardamos en una variable temporal
                strcpy( tmpV, aux->sig->vendedor );
                tmpT = aux->sig->total;
                tmpF = aux->sig->fecha;

                // cambiamos los datos
                strcpy( aux->sig->vendedor,  aux->vendedor );
                aux->sig->total = aux->total;
                aux->sig->fecha = aux->fecha;

                strcpy( aux->vendedor, tmpV );
                aux->total = tmpT;
                aux->fecha = tmpF;

                fin=false;
            }
            aux=aux->sig;
        }
    }
}



// ordenar por fecha
void Registro::ordenarFecha(int forma){
    char tmpV[10];
    int tmpT,tmpF;
    bool fin=true;
    aux=ventas;
    if(forma==1){
        // ascendente
        while (aux->sig!=NULL || fin==false){
            if (aux->sig==NULL)
            {
                fin=true;   
                aux=ventas;
            }
            if(aux->fecha > aux->sig->fecha){
                // guardamos en una variable temporal
                strcpy( tmpV, aux->sig->vendedor );
                tmpT = aux->sig->total;
                tmpF = aux->sig->fecha;

                // cambiamos los datos
                strcpy( aux->sig->vendedor,  aux->vendedor );
                aux->sig->total = aux->total;
                aux->sig->fecha = aux->fecha;

                strcpy( aux->vendedor, tmpV );
                aux->total = tmpT;
                aux->fecha = tmpF;

                fin=false;
            }
            aux=aux->sig;
        }
    }
    else{
        // descendente
        while (aux->sig!=NULL || fin==false){
            if (aux->sig==NULL)
            {
                fin=true;   
                aux=ventas;
            }
            if(aux->fecha < aux->sig->fecha){
                // guardamos en una variable temporal
                strcpy( tmpV, aux->sig->vendedor );
                tmpT = aux->sig->total;
                tmpF = aux->sig->fecha;

                // cambiamos los datos
                strcpy( aux->sig->vendedor,  aux->vendedor );
                aux->sig->total = aux->total;
                aux->sig->fecha = aux->fecha;

                strcpy( aux->vendedor, tmpV );
                aux->total = tmpT;
                aux->fecha = tmpF;

                fin=false;
            }
            aux=aux->sig;
        }
    }
}