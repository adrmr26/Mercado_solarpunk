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

typedef struct Almacen {
    Nodo *lista_productos;
}Almacen;

typedef struct Mercado {
    Producto* productos;
    //pthread_mutex_t mutex;
}Mercado;
