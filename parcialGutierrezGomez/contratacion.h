#ifndef CONTRATACION_H_INCLUDED
#define CONTRATACION_H_INCLUDED

typedef struct
{
    char cuitCliente[15];
    char nombreArchivo [51];
    char precio [15];
    int dias;
    int idContratacion;
    int flagContratacion;
    int idPantalla;
}sContratacion;

#endif // CONTRATACION_H_INCLUDED

#define SIN_CONTRATACION 0
#define CON_CONTRATACION 1

#define CANTIDAD_CONTRATOS 10

int contra_initArray(sContratacion* arrayContrataciones, int length);
int contra_cargarArchivo (sContratacion* arrayContratacion, int idPantalla,int longitudArray);
int contra_buscaIndiceLibre(sContratacion* contratacionArray,int longitud);
void contra_printArchivos(sContratacion *contratacionArray,int longitud);
int contra_buscaIndiceOcupado(sContratacion* contratacionArray, int longitud, int id);
int contra_modificaArchivo(sContratacion* contratacionArray,int idPantalla);
sContratacion* Contratacions_find(sContratacion* pContratos, int longitud, int idContratacion);
