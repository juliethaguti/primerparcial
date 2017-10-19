#ifndef VALIDAR_H_INCLUDED
#define VALIDAR_H_INCLUDED



#endif // VALIDAR_H_INCLUDED

int val_getNombre(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
void myFgets(char* buffer, int limite ,FILE* archivo);
int val_getUnsignedInt(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_getDireccion(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_getTipoPantalla(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_getCuit(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
int val_getArchivo(char* destino, char* mensaje,char* mensajeError,int intentos,int limite);
