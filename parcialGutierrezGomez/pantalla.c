#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "validar.h"
#include "pantalla.h"


static int pant_proximoId(sPantalla* pantallasArray, int longitud);

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

int pant_cargarPantalla (sPantalla* arrayPantalla, int index,int longitudArray)
{
    int retorno = -1;
    char bNombrePantalla[51];
    char bdireccion[51];
    char bPrecio[15];
    char btipoPantalla[3];
    int idPantalla;

    idPantalla=pant_proximoId(arrayPantalla,longitudArray);

    if(arrayPantalla != NULL && index >= 0 && idPantalla != -1 && index<longitudArray)
    {
        if(val_getNombre(bNombrePantalla,"\nNOMBRE?","\nError:\n",3,51)==0)
        {
            if(val_getNombre(bdireccion,"\nBarrio?","\nError:\n",3,51)==0)
            {
                if(val_getUnsignedInt(bPrecio,"\nPrecio?","\nError:\n",3,15)==0)
                {
                    if(val_getUnsignedInt(btipoPantalla,"\nTipo pantalla\n1-Led\n2-LCD\n1 o 2?","\nError:\n",3,3)==0)
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
    return retorno;
}

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

int pant_buscaIndiceLibre(sPantalla* pantallasArray,int longitud)
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

void pant_printpantallas(sPantalla *pantallasArray,int longitud)
{
    int i = 0;

    for(;i < longitud; i++)
    {
        if(pantallasArray[i].flagPantalla == PANTALLA_OCUPADO)
        {
            printf("\n%d\t%s\t%s\t%s\t%d\n",pantallasArray[i].idPantalla,pantallasArray[i].nombrePantalla,pantallasArray[i].direccion,pantallasArray[i].precio,pantallasArray[i].tipoPantalla);
        }
    }
}

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

int pant_modificapantalla(sPantalla* arrayPantalla, int indice)
{

    int retorno = -1;
    char bNombrePantalla[51];
    char bdireccion[51];
    char bPrecio[15];
    char btipoPantalla[3];
    int idPantalla;

    if(arrayPantalla != NULL && indice >= 0)
    {
        if(val_getNombre(bNombrePantalla,"\nNOMBRE?","\nError:\n",3,51)==0)
        {
            if(val_getNombre(bdireccion,"\nBarrio?","\nError:\n",3,51)==0)
            {
                if(val_getUnsignedInt(bPrecio,"\nPrecio?","\nError:\n",3,15)==0)
                {
                    if(val_getUnsignedInt(btipoPantalla,"\nTipo pantalla\n1-Led\n2-LCD\n1 o 2?","\nError:\n",3,3)==0)
                    {

                        strncpy(arrayPantalla[indice].nombrePantalla,bNombrePantalla,51);
                        strncpy(arrayPantalla[indice].direccion,bdireccion,51);
                        strncpy(arrayPantalla[indice].precio,bPrecio,15);
                        arrayPantalla[indice].tipoPantalla = atoi(btipoPantalla);
                        arrayPantalla[indice].flagPantalla = PANTALLA_OCUPADO;
                        arrayPantalla[indice].idPantalla=idPantalla;
                        retorno = 0;
                    }
                }

            }
        }
    }
    return retorno;
}

int pant_bajapantalla(sPantalla* pantallaArray, int id, int longitud)
{
    int retorno = -1;
    int indice;

    if(pantallaArray != NULL && id >=0)
    {

        indice=pant_buscaIndiceOcupado(pantallaArray,longitud,id);

        if(id == pantallaArray[indice].idPantalla)
        {
            pantallaArray[indice].flagPantalla= PANTALLA_EMPTY;
            retorno = 0;
        }
    }
   return retorno;
}

