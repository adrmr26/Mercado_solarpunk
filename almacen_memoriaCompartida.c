/* Semáforos */
#include <semaphore.h>

/* Memoria compartida */
#include <sys/mman.h>
#include <sys/stat.h>       
#include <fcntl.h>           

/* Generales */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* FORK */
#include <sys/types.h>
#include <unistd.h>

/* Wait de los procesos */
#include <sys/wait.h>

/* srand */
#include <time.h>

/* structs.h*/
//#include "lista.c"

/* DEFINES */
#define MC "/memoria_compartida_almacen"
#define MAX_PRODUCTOS 3

 //Lista productos_general;
/*
void inicializar_almacen(Lista *lista_general) {

    srand(time(NULL));

    //Abre el espacio de la memoria compartida 
    int fd_shm = shm_open(MC, O_RDWR | O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR);

    ftruncate(fd_shm, sizeof(Producto)); //NOSE SI ESTA BIEN

    Producto *almacen = mmap(NULL, sizeof(Producto), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);

    if (almacen == MAP_FAILED) {
        perror("Error al mapear la memoria compartida");
        exit(1);
    }

    for(int i = 0; lista_general->inicio != NULL; i++){
        lista_general->inicio->producto = &almacen[i];
        lista_general->inicio = lista_general->inicio->siguiente;
    }
    

    Producto* producto1 = &almacen[0]; 
    producto1->codigo = 1;
    sprintf(producto1->nombre, "Arroz");
    producto1->necesidad = 0;
    producto1->disponibilidad = 0;

    Producto* producto2 = &almacen[1]; 
    producto2->codigo = 2;
    sprintf(producto2->nombre, "Frijoles");
    producto2->necesidad = 0;
    producto2->disponibilidad = 0;

    Producto* producto3 = &almacen[2]; 
    producto3->codigo = 3;
    sprintf(producto3->nombre, "Maiz");
    producto3->necesidad = 0;
    producto3->disponibilidad = 0;


    // Imprimir los productos en la memoria compartida
    printf("Productos en la memoria compartida:\n");
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        printf("Código: %d\n", almacen[i].codigo);
        printf("Nombre: %s\n", almacen[i].nombre);
        printf("Necesidad: %d\n", almacen[i].necesidad);
        printf("Disponibilidad: %d\n", almacen[i].disponibilidad);
        printf("------------------\n");
    }

    //munmap(almacen, sizeof(Producto));
    //close(fd_shm);
   // shm_unlink(MC);

}

//Crea la lista general de productos para ser utilizada por almacen y mercado
void crear_lista_general(char *comidas){
    for(int i = 0 ; i < 11;i++){
        Producto* producto = (Producto*)malloc(sizeof(Producto));
        producto->codigo = i+1;
        strcpy(producto->nombre, comidas[i]);
        producto->disponibilidad = rand() % 10 + 1; 
        producto->necesidad = 0 ; //La necesidad se muestra en 0 , ya que se esta inicializando
        insertar_lista(&productos_general,producto);
    }
}

int main(){
    char nombre_comida[11][10] = {"Arroz","Frijoles","Maiz","Papa","Zanahoria","Yuca","Lentejas","Tomate","Brocoli","Coliflor","Aguacate"} ; 
    crear_lista_general(&nombre_comida);
    //inicializar_almacen(&productos_general);


}
*/