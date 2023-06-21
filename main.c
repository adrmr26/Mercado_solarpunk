#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "encargado.c"

#define NUM_HILOS 6

 Nodo* productos_general;
 Comuna lista_comunas[Numero_comunas]; //Lista de comunas
 int pos_comuna = 0;

//Genera los productos de cada comuna de forma aleatoria  
void generar_productos(Comuna* comuna, char nombre_productos[11][10]) { 
    int i; 
    //int numero_personas = rand() % Max_numero_personas + 1; //Se define la cantidad de personas de forma aleatorea 

    for (i = 0; i < Max_numero_producto; i++) { 
        int index_producto = rand() % 11;
        Producto producto;
        comuna->productos[i] = producto;
        comuna->productos[i].codigo = i + 1; 
        sprintf(comuna->productos[i].nombre,nombre_productos[index_producto]); 
        comuna->productos[i].disponibilidad = rand() % 100; 
        comuna->productos[i].necesidad = rand() % 10; 
    }
    printf("\nComuna %d:\n", pos_comuna);
    for(i=0; i< Max_numero_producto; i++){
        printf("\nNombre producto: %s\n", comuna->productos[i].nombre);
    }
    /*
    comuna->numero_productos = Max_numero_producto; 

   for (i = 0; i < numero_personas; i++) {  
        int id_producto = rand() % Max_numero_producto; 
        comuna->productos[id_producto].necesidad++; // Aumentar la necesidad de un producto aleatorio para iniciar 
    } */
} 

//Gestiona los hilos y su funcionamiento como persona modificando disponibilidad y 
void* gestionar_Producto(void* arg) {
    Producto* producto = (Producto*)arg;
    printf("Persona %lu: Gestionando producto '%s' con disponibilidad: %d\n y con necesidad: %d\n",
           pthread_self(), producto->nombre, producto->disponibilidad, producto->necesidad);
    producto->disponibilidad = producto->disponibilidad + rand() % 5 + 1;
    producto->necesidad = producto->necesidad + rand() % 5 + 1;
    pthread_exit(NULL);
}

/*
//Inicializa las personas , en este caso los hilos con su acción , cantidad de producto y tiempo de duracion  
void* inicializar_persona(int j, int i) { 
    //int* id_persona = (int*)arg; 
    int comuna_id = i;
    int persona_id = j;
    Comuna* comuna = &comunas[comuna_id]; 
 
    int producto_id = rand() % comuna->numero_productos; //Se le asigna un producto de la comuna de forma aleatorea 
    int cantidad_producto = rand() % 10 + 1; //Cantidad que produce o necesita la persona  
    int accion  = rand() % 2; //Selecciona de forma aleatorea que accion hace la persona  
    int tiempo = rand() % 60 + 1; //Cantidad de tiempo que tarda en minutos   
 
    if (accion == 1) { 
        comuna->productos[producto_id].disponibilidad += cantidad_producto; 
        printf("La persona %d de la Comuna ID %d tiene lista %d unidades de %s, en %d minutos\n", persona_id, comuna_id, cantidad_producto, comuna->productos[producto_id].nombre, tiempo); 
        
    } else { 
        comuna->productos[producto_id].necesidad += cantidad_producto;  //En esta misma lista debo revisar el hilo encargado comuna 
        printf("La persona %d de la Comuna ID %d necesita %d unidades de %s, en %d minutos\n", persona_id, comuna_id, cantidad_producto, comuna->productos[producto_id].nombre, tiempo); 
    } 
 
    //sleep(1); //De tiempo toma el que dura  
} */

void* funcion_hilo(void* arg) {
    int id = *((int*)arg);

    int accion = rand() % 2;
    if (accion == 0){
        lista_comunas[pos_comuna].productos[id].necesidad += 1;
        printf("\nSe ha cambiado la necesidad del producto: %s\n", lista_comunas[pos_comuna].productos[id].nombre);
    }
    else{
        lista_comunas[pos_comuna].productos[id].disponibilidad += 1;
        printf("\nSe ha cambiado la disponibilidad del producto: %s\n", lista_comunas[pos_comuna].productos[id].nombre);
    }

    pthread_exit(NULL);
}

void crear_lista_hilos(Comuna comuna) {
    int ids[NUM_HILOS];

    for (int i = 0; i < NUM_HILOS; i++) {
        ids[i] = i;
        if (pthread_create(&comuna.hilos[i], NULL, funcion_hilo, &ids[i]) != 0) {
            printf("Persona %d creada\n", i);
            fprintf(stderr, "Error al crear el hilo %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_HILOS; i++) {
        if (pthread_join(comuna.hilos[i], NULL) != 0) {
            fprintf(stderr, "Error al unirse al hilo %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
}
 
int main() { 
 
    char nombre_comida[11][10] = {"Arroz","Frijoles","Maiz","Papa","Zanahoria","Yuca","Lentejas","Tomate","Brocoli","Coliflor","Aguacate"} ; 
    pthread_t personas_hilos[Numero_comunas][Max_numero_personas]; //Crea una matriz de comunas y sus hilos  

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

    //COMUNAS e HILOS
    
    printf("\nSe está generando la lista de productos general\n");
    imprimir_lista(productos_general);

    printf("\nSe estan generando las comunas con sus respectivos productos e hilos");
    for(int i = 0; i < Numero_comunas; i++){
        Comuna comuna;
        generar_productos(&comuna, nombre_comida);
        lista_comunas[i] = comuna;
        crear_lista_hilos(comuna); 
        pos_comuna++;
    }
    
    // ENCARGADO 
    encargado(productos_general, lista_comunas);
  
    return 0;
}