#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validar.h"
#include "contratacion.h"
#include "pantalla.h"
#include "informes.h"

int main()
{
    sPantalla pantallasArray [CANTIDAD_PANTALLAS];
    sContratacion contratacionArray[CANTIDAD_CONTRATOS];
    sInformes informeArray[TAMANIO];

     char menu[] =
                "\n1-Alta de pantalla\
                 \n2-Modificar datos de pantalla\
                 \n3-Baja del pantalla\
                 \n4-Contratar publicidad\
                 \n5-Modificar condiciones de publicacion\
                 \n6-Cancelar contratacion\
                 \n7-Consultar facturacion\
                 \n8-Listar contrataciones\
                 \n9-Listar pantallas\
                 \n10-Informar\
				 \n11-Salir\
                 \n\nIngrese opcion: ";
        char mensajeErrorMenu[] = "\nSe debe elegir una opcion del 1 al 11";
        char opcion[4];
        char auxidpantalla[3];
        int id;
        char opcionDos [4];
        int indice;
        char menuDos[] =
                "\n\t1-Lista de cada cliente con cantidad de contrataciones e importe a pagar por cada una\
                 \n\t2-Primer cliente con importe mas alto a facturar\
                 \n\t3-Salir\
                 \n\n\tIngrese opcion: ";
        char mensajeErrorMenuDos[] = "\n\tSe debe elegir una opcion del 1 al 11\n";

        contra_initArray(contratacionArray,CANTIDAD_CONTRATOS);
        pant_initArray(pantallasArray,CANTIDAD_PANTALLAS);
        info_initArray(informeArray,TAMANIO);

        do{
                //system("cls");
                val_getUnsignedInt(opcion,menu,mensajeErrorMenu,2,4);
                switch(atoi(opcion))
                {
            case 1:
                pant_cargarPantalla(pantallasArray,CANTIDAD_PANTALLAS);
                printf("\nID\tNOMBRE\tDIRECCION\tPRECIO\tTIPO PANTALLA");
                pant_printpantallas(pantallasArray,CANTIDAD_PANTALLAS);
                break;
            case 2:
                printf("\nID\tNOMBRE\tDIRECCION\t\tPRECIO\tTIPO PANTALLA");
                pant_printpantallas(pantallasArray,CANTIDAD_PANTALLAS);
                if(val_getUnsignedInt(auxidpantalla,"\nId pantalla a modificar?","\nError, reingrese",2,3) == 0)
                {
                    id=atoi(auxidpantalla);
                    pant_modificapantalla(pantallasArray,id,CANTIDAD_PANTALLAS);
                    //pant_printpantallas(pantallasArray,CANTIDAD_PANTALLAS);
                    //system("pause");
                }
                break;
            case 3:
                printf("\nID\tNOMBRE\tDIRECCION\t\tPRECIO\tTIPO PANTALLA");
                pant_printpantallas(pantallasArray,CANTIDAD_PANTALLAS);
                if(val_getUnsignedInt(auxidpantalla,"\nId pantalla a dar de baja?","\nError, reingrese:",2,3) == 0)
                {
                    id = atoi(auxidpantalla);
                    pant_bajapantalla(pantallasArray,id,CANTIDAD_PANTALLAS);
                }
                break;
            case 4:

                contra_printPantallasSinContratar(contratacionArray,CANTIDAD_CONTRATOS,pantallasArray,CANTIDAD_PANTALLAS);
                if(val_getUnsignedInt(auxidpantalla, "\nIngrese id pantalla: ","\nError, reingrese",3,3) == 0)
                {
                    id = atoi(auxidpantalla);
                    indice = pant_encuentraPantalla(pantallasArray,CANTIDAD_PANTALLAS,id);
                    if(indice != -1)
                    {
                        contra_cargarArchivo(contratacionArray,id,CANTIDAD_CONTRATOS);
                    }
                    else
                    {
                        printf("\nEl id no existe!!!\n");
                    }

                }

                break;
            case 5:
                contra_modificaContratacion(contratacionArray,CANTIDAD_CONTRATOS,pantallasArray,CANTIDAD_PANTALLAS);
                break;
            case 6:
                contra_bajaContrato(contratacionArray,CANTIDAD_CONTRATOS,pantallasArray,CANTIDAD_PANTALLAS);
                break;
            case 7:
                contra_consultaFacturacion(contratacionArray,CANTIDAD_CONTRATOS,pantallasArray,CANTIDAD_PANTALLAS);
                break;
            case 8:
                contra_listarContrataciones(contratacionArray,CANTIDAD_CONTRATOS,pantallasArray,CANTIDAD_PANTALLAS);
                break;
            case 9:
                printf("\nID\tNombre\tDireccion\tPrecio\tTipo\n");
                pant_printpantallas(pantallasArray,CANTIDAD_PANTALLAS);
                break;
            case 10:
                do
                {
                    val_getUnsignedInt(opcionDos,menuDos,mensajeErrorMenuDos,2,4);
                    switch(atoi(opcionDos))
                    {
                    case 1:
                        info_printClientesContratacionesXPagar(contratacionArray, CANTIDAD_CONTRATOS,pantallasArray,CANTIDAD_PANTALLAS);
                        break;
                    case 2:
                        info_buscaClienteImporteAlto(contratacionArray,CANTIDAD_CONTRATOS,informeArray,TAMANIO,pantallasArray,CANTIDAD_PANTALLAS);
                        break;
                    case 3:
                        break;
                    }
                }while(atoi(opcionDos) != 3);
                break;
                }


        }while(atoi(opcion) != 11);
    return 0;
}
