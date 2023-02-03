#ifndef LISTACONSUMOS_H_INCLUDED
#define LISTACONSUMOS_H_INCLUDED
#include "CONSUMOS.h"

typedef struct _nodo{
    stConsumos dato;
    int fecha;
    int modificado;
    struct _nodo* siguiente;
}listaConsumos;

listaConsumos* inicConsumo();
listaConsumos* creaConsumo(stConsumos dato, int fecha);
listaConsumos* agregarConsumo(listaConsumos* lista, listaConsumos* nuevo);
listaConsumos* agregarAlPrincipio(listaConsumos* lista, listaConsumos* nuevo);
listaConsumos* buscarUltConsumo(listaConsumos* lista);
listaConsumos* buscaConsumoXId(listaConsumos* lista, int idConsumo);
listaConsumos* borraPrimerConsumo(listaConsumos* lista);
listaConsumos* borraConsumoXId(listaConsumos* lista, int idConsumo);
listaConsumos* agregarConsumoPorFecha(listaConsumos* lista, listaConsumos* nuevo);
void muestraUnaListaConsumo(listaConsumos* consumo);
int buscaNodoConsumoXId(listaConsumos* lista, int id);
listaConsumos* borrarListaConsumos(listaConsumos* lista);
void modificaConsumosDesdeStruct(char nombreArchivo[], int id, int opcion, listaConsumos* lista);
int consumoMensual(listaConsumos* lista, int mes);
int consumoAnio(listaConsumos* lista, int anio);
int sumaConsumos(listaConsumos* lista, int idCliente);

#endif // LISTACONSUMOS_H_INCLUDED
