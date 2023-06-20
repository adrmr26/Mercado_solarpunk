#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "encargado.c"

 Nodo* productos_general;

/*
//Funcion para liberar la memoria compartida y sus datos 
void desvincularAlmacen(Almacen* almacen, int shmId) {
    // Desadjunta el área de memoria compartida
    if (shmdt(almacen) == -1) {
        perror("Error al desadjuntar el área de memoria compartida");
        exit(1);
    }
    // Elimina el área de memoria compartida
    if (shmctl(shmId, IPC_RMID, NULL) == -1) {
        perror("Error al eliminar el área de memoria compartida");
        exit(1);
    }
    else{
        printf("\nSe ha desvinculado el área de memoria compartida del Almacén\n");
    }
}*/



//Genera los productos de cada comuna de forma aleatoria  
void generar_productos(Comuna* comuna, char nombre_productos[11][10]) { 
    int i; 
    int numero_personas = rand() % Max_numero_personas + 1; //Se define la cantidad de personas de forma aleatorea 
 
    for (i = 0; i < Max_numero_producto; i++) { 
        int index_producto = rand() % 11; 
        comuna->productos[i].codigo = i + 1; 
        sprintf(comuna->productos[i].nombre,nombre_productos[index_producto]); 
        comuna->productos[i].disponibilidad = rand() % 100; 
        comuna->productos[i].necesidad = 0; 
    } 
    comuna->numero_productos = Max_numero_producto; 
 
    for (i = 0; i < numero_personas; i++) {  
        int id_producto = rand() % Max_numero_producto; 
        comuna->productos[id_producto].necesidad++; // Aumentar la necesidad de un producto aleatorio para iniciar 
    } 
} 
 
//Inicializa las personas , en este caso los hilos con su acción , cantidad de producto y tiempo de duracion  
void* inicializar_persona(void* arg) { 
    int* id_persona = (int*)arg; 
    int comuna_id = id_persona[0]; 
    int persona_id = id_persona[1]; 
    Comuna* comuna = &comunas[comuna_id]; 
 
    while (1) { //De esta forma el loop es infinito hasta que se encuentre un break  
        int producto_id = rand() % comuna->numero_productos; //Se le asigna un producto de la comuna de forma aleatorea 
        int cantidad_producto = rand() % 10 + 1; //Cantidad que produce o necesita la persona  
        int accion  = rand() % 2; //Selecciona de forma aleatorea que accion hace la persona  
        int tiempo = rand() % 60 + 1; //Cantidad de tiempo que tarda en minutos   
 
        if (accion == 1) { 
           /// sem_wait(&mutex_anaqueles); //AQUI SEMAFORO 
            comuna->productos[producto_id].disponibilidad += cantidad_producto; 
            printf("La persona %d de la Comuna ID %d tiene lista %d unidades de %s, en %d minutos\n", persona_id, comuna_id, cantidad_producto, comuna->productos[producto_id].nombre, tiempo); 
            //sem_post(&mutex_anaqueles); 
        } else { 
           // sem_wait(&mutex_anaqueles); //AQUI SEMAFORO  creo que no los ocupa 
            comuna->productos[producto_id].necesidad += cantidad_producto;  //En esta misma lista debo revisar el hilo encargado comuna 
            printf("La persona %d de la Comuna ID %d necesita %d unidades de %s, en %d minutos\n", persona_id, comuna_id, cantidad_producto, comuna->productos[producto_id].nombre, tiempo); 
          //  sem_post(&mutex_anaqueles); 
        } 
 
        sleep(1); //De tiempo toma el que dura  
    } 
} 

//Inicializa el encargado de cada comuna 
void* inicializar_encargado(void* arg) { 
    int* id_persona = (int*)arg; 
    int comuna_id = id_persona[0]; 
    int persona_id = id_persona[1]; 
    Comuna* comuna = &comunas[comuna_id]; 
 
    while (1) { //mando la lista 
    } 
}
 
// Ejemplo de uso 
int main() { 
 
    char nombre_comida[11][10] = {"Arroz","Frijoles","Maiz","Papa","Zanahoria","Yuca","Lentejas","Tomate","Brocoli","Coliflor","Aguacate"} ; 
    Comuna lista_comunas[Numero_comunas]; //Lista de comunas inicializadas 
    pthread_t personas_hilos[Numero_comunas][Max_numero_personas]; //Crea una matriz de comunas y sus hilos  
 
     // Inicializa un semaforo  
    sem_init(&mutex_anaqueles, 0, 1); 
    sem_init(&mutex_almacen, 0, 1); 

    productos_general = NULL;  // Inicialmente, la lista está vacía
    
    //Crea la lista general que utiliza mercado y almacen
    Producto producto1;
    strcpy(producto1.nombre, nombre_comida[0]);
    producto1.codigo = 1001;
    producto1.disponibilidad = rand() % 10 + 1;
    producto1.necesidad = rand() % 10 + 1;
    
    Producto producto2;
    strcpy(producto2.nombre, nombre_comida[1]);
    producto2.codigo = 1002;
    producto2.disponibilidad = rand() % 10 + 1;
    producto2.necesidad = rand() % 10 + 1;
    
    Producto producto3;
    strcpy(producto3.nombre, nombre_comida[2]);
    producto3.codigo = 1003;
    producto3.disponibilidad = rand() % 10 + 1;
    producto3.necesidad = rand() % 10 + 1;
    
    Producto producto4;
    strcpy(producto4.nombre, nombre_comida[3]);
    producto4.codigo = 1004;
    producto4.disponibilidad = rand() % 10 + 1;
    producto4.necesidad = rand() % 10 + 1;
     
    Producto producto5;
    strcpy(producto5.nombre, nombre_comida[4]);
    producto5.codigo = 1005;
    producto5.disponibilidad = rand() % 10 + 1;
    producto5.necesidad = rand() % 10 + 1;
    
    Producto producto6;
    strcpy(producto6.nombre, nombre_comida[5]);
    producto6.codigo = 1006;
    producto6.disponibilidad = rand() % 10 + 1;
    producto6.necesidad = rand() % 10 + 1;

    Producto producto7;
    strcpy(producto7.nombre, nombre_comida[6]);
    producto7.codigo = 1007;
    producto7.disponibilidad = rand() % 10 + 1;
    producto7.necesidad = rand() % 10 + 1;
    
    Producto producto8;
    strcpy(producto8.nombre, nombre_comida[7]);
    producto8.codigo = 1008;
    producto8.disponibilidad = rand() % 10 + 1;
    producto8.necesidad = rand() % 10 + 1;
    
    Producto producto9;
    strcpy(producto9.nombre, nombre_comida[8]);
    producto9.codigo = 1009;
    producto9.disponibilidad = rand() % 10 + 1;
    producto9.necesidad = rand() % 10 + 1;
    
    Producto producto10;
    strcpy(producto10.nombre, nombre_comida[9]);
    producto10.codigo = 1010;
    producto10.disponibilidad = rand() % 10 + 1;
    producto10.necesidad = rand() % 10 + 1;
    
    Producto producto11;
    strcpy(producto11.nombre, nombre_comida[10]);
    producto11.codigo = 1011;
    producto11.disponibilidad = rand() % 10 + 1;
    producto11.necesidad = rand() % 10 + 1;
    
    // Insertar los productos en la lista
    insertar_lista(&productos_general, producto1);
    insertar_lista(&productos_general, producto2);
    insertar_lista(&productos_general, producto3);
    insertar_lista(&productos_general, producto4);
    insertar_lista(&productos_general, producto5);
    insertar_lista(&productos_general, producto6);
    insertar_lista(&productos_general, producto7);
    insertar_lista(&productos_general, producto8);
    insertar_lista(&productos_general, producto9);
    insertar_lista(&productos_general, producto10);
    insertar_lista(&productos_general, producto11);
    // Crea los productos generales 
    
    imprimir_lista(productos_general);

    inicializar_almacen(productos_general);
    imprimir_productos_almacen();
    desvincular_MC_almacen();

    inicializar_mercado(productos_general);
    imprimir_anaqueles();
    desvincular_MC_mercado();
    


    //destruir_lista(&productos_general)

    /*

    //Inicializa el ecnargado general de almacen y mercado
    inicializar_encargado_principal(&productos_general);

    //Genera las comunas y personas de cada comuna
    int i = 0;
    int j = 0;
    for (i; i < Numero_comunas; i++) { 
        generar_productos(&comunas[i],nombre_comida); 
        for (j; j < Max_numero_personas; j++) { 
            int* persona_id = malloc(2 * sizeof(int)); 
            persona_id[0] = i; // Comuna ID 
            persona_id[1] = j; // Persona ID 
            pthread_create(&personas_hilos[i][j], NULL, inicializar_persona, persona_id); 
        } 
       // int* persona_id = malloc(2 * sizeof(int)); 
        //pthread_create(&personas_hilos[i][j], NULL, inicializar_encargado, persona_id); //crear el encargado
    }
  
    
    /*
// Ejemplo de uso
int main() {

      // Genera una clave única para la memoria compartida
    key_t clave = ftok(".", 'a'); 

    // Crea/obtiene el ID de la memoria compartida
    int shmId = shmget(clave, sizeof(Almacen), IPC_CREAT | 0666); 

    // Adjunta el segmento de memoria compartida al puntero "almacen"
    Almacen* almacen = (Almacen*)shmat(shmId, NULL, 0);


    // Inicializar lista de productos de almacen
    almacen->lista_productos = NULL;


  // Creación de productos
    Producto* producto1 = (Producto*)malloc(sizeof(Producto));
    producto1->codigo = 1;
    strcpy(producto1->nombre,"Arroz");
    producto1->disponibilidad= 5;
    producto1->necesidad = 0;

    Producto* producto2 = (Producto*)malloc(sizeof(Producto));
    producto2->codigo = 2;
    strcpy(producto2->nombre,"Frijoles");
    producto2->disponibilidad = 5;
    producto2->necesidad = 0;

    Producto* producto3 = (Producto*)malloc(sizeof(Producto));
    producto3->codigo = 3;
    strcpy(producto3->nombre,"Maiz");
    producto3->disponibilidad = 5;
    producto3->necesidad= 0;
    

    insertar_lista(&almacen->lista_productos, producto1);
    insertar_lista(&almacen->lista_productos, producto2);
    insertar_lista(&almacen->lista_productos, producto3);


    //Inicializa las comunas 
/*
    int i, j;
    for (i = 0; i < Numero_comunas; i++) {  //Crea la comuna con su numero
        lista_comunas[i].numero_comuna = i;

        //SELECCIONAR PRODUCTOS inicializarProductos(lista_comunas[i].productos);

        for (j = 0; j < Numero_personas; j++) {     //Crea la persona que seria un hilo
            int persona_index = i * Numero_personas + j;
            int* puntero = malloc(sizeof(int));
            *puntero = persona_index;
            pthread_create(&(lista_comunas[i].personas[j]), NULL, crearPersona, puntero);
        }
    }

    for (i = 0; i < Numero_comunas; i++) {      //Une la persona con la comuna 
        for (j = 0; j < Numero_personas; j++) {
            pthread_join(lista_comunas[i].personas[j], NULL);
        }
    }*/


    /*

    // Imprimir la lista de productos
    imprimirLista(almacen->lista_productos);

    // Modificar la disponibilidad de un producto
    modificarDisponibilidad(almacen->lista_productos, 2, 8);

    // Modificar la necesidad de un producto
    modificarNecesidad(almacen->lista_productos, 3, 2);

    // Imprimir la lista de productos
    imprimirLista(almacen->lista_productos);

    // Liberar la memoria ocupada por la lista
    liberarLista(&almacen->lista_productos);

    // Desvincula el segmento de memoria compartida
    desvincularAlmacen(almacen, shmId); 
    */

    return 0;
}