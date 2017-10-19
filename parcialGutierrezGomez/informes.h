#ifndef INFORMES_H_INCLUDED
#define INFORMES_H_INCLUDED

typedef struct
{
    int idPantalla;
    int idInfo;
    int totalXPagar;
    int flagInfo;
}sInformes;

#endif // INFORMES_H_INCLUDED

#define SIN_INFORME 0
#define CON_INFORME 1

#define TAMANIO 10

int info_initArray(sInformes *infoArray, int longitud);
int info_calculaXPagar(sContratacion *contratoArray,int contralong,sPantalla *pantallArray, int pantallaLong, sInformes *infoArray,int infoLong);
int info_ImporteMasAlto(sInformes *infoArray,int infolong);
int info_buscaClienteImporteAlto(sContratacion *contratoArray, int contralong, sInformes *informesArray, int infolong,sPantalla *pantallArray, int pantlong);
int info_ordenarArray(sContratacion *contratoArray, int contraLong);
int info_printClientesContratacionesXPagar(sContratacion *contratoArray, int contraLong, sPantalla *arrayPantalla, int PantallaLong);
