#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "structs.h"

Nodo *listaCrear(Nodo *lista){
   lista = NULL;
   return lista;
}

int main(void) {

	int opcion;
   Nodo * lista1 = listaCrear(lista1);
   printf(lista1);

   	/*do {
		system("cls"); 
		printf("Menu:\n");
      	printf("1. Opcion Round Robin\n");
      	printf("2. Opcion Trabajo mas corto\n");
      	printf("3. Primero en llegar\n");
      	printf("4. Salir\n");
      	printf("Seleccione una opcion (1-4): ");
      	scanf("%d", &opcion);

      switch(opcion) {
         case 1:
            printf("Selecciono la opcion 1\n");
			system("cls"); 
			round_robin(&cola_principal, 100);
			system ("pause");
            break;
         case 2:
            printf("Selecciono la opcion 2\n");
            system("cls"); 
            correr_Trabajo_corto(&cola_principal);
            system ("pause");
            break;
         case 3:
            printf("Selecciono la opcion 3\n");
            system("cls");
			primero_llegar(&cola_principal,100);
			system ("pause");
            break;
        case 4:
        	printf("Selecciono la opcion 4\n");
        	exit(-1);
         default:
            printf("Opcion invalida\n");
      }
   } while(opcion != 4);*/

	return 0;
}