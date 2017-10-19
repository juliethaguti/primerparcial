#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validar.h"
#include "contratacion.h"
#include "pantalla.h"
#include "informes.h"


static int contra_proximoId(sContratacion* contratacionArray, int longitud);
static int contra_buscaIndiceLibre(sContratacion* contratacionArray,int longitud);

/** \brief  Se marcan todas las posiciones del array como libres
 *          colocando en cada elmento el flag de flagEstado en #define SIN_CONTRATACION
 *
 * \param sContratacion* arrayContrataciones Puntero al array de contrataciones
 * \param length Longitud del array
 * \return Retorna (-1) si hay un Error [Longitud invalida o puntero NULL] - (0) si Ok
 *
 */
int contra_initArray(sContratacion* arrayContrataciones, int length)
{
    int i;
    int retorno = -1;

    if(arrayContrataciones != NULL && length > 0)
    {
        for(i = 0; i < length; i++)
        {
            arrayContrataciones[i].flagContratacion = SIN_CONTRATACION;
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Agrega a la lista de contrataciones un nuevo elemento, el id no lo recibe lo calcula
 * \param sContratacion* arrayContratacion Puntero al array de contratos
 * \param longitudArray Longitud del array
 * \param idPantalla Numero de la pantalla
 * \return int Return (-1) si hay un Error [Longitud invalida o puntero NULL o sin espacio libre] - (0) si Ok
 *
 */
int contra_cargarArchivo (sContratacion* arrayContratacion, int idPantalla,int longitudArray)
{
    int retorno = -1;
    char bCuitCliente[15];
    char bNombreArchivo[51];
    int idArchivo;
    char bDias[15];
    int index;

    index = contra_buscaIndiceLibre(arrayContratacion,longitudArray);
    idArchivo=contra_proximoId(arrayContratacion,longitudArray);

    if(arrayContratacion != NULL && idPantalla >= 0)
    {
        if(val_getCuit(bCuitCliente,"\ncuit cliente?","\nError, reingrese:",3,15) == 0)
        {

            if(val_getArchivo(bNombreArchivo,"\nNOMBRE Archivo?","\nError, reingrese:",3,51)==0)
            {

                if(val_getUnsignedInt(bDias,"\nDuracion publicidad en dias?","\nError, reingrese: ",2,15) == 0)
                {

                    if(index != -1)
                    {
                        strncpy(arrayContratacion[index].cuitCliente,bCuitCliente,15);
                        strncpy(arrayContratacion[index].nombreArchivo,bNombreArchivo,51);
                        arrayContratacion[index].dias = atoi(bDias);
                        arrayContratacion[index].flagContratacion = CON_CONTRATACION;
                        arrayContratacion[index].idContratacion=idArchivo;
                        arrayContratacion[index].idPantalla = idPantalla;
                        retorno = 0;
                    }
                    else
                    {
                        printf("No ha lugar libre!!");
                    }
                }
            }
        }
    }
    return retorno;
}

/** \brief  Busca en el array el proximo id libre a asignar
 * \param sContratacion* contratacionArray Puntero al array de contratos
 * \param longitud Longitud del array
 * \return int Return (-1) si hay un Error [Longitud invalida o puntero NULL] - (proximo ID) si Ok
 *
 */
static int contra_proximoId(sContratacion* contratacionArray, int longitud)
{
    int i;
    int retorno = -1;
    int mayorIdOcupado = -1;

    if(contratacionArray != NULL && longitud > 0)
    {
        for(i = 0; i < longitud; i++)
        {
            if(contratacionArray[i].flagContratacion == CON_CONTRATACION)
            {
                if(mayorIdOcupado < contratacionArray[i].idContratacion || mayorIdOcupado == -1)
                {
                    mayorIdOcupado = contratacionArray[i].idContratacion;
                }

            }
        }
        retorno = mayorIdOcupado + 1;
    }
    return retorno;
}

/** \brief  Busca en el array la primer posicion libre
 * \param sContratacion* contratacionArray Puntero al array de contrataciones
 * \param longitud Longitud del array
 * \return int Return (-1) si hay un Error [Longitud invalida o puntero NULL] - (index del lugar libre) si Ok
 *
 */
static int contra_buscaIndiceLibre(sContratacion* contratacionArray,int longitud)
{
    int i = 0;
    int retorno = -1;

    if(contratacionArray != NULL && longitud > 0)
    {
        for(;i < longitud; i++)
        {
            if(contratacionArray[i].flagContratacion == SIN_CONTRATACION)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

/** \brief Imprime lista de pantallas sin contratar
 *
 * \param sContratacion *contratacionArray Puntero al array de contratos
 * \param longitudContratacion Longitud del array de contratos
 * \param sPantalla *pantallasArray Puntero al array de pantallas
 * \param longitud Longitud del array de pantallas
 * \return (-)
 *
 */
void contra_printPantallasSinContratar(sContratacion *contratacionArray,int longitudContratacion, sPantalla* pantallasArray, int longitudPantallas)
{
    int i = 0;
    int auxIdPantalla;

    printf("\nID\tNOMBRE\tDIRECCION\tPRECIO\tTIPO PANTALLA");
    for(;i < longitudPantallas; i++)
    {
        if(pantallasArray[i].flagPantalla == PANTALLA_OCUPADO)
        {
            auxIdPantalla = pantallasArray[i].idPantalla;

            if(contra_buscaIdPantalla(contratacionArray,longitudContratacion,auxIdPantalla) == -1)
            {
                printf("\n%d\t%s\t%s\t%s\t%d\n",pantallasArray[i].idPantalla,pantallasArray[i].nombrePantalla,pantallasArray[i].direccion,pantallasArray[i].precio,pantallasArray[i].tipoPantalla);
            }
        }
    }
}

/** \brief Modifica los dias de un contrato existente
 *
 * \param sContratacion* contratacionArray Puntero al array de contratos
 * \param longitud Longitud del array de contratos
 * \param sPantalla *pantallasArray Puntero al array de pantallas
 * \param longitudPant Longitud del array de pantallas
 * \return int Return (-1) si hay un Error [Longitud invalida o puntero NULL o si la longitud del nombre/apellido es < 1] - (0) si Ok
 *
 */
int contra_modificaContratacion(sContratacion* contratacionArray,int longitud, sPantalla *pantallasArray, int longitudPant)
{
    int retorno = -1;
    char bCuit[15];
    int idPantalla, i, dias, indice,auxIdPantalla;
    char bId [3];
    char bDias [15];
    int index;

    if(contratacionArray != NULL && pantallasArray !=NULL && longitud > 0 && longitudPant >0)
    {
        if(val_getCuit(bCuit,"\nIngrese cuit: ","\nError, reingrese: ",2,15) == 0)
        {
            for(i = 0; i < longitud; i++)
            {
                if(strcmp(bCuit,contratacionArray[i].cuitCliente) == 0)
                {
                    auxIdPantalla = contratacionArray[i].idPantalla;
                    index =pant_buscaIndiceOcupado(pantallasArray,longitudPant,auxIdPantalla);
                    printf("\nID\tNOMBRE\tDIRECCION\tPRECIO\tTIPO PANTALLA\tDIAS");
                    printf("\n%d\t%s\t%s\t%s\t%d\t%d\n",pantallasArray[index].idPantalla,pantallasArray[index].nombrePantalla,pantallasArray[index].direccion,pantallasArray[index].precio,pantallasArray[index].tipoPantalla,contratacionArray[i].dias);
                }
            }
            if(val_getUnsignedInt(bId,"\nIngrese id de la pantalla a modificar: ","\nError, reingrese: ",2,3) == 0)
            {
                idPantalla = atoi(bId);
                indice = contra_buscaIdPantalla(contratacionArray,longitud,idPantalla);
                if(indice != -1)
                {
                    if(val_getUnsignedInt(bDias,"\n Ingrese la nueva cantidad de dias","\nError, reingrese: " ,2,15) == 0)
                    {
                        dias = atoi(bDias);

                        contratacionArray[indice].dias = dias;
                        printf("\nModificacion exitosa!!! \n");

                        retorno = 0;
                    }
                }
            }
        }
    }
    return retorno;
}

/** \brief Elimina de manera logica un contrato de la lista
 *         colocando el flag de flagEstado en SIN_CONTRATACION
 *
 * \param sContratacion* contratacionArray Puntero al array de contratos
 * \param longitud Longitud del array de contratos
 * \param sPantalla* pantallaArray Puntero al array de pantallas
 * \param longitudPanta Longitud del array de pantallas
 * \return retorna(-1) si hay un Error [Longitud invalida o puntero NULL]  ( 0) si Ok
 *
 */
int contra_bajaContrato(sContratacion* contratacionArray, int longitud, sPantalla *pantallasArray, int longitudPant)
{
    int retorno = -1;
    char bCuit[15];
    int idPantalla, i, indice,auxIdPantalla;
    char bId [3];
    int index;

    if(contratacionArray != NULL)
    {
        if(val_getCuit(bCuit,"\nIngrese cuit: ","\nError, reingrese: ",2,15) == 0)
        {
            for(i = 0; i < longitud; i++)
            {
                if(strcmp(bCuit,contratacionArray[i].cuitCliente) == 0)
                {
                    auxIdPantalla = contratacionArray[i].idPantalla;
                    index =pant_buscaIndiceOcupado(pantallasArray,longitudPant,auxIdPantalla);
                    printf("\nID\tNOMBRE\tDIRECCION\tPRECIO\tTIPO PANTALLA\tDIAS");
                    printf("\n%d\t%s\t%s\t%s\t%d\t%d\n",pantallasArray[index].idPantalla,pantallasArray[index].nombrePantalla,pantallasArray[index].direccion,pantallasArray[index].precio,pantallasArray[index].tipoPantalla,contratacionArray[i].dias);
                }
            }
            if(val_getUnsignedInt(bId,"\nIngrese id de la pantalla a cancelar contrato: ","\nError, reingrese: ",2,3) == 0)
            {
                idPantalla = atoi(bId);
                indice = contra_buscaIdPantalla(contratacionArray,longitud,idPantalla);
                if(indice != -1)
                {
                        contratacionArray[indice].flagContratacion = SIN_CONTRATACION;
                        printf("\nCancelacion exitosa!!\n");
                        retorno = 0;
                }
            }
        }
    }
    return retorno;
}

/** \brief Busca en la lista pantallas la que coincida con el Id recibido
 *
 * \param sContratacion contratoArray[] Puntero al array de contratos
 * \param longitud Longitud del array de contratos
 * \param idPantalla ID de la pantalla
 * \return int Return (-1) si hay un Error [Longitud invalida o puntero NULL o si no se encontro el id pantalla] - (i) si Ok
 *
 */
int contra_buscaIdPantalla(sContratacion contratoArray[],int longitud,int idPantalla)
{
    int i;
    int retorno = -1;

    if( contratoArray != NULL && longitud > 0)
    {
        for( i = 0; i < longitud; i++)
        {
            if(idPantalla == contratoArray[i].idPantalla && contratoArray[i].flagContratacion == CON_CONTRATACION)
            {
                retorno = i;
            }
        }
    }
    return retorno;
}

/** \brief Lista el importe a pagar por cada contratación
 *
 * \param sContratacion *contratoArray Puntero al array de contratos
 * \param longitud Longitud del array contratos
 * \param sPantalla *pantallaArray Puntero al array de pantallas
 * \param longitudPanta Longitud del array de pantallas
* \param sInforme *informeArray Puntero al array de informes
 * \param longInforme Longitud del array de informes
* \return return (-1) si hay un Error [Longitud invalida o puntero NULL] - (0) si Ok
*
*/
int contra_consultaFacturacion(sContratacion *contratoArray,int longitud, sPantalla *pantallaArray, int longitudPanta)
{
    int i,auxIndice, auxPrecioInt;
    int retorno = -1;
    int auxCuit[15];
    int totalXPagar;
    char auxPrecio[15];
    int auxIdPantalla;


    if(contratoArray !=NULL && longitud > 0)
    {
        if(val_getCuit(auxCuit, "\nIngrese cuit: ","\nError, reingrese",2,15) == 0)
        {
            printf("\nNOMBRE ARCHIVO\tDIAS\tNOMBRE PANTALLA\tPRECIO\tPAGO TOTAL");
            for( i = 0; i < longitud; i++)
            {
                if( strcmp(auxCuit,contratoArray[i].cuitCliente) == 0)
                {
                    auxIdPantalla = contratoArray[i].idPantalla;
                    auxIndice = pant_buscaIndiceOcupado(pantallaArray,longitudPanta,auxIdPantalla);
                    strncpy(auxPrecio,pantallaArray[auxIndice].precio,15);
                    auxPrecioInt = atoi(auxPrecio);
                    totalXPagar = auxPrecioInt*contratoArray[i].dias;


                    printf("\n%s\t\t%d\t%s\t\t%s\t%d",contratoArray[i].nombreArchivo,contratoArray[i].dias,pantallaArray[auxIndice].nombrePantalla,pantallaArray[auxIndice].precio,totalXPagar);
                    retorno = 0;
                }
            }
        }
    }
    return retorno;
}

/** \brief Lista las contrataciones incluyendo el nombre de pantalla
 *
 * \param sContratacion *contratoArray Puntero al array de contratos
 * \param longitud Longitud del array contratos
 * \param sPantalla *pantallaArray Puntero al array de pantallas
 * \param longitudPanta Longitud del array de pantallas
* \return return (-1) si hay un Error [Longitud invalida o puntero NULL] - (0) si Ok *
 */

int contra_listarContrataciones(sContratacion *contratoArray, int longitudContra, sPantalla *pantallaArray, int longitudPant)
{
    int i;
    int retorno = -1;
    int auxIndex;
    int auxId;

    if(contratoArray != NULL && pantallaArray != NULL && longitudContra > 0 && longitudPant > 0)
    {
        printf("\nNOMBRE PANTALLA\tNOMBRE ARCHIVO\tDIAS\tCUIT CLIENTE");
        for(i = 0; i < longitudContra; i++)
        {
            if(contratoArray[i].flagContratacion == CON_CONTRATACION)
            {
                auxId = contratoArray[i].idPantalla;
                auxIndex = pant_buscaIndiceOcupado(pantallaArray,longitudPant,auxId);

                printf("\n%s\t\t%s\t\t%d\t%s",pantallaArray[auxIndex].nombrePantalla,contratoArray[i].nombreArchivo,contratoArray[i].dias,contratoArray[i].cuitCliente);
                retorno = 0;
            }
        }
    }
    return retorno;
}
