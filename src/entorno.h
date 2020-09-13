/**

	INTRODUCCIÓN A LA PROGRAMACIÓN / FUNDAMENTOS DE PROGRAMACIÓN
	Curso 2010/2011

	Nombre: entorno.h
	Descripción: Especificación del TAD Entorno para el proyecto LIGTHS OUT.
	     	 	 Encargado del manejo de la interfaz del juego.
	Autor:	Profesores de las asignaturas
	Fecha:	03/11/2010

*/


#ifndef ENTORNO_H_
#define ENTORNO_H_


#include <allegro.h>

// -------------------------------------------------------------
// Definicion de constantes necesarias
// -------------------------------------------------------------

// Máxima y mínima dimensiones del tablero (el tablero es cuadrado, con lo que coindicen con
//    la fila y columna)
const int MAX_DIMENSION = 10;
const int MIN_DIMENSION =  4;

// Máximo tamaño de un mensaje a imprimir en el entorno
const int MAX_MENSAJE   = 50;

// -------------------------------------------------------------
// Definicion de tipos
// -------------------------------------------------------------

/**
 *   Este es el tipo devuelto por la operacion LeerTecla que indica la tecla
 *   de los cursores que se ha pulsado
 */
enum TipoTecla {TNada, TIzquierda, TDerecha, TArriba, TAbajo, TSalir, TEnter, TC, TX};

/**
 *   Zonas en el entorno para imprimir mensajes. Existen 3 zonas delimitadas para imprimir un
 *   mensaje en la pantalla del entorno. Se pueden usar para imprimir mensajes de estado de
 *   diferentes tipos (p.e. Movs. restantes, patrón actual, etc.)
 */
enum TipoZona {Zona1, Zona2, Zona3};


/**
 *   Tipo para los mensajes a imprimir en pantalla
 */
typedef char TipoMensaje [MAX_MENSAJE];


// -------------------------------------------------------------
// Declaración de interfaz (módulos) PÚBLICA
// -------------------------------------------------------------


/**
	PRE:  MIN_DIMENSION <= dimension <= MAX_DIMENSION,
	POST: Inicia la pantalla de juego, incluyendo una rejilla cuadrada de dimension "dimension".
	      Devuelve:
	       true:  Si todo se inicio correctamente
	       false: Si hay algún problema al iniciar
*/
bool TEntornoIniciar (int dimension);


/**
	PRE:
	POST: Destruye el contexto del entorno gráfico.
*/
void TEntornoTerminar();


/**
	PRE: Archivo luces.cnf correcto y en la carpeta raíz del proyecto
	     (NO SE COMPRUEBAN ERRORES EN LOS DATOS)
	POST: Devuelve:
	         TRUE:  si se carga correctamente la configuración del juego,
		     FALSE: en caso contrario.

		Si la configuración se lee de forma correcta se devolverá:
		   dimension:       Dimensión del tablero.
		   patron:          Patron inicial para encendido/apagado de luces
		   movs_restantes:  Cuantos movimientos se tienen para resolver el juego
		   comodin:         Entero que se puede usar como comodín para ampliaciones del juego
		   aleatorio:       Si se genera la configuración inicial de forma aleatoria (con el número de
		                    luces inicialmente encendidas) o se lee del archivo
		   casillas:        Si la carga del la config. inicial es desde el archivo, esta es la disposición

		Por defecto, el archivo luces.cnf se encuentra en el directorio  [proyecto].
 */
bool TEntornoCargarConfiguracion (int         &dimension,
		                          int         &patron,
		                          int         &movs_restantes,
		                          int         &comodin,
		                          int         &aleatorio,
		                          bool         casillas  [MAX_DIMENSION][MAX_DIMENSION]);


/**
	PRE:  fila y columna son coordenadas válidas en el entorno.  (>= MIN_DIMENSION && <= MAX_DIMENSION)
	POST: Establece una casilla con coordenadas fila, columna como activa con un rectángulo rojo.
*/
void TEntornoActivarCasilla(int fila, int columna);


/**
PRE: fila y columna son coordenadas válidas en el entorno. (>= MIN_DIMENSION && <= MAX_DIMENSION)
POST: Establece una casilla con coordenadas fila, columna en su estado habitual, sin resaltar.
*/
void TEntornoDesactivarCasilla(int fila, int columna);


/**
PRE:  fila y columna son coordenadas válidas en el entorno. (>= MIN_DIMENSION && <= MAX_DIMENSION)
POST: Enciende la luz de una casilla
*/
void TEntornoEncenderCasilla (int fila, int columna);


/**
PRE:  fila y columna son coordenadas válidas en el entorno. (>= MIN_DIMENSION && <= MAX_DIMENSION)
POST: Apaga la luz de una casilla
*/
void TEntornoApagarCasilla (int fila, int columna);


/**
PRE: El módulo recibe la zona en la que imprimir el mensaje (TipoZona) y una cadena de caracteres.
POST:Escribe el mensaje pasado por parámetro en el entorno, concretamente, en la zona especificada.
*/
void TEntornoMostrarMensaje (TipoZona zona, TipoMensaje msg);


/**
PRE:  cad es una cadena de caracteres a mostrar
POST: Muestra un mensaje para indicar que se ha conseguido (o no) el objetivo.
*/
void TEntornoMostrarMensajeFin (TipoMensaje cad);


/**
PRE:
POST:Devuelve un valor enumerado de TipoTecla con la tecla que se ha pulsado y que se deben interpretar.
*/
TipoTecla TEntornoLeerTecla(void);


#endif
