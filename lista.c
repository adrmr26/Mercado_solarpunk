#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "structs.h"

//Inicializar una lista 
void inicializar_lista (Lista *lista){
  lista->inicio = NULL;
  lista->fin = NULL;
  lista ->tamano = 0;
}

//Insertar al inicio de la lista 
int insertar_lista (Lista *lista, Producto *producto){
    Nodo *nuevo_nodo;
    if ((nuevo_nodo = (Nodo *) malloc (sizeof (Nodo))) == NULL) {
        return -1;
    }
    strcpy (nuevo_nodo->producto, producto);
    nuevo_nodo->siguiente = lista->inicio;
    lista->inicio = nuevo_nodo;
    lista->tamano++;
    return 0;
}

//Elimina el primer elemento de la lista 
int eliminar_nodo (Lista *lista){
  if (lista->tamano == 0)
    return -1;
  Producto *producto_eliminado;
  producto_eliminado = lista->inicio;
  lista->inicio = lista->inicio->siguiente;
  if (lista->tamano == 1)
    lista->fin = NULL;
  //free (producto_eliminado->producto);
  free (producto_eliminado);
  lista->tamano--;
  return 0;
}

//Imprime la lista completa 
void imprimir_lista (Lista *lista){
  Nodo *nodo_actual;
  nodo_actual = lista->inicio;
  while (nodo_actual != NULL){
      printf ("%p - %s\n", nodo_actual, nodo_actual->producto);
      nodo_actual = nodo_actual->siguiente;
  }
}

//Destruye la lista 
void destruir (Lista *lista){
  while (lista->tamano > 0)
    eliminar_nodo (lista);
}


