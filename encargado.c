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

/* lista.c */
#include "lista.c"

/* DEFINES */
#define MCA "/memoria_compartida_almacen"
#define MCM "/memoria_compartida_mercado"
#define MAX_PRODUCTOS 11  //Máximo de productos en la lista general
#define NUM_ANAQUELES 3  // Número de anaqueles

Producto *almacen;
Producto *mercado;

int fd_shm_almacen;
int fd_shm_mercado;

sem_t* sem_lectura;
sem_t* sem_escritura;

void encargado(Nodo *lista_general_productos, Comuna *lista_comunas){
    // Se crea la memoria compartida de almacen
    inicializar_almacen(lista_general_productos);
    imprimir_productos_almacen();

    // Se crea la memoria compartida de mercado
    inicializar_mercado(lista_general_productos);
    imprimir_anaqueles();

    //Se crean los semáforos
    crear_semaforos();

    //Lee constantemente el mercado
    int i = 0;
    while (i < 3) {
        int productos_encontrados = 0;
        int productos_no_encontrados = 0;
        printf("\nEncargado revisando\n");
        for(int i = 0; i < Numero_comunas; i++){
            for(int j = 0; j < Max_numero_producto; j++){
                for(int k = 0; k < NUM_ANAQUELES; k++){
                    //sem_wait(sem_lectura);  // Espera al semáforo de escritura
                    if (strcmp(mercado[k].nombre , lista_comunas[i].productos[j].nombre) == 0){
                        //sem_post(sem_escritura);  // Libera el semáforo de escritura
                        productos_encontrados++;
                        //sem_wait(sem_escritura);  // Espera al semáforo de escritura
                        mercado[i].disponibilidad += lista_comunas[i].productos[j].disponibilidad;
                        mercado[i].necesidad -= lista_comunas[i].productos[j].necesidad;
                        mercado[i].codigo = lista_comunas[i].productos[j].codigo;
                        strcpy(mercado[i].nombre, lista_comunas[i].productos[j].nombre);
                    }
                    else{
                     productos_no_encontrados++;
                    }
                    //sem_post(sem_lectura);  // Libera el semáforo de lectura
                }
            }
        }
        i++;
        printf("\nCantidad de productos encontrados: %d", productos_encontrados);
        printf("\nCantidad de productos NO encontrados: %d\n", productos_no_encontrados);
        intercambiar_productos_FIFO();
        //intercambiar_productos_MFU();
    }

    desvincular_MC_mercado();
    desvincular_MC_almacen();

}

void intercambiar_productos_FIFO() {

    int rand_almacen = rand() % 11;
    int rand_mercado = rand() % 3;

    Producto producto1_almacen = almacen[rand_almacen];
    Producto producto2_mercado = mercado[rand_mercado];

    almacen[rand_almacen] = producto2_mercado;
    mercado[rand_mercado] = producto1_almacen;

}

void intercambiar_productos_MFU(){

    int pos_menor_disp = 0;
    int pos_mayor_disp = 0;

    for(int i = 0; i < MAX_PRODUCTOS; i++){
        if(almacen[i].disponibilidad > almacen[pos_mayor_disp].disponibilidad){
            pos_mayor_disp = i;
        }
    }

    for(int j = 0; j < NUM_ANAQUELES; j++){
        if(mercado[j].disponibilidad < mercado[pos_menor_disp].disponibilidad){
            pos_menor_disp = j;
        }
    }

    // Se hace el intercambio de productos 
    Producto producto_almacen = almacen[pos_mayor_disp];
    Producto producto_mercado = mercado[pos_menor_disp];

    almacen[pos_mayor_disp] = producto_mercado;
    mercado[pos_menor_disp] = producto_almacen;

}

// Se crean los semáforos de lectura y escritura 
void crear_semaforos(){
    sem_lectura = sem_open("/sem_lectura", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
    sem_escritura = sem_open("/sem_escritura", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
}

// Se eliminan los semáforos de lectura y escritura 
void eliminar_semaforos(){
    sem_close(sem_lectura);
    sem_close(sem_escritura);
    sem_unlink("/sem_lectura");
    sem_unlink("/sem_escritura");
}

// Se crea la memoria compartida de almacen
void inicializar_almacen(Nodo *lista_general) {

    srand(time(NULL));

    //Abre el espacio de la memoria compartida 
    fd_shm_almacen = shm_open(MCA, O_RDWR | O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR);

    ftruncate(fd_shm_almacen, MAX_PRODUCTOS * sizeof(Producto)); 

    almacen = mmap(NULL, sizeof(Producto), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm_almacen, 0);

    if (almacen == MAP_FAILED) {
        perror("\nError al mapear la memoria compartida del almacén");
        exit(1);
    }
    
    Nodo* actual = lista_general;

    // Se agrega la lista de productos en la memoria compartida del almacen
    for(int i = 0; actual != NULL; i++){
        Producto* producto = &almacen[i];
        producto->codigo = actual->producto.codigo;
        strcpy(producto->nombre, actual->producto.nombre);
        producto->necesidad = actual->producto.necesidad;
        producto->disponibilidad = actual->producto.disponibilidad;
        actual = actual->siguiente;
    }
}

// Desvincula la memoria compartida del almacen
void desvincular_MC_almacen(){
    munmap(almacen, sizeof(Producto));
    if (close(fd_shm_almacen) == -1) {
        perror("Error al cerrar la memoria compartida");
        exit(EXIT_FAILURE);
    }
    if (shm_unlink(MCA) == -1) {
        perror("Error al eliminar la memoria compartida");
        exit(EXIT_FAILURE);
    }
    printf("\nSe ha desvinculado correctamente la memoria compartida del almacén\n");
}

// Imprimir los productos en la memoria compartida del almacen
void imprimir_productos_almacen(){
    printf("\nProductos en la memoria compartida de almacen:\n");
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        printf("Nombre: %s\n", almacen[i].nombre);
        printf("Código: %d\n", almacen[i].codigo);
        printf("Disponibilidad: %d\n", almacen[i].disponibilidad);
        printf("Necesidad: %d\n", almacen[i].necesidad);
        printf("------------------\n");
    }
}

// Se crea la memoria compartida de mercado
void inicializar_mercado(Nodo *lista_general){

    srand(time(NULL));
    
    //Abre la memoria compartida
    fd_shm_mercado = shm_open(MCM, O_RDWR | O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR);

    ftruncate(fd_shm_mercado, NUM_ANAQUELES * sizeof(Producto)); //Tamaño de la memoria compartida

    mercado = mmap(NULL, sizeof(Producto), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm_mercado, 0);
  
    if (mercado == MAP_FAILED) {
        perror("\nError al mapear la memoria compartida del mercado");
        exit(1);
    }
    
    Nodo* actual = lista_general;

    // Se agrega la lista de productos que funciona como anaqueles en el mercado
    for(int i = 0; i < NUM_ANAQUELES; i++){
        Producto* producto = &mercado[i];
        producto->codigo = actual->producto.codigo;
        strcpy(producto->nombre, actual->producto.nombre);
        producto->necesidad = actual->producto.necesidad;
        producto->disponibilidad = actual->producto.disponibilidad;
        actual = actual->siguiente;
    }

}

// Desvincula la memoria compartida del mercado
void desvincular_MC_mercado(){
    munmap(mercado, sizeof(Producto));
    if (close(fd_shm_mercado) == -1) {
        perror("Error al cerrar la memoria compartida");
        exit(EXIT_FAILURE);
    }
    if (shm_unlink(MCM) == -1) {
        perror("Error al eliminar la memoria compartida");
        exit(EXIT_FAILURE);
    }
    printf("\nSe ha desvinculado correctamente la memoria compartida del mercado\n");
}

// Imprimir los anaqueles en la memoria compartida del mercado
void imprimir_anaqueles(){
    printf("\nAnaqueles en la memoria compartida de mercado:\n");
    for (int i = 0; i < 3; i++) {
        printf("Nombre: %s\n", mercado[i].nombre);
        printf("Código: %d\n", mercado[i].codigo);
        printf("Disponibilidad: %d\n", mercado[i].disponibilidad);
        printf("Necesidad: %d\n", mercado[i].necesidad);
        printf("------------------\n");
    }
}
/*
void crearMemoriaCompartida() {
    // Crear y configurar la memoria compartida
    fd_shm = shm_open(MC, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd_shm == -1) {
        perror("Error al crear la memoria compartida");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(fd_shm, MAX_PRODUCTOS * sizeof(Producto)) == -1) {
        perror("Error al ajustar el tamaño de la memoria compartida");
        exit(EXIT_FAILURE);
    }
}

void borrarMemoriaCompartida() {
    // Liberar recursos
    if (close(fd_shm) == -1) {
        perror("Error al cerrar la memoria compartida");
        exit(EXIT_FAILURE);
    }
    if (shm_unlink(MC) == -1) {
        perror("Error al eliminar la memoria compartida");
        exit(EXIT_FAILURE);
    }
}
*/
/*
void* inicializar_encargado_principal(Lista *lista_principal) { 
    inicializar_almacen(lista_principal);
    Mercado* anaqueles = inicializar_mercado(lista_principal);
    

    while (1) { //De esta forma el loop es infinito hasta que se encuentre un break  
      //vE LISTAS 

    } 
} 
*/
/*
int main() {
    // Crear la memoria compartida
    crearMemoriaCompartida();

    printf("Memoria compartida creada correctamente\n");

    // Borrar la memoria compartida
    borrarMemoriaCompartida();

    return 0;
}   */