#include <semaphore.h>
#define Max_numero_personas 5 
#define Max_numero_producto 6 
#define Numero_comunas 6 
#define Numero_anaqueles 3 

 
typedef struct Producto { 
    int codigo; 
    char nombre[25]; 
    int necesidad;  
    int disponibilidad;  
} Producto; 
 
typedef struct Nodo { 
    Producto producto; 
    struct Nodo *siguiente; 
}Nodo; 


typedef struct Comuna { 
    pthread_t hilos[Max_numero_personas];
    Producto productos[Max_numero_producto];
} Comuna; 
 
typedef struct Mercado { 
    Nodo *lista_productos_anaqueles;
    sem_t mutex;
    int cantidad_anaqueles;
}Mercado; 
