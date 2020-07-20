/* Paquete con funciones y librerias para Traductor.c */

/** Librerias **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>

/** Protoripos **/

// Asigna las traducciones a los caracteres
//  Postcondición: Devuelve una tabla de equivalencias entre caracteres y morse
char** Asignacion();

// Lee desde el teclado una cadena de caracteres
//  Precondición: Dirección de una cadena de caracteres inicializada
//  Postcondición: Devuelve la cadena leida desde la entrada estándar
void LeerCadena(char **cad);

// Lee desde la entrada estándar una cadena de caracteres de tipo wchar
//  Precondición: Dirección de una cadena de caracteres de tipo wchar inicializada
//  Postcondición: Devuelve la cadena leida desde la entrada estándar
void LeerWCadena(wchar_t **cad);

// Lee desde un fichero una cadena de caracteres
//  Precondición: Fichero desde donde vamos a leer la cadena y dirección de una
//      cadena de caracteres inicializada
//  Postcondición: Devuelve todo el texto escrito en el fichero
void LeerWCadenaFich(FILE *, wchar_t **usu);

// Imprime una cadena de caracteres de tipo wchar_t por la salida estándar. Imprime un
// '\n' al final
//  Precondición: cadena de caracteres de tipo wchar_t.
void ImprimirWCadena(wchar_t *cad);

// Escribe una cadena de caracteres en un fichero "traduccion.txt"
void ImprimirCadenaFich(char *cad, char *fich);

// Convierte las letras con tildes a letras sin tildes
//  Precondición: Recibe una cadena de caracteres de tipo wchar_t
//  Postcondición: Devuelve la misma cadena sin tildes
void QuitarTildes(wchar_t *);

// Elimina los carácteres que no sean letras o números
//  Precondición: Recibe una cadena de caracteres de tipo wchar_t y la longuitud de esta
//  Postcondición: Devuelve la cadena sin caracteres que no sean alfanumericos
void EliminarCarac(wchar_t **, int);

// Convierte a mayúscula las minúsculas
//  Precondición: Cadena de caracteres
//  Postcondición: Devuelve la cadena con todas las letras en mayúscula
void PasoMayus(wchar_t *);

// Traduce a morse una cadena de caracteres
//  Precondición: Cadena donde vamos a almacenar la traducción, la cadena que
//      vamos a traducir(wchar_t) y la tabla con las traducciones
//  Postcondición: Devuelve la cadena traducida a morse
void Traduccion(char **traduc, wchar_t *usu, char **tabla);
