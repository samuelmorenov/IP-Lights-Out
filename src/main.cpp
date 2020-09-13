/**

	INTRODUCCIÓN A LA PROGRAMACIÓN / FUNDAMENTOS DE PROGRAMACIÓN
	Curso 2010/2011

	Nombre: main.cpp
	Descripción: Implementación del programa principal
	Autor:	Samuel Moreno Vincent
	Fecha:	13/01/2011

*/


#include <iostream>
#include <stdio.h>

#include "entorno.h"
#include "tadtablero.h"

using namespace std;

int main () {

	int			fila;
	int			col;
	int			dimension;
	bool		salir	= false;
	TipoTecla	tecla	= TNada;
	bool		ganador	= false;


	  Inicializar_parametros(dimension);
	  Inicializar_apagado (fila, col, dimension);
	  Inicializar_aleatorio (fila, col, dimension);
	  encender_luces (fila, col, dimension);

	  while (!salir) {

	       tecla = TEntornoLeerTecla();

	       switch (tecla) {

			   case TDerecha:

				   TEntornoDesactivarCasilla(fila, col);
				   col++;
				   if (col == dimension) col = 0;
				   TEntornoActivarCasilla(fila, col);

				   break;

			   case TIzquierda:

				   TEntornoDesactivarCasilla(fila, col);
				   col--;
				   if (col < 0) col = dimension - 1;
				   TEntornoActivarCasilla(fila, col);

				   break;

			   case TArriba:

				   TEntornoDesactivarCasilla(fila, col);
				   fila--;
				   if (fila < 0) fila = dimension - 1;
				   TEntornoActivarCasilla(fila, col);

				   break;

			   case TAbajo:

				   TEntornoDesactivarCasilla(fila, col);
				   fila++;
				   if (fila == dimension) fila = 0;
				   TEntornoActivarCasilla(fila, col);

				   break;

			   case TEnter:

				   Usar_patron (fila, col, dimension, salir, ganador);
				   break;

			   case TC:

				   cambiar_patron ();
				   break;

			   case TX:
				   Uso_de_comodin (fila, col, dimension, salir, ganador);
				   break;

			   case TSalir:

				   salir = true;
				   break;

			   default:
				   break;
	       }
	     }

	if (ganador) {
		TipoMensaje msg = "¡ ¡ Has completado el desafio ! !";
		TEntornoMostrarMensajeFin(msg);
	} else {
		TipoMensaje msg = "¡OOOOOhh.. No lo has conseguido!";
		TEntornoMostrarMensajeFin(msg);
	}
	TEntornoLeerTecla();

	TEntornoTerminar();


	return 0;
	  }
