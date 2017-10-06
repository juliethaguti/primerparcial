#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validar.h"
#include "contratacion.h"
#include "pantalla.h"

int main()
{
    sPantalla pantallasArray [CANTIDAD_PANTALLAS];
    sContratacion contratacionArray[CANTIDAD_CONTRATOS];

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
                 \nIngrese opcion: ";
        char mensajeErrorMenu[] = "\nSe debe elegir una opcion del 1 al 11";
        char opcion[4];
        int indice;
        char auxidpantalla[3];
        int id,i;

        contra_initArray(contratacionArray,CANTIDAD_CONTRATOS);
        pant_initArray(pantallasArray,CANTIDAD_PANTALLAS);

        do{
                //system("cls");
                val_getUnsignedInt(opcion,menu,mensajeErrorMenu,2,4);
                switch(atoi(opcion))
                {
            case 1:
                indice = pant_buscaIndiceLibre(pantallasArray,CANTIDAD_PANTALLAS);
                pant_cargarPantalla(pantallasArray,indice,CANTIDAD_PANTALLAS);
                pant_printpantallas(pantallasArray,CANTIDAD_PANTALLAS);
                break;
            case 2:

                if(val_getUnsignedInt(auxidpantalla,"Id pantalla a modificar?","Error, reingrese",2,3) == 0)
                {
                    id=atoi(auxidpantalla);

                    indice=pant_buscaIndiceOcupado(pantallasArray,CANTIDAD_PANTALLAS,id);
                    pant_modificapantalla(pantallasArray,indice);
                    pant_printpantallas(pantallasArray,CANTIDAD_PANTALLAS);
                    system("pause");
                }
                break;
            case 3:
                if(val_getUnsignedInt(auxidpantalla,"\nId pantalla a dar de baja?","\nError, reingrese:",2,3) == 0)
                {
                    id = atoi(auxidpantalla);
                    pant_bajapantalla(pantallasArray,id,CANTIDAD_PANTALLAS);
                }

                break;
            case 4:
                pant_printpantallas(pantallasArray,CANTIDAD_PANTALLAS);
                if(val_getUnsignedInt(auxidpantalla, "\nIngrese id pantalla: ","\nError, reingrese",3,3) == 0)
                {
                    id = atoi(auxidpantalla);
                    for(i=0;i<CANTIDAD_PANTALLAS;i++)
                    {
                        if(id == pantallasArray[i].idPantalla)
                        {
                        contra_cargarArchivo(contratacionArray,id,CANTIDAD_CONTRATOS);
                        }
                    }

                }

                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                printf("\nID\tNombre\tBarrio\tPrecio\tTipo");
                pant_printpantallas(pantallasArray,CANTIDAD_PANTALLAS);
                break;
                }


        }while(atoi(opcion) != 11);
    return 0;
}
