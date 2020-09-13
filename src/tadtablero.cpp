/**

	INTRODUCCIÓN A LA PROGRAMACIÓN / FUNDAMENTOS DE PROGRAMACIÓN
	Curso 2010/2011

	Nombre: entorno.cpp
	Descripción: Implementación del TAD Tablero para el proyecto LIGTHS OFF.
	Autor:	Samuel Moreno
	Fecha:	01/17/2011

*/

#include "entorno.h"
#include "tadtablero.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <allegro.h>

using namespace std;

// -------------------------------------------------------------
// Definicion de constantes privadas
// -------------------------------------------------------------

//typedef struct TadTablero{
int          aleatorio;
int          movs_restantes;
int          comodin;
int          patron;
bool		 casillas[MAX_DIMENSION][MAX_DIMENSION];



void Inicializar_apagado (int fila, int col, int dimension){
for (fila = 0; fila < dimension; fila++) {
	 for (col = 0; col < dimension; col++) {
		 casillas[fila][col] = false;
	 }
}
}
void Inicializar_aleatorio (int fila, int col, int dimension){
if (aleatorio != 0) {

	  int  nluces = aleatorio;

	  srand(time(NULL));

	  while (nluces > 0) {
		  fila = rand() % dimension;
		  col  = rand() % dimension;
		  if (casillas[fila][col] == false) {
			  casillas[fila][col] = true;
			  nluces--;
		  }
	  }

}
}
void encender_luces (int &fila, int &col, int dimension){
for (fila = 0; fila < dimension; fila++) {
	 for (col = 0; col < dimension; col++) {
		 if (casillas[fila][col] == true)
			 TEntornoEncenderCasilla(fila, col);
	 }
}


fila = 0;
col  = 0;
TEntornoActivarCasilla  (fila, col);
}


bool Inicializar_parametros (int &dimension){
	char msg[40];
	if (! TEntornoCargarConfiguracion (dimension,
		                             patron,
		                             movs_restantes,
		                             comodin,
		                             aleatorio,
		                             casillas)) {
	  cout << "Error al cargar la configuración desde fichero [luces.cnf]."  << endl;
	  return false;
}

if (! TEntornoIniciar (dimension))   return false;



sprintf(msg, "Patrón actual: %d", patron);
TEntornoMostrarMensaje(Zona1, msg);

sprintf(msg, "Movs. Restantes: %d", movs_restantes);
TEntornoMostrarMensaje(Zona2, msg);

sprintf(msg, "Usos del comodin: %d", comodin);
TEntornoMostrarMensaje(Zona3, msg);
}


void Usar_patron (int fila, int col, int dimension, bool &salir, bool &ganador){
	char msg[40];
	  if (patron == 0) TEpatron0 (fila, col, dimension);
else  if (patron == 1) TEpatron1 (fila, col, dimension);
else  if (patron == 2) TEpatron2 (fila, col, dimension);
else  if (patron == 3) TEpatron3 (fila, col, dimension);
else  if (patron == 4) TEpatron4 (fila, col, dimension);


//Contador de movimientos//
movs_restantes = movs_restantes - 1;
sprintf(msg, "Movs. Restantes: %d", movs_restantes);
TEntornoMostrarMensaje(Zona2, msg);

//Casos en los que sale//
if (movs_restantes == 0)
salir = true;
if ( TEApagado (fila, col, dimension) == true){
ganador = true;
salir = true;
}
}

void cambiar_patron (){
	char msg[40];
	patron = patron + 1;
    if (patron > 4)
  	  patron = 0;

	  sprintf(msg, "Patrón actual: %d", patron);
	  TEntornoMostrarMensaje(Zona1, msg);

}

///////////////////// Modulo de comprobación de matriz apagada///////////////////////////////////////
bool TEApagado (int fila, int col, int dimension){
	  for (fila = 0; fila < dimension; fila++) {
		 for (col = 0; col < dimension; col++) {
			 if (casillas[fila][col] == true) {
				 return false;
			 }
		 }
	  }
	  return true;
}
/////////////////COMODIN////////////////////////////

void Uso_de_comodin (int fila, int col, int dimension, bool &salir, bool &ganador){
	char msg[40];
	bool estado;
	 if (comodin > 0){

	   estado = casillas[fila][col];
	   if (estado == true){
		   TEntornoApagarCasilla(fila, col);
	   	   casillas[fila][col] = false;
			 comodin = comodin - 1;
			 sprintf(msg, "Usos del comodin: %d", comodin);
		   TEntornoMostrarMensaje(Zona3, msg);
	   }
	   if ( TEApagado (fila, col, dimension) == true){
	  	   ganador = true;
	  	   salir = true;
	   }
	 }

}
/////////////////PATRON 0///////////////////////////
void TEpatron0 (int fila, int col, int dimension){
	bool estado;
//CASILLA DEL CENTRO//

estado = casillas[fila][col];

if (estado == false)
TEntornoEncenderCasilla(fila, col);
else
TEntornoApagarCasilla(fila, col);

casillas[fila][col] = ! estado;

//CASILLA DE ARRIBA//
if (fila - 1 >= 0){
estado = casillas[fila - 1][col];

if (estado == false)
TEntornoEncenderCasilla(fila - 1, col);
else
TEntornoApagarCasilla(fila - 1, col);

casillas[fila - 1][col] = ! estado;
}
//CASILLA DE ABAJO//
if (fila + 1 < dimension){
estado = casillas[fila + 1][col];

if (estado == false)
TEntornoEncenderCasilla(fila + 1, col);
else
TEntornoApagarCasilla(fila + 1, col);

casillas[fila + 1][col] = ! estado;
}
//CASILLA DE LA DERECHA//
if (col + 1 < dimension){
estado = casillas[fila][col + 1];

if (estado == false)
TEntornoEncenderCasilla(fila, col + 1);
else
TEntornoApagarCasilla(fila, col + 1);

casillas[fila][col + 1] = ! estado;
}
//CASILLA DE LA IZQUIERDA//
if (col - 1 >= 0){
estado = casillas[fila][col - 1];

if (estado == false)
TEntornoEncenderCasilla(fila, col - 1);
else
TEntornoApagarCasilla(fila, col - 1);

casillas[fila][col - 1] = ! estado;
}
}

/////////////////PATRON 1///////////////////////////
void TEpatron1 (int fila, int col, int dimension){
	bool estado;
	int fil = fila;
	int co = col;

	  for (fil = 0; fil < dimension; fil++) { //cambia la fila
		  estado = casillas[fil][col];
		  if (estado == false)
		  TEntornoEncenderCasilla(fil, col);
		  else
		  TEntornoApagarCasilla(fil, col);

		  casillas[fil][col] = ! estado;
	  }

	  for (co = 0; co < dimension; co++) { //cambia la columna
		  estado = casillas[fila][co];
		  if (estado == false)
		  TEntornoEncenderCasilla(fila, co);
		  else
		  TEntornoApagarCasilla(fila, co);

		  casillas[fila][co] = ! estado;
	  }

	  //Al cambiarse 2 veces la casilla central, hay que cambiala una vez mas
		estado = casillas[fila][col];
		if (estado == false)
			TEntornoEncenderCasilla(fila, col);
		   else
			   TEntornoApagarCasilla(fila, col);
		casillas[fila][col] = ! estado;
}
/////////////////PATRON 2///////////////////////////
void TEpatron2 (int fila, int col, int dimension){
	bool estado;
	int fil = fila;
	int co = col;

	while (fil >= 0 && fil < dimension && co >= 0 && co < dimension){
		estado = casillas[fil][co];
		if (estado == false) // Apagado
			TEntornoEncenderCasilla(fil, co);
		   else  // Encendido
			   TEntornoApagarCasilla(fil, co);
		casillas[fil][co] = ! estado;
		fil--;
		co--;
	}
	fil = fila;
	co = col;
	while (fil >= 0 && fil < dimension && co >= 0 && co < dimension){
		estado = casillas[fil][co];
		if (estado == false) // Apagado
			TEntornoEncenderCasilla(fil, co);
		   else  // Encendido
			   TEntornoApagarCasilla(fil, co);
		casillas[fil][co] = ! estado;
		fil++;
		co--;
	}
	fil = fila;
	co = col;
	while (fil >= 0 && fil < dimension && co >= 0 && co < dimension){
		estado = casillas[fil][co];
		if (estado == false) // Apagado
			TEntornoEncenderCasilla(fil, co);
		   else  // Encendido
			   TEntornoApagarCasilla(fil, co);
		casillas[fil][co] = ! estado;
		fil--;
		co++;
	}
	fil = fila;
	co = col;
	while (fil >= 0 && fil < dimension && co >= 0 && co < dimension){
		estado = casillas[fil][co];
		if (estado == false) // Apagado
			TEntornoEncenderCasilla(fil, co);
		   else  // Encendido
			   TEntornoApagarCasilla(fil, co);
		casillas[fil][co] = ! estado;
		fil++;
		co++;
	}
	estado = casillas[fila][col];
	if (estado == false)
		TEntornoEncenderCasilla(fila, col);
	   else
		   TEntornoApagarCasilla(fila, col);
	casillas[fila][col] = ! estado;
}
/////////////////PATRON 3///////////////////////////
void TEpatron3 (int fila, int col, int dimension){
	bool estado;
	//CASILLA DEL CENTRO//

	estado = casillas[fila][col];

	if (estado == false)
	TEntornoEncenderCasilla(fila, col);
	else
	TEntornoApagarCasilla(fila, col);

	casillas[fila][col] = ! estado;

	//CASILLA DE ARRIBA//
	if (fila - 1 >= 0){
	estado = casillas[fila - 1][col];

	if (estado == false)
	TEntornoEncenderCasilla(fila - 1, col);
	else
	TEntornoApagarCasilla(fila - 1, col);

	casillas[fila - 1][col] = ! estado;
	}
	//CASILLA DE ABAJO//
	if (fila + 1 < dimension){
	estado = casillas[fila + 1][col];

	if (estado == false)
	TEntornoEncenderCasilla(fila + 1, col);
	else
	TEntornoApagarCasilla(fila + 1, col);

	casillas[fila + 1][col] = ! estado;
	}
	//CASILLA DE LA DERECHA//
	if (col + 1 < dimension){
	estado = casillas[fila][col + 1];

	if (estado == false)
	TEntornoEncenderCasilla(fila, col + 1);
	else
	TEntornoApagarCasilla(fila, col + 1);

	casillas[fila][col + 1] = ! estado;
	}
	//CASILLA DE LA IZQUIERDA//
	if (col - 1 >= 0){
	estado = casillas[fila][col - 1];

	if (estado == false)
	TEntornoEncenderCasilla(fila, col - 1);
	else
	TEntornoApagarCasilla(fila, col - 1);

	casillas[fila][col - 1] = ! estado;
	}
	//CASILLA DE LA SUPERIOR IZQUIERDA//
	if (fila - 1 >= 0 && col - 1 >= 0){
	estado = casillas[fila - 1][col - 1];

	if (estado == false)
		TEntornoEncenderCasilla(fila -1, col - 1);
	else
		TEntornoApagarCasilla(fila -1, col - 1);

	casillas[fila - 1][col - 1] = ! estado;
	}
	//CASILLA DE LA SUPERIOR DERECHA//
	if (fila - 1 >= 0 && col + 1 < dimension){
	estado = casillas[fila - 1][col + 1];

	if (estado == false)
		TEntornoEncenderCasilla(fila -1, col + 1);
	else
		TEntornoApagarCasilla(fila -1, col + 1);

	casillas[fila - 1][col + 1] = ! estado;
	}
	//CASILLA DE LA INFERIOR IZQUIERDA//
	if (fila + 1 < dimension && col - 1 >= 0){
	estado = casillas[fila + 1][col - 1];

	if (estado == false)
		TEntornoEncenderCasilla(fila + 1, col - 1);
	else
		TEntornoApagarCasilla(fila + 1, col - 1);

	casillas[fila + 1][col - 1] = ! estado;
	}
	//CASILLA DE LA INFERIOR DERECHA//
	if (fila + 1 < dimension && col + 1 < dimension){
	estado = casillas[fila + 1][col + 1];

	if (estado == false)
		TEntornoEncenderCasilla(fila + 1, col + 1);
	else
		TEntornoApagarCasilla(fila + 1, col + 1);

	casillas[fila + 1][col + 1] = ! estado;
	}
}

void TEpatron4 (int fila, int col, int dimension){
	bool estado;
	if (fila > 0 && col > 0 && fila < dimension - 1 && col < dimension - 1)	TEpatron0 (fila, col, dimension);
	else if (((fila == 0 && col == 0) || (fila == 0 && col == dimension - 1)) || ((fila == dimension - 1 && col == 0) || (fila == dimension - 1 && col == dimension - 1))) TEpatron3 (fila, col, dimension);
	else if (fila == 0 || fila == dimension - 1){
		//CASILLA DEL CENTRO//

		estado = casillas[fila][col];

		if (estado == false)
		TEntornoEncenderCasilla(fila, col);
		else
		TEntornoApagarCasilla(fila, col);

		casillas[fila][col] = ! estado;
		//CASILLA DE LA DERECHA//
		if (col + 1 < dimension){
		estado = casillas[fila][col + 1];

		if (estado == false)
		TEntornoEncenderCasilla(fila, col + 1);
		else
		TEntornoApagarCasilla(fila, col + 1);

		casillas[fila][col + 1] = ! estado;
		}
		//CASILLA DE LA IZQUIERDA//
		if (col - 1 >= 0){
		estado = casillas[fila][col - 1];

		if (estado == false)
		TEntornoEncenderCasilla(fila, col - 1);
		else
		TEntornoApagarCasilla(fila, col - 1);

		casillas[fila][col - 1] = ! estado;
		}
	}
	else if (col == 0 || col == dimension - 1){
		//CASILLA DEL CENTRO//

		estado = casillas[fila][col];

		if (estado == false)
		TEntornoEncenderCasilla(fila, col);
		else
		TEntornoApagarCasilla(fila, col);

		casillas[fila][col] = ! estado;

		//CASILLA DE ARRIBA//
		if (fila - 1 >= 0){
		estado = casillas[fila - 1][col];

		if (estado == false)
		TEntornoEncenderCasilla(fila - 1, col);
		else
		TEntornoApagarCasilla(fila - 1, col);

		casillas[fila - 1][col] = ! estado;
		}
		//CASILLA DE ABAJO//
		if (fila + 1 < dimension){
		estado = casillas[fila + 1][col];

		if (estado == false)
		TEntornoEncenderCasilla(fila + 1, col);
		else
		TEntornoApagarCasilla(fila + 1, col);

		casillas[fila + 1][col] = ! estado;
		}
	}
}
