#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "ARBOLCLIENTES.h"

void muestraMenu();
void menuClientes();
void menuConsumos();
void menuModificacionClientes();
void menuModificacionConsumos();
void menuConsultaConsumos();
void menuConsultaClientes();
void menuListadoClientes();
void replicachar(char e, int cant);
void menuArbolDeListas();
void menuConsultaArbol(arbolClientes* arbolito);
void menuMostrarArbol(arbolClientes* arbolito);
arbolClientes* menuBorradoArbol(arbolClientes* arbolito);
arbolClientes* menuModificacionClientesArbol(arbolClientes* arbolito);
arbolClientes* menuModificacionCosumosArbol(arbolClientes* arbolito);
void menuModificaciones(arbolClientes* arbolito);
void menuFacturacion(arbolClientes* arbolito);
void facturacion(arbolClientes* arbolito, int acum);

#endif // MENU_H_INCLUDED
