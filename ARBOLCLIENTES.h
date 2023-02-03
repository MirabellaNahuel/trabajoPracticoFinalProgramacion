#ifndef ARBOLCLIENTES_H_INCLUDED
#define ARBOLCLIENTES_H_INCLUDED
#include "CLIENTES.h"
#include "LISTACONSUMOS.h"

typedef struct _Arbol{
    stClientes dato;
    int modificado;
    listaConsumos* consumos;
    struct _Arbol* derecha;
    struct _Arbol* izquierda;
}arbolClientes;

arbolClientes* inicCliente();
arbolClientes* creaNodoCliente(stClientes dato);
arbolClientes* cargaCliente(arbolClientes* arbol, stClientes dato);
arbolClientes* buscaClienteXId(arbolClientes* arbol, int idCliente);
arbolClientes* buscaClienteXDNI(arbolClientes* arbol, char dni[]);
arbolClientes* buscaClienteXEmail(arbolClientes* arbol, char email[]);
arbolClientes* arrayToArbol (stClientes a[], int base, int tope);
arbolClientes* cargaConsumosArchi2Arbol (char nombreArchivo[], arbolClientes* arbol);
void inOrder(arbolClientes* arbol);
void preOrder(arbolClientes* arbol);
void postOrder(arbolClientes* arbol);
arbolClientes* cargaEstructuraComp();
arbolClientes* nodoMasIzquierda(arbolClientes* arbol);
arbolClientes* nodoMasDerecha (arbolClientes* arbol);
arbolClientes* borrar(arbolClientes* arbol, int idcliente);
int existeCliente(arbolClientes* arbol, int idCliente);
void modificaArchivoDesdeArbol(char nombreArchivo[], arbolClientes* arbol, char dni[], int opcion);

#endif // ARBOLCLIENTES_H_INCLUDED
