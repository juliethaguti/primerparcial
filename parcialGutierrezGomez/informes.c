#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "validar.h"
#include "pantalla.h"
#include "contratacion.h"
#include "informes.h"

static int info_buscaIndiceLibre(sInformes *infoArray, int infoLongitud);
static int info_proximoId(sInformes *infoArray, int longitud);

/** \brief  Se marcan todas las posiciones del array como libres
 *          colocando en cada elemento el flag de flagEstado en SIN_INFORME
 *
 * \param sInformes *infoArray Puntero al array de informes
 * \param longitud Longitud del array
 * \return Retorna (-1) si hay un Error [Longitud invalida o puntero NULL] - (0) si Ok
 *
 */
int info_initArray(sInformes *infoArray, int longitud)
{
    int i;
    int retorno = -1;

    if(infoArray != NULL && longitud > 0)
    {
        for(i = 0; i < longitud; i++)
        {
            infoArray[i].flagInfo = SIN_INFORME;
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Calcula total a pagar y lo guarda en el array
 *
 * \param sInformes *infoArray Puntero al array de informes
 * \param infoLong Longitud array informes
 * \param sContratacion *contratoArray Puntero al array de contratos
 * \param contraLong Longitud del array contratos
 * \param sPantalla *pantallArray Puntero al array de pantallas
 * \param pantallaLong Longitud del array de pantallas
* \return return (-1) si hay un Error [Longitud invalida o puntero NULL] - (valor por pagar) si Ok
 *
 */
 int info_calculaXPagar(sContratacion *contratoArray,int contralong,sPantalla *pantallArray, int pantallaLong, sInformes *infoArray,int infoLong)
{
    int i,j;
    int retorno = -1;
    int auxIdPantalla, auxIdInfo, auxIndice;
    int auxDias, precioEntero;
    char auxPrecio[15];

    if(contratoArray != NULL && pantallArray != NULL && contralong > 0 && pantallaLong > 0)
    {
        for(i = 0; i < contralong; i++)
        {
            auxIdInfo = info_proximoId(infoArray,infoLong);
            auxIndice = info_buscaIndiceLibre(infoArray,infoLong);

            if(contratoArray[i].flagContratacion == CON_CONTRATACION)
            {
                auxIdPantalla = contratoArray[i].idPantalla;
                auxDias = contratoArray[i].dias;

                for(j = 0; j <pantallaLong; j++)
                {
                    if(auxIdPantalla == pantallArray[j].idPantalla)
                    {
                        strncpy(auxPrecio,pantallArray[j].precio,15);
                        precioEntero = atoi(auxPrecio);
                    }
                }

                if(auxIdInfo != -1 && auxIndice != -1)
                {
                    infoArray[auxIndice].totalXPagar = precioEntero * auxDias;
                    infoArray[auxIndice].idInfo = auxIdInfo;
                    infoArray[auxIndice].flagInfo = CON_INFORME;
                    infoArray[auxIndice].idPantalla = auxIdPantalla;
                    retorno = 0;
                }
            }
        }
    }
    return retorno;
}

/** \brief Informa el importe mas alto
 *
 * \param sInformes *infoArray Puntero al array de informes
 * \param infolong Longitud array informes
 * \param sContratacion *contratoArray Puntero al array de contratos
 * \param contralong Longitud del array contratos
 * \return * \return return (-1) si hay un Error [Longitud invalida o puntero NULL] - (el importe mas alto) si Ok *
 *
 */

int info_ImporteMasAlto(sInformes *infoArray,int infolong)
{
    int i;
    int retorno = -1;
    int auxImporteMasAlto;
    int flagPrimerVez = 0;

    if(infoArray != NULL && infolong > 0)
    {
        for(i = 0; i < infolong; i++)
        {
            if(flagPrimerVez == 0 && infoArray[i].flagInfo == CON_INFORME)
            {
                auxImporteMasAlto = infoArray[i].totalXPagar;
                flagPrimerVez = 1;
            }
            else
            {
                if(flagPrimerVez != 0 && auxImporteMasAlto < infoArray[i].totalXPagar && infoArray[i].flagInfo == CON_INFORME)
                {
                    auxImporteMasAlto = infoArray[i].totalXPagar;
                }
            }
            retorno = auxImporteMasAlto;
        }
    }
    return retorno;
}

/** \brief  Busca en el array la primer posicion libre
 * \param sInformes *infoArray Puntero al array de informes
 * \param infoLongitud Longitud del array
 * \return int Return (-1) si hay un Error [Longitud invalida o puntero NULL] - (index del lugar libre) si Ok
 *
 */
static int info_buscaIndiceLibre(sInformes *infoArray, int infoLongitud)
{
    int i;
    int retorno = -1;

    if(infoArray != NULL && infoLongitud > 0)
    {
         for(i = 0;i < infoLongitud; i++)
        {
            if(infoArray[i].flagInfo == SIN_INFORME)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

/** \brief  Busca en el array el proximo id libre a asignar
 * \param sInformes *infoArray Puntero al array de informes
 * \param longitud Longitud del array
 * \return int Return (-1) si hay un Error [Longitud invalida o puntero NULL] - (proximo ID) si Ok
 *
 */
static int info_proximoId(sInformes *infoArray, int longitud)
{
    int i;
    int retorno = -1;
    int mayorIdOcupado = -1;

    if(infoArray != NULL && longitud > 0)
    {
        for(i = 0; i < longitud; i++)
        {
            if(infoArray[i].flagInfo == CON_INFORME)
            {
                if(mayorIdOcupado < infoArray[i].idInfo || mayorIdOcupado == -1)
                {
                    mayorIdOcupado = infoArray[i].idInfo;
                }

            }
        }
        retorno = mayorIdOcupado + 1;
    }
    return retorno;
}

/** \brief Busca el cliente con el importe mas alto
 *
 * \param sInformes *infoArray Puntero al array de informes
 * \param infolong Longitud array informes
 * \param sContratacion *contratoArray Puntero al array de contratos
 * \param contralong Longitud del array contratos
 * \return * \return return (-1) si hay un Error [Longitud invalida o puntero NULL] - (el importe mas alto) si Ok
 */
int info_buscaClienteImporteAlto(sContratacion *contratoArray, int contralong, sInformes *informesArray, int infolong,sPantalla *pantallArray, int pantlong)
{
    int retorno = -1;
    int i;
    int auxidPantalla;
    int importeMasAlto;

    info_calculaXPagar(contratoArray,contralong,pantallArray,pantlong,informesArray,infolong);
    importeMasAlto = info_ImporteMasAlto(informesArray,infolong);

    for(i = 0; i < infolong; i++)
    {
        if(importeMasAlto == informesArray[i].totalXPagar)
        {
            auxidPantalla = informesArray[i].idPantalla;
            break;
        }
    }
    for(i = 0; i < contralong; i++)
    {
        if(auxidPantalla == contratoArray[i].idPantalla)
        {
            printf("\nEl primer cliente con el importe mas alto tiene el cuit: %s\n",contratoArray[i].cuitCliente);
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Ordena el array segun cuit
 *
 * \param sContratacion* contratoArray Puntero al array de contratos
 * \param contraLong Longitud del array
 * \return Retorna (-1) si hay un Error [Longitud invalida o puntero NULL] - (0) si Ok
 *
 */

int info_ordenarArray(sContratacion *contratoArray, int contraLong)
{
    sContratacion aux;
    int i,j;
    int retorno = -1;

    if(contratoArray != NULL && contraLong > 0)
    {

        for(i = 0; i < contraLong - 1; i++)
        {
            for(j = 1; j < contraLong; j++)
            {
                if(strcmp(contratoArray[i].cuitCliente,contratoArray[j].cuitCliente) < 0)
                {
                    aux = contratoArray[i];
                    contratoArray[i] = contratoArray[j];
                    contratoArray[j] = aux;
                    retorno = 0;
                }
            }
        }
    }
    return retorno;
}

/** \brief Muestra cada cliente con sus contrataciones
 *
 * \param sContratacion *contratoArray Puntero al array de contratos
 * \param longitud Longitud del array contratos
 * \param sPantalla *pantallaArray Puntero al array de pantallas
 * \param longitudPanta Longitud del array de pantallas
* \return return (-1) si hay un Error [Longitud invalida o puntero NULL] - (0) si Ok *
 *
 */

int info_printClientesContratacionesXPagar(sContratacion *contratoArray, int contraLong, sPantalla *arrayPantalla, int PantallaLong)
{
    int retorno = -1;
    int i;
    int ordenar;
    int auxXPagar;
    char auxPrecio[15];
    int auxPrecioInt;
    int auxIdPantalla;
    int auxIndice;
    int auxDias;
    char auxCuit[15] = "0000000000";

    if(contratoArray != NULL && arrayPantalla != NULL && contraLong > 0 && PantallaLong > 0)
    {
        ordenar = info_ordenarArray(contratoArray,contraLong);
        if(ordenar != -1)
        {
            for( i = 0; i < contraLong; i++)
            {
                if((strcmp(auxCuit,contratoArray[i].cuitCliente) != 0) )
                {
                    if(contratoArray[i].flagContratacion == CON_CONTRATACION)
                    {
                        strncpy(auxCuit,contratoArray[i].cuitCliente,15);
                        printf("\nCuit: %s\n",auxCuit);
                        printf("\nNOMBRE ARCHIVO\tNOMBRE PANTALLA\tPRECIO\tDIAS\tPAGO TOTAL");
                    }
                }

                if(contratoArray[i].flagContratacion == CON_CONTRATACION)
                {
                    auxDias = contratoArray[i].dias;
                    auxIdPantalla = contratoArray[i].idPantalla;
                    auxIndice = pant_buscaIndiceOcupado(arrayPantalla,PantallaLong,auxIdPantalla);
                    strncpy(auxPrecio,arrayPantalla[auxIndice].precio,15);
                    auxPrecioInt = atoi(auxPrecio);
                    auxXPagar =auxDias * auxPrecioInt;
                    printf("\n%s\t\t%s\t\t%s\t%d\t%d\n",contratoArray[i].nombreArchivo,arrayPantalla[auxIndice].nombrePantalla,arrayPantalla[auxIndice].precio,contratoArray[i].dias,auxXPagar);
                    retorno = 0;
                }
            }
        }
    }
    return retorno;
}
