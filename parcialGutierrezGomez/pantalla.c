#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "validar.h"
#include "pantalla.h"
#include "contratacion.h"


static int pant_proximoId(sPantalla* pantallasArray, int longitud);
static int pant_buscaIndiceLibre(sPantalla* pantallasArray,int longitud);

/** \brief  Se marcan todas las posiciones del array como libres
 *          colocando en cada elmento el flag de flagEstado en PANTALLA_EMPTY
 *
 * \param sPantalla* arrayPantallas Puntero al array de pantallas
 * \param length Longitud del array
 * \return Retorna (-1) si hay un Error [Longitud invalida o puntero NULL] - (0) si Ok
 *
 */
int pant_initArray(sPantalla* arrayPantallas, int length)
{
    int i;
    int retorno = -1;

    if(arrayPantallas != NULL && length > 0)
    {
        for(i = 0; i < length; i++)
        {
            arrayPantallas[i].flagPantalla = PANTALLA_EMPTY;
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Agrega a la lista de pantallas un nuevo elemento, el id no lo recibe lo calcula
 * \param sPantalla* arrayPantalla Puntero al array de pantallas
 * \param longitudArray Longitud del array
 * \return int Return (-1) si hay un Error [Longitud invalida o puntero NULL o sin espacio libre] - (0) si Ok
 *
 */
int pant_cargarPantalla (sPantalla* arrayPantalla,int longitudArray)
{
    int retorno = -1;
    char bNombrePantalla[51];
    char bdireccion[51];
    char bPrecio[15];
    char btipoPantalla[3];
    int idPantalla;
    int index;

    idPantalla=pant_proximoId(arrayPantalla,longitudArray);

    if(arrayPantalla != NULL  && idPantalla != -1 && 0 < longitudArray)
    {
        index = pant_buscaIndiceLibre(arrayPantalla,longitudArray);

        if(index == -1)
        {
            printf("No hay más lugar!!");
        }
        else
        {
            if(val_getNombre(bNombrePantalla,"\nNOMBRE?","\nError, reingrese:\n",3,51)==0)
            {
                if(val_getDireccion(bdireccion,"\nDireccion?","\nError, reingrese:\n",3,51)==0)
                {
                    if(val_getUnsignedInt(bPrecio,"\nPrecio?","\nError, reingrese:\n",3,15)==0)
                    {
                        if(val_getTipoPantalla(btipoPantalla,"\nTipo pantalla:\n\t1-Led\n\t2-LCD\n\t1 o 2?","\nError, reingrese:\n",3,3)==0)
                        {
                            strncpy(arrayPantalla[index].nombrePantalla,bNombrePantalla,51);
                            strncpy(arrayPantalla[index].direccion,bdireccion,51);
                            strncpy(arrayPantalla[index].precio,bPrecio,15);
                            arrayPantalla[index].tipoPantalla = atoi(btipoPantalla);
                            arrayPantalla[index].flagPantalla = PANTALLA_OCUPADO;
                            arrayPantalla[index].idPantalla=idPantalla;
                            retorno = 0;
                        }
                    }
                }
            }
        }
    }
    return retorno;
}

/** \brief  Busca en el array el proximo id libre a asignar
 * \param sPantalla* pantallasArray Puntero al array de pantallas
 * \param longitud Longitud del array
 * \return int Return (-1) si hay un Error [Longitud invalida o puntero NULL] - (proximo ID) si Ok
 *
 */
static int pant_proximoId(sPantalla* pantallasArray, int longitud)
{
    int i;
    int retorno = -1;
    int mayorIdOcupado = -1;

    if(pantallasArray != NULL && longitud > 0)
    {
        for(i = 0; i < longitud; i++)
        {
            if(pantallasArray[i].flagPantalla == PANTALLA_OCUPADO)
            {
                if(mayorIdOcupado < pantallasArray[i].idPantalla || mayorIdOcupado == -1)
                {
                    mayorIdOcupado = pantallasArray[i].idPantalla;
                }

            }
        }
        retorno = mayorIdOcupado + 1;
    }
    return retorno;
}

/** \brief  Busca en el array la primer posicion libre
 * \param sPantalla* pantallasArray Puntero al array de pantallas
 * \param longitud Longitud del array
 * \return int Return (-1) si hay un Error [Longitud invalida o puntero NULL] - (index del lugar libre) si Ok
 *
 */
static int pant_buscaIndiceLibre(sPantalla* pantallasArray,int longitud)
{
    int i = 0;
    int retorno = -1;

    if(pantallasArray != NULL && longitud > 0)
    {
        for(;i < longitud; i++)
        {
            if(pantallasArray[i].flagPantalla == PANTALLA_EMPTY)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

/** \brief Imprime lista de pantallas
 *
 * \param sPantalla *pantallasArray Puntero al array de pantallas
 * \param longitud Longitud del array de pantallas
 * \return (-)
 *
 */

void pant_printpantallas(sPantalla *pantallasArray,int longitud)
{
    int i = 0;

    for(;i < longitud; i++)
    {
        if(pantallasArray[i].flagPantalla == PANTALLA_OCUPADO)
        {
            printf("\n%d\t%s\t%s\t%s\t  %d\n",pantallasArray[i].idPantalla,pantallasArray[i].nombrePantalla,pantallasArray[i].direccion,pantallasArray[i].precio,pantallasArray[i].tipoPantalla);
        }
    }
}

/** \brief Busca en la lista una pantalla que coincida con el Id recibido
 *
 * \param sPantalla* pantallaArray Puntero al array de pantallas
 * \param longitud Longitud del array
 * \param id ID de la pantalla
 * \return int Return (-1) si hay un Error [Longitud invalida o puntero NULL o sin no se encontro el abonado] - (indice de la pantalla encontrada) si Ok
 *
 */
int pant_buscaIndiceOcupado(sPantalla* pantallaArray, int longitud, int id)
{
    int i;
    int retorno = -1;
    if(pantallaArray != NULL && longitud > 0 && id >= 0)
    {
        for(i = 0; i < longitud; i++)
        {
            if(id == pantallaArray[i].idPantalla && pantallaArray[i].flagPantalla == PANTALLA_OCUPADO)
            {
                retorno = i;
            }
        }
    }
    return retorno;
}

/** \brief Modifica los datos de una pantalla existente
 *
 * \param sPantalla *arrayPantalla Puntero al array de pantallas
 * \param longitud Longitud del array de pantallas
 *\param idPantalla numero identificador de la pantalla a modificar
 * \return int Return (-1) si hay un Error [Longitud invalida o puntero NULL o si la longitud del nombre/apellido es < 1] - (0) si Ok
 *
 */
int pant_modificapantalla(sPantalla* arrayPantalla, int idPantalla, int longitud)
{

    int retorno = -1;
    char bNombrePantalla[51];
    char bdireccion[51];
    char bPrecio[15];
    char btipoPantalla[3];
    int indice;

    if(arrayPantalla != NULL && longitud > 0)
    {
        indice = pant_buscaIndiceOcupado(arrayPantalla,longitud,idPantalla);

        if(pant_encuentraPantalla(arrayPantalla,longitud,idPantalla) == -1)
        {
            printf("\nNo se encontro ID!!!\n");
        }
        else
        {
            if(val_getNombre(bNombrePantalla,"\nNOMBRE?","\nError, reingrese:\n",3,51)==0)
            {
                if(val_getDireccion(bdireccion,"\nDireccion?","\nError, reingrese:\n",3,51)==0)
                {
                    if(val_getUnsignedInt(bPrecio,"\nPrecio?","\nError, reingrese:\n",3,15)==0)
                    {
                        if(val_getTipoPantalla(btipoPantalla,"\nTipo pantalla\n1-Led\n2-LCD\n1 o 2?","\nError, reingrese:\n",3,3)==0)
                        {
                            strncpy(arrayPantalla[indice].nombrePantalla,bNombrePantalla,51);
                            strncpy(arrayPantalla[indice].direccion,bdireccion,51);
                            strncpy(arrayPantalla[indice].precio,bPrecio,15);
                            arrayPantalla[indice].tipoPantalla = atoi(btipoPantalla);
                            retorno = 0;
                        }
                    }
                }
            }
        }
    }
    return retorno;
}

/** \brief Elimina de manera logica una pantalla de la lista
 *         colocando el flag de flagEstado en PANTALLA_EMPTY
 *
 * \param sPantalla* pantallaArray Puntero al array de pantallas
 * \param longitud Longitud del array
 * \param id ID de la pantalla
 * \return retorna(-1) si hay un Error [Longitud invalida o puntero NULL]
 *                    (-2) si no se encontro la pantalla] ( 0) si Ok
 *
 */
int pant_bajapantalla(sPantalla* pantallaArray, int id, int longitud)
{
    int retorno = -1;
    int indice;

    if(pantallaArray != NULL && id >=0)
    {

        indice=pant_buscaIndiceOcupado(pantallaArray,longitud,id);

        if(indice != -1)
        {
            pantallaArray[indice].flagPantalla= PANTALLA_EMPTY;
            retorno = 0;
        }
        else
        {
            printf("\nNo se encontro Id!!!\n");
            retorno = -2;
        }
    }
   return retorno;
}

/** \brief Busca en la lista una pantalla que coincida con el Id recibido
 *
 * \param sPantalla *pantallaArray Puntero al array de pantallas
 * \param longitud Longitud del array
 * \param idPantalla ID de la pantalla
 * \return int Return (-1) si hay un Error [Longitud invalida o puntero NULL o sin no se encontro la pantalla] - (0) si Ok
 *
 */
int pant_encuentraPantalla(sPantalla *pantallaArray,int longitud, int idPantalla)
{
    int i;
    int retorno = -1;

    if(pantallaArray != NULL && longitud > 0)
    {
         for(i = 0; i < longitud; i++)
        {
            if(idPantalla == pantallaArray[i].idPantalla)
            {
                retorno = 0;
            }
        }
    }
    return retorno;
}

