#include <semaphore.h>
#define Max_numero_personas 5 
#define Max_numero_producto 6 
#define Numero_comunas 6 
#define Numero_anaqueles 3 
 
typedef struct Producto { 
 int codigo; 
    char nombre[20]; 
    int necesidad;  
    int disponibilidad;  
}Producto; 
 
typedef struct Nodo { 
 Producto *producto; 
    struct Nodo *siguiente; 
}Nodo; 
 
typedef struct Comuna { 
    Producto productos[Max_numero_producto]; 
    int numero_productos; 
} Comuna; 
 

typedef struct Almacen { 
    Nodo *lista_productos; 
}Almacen; 
 
typedef struct Mercado { 
    Producto anaqueles[Numero_anaqueles]; 
    Producto almacen[Max_numero_producto]; 
    int num_anaqueles; 
}Mercado; 
 
Comuna comunas[Numero_comunas];
sem_t mutex_anaqueles;
sem_t mutex_almacen;