typedef struct Comuna {
	int num_personas;
}Comuna;

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