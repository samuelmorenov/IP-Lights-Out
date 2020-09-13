/**

	INTRODUCCIÓN A LA PROGRAMACIÓN / FUNDAMENTOS DE PROGRAMACIÓN
	Curso 2010/2011

	Nombre: entorno.cpp
	Descripción: Implementación del TAD Tablero para el proyecto LIGTHS OFF.
	Autor:	Samuel Moreno
	Fecha:	01/17/2011

*/


#include <iostream>
#include <stdio.h>
#include <allegro.h>
#include "entorno.h"

using namespace std;


/**
	PRE:
	POST: Inicia todo a apagado
	Complejidad: O(n)
*/
void Inicializar_apagado (int fila, int col, int dimension);


/**
	PRE:
	POST: Generar "aleatorio" numero de luces encendidas
	Complejidad: O(n)
*/
void Inicializar_aleatorio (int fila, int col, int dimension);


/**
	PRE:
	POST: Sea o no aleatorio (leido de archivo), encender las luces
	Complejidad: O(n)
*/
void encender_luces (int &fila, int &col, int dimension);


/**
	PRE:
	POST: Accedo a p.Tablero.Casillas por no crear una vble. nueva y copiar.
	Complejidad: O(1)
*/
bool Inicializar_parametros (int &dimension);


/**
	PRE:
	POST: Utiliza el patron de juego que este seleccionado, entre los 5 disponibles
	Complejidad: O(1)
*/
void Usar_patron (int fila, int col, int dimension, bool &salir, bool &ganador);


/**
	PRE:
	POST: Cambia el patron de juego entre los 5 disponibles y muetra el pantalla en nuevo valor del patron
	Complejidad: O(1)
*/
void cambiar_patron ();


/**
	PRE:
	POST: Comprueba si esta todo apagado
	Complejidad: O(log n)
*/
bool TEApagado (int fila, int col, int dimension);


/**
	PRE:
	POST: Usa la tecla C como comodin. La tecla de comodin cambia unicamente la celda seleccionada.
	Si esta esta encendida la apaga, si esta apagada no la enciende.
	No cuenta como movimiento, si no que consume el numero de comodines restantes.
	Si la celde esta apagada y se pulsa el comodin, no consume comodin al no encenderla.
	Complejidad: O(1)
*/
void Uso_de_comodin (int fila, int col, int dimension, bool &salir, bool &ganador);


/**
	PRE:
	POST: Utiliza el patron de juego numero: 0
	Este consiste en cambiar las casillas superior, inferior, izquierda, derecha y en la que se encuentra el cursor.
	Complejidad: O(1)
*/
void TEpatron0 (int fila, int col, int dimension);


/**
	PRE:
	POST: Utiliza el patron de juego numero: 1
	Este consiste en cambiar las casillas de la columna y de la fila que pasan por la casilla en la que se encuentra el cursor.
	Complejidad: O(n)
*/
void TEpatron1 (int fila, int col, int dimension);


/**
	PRE:
	POST: Utiliza el patron de juego numero: 2
	Este consiste en cambiar las casillas de las diagonales que pasan por la casilla en la que se encuentra el cursor.
	Complejidad: O(n)
*/
void TEpatron2 (int fila, int col, int dimension);


/**
	PRE:
	POST: Utiliza el patron de juego numero: 3
	Este consiste en cambiar las casillas que rodean a la que se encuentra el cursor.
	Complejidad: O(1)
*/
void TEpatron3 (int fila, int col, int dimension);


/**
	PRE:
	POST: Utiliza el patron de juego numero: 4
	Este consiste en cambiar las casillas superior, inferior, izquierda, derecha y en la que se encuentra el cursor,
	cuando este no esta al final del tablero.
	Cambia en la que esta y las 3 mas proximas cuando esta en una esquina.
	Y cuando se encuentra en un lado, la que esta y las 2 mas cercanas paralelas al lado en el que está.
	Complejidad: O(1)
*/
void TEpatron4 (int fila, int col, int dimension);
