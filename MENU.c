#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "MENU.h"
#include "ARBOLCLIENTES.h"
#include "gotoxy.h"
#include "windows.h"

#define ESC 27
#define DIM_CONSUMOS 500
#define DIM_CLIENTES 100
#define ARCHIVO_CLIENTES "clientes.bin"
#define ARCHIVO_CONSUMOS "consumos.bin"

void muestraMenu(){

    gotoxy(15,8);
    color(11);
    printf("\t\t\t Bienvenido a Compania telefonica MoviTur \n");
    gotoxy(35,10);
    color(3);
    hidecursor(0);
    system("\t\t\t pause");

    char opcion=0;

    do{
        system("cls");
        replicachar('-', 30);
        printf("\nMENU PRINCIPAL\n");
        replicachar('-', 30);
        printf("\nElija la opcion que desee:\n");
        printf("\n1-CLIENTES");
        printf("\n2-CONSUMOS");
        printf("\n3-ARBOL DE LISTAS");
        printf("\n\nPresione ESC para salir");
        opcion = getch();

        switch(opcion){
            case 49:
                menuClientes();
                break;
            case 50:
                menuConsumos();
                break;
            case 51:
                menuArbolDeListas();
                break;
        }

    }while(opcion != ESC);
    printf("\nFin de la ejecucion\n");

}

void menuClientes(){
    char opcion= 0;
    char dni[30];
    int idcl = buscaUltimoIdClientes(ARCHIVO_CLIENTES);

    do{
        system("cls");
        color(3);
        printf("\n CLIENTES \n");
        printf("\n1-Alta");
        printf("\n2-Baja");
        printf("\n3-Modificacion");
        printf("\n4-Consulta");
        printf("\n5-Listado");
        printf("\n\nPresione ESC para volver al menu principal\n");

        opcion = getch();

        switch(opcion){
            case 49:
                system("cls");
                cargaArchivoClientes(ARCHIVO_CLIENTES, idcl);
                break;
            case 50:
                printf("Ingrese el DNI del cliente que desea dar de baja:");
                fflush(stdin);
                gets(dni);
                bajaDeCliente(ARCHIVO_CLIENTES, dni);
                break;
            case 51:
                menuModificacionClientes();
                break;
            case 52:
                menuConsultaClientes();
                break;
            case 53:
                menuListadoClientes();
                break;
        }

    }while(opcion!= ESC);
}

void menuConsumos(){
    char opcion = 0;
    int idco = buscaUltimoIdConsumos(ARCHIVO_CONSUMOS);
    int id;

    do{
        system("cls");
        color(3);
        printf("\n CONSUMOS \n");
        printf("\n1-Alta");
        printf("\n2-Baja");
        printf("\n3-Modificacion");
        printf("\n4-Consulta");
        printf("\n\nPresione ESC para volver al menu principal\n");

        opcion = getch();

        switch(opcion){
            case 49:
                system("cls");
                cargaArchivoConsumos(ARCHIVO_CONSUMOS, idco);
                break;
            case 50:
                system("cls");
                printf("Ingrese el ID del consumo que desea dar de baja:");
                scanf("%d", &id);
                bajaDeConsumo(ARCHIVO_CONSUMOS, id);
                break;
            case 51:
                menuModificacionConsumos();
                break;
            case 52:
                menuConsultaConsumos();
                break;
        }

    }while(opcion!= ESC);
}

void menuModificacionClientes(){
    char opcion2 = 0;
    char dni[10];

    system("cls");
    printf("Ingrese el DNI del cliente que desea modificar:");
    fflush(stdin);
    gets(dni);

    consultaXDni(ARCHIVO_CLIENTES, dni);
    system("pause");

    do{
        system("cls");
        color(3);
        printf("\n MODIFICACION CLIENTES \n");
        printf("\n1-Nombre");
        printf("\n2-Apellido");
        printf("\n3-DNI");
        printf("\n4-Email");
        printf("\n5-Domicilio");
        printf("\n6-Movil");
        printf("\n\nPresione ESC para volver al menu de clientes\n");

        opcion2 = getch();

        switch(opcion2){
            case 49:
                modificaCliente(ARCHIVO_CLIENTES, dni, 1);
                break;
            case 50:
                modificaCliente(ARCHIVO_CLIENTES, dni, 2);
                break;
            case 51:
                modificaCliente(ARCHIVO_CLIENTES, dni, 3);
                break;
            case 52:
                modificaCliente(ARCHIVO_CLIENTES, dni, 4);
                break;
            case 53:
                modificaCliente(ARCHIVO_CLIENTES, dni, 5);
                break;
            case 54:
                modificaCliente(ARCHIVO_CLIENTES, dni, 6);
                break;
        }

    }while(opcion2!= ESC);
}

void menuModificacionConsumos(){
    char opcion2 = 0;
    int id;

    system("cls");
    printf("Ingrese el ID del consumo que desea modificar:");
    scanf("%d", &id);

    consultaConsumoXId(ARCHIVO_CONSUMOS, id);
    system("pause");

    do{
        system("cls");
        color(3);
        printf("\n MODIFICACION CONSUMOS \n");
        printf("\n1-ID Cliente");
        printf("\n2-Anio");
        printf("\n3-Mes");
        printf("\n4-Dia");
        printf("\n5-Datos Consumidos");
        printf("\n\nPresione ESC para volver al menu de consumos\n");

        opcion2 = getch();

        switch(opcion2){
            case 49:
                modificaConsumos(ARCHIVO_CONSUMOS, id, 1);
                break;
            case 50:
                modificaConsumos(ARCHIVO_CONSUMOS, id, 2);
                break;
            case 51:
                modificaConsumos(ARCHIVO_CONSUMOS, id, 3);
                break;
            case 52:
                modificaConsumos(ARCHIVO_CONSUMOS, id, 4);
                break;
            case 53:
                modificaConsumos(ARCHIVO_CONSUMOS, id, 5);
                break;
        }

    }while(opcion2!= ESC);
}

void menuConsultaConsumos(){
    char opcion2 = 0;
    stConsumos consumosPorCliente [DIM_CONSUMOS];
    stConsumos consumosPorFecha [DIM_CONSUMOS];
    char dni[10];
    int vConsumosCliente;
    int vConsumosFecha;
    int idconsumo;
    int idcliente;
    int anio;
    int mes;
    int dia;

    do{
        system("cls");
        color(3);
        printf("\n CONSULTA DE CONSUMOS \n");
        printf("\n1-Por ID de Consumo");
        printf("\n2-Por ID de Cliente");
        printf("\n3-Por DNI de Cliente");
        printf("\n4-Por Fecha");
        printf("\n5-Todos los Consumos");
        printf("\n\nPresione ESC para volver al menu de consumos\n");

        opcion2 = getch();
        system("cls");

        switch(opcion2){
            case 49:
                printf("Ingrese el ID del consumo:");
                scanf("%d", &idconsumo);
                consultaConsumoXId(ARCHIVO_CONSUMOS, idconsumo);
                system("pause");
                break;
            case 50:
                printf("Ingrese el ID del cliente:");
                scanf("%d", &idcliente);
                vConsumosCliente=0;

                if(buscaIdClienteConsumos(ARCHIVO_CONSUMOS, idcliente)==1){
                    for(mes=1;mes<13;mes++){
                        vConsumosCliente=archi2arregloConsumosDeCliente(ARCHIVO_CONSUMOS, consumosPorCliente, DIM_CONSUMOS, idcliente, mes);
                        ordenaArregloPorFecha(consumosPorCliente, vConsumosCliente);
                        muestraArregloConsumos(consumosPorCliente, vConsumosCliente);
                    }
                }else{
                    printf("\nEl cliente no tiene consumos\n\n");
                }

                system("pause");

                break;
            case 51:
                printf("Ingrese el DNI del cliente:");
                fflush(stdin);
                gets(dni);
                idcliente = retornaNroClientePorDni(ARCHIVO_CLIENTES, dni);
                vConsumosCliente=0;

                if(buscaIdClienteConsumos(ARCHIVO_CONSUMOS, idcliente)==1){
                    for(mes=1;mes<13;mes++){
                        vConsumosCliente=archi2arregloConsumosDeCliente(ARCHIVO_CONSUMOS, consumosPorCliente, DIM_CONSUMOS, idcliente, mes);
                        ordenaArregloPorFecha(consumosPorCliente, vConsumosCliente);
                        muestraArregloConsumos(consumosPorCliente, vConsumosCliente);
                    }
                }else{
                    printf("\nEl cliente no tiene consumos\n");
                }

                system("pause");

                break;
            case 52:
                printf("Ingrese el anio: ");
                scanf("%d", &anio);
                printf("Ingrese el mes: ");
                scanf("%d", &mes);
                printf("Ingrese el dia: ");
                scanf("%d", &dia);
                vConsumosFecha=0;

                if(buscaFechaConsumos(ARCHIVO_CONSUMOS, anio, mes, dia)==1){
                    vConsumosFecha=arregloConsumosDeFecha(ARCHIVO_CONSUMOS, consumosPorFecha, DIM_CONSUMOS, anio, mes, dia);
                    muestraArregloConsumos(consumosPorFecha, vConsumosFecha);
                }else{
                    printf("\nNo hay consumos de esa fecha\n");
                }
                system("pause");

                break;
            case 53:
                muestraArchivoConsumos(ARCHIVO_CONSUMOS);
                system("pause");
                break;

        }
    }while(opcion2!= ESC);
}

void menuConsultaClientes(){
    int opcion3=0;
    char dni[30];
    int nroCliente;
    int existe;

    do{
        system("cls");
        color(3);
        printf("\n CONSULTA DE CLIENTES\n");
        printf("\n1-Por DNI");
        printf("\n2-Por Nro. de cliente");
        printf("\nPresione ESC para volver al menu de clientes\n");

        opcion3 = getch();
        system("cls");
        switch(opcion3){
            case 49:
                do{
                    printf("Ingrese numero de DNI: ");
                    fflush(stdin);
                    gets(dni);
                    existe=busquedaClienteXDni(ARCHIVO_CLIENTES, dni);
                    consultaXDni(ARCHIVO_CLIENTES, dni);
                    system("cls");
                }while(existe==0);

                break;
            case 50:
                do{
                    printf("Ingrese numero de cliente: ");
                    scanf("%d", &nroCliente);
                    existe=consultaXNroCl(ARCHIVO_CLIENTES, nroCliente);
                if(existe==0){
                    printf("\nNumero de cliente incorrecto.\n");
                    getch();
                }
                system("cls");

                }while(existe==0);

                break;
        }
    }while(opcion3 != ESC);
}

void menuListadoClientes(){
    stClientes clientes[DIM_CLIENTES];
    int validosClientes=0;
    int opcion4=0;

    do{
        system("cls");
        color(3);
        printf("\n LISTADO \n");
        printf("\n1-Ordenar por apellido");
        printf("\n2-Ordenar por DNI");
        printf("\n3-Ordenar por Nro. de cliente");
        printf("\n4-Listado");

        printf("\n\nPresione ESC para volver al menu de clientes\n");
        opcion4 = getch();

        system("cls");
        switch(opcion4){
             case 49:
                 validosClientes=0;
                 validosClientes=deArchivoAArreglo(ARCHIVO_CLIENTES, clientes, DIM_CLIENTES, validosClientes);
                 ordenaClientePorApellido(clientes, validosClientes);
                 muestraArregloClientes(clientes, validosClientes);
                 break;
             case 50:
                 validosClientes=0;
                 validosClientes=deArchivoAArreglo(ARCHIVO_CLIENTES, clientes, DIM_CLIENTES, validosClientes);
                 ordenaClientePorDni(clientes, validosClientes);
                 muestraArregloClientes(clientes, validosClientes);
                 break;
             case 51:
                 validosClientes=0;
                 validosClientes=deArchivoAArreglo(ARCHIVO_CLIENTES, clientes, DIM_CLIENTES, validosClientes);
                 ordenXNroCliente(clientes, validosClientes);
                 muestraArregloClientes(clientes, validosClientes);
                 break;
             case 52:
                 muestraArchivoCliente(ARCHIVO_CLIENTES);
                 system("pause");
                 break;
        }
    }while(opcion4!= ESC);
}

void replicachar(char e, int cant){

    for(int i=0; i<cant; i++){
        printf("%c", e);
    }
    printf("\n");
}

void menuArbolDeListas(){
    arbolClientes* arbolito;
    arbolito=inicCliente();
    arbolito = cargaEstructuraComp();
    int opcion5=0;

    do{
        system("cls");
        color(3);
        printf("\n ARBOL DE LISTAS: \n");
        printf("\n1-Consultas");
        printf("\n2-Modificacion");
        printf("\n3-Borrado");
        printf("\n4-Facturacion");
        printf("\n\nPresione ESC para volver al menu de consumos\n");

        opcion5 = getch();
        system("cls");

        switch(opcion5){
            case 49:
                menuConsultaArbol(arbolito);
                break;
            case 50:
                menuModificaciones(arbolito);
                break;
            case 51:
                arbolito=menuBorradoArbol(arbolito);
                break;
            case 52:
                menuFacturacion(arbolito);
                break;
        }
    }while(opcion5!= ESC);
}

void menuConsultaArbol(arbolClientes* arbolito){

    arbolClientes* buscado=inicCliente();
    arbolClientes* buscado2=inicCliente();

    char opcion6=0;
    int id;

    do{
        system("cls");
        color(3);
        printf("\n CONSULTA: \n");
        printf("\n1-Ver cliente");
        printf("\n2-Ver consumos de cliente");
        printf("\n3-Mostrar Arbol");
        printf("\n\nPresione ESC para volver al menu de consumos\n");

        opcion6 = getch();
        system("cls");

        switch(opcion6){
            case 49:
                do{
                printf("\nIngrese ID del cliente: ");
                scanf("%d", &id);
                buscado = buscaClienteXId(arbolito, id);

                if(buscado==NULL)
                {
                    printf("\nID incorrecto, ingrese ID valido\n");
                }
                }while(buscado==NULL);

                muestraUnCliente(buscado->dato);

                system("pause");
                break;
            case 50:
                do{
                printf("\nIngrese ID del cliente: ");
                scanf("%d", &id);
                buscado2 = buscaClienteXId(arbolito, id);

                if(buscado2==NULL)
                {
                    printf("\nID incorrecto, ingrese ID valido\n");
                }
                }while(buscado2==NULL);

                muestraUnCliente(buscado2->dato);
                muestraUnaListaConsumo(buscado2->consumos);
                system("pause");
                break;
            case 51:
                menuMostrarArbol(arbolito);
                break;
        }
    }while(opcion6!= ESC);
}

void menuMostrarArbol(arbolClientes* arbolito)
{
    char opcion7=0;

    do{
        system("cls");
        color(3);
        printf("\n MOSTRAR ARBOL: \n");
        printf("\n1-InOrder");
        printf("\n2-PreOrder");
        printf("\n3-PostOrder");
        printf("\n\nPresione ESC para volver al menu de consumos\n");

        opcion7 = getch();
        system("cls");

        switch(opcion7){
            case 49:
                inOrder(arbolito);
                system("pause");
                break;
            case 50:
                preOrder(arbolito);
                system("pause");
                break;
            case 51:
                postOrder(arbolito);
                system("pause");
                break;
        }
    }while(opcion7!= ESC);
}

arbolClientes* menuBorradoArbol(arbolClientes* arbolito){
    arbolClientes* buscado=inicCliente();
    int id;
    int id2;
    int existe=0;
    int existe2=0;
    char dni[50];

    char opcion8=0;

    do{
        system("cls");
        color(3);
        printf("\n MENU BORRADO: \n");
        printf("\n1-Borrar un cliente");
        printf("\n2-Borrar un consumo");
        printf("\n\nPresione ESC para volver al menu de consumos\n");

        opcion8 = getch();
        system("cls");

        switch(opcion8){
            case 49:
                do{
                printf("Ingrese el ID del Cliente que desea borrar:");
                scanf("%d", &id);
                buscado=buscaClienteXId(arbolito, id);
                if(buscado==NULL)
                {
                    printf("\nID incorrecto, ingrese ID valido\n");
                }
                muestraUnCliente(buscado->dato);
                }while(buscado==NULL);

                buscado->modificado=1;
                buscado->consumos->modificado=1;
                buscado->consumos=borrarListaConsumos(buscado->consumos);
                bajaDeCliente(ARCHIVO_CLIENTES, buscado->dato.dni);
                arbolito = borrar(arbolito, id);

                break;
            case 50:
                do{
                    printf("\nIngrese DNI del cliente, el cual desea borrar su consumo: ");
                    fflush(stdin);
                    gets(dni);
                    existe=busquedaClienteXDni(ARCHIVO_CLIENTES, dni);
                    if(existe==0)
                    {
                        printf("\nDNI incorrecto, ingrese DNI valido\n");
                        getch();
                    }
                    system("cls");
                }while(existe==0);
                id2=retornaNroClientePorDni(ARCHIVO_CLIENTES, dni);
                buscado=buscaClienteXId(arbolito, id2);
                printf("\nEstos son sus consumos: \n");
                muestraUnaListaConsumo(buscado->consumos);
                getch();
                do{
                printf("\nIngrese el ID del consumo que desea borrar: ");
                fflush(stdin);
                scanf("%d", &id);
                fflush(stdin);
                existe2=buscaNodoConsumoXId(buscado->consumos, id);
                if(existe2==0)
                    {
                        printf("\nID incorrecto, ingrese ID valido\n");
                    }
                }while(existe2==0);
                buscado->consumos=borraConsumoXId(buscado->consumos, id);
                bajaDeConsumo(ARCHIVO_CONSUMOS, id);

                break;

        }
    }while(opcion8!= ESC);
    return arbolito;
}

arbolClientes* menuModificacionClientesArbol(arbolClientes* arbolito)
{
    int id;
    arbolClientes* buscado=inicCliente();
    char opcion8=0;
    int existe=0;
    int existe2=0;
    int existe3=0;
    int existe4=0;
    int existe5=0;

    do{
        system("cls");
        color(3);
        printf("\n ¿QUE DESEA MODIFICAR?: \n");
        printf("\n1-Nombre");
        printf("\n2-Apellido");
        printf("\n3-DNI");
        printf("\n4-Direccion");
        printf("\n5-Nro de celular");
        printf("\n\nPresione ESC para volver al menu de consumos\n");

        opcion8 = getch();
        system("cls");

        switch(opcion8){
            case 49:
                do{
                printf("\nIngrese el ID del cliente, para cambiar su nombre: ");
                fflush(stdin);
                scanf("%d", &id);
                fflush(stdin);
                existe=existeCliente(arbolito, id);
                if(existe==0)
                    {
                        printf("\nID incorrecto, ingrese ID valido\n");
                    }
                }while(existe==0);
                buscado=buscaClienteXId(arbolito, id);
                buscado->dato=cambiaNombre(buscado->dato);
                modificaArchivoDesdeArbol(ARCHIVO_CLIENTES, buscado, buscado->dato.dni, 1);

                break;
            case 50:
                do{
                printf("\nIngrese el ID del cliente para cambiar su apellido: ");
                fflush(stdin);
                scanf("%d", &id);
                fflush(stdin);
                existe2=existeCliente(arbolito, id);
                if(existe2==0)
                    {
                        printf("\nID incorrecto, ingrese ID valido\n");
                    }
                }while(existe2==0);
                buscado=buscaClienteXId(arbolito, id);
                buscado->dato=cambiaApellido(buscado->dato);
                modificaArchivoDesdeArbol(ARCHIVO_CLIENTES, buscado, buscado->dato.dni, 2);
                break;
            case 51:
                do{
                printf("\nIngrese el ID del cliente, para cambiar su DNI: ");
                fflush(stdin);
                scanf("%d", &id);
                fflush(stdin);
                existe3=existeCliente(arbolito, id);
                if(existe3==0)
                    {
                        printf("\nID incorrecto, ingrese ID valido\n");
                    }
                }while(existe3==0);
                buscado=buscaClienteXId(arbolito, id);
                buscado->dato=cambiaDni(buscado->dato);
                modificaArchivoDesdeArbol(ARCHIVO_CLIENTES, buscado, buscado->dato.dni, 3);
                break;
            case 52:
                do{
                printf("\nIngrese el ID del cliente, para cambiar su direccion: ");
                fflush(stdin);
                scanf("%d", &id);
                fflush(stdin);
                existe4=existeCliente(arbolito, id);
                if(existe4==0)
                    {
                        printf("\nID incorrecto, ingrese ID valido\n");
                    }
                }while(existe4==0);
                buscado=buscaClienteXId(arbolito, id);
                buscado->dato=cambiaDireccion(buscado->dato);
                modificaArchivoDesdeArbol(ARCHIVO_CLIENTES, buscado, buscado->dato.dni, 4);

                break;
            case 53:
                do{
                printf("\nIngrese el ID del cliente, para cambiar su Nro de celular: ");
                fflush(stdin);
                scanf("%d", &id);
                fflush(stdin);
                existe5=existeCliente(arbolito, id);
                if(existe5==0)
                    {
                        printf("\nID incorrecto, ingrese ID valido\n");
                    }
                }while(existe5==0);
                buscado=buscaClienteXId(arbolito, id);
                buscado->dato=cambiaMovil(buscado->dato);
                modificaArchivoDesdeArbol(ARCHIVO_CLIENTES, buscado, buscado->dato.dni, 5);

                break;
        }
    }while(opcion8!= ESC);

    return arbolito;
}

void menuModificaciones(arbolClientes* arbolito)
{
    char opcion9=0;
    do{
        system("cls");
        color(3);
        printf("MENU MODIFICACION\n");
        printf("\n1-Clientes");
        printf("\n2-Consumos");
        printf("\n\nPresione ESC para volver al menu anterior\n");

        opcion9 = getch();
        system("cls");

        switch(opcion9){
            case 49:
                arbolito=menuModificacionClientesArbol(arbolito);
                break;
            case 50:
                arbolito=menuModificacionCosumosArbol(arbolito);
                break;
        }
    }while(opcion9!= ESC);
}

arbolClientes* menuModificacionCosumosArbol(arbolClientes* arbolito)
{
        arbolClientes* buscado=inicCliente();
        listaConsumos* aux=inicConsumo();
        int id;
        int id2;
        int existe=0;
        int existe2=0;
        char dni[30];
        char opcion10=0;
    do{
        system("cls");
        color(3);
        printf("\n ¿QUE DESEA MODIFICAR?: \n");
        printf("\n1-Anio de consumo");
        printf("\n2-Mes de consumo");
        printf("\n3-Dia de consumo");
        printf("\n4-Cant. de  datos consumidos");
        printf("\n\nPresione ESC para volver al menu anterior\n");

        opcion10 = getch();
        system("cls");

        switch(opcion10){

            case 49:
                do{
                    printf("\nIngrese DNI del cliente: ");
                    fflush(stdin);
                    gets(dni);
                    existe=busquedaClienteXDni(ARCHIVO_CLIENTES, dni);
                    if(existe==0)
                    {
                        printf("\nDNI incorrecto, ingrese DNI valido\n");
                        getch();
                    }
                    system("cls");
                }while(existe==0);
                    id2=retornaNroClientePorDni(ARCHIVO_CLIENTES, dni);
                    buscado=buscaClienteXId(arbolito, id2);
                    printf("\nEstos son sus consumos: \n");
                    muestraUnaListaConsumo(buscado->consumos);
                    getch();
            do{
                printf("\nIngrese el ID del consumo que desea modificar: ");
                fflush(stdin);
                scanf("%d", &id);
                fflush(stdin);
                existe2=buscaNodoConsumoXId(buscado->consumos, id);
                if(existe2==0)
                    {
                        printf("\nID incorrecto, ingrese ID valido\n");
                    }
                }while(existe2==0);
                aux=buscaConsumoXId(buscado->consumos, id);
                aux->dato.anio=cambiaAnio();
                modificaConsumosDesdeStruct(ARCHIVO_CONSUMOS, aux->dato.id, 1, aux);
                break;

            case 50:
                do{
                    printf("\nIngrese DNI del cliente: ");
                    fflush(stdin);
                    gets(dni);
                    existe=busquedaClienteXDni(ARCHIVO_CLIENTES, dni);
                    if(existe==0)
                    {
                        printf("\nDNI incorrecto, ingrese DNI valido\n");
                        getch();
                    }
                    system("cls");
                }while(existe==0);
                    id2=retornaNroClientePorDni(ARCHIVO_CLIENTES, dni);
                    buscado=buscaClienteXId(arbolito, id2);
                    printf("\nEstos son sus consumos: \n");
                    muestraUnaListaConsumo(buscado->consumos);
                    getch();
            do{
                printf("\nIngrese el ID del consumo que desea modificar: ");
                fflush(stdin);
                scanf("%d", &id);
                fflush(stdin);
                existe2=buscaNodoConsumoXId(buscado->consumos, id);
                if(existe2==0)
                    {
                        printf("\nID incorrecto, ingrese ID valido\n");
                    }
                }while(existe2==0);
                aux=buscaConsumoXId(buscado->consumos, id);
                aux->dato.mes=cambiaMes();
                modificaConsumosDesdeStruct(ARCHIVO_CONSUMOS, aux->dato.id, 2, aux);

                break;

            case 51:
                do{
                    printf("\nIngrese DNI del cliente: ");
                    fflush(stdin);
                    gets(dni);
                    existe=busquedaClienteXDni(ARCHIVO_CLIENTES, dni);
                    if(existe==0)
                    {
                        printf("\nDNI incorrecto, ingrese DNI valido\n");
                        getch();
                    }
                    system("cls");
                }while(existe==0);
                    id2=retornaNroClientePorDni(ARCHIVO_CLIENTES, dni);
                    buscado=buscaClienteXId(arbolito, id2);
                    printf("\nEstos son sus consumos: \n");
                    muestraUnaListaConsumo(buscado->consumos);
                    getch();
            do{
                printf("\nIngrese el ID del consumo que desea modificar: ");
                fflush(stdin);
                scanf("%d", &id);
                fflush(stdin);
                existe2=buscaNodoConsumoXId(buscado->consumos, id);
                if(existe2==0)
                    {
                        printf("\nID incorrecto, ingrese ID valido\n");
                    }
                }while(existe2==0);
                aux=buscaConsumoXId(buscado->consumos, id);
                aux->dato=cambiaDia(aux->dato);
                modificaConsumosDesdeStruct(ARCHIVO_CONSUMOS, aux->dato.id, 3, aux);

                break;

            case 52:
                do{
                    printf("\nIngrese DNI del cliente: ");
                    fflush(stdin);
                    gets(dni);
                    existe=busquedaClienteXDni(ARCHIVO_CLIENTES, dni);
                    if(existe==0)
                    {
                        printf("\nDNI incorrecto, ingrese DNI valido\n");
                        getch();
                    }
                    system("cls");
                }while(existe==0);
                    id2=retornaNroClientePorDni(ARCHIVO_CLIENTES, dni);
                    buscado=buscaClienteXId(arbolito, id2);
                    printf("\nEstos son sus consumos: \n");
                    muestraUnaListaConsumo(buscado->consumos);
                    getch();
            do{
                printf("\nIngrese el ID del consumo que desea modificar: ");
                fflush(stdin);
                scanf("%d", &id);
                fflush(stdin);
                existe2=buscaNodoConsumoXId(buscado->consumos, id);
                if(existe2==0)
                    {
                        printf("\nID incorrecto, ingrese ID valido\n");
                    }
                }while(existe2==0);
                aux=buscaConsumoXId(buscado->consumos, id);
                aux->dato.datosConsumidos=cambiaDatosConsumidos();
                modificaConsumosDesdeStruct(ARCHIVO_CONSUMOS, aux->dato.id, 4, aux);
                break;
        }
    }while(opcion10!= ESC);

    return arbolito;
}

void menuFacturacion(arbolClientes* arbolito){
    arbolClientes* arbol = inicCliente();
    char opcion11=0;
    int id=0;
    int num=0;
    int acum = 0;
    printf("\nIngrese ID Cliente a facturar: ");
    scanf("%d", &id);
    arbol = buscaClienteXId(arbolito, id);

    do{
        system("cls");
        color(3);
        printf("\n FACTURACION: \n");
        printf("\n1-Mensual");
        printf("\n2-Anual");
        printf("\n3-Total facturado");

        opcion11 = getch();

        system("cls");

        switch(opcion11){
            case 49:
                printf("Ingrese Mes a facturar: ");
                scanf("%d", &num);
                acum = consumoMensual(arbol->consumos, num);
                system("cls");
                facturacion(arbol, acum);
                system("pause");
                break;
            case 50:
                printf("\nIngrese Anio a facturar: ");
                scanf("%d", &num);
                acum = consumoAnio(arbol->consumos, num);
                system("cls");
                facturacion(arbol, acum);
                system("pause");
                break;
            case 51:
                acum = sumaConsumos(arbol->consumos, id);
                system("cls");
                facturacion(arbol, acum);
                system("pause");
                break;
        }
    }while(opcion11!= ESC);
}

void facturacion(arbolClientes* arbolito, int acum){
    int i=0;
    float precio =(float) acum*(0.25);
    float iva =(float) precio*(1.21);

    printf("%c", 201);
    for(i=0; i<60; i++){
        printf("%c", 205);
    }
    printf("%c", 187);

    gotoxy(0,1);
    printf("%c\t\t\t MoviTur", 186);
    gotoxy(61,1);
    printf("%c", 186);

    gotoxy(0,2);
    printf("%c", 204);
    for(i=0; i<60; i++){
        printf("%c", 205);
    }
    gotoxy(61,2);
    printf("%c", 185);

    gotoxy(0,3);
    printf("%c Cliente: %d", 186, arbolito->dato.nroCliente);
    gotoxy(61,3);
    printf("%c", 186);

    gotoxy(0,4);
    printf("%c   Nombre: ................. %s", 186, arbolito->dato.nombre);
    gotoxy(61,4);
    printf("%c", 186);
    gotoxy(0,5);
    printf("%c   Apellido: ............... %s", 186, arbolito->dato.apellido);
    gotoxy(61,5);
    printf("%c", 186);
    gotoxy(0,6);
    printf("%c   Domicilio: .............. %s", 186, arbolito->dato.domicilio);
    gotoxy(61,6);
    printf("%c", 186);
    gotoxy(0,7);
    printf("%c   DNI: .................... %s", 186, arbolito->dato.dni);
    gotoxy(61,7);
    printf("%c", 186);
    gotoxy(0,8);
    printf("%c   Mail: ................... %s", 186, arbolito->dato.email);
    gotoxy(61,8);
    printf("%c", 186);

    gotoxy(0,9);
    printf("%c", 186);
    gotoxy(61,9);
    printf("%c", 186);
    gotoxy(0,10);
    printf("%c", 186);
    gotoxy(61,10);
    printf("%c", 186);
    gotoxy(0,11);
    printf("%c", 186);
    gotoxy(61,11);
    printf("%c", 186);
    gotoxy(0,12);
    printf("%c", 186);
    gotoxy(61,12);
    printf("%c", 186);
    gotoxy(0,13);
    printf("%c", 186);
    gotoxy(61,13);
    printf("%c", 186);

    gotoxy(0,14);
    printf("%c", 186);
    gotoxy(30,14);
    printf("Total Datos consumidos: %d", acum);
    gotoxy(61,14);
    printf("%c", 186);
    gotoxy(0,15);
    printf("%c", 186);
    gotoxy(30,15);
    printf("Total: .............. $ %2.f", precio);
    gotoxy(61,15);
    printf("%c", 186);
    gotoxy(0,16);
    printf("%c", 186);
    gotoxy(30,16);
    printf("Total + IVA: ........ $ %2.f", iva);
    gotoxy(61,16);
    printf("%c", 186);

    gotoxy(0,17);
    printf("%c", 186);
    gotoxy(61,17);
    printf("%c", 186);
    gotoxy(0,18);
    printf("%c", 200);
    for(i=0; i<60; i++){
        printf("%c", 205);
    }
    gotoxy(61,18);
    printf("%c", 188);

    printf("\n");
}
