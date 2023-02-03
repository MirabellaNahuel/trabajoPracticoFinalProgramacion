#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "LISTACONSUMOS.h"
#define ARCHIVO_CONSUMOS "consumos.bin"

/** \brief inicializa una lista en NULL
 *
 * \return NULL
 *
 */
listaConsumos* inicConsumo(){
    return NULL;
}

/** \brief crea una lista de consumos
 *
 * \param dato stConsumos
 * \param fecha int
 * \return listaConsumos* nuevo
 *
 */
listaConsumos* creaConsumo(stConsumos dato, int fecha){
    listaConsumos* nuevo=(listaConsumos*)malloc(sizeof(listaConsumos));
    nuevo->dato=dato;
    nuevo->fecha= fecha;
    nuevo->modificado=0;
    nuevo->siguiente=NULL;
    return nuevo;
}

/** \brief ingresa un nuevo dato al principio de la lista
 *
 * \param lista listaConsumos*
 * \param nuevo listaConsumos*
 * \return listaConsumos* nuevo
 *
 */
listaConsumos* agregarAlPrincipio(listaConsumos* lista, listaConsumos* nuevo){
    nuevo->siguiente=lista;
    return nuevo;
}

/** \brief agrega un consumo a la lista de forma ordenada
 *
 * \param lista listaConsumos*
 * \param nuevo listaConsumos*
 * \return listaConsumos* lista
 *
 */
listaConsumos* agregarConsumo(listaConsumos* lista, listaConsumos* nuevo){
    if(!lista){
        lista = nuevo;
    }else{
        if(nuevo->fecha <= lista->fecha){
            lista = agregarAlPrincipio(lista, nuevo);
        }else{
            listaConsumos* ante = lista;
            listaConsumos* seg = lista;

            while(seg && (nuevo->fecha > seg->fecha)){
                ante = seg;
                seg = seg->siguiente;
            }
            nuevo->siguiente = seg;
            ante->siguiente = nuevo;
        }
    }
    return lista;
}

/** \brief busca el ultimo dato de la lista
 *
 * \param lista listaConsumos*
 * \return listaConsumos* lista
 *
 */
listaConsumos* buscarUltConsumo(listaConsumos* lista){
    if(lista!=NULL){
        while(lista->siguiente!=NULL){
            lista=lista->siguiente;
        }
    }
    return lista;
}

/** \brief busca el ultimo consumo de una lista segun el id
 *
 * \param lista listaConsumos*
 * \param idConsumo int
 * \return listaConsumos* buscado
 *
 */
listaConsumos* buscaConsumoXId(listaConsumos* lista, int idConsumo){
    listaConsumos* buscado=NULL;
    if(lista!=NULL){
        while(lista!=NULL){
            if(lista->dato.id==idConsumo){
                buscado=lista;
            }
            lista=lista->siguiente;
        }
    }
    return buscado;
}

/** \brief borra el primer dato de la lista
 *
 * \param lista listaConsumos*
 * \return listaConsumos* lista
 *
 */
listaConsumos* borraPrimerConsumo(listaConsumos* lista){
    if(lista!=NULL){
        listaConsumos* aux=lista;
        lista=lista->siguiente;
        free(aux);
        aux=NULL;
    }
    return lista;
}

/** \brief compara el id del cliente hasta que lo encuentra y elimina la lista que contiene sus consumos
 *
 * \param lista listaConsumos*
 * \param idConsumo int
 * \return listaConsumos* lista
 *
 */
listaConsumos* borraConsumoXId(listaConsumos* lista, int idConsumo){
    listaConsumos* seg;
    listaConsumos* ante;
    if(lista && idConsumo==lista->dato.id){
        listaConsumos* aux=lista;
        lista=lista->siguiente;
        free(aux);
    }else{
        seg = lista;
        while(seg && idConsumo==lista->dato.id){
            ante = seg;
            seg = seg->siguiente;
        }if(seg){
            ante->siguiente=seg->siguiente;
            free(seg);
        }
    }
    return lista;
}

/** \brief agrega los consumos ordenado por fecha
 *
 * \param lista listaConsumos*
 * \param nuevo listaConsumos*
 * \return listaConsumos* lista
 *
 */
listaConsumos* agregarConsumoPorFecha(listaConsumos* lista, listaConsumos* nuevo){
    if(!lista){
        lista = nuevo;
    }else{
        if(nuevo->dato.id <= lista->dato.id){
            lista = agregarAlPrincipio(lista, nuevo);
        }else{
            listaConsumos* ante = lista;
            listaConsumos* seg = lista;

            while(seg && (nuevo->dato.id > seg->dato.id)){
                ante = seg;
                seg = seg->siguiente;
            }
            nuevo->siguiente = seg;
            ante->siguiente = nuevo;
        }
    }
    return lista;
}

/** \brief muestra una lista
 *
 * \param consumo listaConsumos*
 * \return void
 *
 */
void muestraUnaListaConsumo(listaConsumos* consumo){
    while(consumo!=NULL){
        if(consumo->dato.baja==0){
            muestraUnConsumo(consumo->dato);
        }
        consumo=consumo->siguiente;
    }
}

/** \brief busca el consumo por idConsumo
 *
 * \param lista listaConsumos*
 * \param id int
 * \return int flag
 *
 */
int buscaNodoConsumoXId(listaConsumos* lista, int id){
    int flag=0;
    while(flag==0 && lista!=NULL){
        if(lista->dato.id==id){
            flag=1;
        }
        lista=lista->siguiente;
    }
    return flag;
}

/** \brief borra la lista de consumo
 *
 * \param lista listaConsumos*
 * \return listaConsumos* lista
 *
 */
listaConsumos* borrarListaConsumos(listaConsumos* lista){
    listaConsumos* aux=NULL;
    while(lista){
        aux=lista;
        bajaDeConsumo(ARCHIVO_CONSUMOS, aux->dato.id);
        lista=lista->siguiente;
        free(aux);
    }
    return lista;
}

/** \brief segun la opcion elegida por usario la funcion modifica el dato, una vez terminado lo guarda restaurado en el archivo
 *
 * \param nombreArchivo[] char
 * \param id int
 * \param opcion int
 * \param lista listaConsumos*
 * \return void
 *
 */
void modificaConsumosDesdeStruct(char nombreArchivo[], int id, int opcion, listaConsumos* lista){
    stConsumos co;
    int flag=0;

    FILE * consu = fopen(nombreArchivo, "r+b");

    if(consu){
        while(flag==0 && fread(&co, sizeof(stConsumos), 1, consu)>0){
            if(co.id == id){
                fseek(consu, -1 * sizeof(stConsumos), SEEK_CUR);

                if (opcion == 1){
                    co.anio = lista->dato.anio;
                    lista->modificado = 1;

                }
                if (opcion == 2){
                    co.mes = lista->dato.mes;
                    lista->modificado = 1;
                }
                if (opcion == 3){
                    co.dia = lista->dato.dia;
                    lista->modificado = 1;
                }
                if (opcion == 4){
                    co.datosConsumidos = lista->dato.datosConsumidos;
                    lista->modificado = 1;
                }
                if(lista->modificado == 1){
                fwrite(&co, sizeof(stConsumos), 1, consu);
                muestraUnConsumo(co);
                }
                system("pause");
                flag=1;
            }
        }
        fclose(consu);
    }
}

/** \brief acumula los datos consumidos en un mes
 *
 * \param lista listaConsumos*
 * \param mes int
 * \return int acum
 *
 */
int consumoMensual(listaConsumos* lista, int mes){
    int acum=0;
    if(lista){
        while(lista!=NULL){
            if(lista->dato.mes == mes){
                acum = acum + lista->dato.datosConsumidos;
            }
            lista = lista->siguiente;
        }
    }
    return acum;
}

/** \brief acumula los datos consumidos en un año
 *
 * \param lista listaConsumos*
 * \param anio int
 * \return int acum
 *
 */
int consumoAnio(listaConsumos* lista, int anio){
    int acum=0;
    if(lista){
        while(lista!=NULL){
            if(lista->dato.anio == anio){
                acum = acum + lista->dato.datosConsumidos;
            }
            lista = lista->siguiente;
        }
    }
    return acum;
}

/** \brief acumula los datos total consumidos por un usuario
 *
 * \param lista listaConsumos*
 * \param idCliente int
 * \return int acum
 *
 */
int sumaConsumos(listaConsumos* lista, int idCliente){
    int acum=0;
    if(lista){
        while(lista!=NULL){
            if(lista->dato.idCliente == idCliente){
                acum = acum + lista->dato.datosConsumidos;
                lista = lista->siguiente;
            }else{
                lista = lista->siguiente;
            }
        }
    }
    return acum;
}
