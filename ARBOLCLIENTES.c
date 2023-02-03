#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "ARBOLCLIENTES.h"

#define DIM_CONSUMOS 500
#define DIM_CLIENTES 100
#define ARCHIVO_CLIENTES "clientes.bin"
#define ARCHIVO_CONSUMOS "consumos.bin"

/** \brief inicializa un arbol en NULL
 *
 * \return NULL
 *
 */
arbolClientes* inicCliente(){
    return NULL;
}

/** \brief crea un nodo en el arbol
 *
 * \param dato stClientes
 * \return arbolClientes* nuevo
 *
 */
arbolClientes* creaNodoCliente(stClientes dato){
    arbolClientes* nuevo=(arbolClientes*)malloc(sizeof(arbolClientes));
    nuevo->dato=dato;
    nuevo->modificado=0;
    nuevo->consumos= inicConsumo();
    nuevo->derecha=NULL;
    nuevo->izquierda=NULL;

    return nuevo;
}

/** \brief carga clientes al arbol( si el arbol no contiene datos , lo crea. si el dato es mayor a la raiz lo acomoda en su lugar correspondiente a la derecha, si no lo es en la izquierda)
 *
 * \param arbol arbolClientes*
 * \param dato stClientes
 * \return arbolClientes* arbol
 *
 */
arbolClientes* cargaCliente(arbolClientes* arbol, stClientes dato){
    if(arbol==NULL){
        arbol=creaNodoCliente(dato);
    }else{
        if(dato.id > arbol->dato.id){
            arbol->derecha=cargaCliente(arbol->derecha, dato);
        }else{
            arbol->izquierda=cargaCliente(arbol->izquierda, dato);
        }
    }
    return arbol;
}

/** \brief busca un cliente por id, compara el entero ingresado por parametro con los id guardados en el arbol)
 *
 * \param arbol arbolClientes*
 * \param idCliente int
 * \return arbolClientes* buscado
 *
 */
arbolClientes* buscaClienteXId(arbolClientes* arbol, int idCliente){
    arbolClientes* buscado=NULL;
    if(arbol!=NULL){
        if(idCliente==arbol->dato.id){
            buscado=arbol;
        }else{
            if(idCliente>arbol->dato.id){
                buscado=buscaClienteXId(arbol->derecha, idCliente);
            }else{
            buscado=buscaClienteXId(arbol->izquierda, idCliente);
            }
        }
    }
    return buscado;
}

/** \brief busca un cliente por dni comparando el char ingresado por parametro con los dni guardados en el arbol
 *
 * \param arbol arbolClientes*
 * \param dni[] char
 * \return arbolClientes* buscado
 *
 */
arbolClientes* buscaClienteXDNI(arbolClientes* arbol, char dni[]){
    arbolClientes* buscado=NULL;
    if(arbol!=NULL){
        if(strcmp(dni,arbol->dato.dni)==0){
            buscado=arbol;
        }else{
            if(strcmp(dni,arbol->dato.dni)>0){
                buscado=buscaClienteXDNI(arbol->derecha, dni);
            }else{
                buscado=buscaClienteXDNI(arbol->izquierda, dni);
            }
        }
    }
    return buscado;
}

/** \brief al igual que la funcion de busqueda por dni compara los strings del mail guardado en el arbol con el ingresado por parametro
 *
 * \param arbol arbolClientes*
 * \param email[] char
 * \return arbolClientes* buscado
 *
 */
arbolClientes* buscaClienteXEmail(arbolClientes* arbol, char email[]){
    arbolClientes* buscado=NULL;
    if(arbol!=NULL){
        if(strcmp(email,arbol->dato.email)==0){
            buscado=arbol;
        }else{
            if(strcmp(email,arbol->dato.email)>0){
                buscado=buscaClienteXEmail(arbol->derecha, email);
            }else{
                buscado=buscaClienteXEmail(arbol->izquierda, email);
            }
        }
    }
    return buscado;
}

/** \brief crea un arbol de arreglos
 *
 * \param stClientes a[]
 * \param int base, int tope
 * \return arbolCliente* arbol
 *
 */
arbolClientes* arrayToArbol (stClientes a[], int base, int tope){
    int medio;

    arbolClientes* arbol=inicCliente();

    if(!(base>tope))
    {

        medio=(base+tope)/2;

        arbol=creaNodoCliente(a[medio]);

        arbol->izquierda=arrayToArbol(a,base,medio-1);
        arbol->derecha=arrayToArbol(a,medio+1,tope);
    }

    return arbol;
}

/** \brief pasa los datos del archivo al arbol
 *
 * \param nombreArchivo[] char
 * \param arbol arbolClientes*
 * \return arbolClientes* arbol
 *
 */
arbolClientes* cargaConsumosArchi2Arbol(char nombreArchivo[], arbolClientes* arbol){
    stConsumos co;
    arbolClientes * buscado = arbol;
    int fecha;

    FILE* consu = fopen(nombreArchivo, "rb");
    if(consu){
        while(fread(&co, sizeof(stConsumos), 1, consu)>0){
            buscado = buscaClienteXId(arbol, co.idCliente);
            fecha = (co.anio * 100 + co.mes) * 100 + co.dia;
            buscado->consumos = agregarConsumo(buscado->consumos, creaConsumo(co, fecha));
        }
        fclose(consu);
    }
    return arbol;
}

/** \brief muestra el arbol primero el lado izquierdo , luego la raiz y por ultimo el lado derecho
 *
 * \param arbol arbolClientes*
 * \return void
 *
 */
void inOrder(arbolClientes* arbol){
    if(arbol!=NULL){
        inOrder(arbol->izquierda);
        if(arbol->dato.eliminado==0){
        muestraUnCliente(arbol->dato);
        muestraUnaListaConsumo(arbol->consumos);
        }
        inOrder(arbol->derecha);
    }
}

/** \brief muestra el arbol primero la raiz, luego de izquierda a derecha
 *
 * \param arbol arbolClientes*
 * \return void
 *
 */
void preOrder(arbolClientes* arbol){
    if(arbol!=NULL){
        if(arbol->dato.eliminado==0){
        muestraUnCliente(arbol->dato);
        }
        preOrder(arbol->izquierda);
        preOrder(arbol->derecha);
    }
}

/** \brief muestra el arbol , primero el lado izquierdo , luego el derecho y por ultimo la raiz
 *
 * \param arbol arbolClientes*
 * \return void
 *
 */
void postOrder(arbolClientes* arbol){
    if(arbol!=NULL){
        postOrder(arbol->izquierda);
        postOrder(arbol->derecha);
        if(arbol->dato.eliminado==0){
        muestraUnCliente(arbol->dato);
        }
    }
}

/** \brief carga los clientes en el arbol y luego sus consumos
 *
 * \return arbolClientes* arbolito
 *
 */
arbolClientes* cargaEstructuraComp(){
    arbolClientes* arbolito;
    arbolito=inicCliente();
    stClientes cl[DIM_CLIENTES];
    int validos=0;
    ///carga clientes en arbol
    validos=deArchivoAArreglo(ARCHIVO_CLIENTES, cl, DIM_CLIENTES, validos);
    arbolito=arrayToArbol(cl, 0, validos-1);
    ///carga consumos en arbol
    arbolito = cargaConsumosArchi2Arbol(ARCHIVO_CONSUMOS, arbolito);

    return arbolito;
}

/** \brief busca el ultimo nodo a la izquierda
 *
 * \param arbol arbolClientes*
 * \return arbolClientes* ultimo
 *
 */
arbolClientes* nodoMasIzquierda(arbolClientes* arbol){
    arbolClientes* ultimo = inicCliente();

    if(arbol != NULL){
        ultimo = nodoMasIzquierda(arbol->izquierda);
    }
    if(ultimo == NULL){
        ultimo = arbol;
    }
    return ultimo;
}

/** \brief busca el ultimo nodo a la derecha
 *
 * \param arbolClientes* arbol
 *
 * \return
 *
 */
arbolClientes* nodoMasDerecha (arbolClientes* arbol){
    arbolClientes* ultimo = inicCliente();

    if(arbol){
        ultimo = nodoMasDerecha(arbol->derecha);
    }
    if(!ultimo){
        ultimo = arbol;
    }
    return ultimo;
}

/** \brief compara los datos de id ingresado por parametro con los del arbol y elimina el nodo que cumple con la similitud
 *
 * \param arbol arbolClientes*
 * \param idcliente int
 * \return arbolClientes* arbol
 *
 */
arbolClientes* borrar(arbolClientes* arbol, int idcliente){
    if(arbol){
        if(arbol->dato.id == idcliente){
            if (arbol->izquierda){
                arbolClientes* ultimoDerecha = nodoMasDerecha(arbol->izquierda);
                arbol->dato = ultimoDerecha->dato;
                arbol->izquierda = borrar(arbol->izquierda, ultimoDerecha->dato.id);
            }else if (arbol->derecha){
                arbolClientes* ultimoIzquierda = nodoMasIzquierda(arbol->derecha);
                arbol->dato = ultimoIzquierda->dato;
                arbol->derecha = borrar(arbol->derecha, ultimoIzquierda->dato.id);
            }else{
                free(arbol);
                arbol = NULL;
            }
        }else{
            if(idcliente > arbol->dato.id){
                arbol->derecha = borrar(arbol->derecha, idcliente);
            }else{
                arbol->izquierda = borrar(arbol->izquierda, idcliente);
            }
        }
    }
    return arbol;
}

/** \brief verifica si existe un cliete en el arbol a travez de la comparacion de los id
 *
 * \param arbol arbolClientes*
 * \param idCliente int
 * \return int i
 *
 */
int existeCliente(arbolClientes* arbol, int idCliente){
    int i=0;
    if(i==0 && arbol!=NULL){
        if(idCliente==arbol->dato.id){
            i=1;
        }else{
            if(idCliente>arbol->dato.id){
                i=existeCliente(arbol->derecha, idCliente);
            }else{
                i=existeCliente(arbol->izquierda, idCliente);
            }
        }
    }
    return i;
}

/** \brief segun la opcion elegida por usario la funcion modifica el dato, una vez termino lo guarda restaurado en el archivo
 *
 * \param nombreArchivo[] char
 * \param arbol arbolClientes*
 * \param dni[] char
 * \param opcion int
 * \return void
 *
 */
void modificaArchivoDesdeArbol(char nombreArchivo[], arbolClientes* arbol, char dni[], int opcion){
    stClientes cl;
    int flag=0;

    FILE *clientes= fopen(nombreArchivo, "r+b");

    if(clientes){
        while(flag==0 && fread(&cl, sizeof(stClientes), 1, clientes)>0){
            if(strcmp(cl.dni, arbol->dato.dni)==0){
                fseek(clientes,-1 * sizeof(stClientes), SEEK_CUR);
                if(opcion==1){
                    strcpy(cl.nombre,arbol->dato.nombre);
                    arbol->modificado = 1;
                }
                if(opcion==2){
                    strcpy(cl.apellido,arbol->dato.apellido);
                    arbol->modificado = 1;
                }
                if(opcion==3){
                    strcpy(cl.dni,arbol->dato.dni);
                    arbol->modificado = 1;
                }
                if(opcion==4){
                    strcpy(cl.email,arbol->dato.email);
                    arbol->modificado = 1;
                }
                if(opcion==5){
                    strcpy(cl.domicilio,arbol->dato.domicilio);
                    arbol->modificado = 1;
                }
                if(opcion==6){
                    strcpy(cl.movil,arbol->dato.movil);
                    arbol->modificado = 1;
                }
                ///escribimos una vez que tengamos la estructura modificada
                if(arbol->modificado == 1){
                fwrite(&cl, sizeof(stClientes), 1, clientes);
                muestraUnCliente(cl);
                }
                flag=1;
                system("pause");
            }
        }
        fclose(clientes);
    }
}
