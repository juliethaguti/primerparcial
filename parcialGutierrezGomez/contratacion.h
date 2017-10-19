#ifndef CONTRATACION_H_INCLUDED
#define CONTRATACION_H_INCLUDED

typedef struct
{
    char cuitCliente[15];
    char nombreArchivo [51];
    int dias;
    int idContratacion;
    int flagContratacion;
    int idPantalla;
}sContratacion;

#endif // CONTRATACION_H_INCLUDED

#include "pantalla.h"

#define SIN_CONTRATACION 0
#define CON_CONTRATACION 1

#define CANTIDAD_CONTRATOS 10

int contra_initArray(sContratacion* arrayContrataciones, int length);
int contra_cargarArchivo (sContratacion* arrayContratacion, int idPantalla,int longitudArray);
void contra_printPantallasSinContratar(sContratacion *contratacionArray,int longitudContratacion, sPantalla* pantallasArray, int longitudPantallas);
int contra_modificaContratacion(sContratacion* contratacionArray,int longitud, sPantalla *pantallaArray, int longitudPant);
int contra_bajaContrato(sContratacion* contratacionArray, int longitud, sPantalla *pantallasArray, int longitudPant);
int contra_buscaIdPantalla(sContratacion contratoArray[],int longitud,int idPantalla);
int contra_consultaFacturacion(sContratacion *contratoArray,int longitud, sPantalla *pantallaArray, int longitudPanta);
int contra_listarContrataciones(sContratacion *contratoArray, int longitudContra, sPantalla *pantallaArray, int longitudPant);
