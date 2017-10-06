#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validar.h"
#include "contratacion.h"
#include "pantalla.h"


static int contra_proximoId(sContratacion* contratacionArray, int longitud);


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
        if(val_getUnsignedInt(bCuitCliente,"\ncuit cliente?","\nError, ingrese:",3,15))
        {

            if(val_getNombre(bNombreArchivo,"\nNOMBRE Archivo?","\nError, reingrese:\n",3,51)==0)
            {
                //printf(bNombreArchivo);
                if(val_getUnsignedInt(bDias,"Duracion publicidad?","Error, reingrese: ",2,15) == 0)
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

int contra_buscaIndiceLibre(sContratacion* contratacionArray,int longitud)
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

void contra_printArchivos(sContratacion *contratacionArray,int longitud)
{
    int i = 0;

    for(;i < longitud; i++)
    {
        if(contratacionArray[i].flagContratacion == CON_CONTRATACION)
        {
            printf("\n%d\n%s\n",contratacionArray[i].idContratacion,contratacionArray[i].nombreArchivo);
        }
    }
}

int contra_buscaIndiceOcupado(sContratacion* contratacionArray, int longitud, int id)
{
    int i;
    int retorno = -1;
    if(contratacionArray != NULL && longitud > 0 && id >= 0)
    {
        for(i = 0; i < longitud; i++)
        {
            if(id == contratacionArray[i].idContratacion && contratacionArray[i].flagContratacion == CON_CONTRATACION)
            {
                retorno = i;
            }
        }
    }
    return retorno;
}

int contra_modificaContratacion(sContratacion* contratacionArray,int idPantalla,int longitud)
{
    int retorno = -1;
    char bPrecio[15];
    int indice;

    if(contratacionArray != NULL)
    {
        indice = contra_buscaIndiceOcupado(contratacionArray,longitud,idPantalla);
        if(indice != -1)
        {

             if(val_getNombre(bPrecio,"Precio?","Error, reingrese:",2,15) == 0)
            {
                strncpy(contratacionArray[indice].precio,bPrecio,51);
                retorno = 0;

            }
        }

    }
    return retorno;
}

int contra_bajaArchivo(sContratacion* contratacionArray, int id, int longitud)
{
    int retorno = -1;
    int indice;

    if(contratacionArray != NULL && id >=0)
    {

        indice=contra_buscaIndiceOcupado(contratacionArray,longitud,id);

        if(id == contratacionArray[indice].idContratacion)
        {
            contratacionArray[indice].flagContratacion= SIN_CONTRATACION;
            retorno = 0;
        }
    }
   return retorno;
}

sContratacion* Contratacions_find(sContratacion* pContratos, int longitud, int idContratacion)
{
    sContratacion* pRetorno = NULL;
    int i;
    if(pContratos != NULL && longitud > 0)
    {
        for(i=0;i<longitud;i++)
        {
            if(pContratos[i].idContratacion == idContratacion && pContratos[i].flagContratacion == CON_CONTRATACION)
            {
                pRetorno = (pContratos+i);
                break;
            }
        }
    }
    return pRetorno;
}



