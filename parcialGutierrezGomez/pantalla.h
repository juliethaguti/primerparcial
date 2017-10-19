#ifndef PANTALLA_H_INCLUDED
#define PANTALLA_H_INCLUDED

typedef struct
{
    char nombrePantalla[51];
    char direccion[51];
	char precio [15];
	int tipoPantalla;
    int idPantalla;
    int flagPantalla;
}sPantalla;

#endif // Pantalla_H_INCLUDED

#define PANTALLA_EMPTY 0
#define PANTALLA_OCUPADO 1

#define PANTALLA_LCD 2
#define PANTALLA_LED 1

#define CANTIDAD_PANTALLAS 3

int pant_initArray(sPantalla* arrayPantallas, int length);
int pant_cargarPantalla (sPantalla* arrayPantalla,int longitudArray);
void pant_printpantallas(sPantalla *pantallasArray,int longitud);
int pant_buscaIndiceOcupado(sPantalla* PantallaArray, int longitud, int id);
int pant_modificapantalla(sPantalla* arrayPantalla, int idPantalla, int longitud);
int pant_bajapantalla(sPantalla* PantallaArray, int id, int longitud);
int pant_encuentraPantalla(sPantalla *pantallaArray,int longitud, int idPantalla);
