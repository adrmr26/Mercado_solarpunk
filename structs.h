#define Numero_personas 3

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
    int numero_comuna;
    Producto productos[Numero_personas];
    pthread_t personas[Numero_personas];
} Comuna;

typedef struct Almacen {
    Nodo *lista_productos;
}Almacen;

typedef struct Mercado {
    Producto* productos;
    //pthread_mutex_t mutex;
}Mercado;
