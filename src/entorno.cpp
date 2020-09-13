/**

	INTRODUCCIÓN A LA PROGRAMACIÓN / FUNDAMENTOS DE PROGRAMACIÓN
	Curso 2010/2011

	Nombre: entorno.cpp
	Descripción: Implementación del TAD Entorno para el proyecto LIGTHS OFF.
	     	 	 Encargado del manejo de la interfaz del juego.
	Autor:	Profesores de las asignaturas
	Fecha:	03/11/2010

*/

#include "entorno.h"

#include <iostream>
#include <fstream>
#include <cstring>


using namespace std;


// -------------------------------------------------------------
// Definicion de constantes privadas
// -------------------------------------------------------------

const int MAX_CADENA      = 20;
const int COLOR_RESALTADO =  2;
const int COLOR_NORMAL    =  3; //NORMAL
const int C_VACIA         =  0; // Carácter para escribir vacio

// Definición de colores que usa el entorno
const int COLOR_BLANCO    = 0;
const int COLOR_ROJO      = 1;
const int COLOR_NEGRO     = 2;
const int COLOR_AMARILLO  = 3;
const int COLOR_VERDE     = 4;

// Número de imágenes de fichas que se usan en el tablero y su significado
const int MAX_FICHAS      = 2;
const int APAGADO         = 0;
const int ENCENDIDO       = 1;


// Tamaño de la ventana del juego
const int ANCHO_VENTANA   = 800;
const int ALTO_VENTANA    = 600;

// Definicón de constantes para posicionar los números en el tablero
const int DISTANCIA_COLS  = 55;  // Distancia entre columnas
const int DISTANCIA_FILAS = 55;  // Distancia entre filas
const int ORIGEN_X        = 20;  // Origen de las x
const int ORIGEN_Y        = 20;  // Origen de las y


// -------------------------------------------------------------
// Definicion de constantes privadas
// -------------------------------------------------------------

// Imágenes de fichas que se usan en el tablero
BITMAP *fichas[MAX_FICHAS];  // vector que contiene enlace a las imágenes de las fichas


// -------------------------------------------------------------
// Declaración de módulos PRIVADOS
// -------------------------------------------------------------

// define el color en función de los valores makecol - allegro library
int makecolor2 (int color);

// Dibuja en la pantalla el borde de un tablero con el ancho indicado
void TEntornoPintarRejilla (int f, int c);

// Invierte fila/columna.  El tablero gráfico (entorno) se dibuja por
// Columnas/Filas, mientras en C++ se trata con matrices en Filas/Columnas.
// Para que sea transparente al uso de matrices se invierte en el entorno
void InvertirFC (int &fila, int &columna);


// -------------------------------------------------------------
// Definición de módulos PRIVADOS
// -------------------------------------------------------------
int makecolor2 (int color) {

  int col;

  switch (color) {
    case COLOR_BLANCO:   col = makecol( 255, 255, 255); break;
    case COLOR_ROJO:     col = makecol( 255,   0,   0); break;
    case COLOR_NEGRO:    col = makecol( 100, 100, 100); break;
    case COLOR_AMARILLO: col = makecol( 200, 200,  50); break;
    default:             col = makecol( 255, 255, 255); break; //color blanco
  }

  return col;
}


void TEntornoPintarRejilla (int filas, int columnas) {
    // Comenzamos en la 0,0
	int  i;
	
	acquire_screen();

	// horizontales
	for (i = 0; i <= columnas; i++)
	  line( screen, ORIGEN_X+0*DISTANCIA_COLS, ORIGEN_Y+i*DISTANCIA_FILAS, ORIGEN_X+columnas*DISTANCIA_COLS, ORIGEN_Y+i*DISTANCIA_FILAS, makecol( 255, 255, 255));
	
	//verticales
	for (i = 0;i <= filas; i++)
	  line( screen, ORIGEN_X+i*DISTANCIA_COLS, ORIGEN_Y+0*DISTANCIA_FILAS, ORIGEN_X+i*DISTANCIA_COLS, ORIGEN_Y+filas*DISTANCIA_FILAS, makecol( 255, 255, 255));
	
	textout_ex (screen, font, "***   LIGHTS OUT   ***",    600,  50, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "PROYECTO DE PROGRAMACIÓN",  600,  70, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "TECLAS:",                   600, 120, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "Arriba: Fecha arriba",      600, 140, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "Abajo:  Flecha abajo",      600, 160, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "Drcha:  Flecha derecha",    600, 180, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "Izqda:  Flecha izquierda",  600, 200, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "Salir:  Escape",            600, 220, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "Encender/Apagar: Enter",    600, 240, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "Cambiar patrón:  C",        600, 260, makecol(255, 255, 255), makecol(0, 0, 0));
	textout_ex (screen, font, "Tecla comodín:   X",        600, 280, makecol(255, 255, 255), makecol(0, 0, 0));
	
	release_screen();

}


void InvertirFC (int &fila, int &columna) {

	int aux = columna;
	columna = fila;
	fila    = aux;

}



// -------------------------------------------------------------
// Definición de la interfaz PÚBLICA
// -------------------------------------------------------------

bool TEntornoIniciar (int dimension) {

  char nomfig[20];
  int  f = dimension;
  int  c = dimension;


  // Iniciar el entorno
  allegro_init();
  install_keyboard();
  set_color_depth(16);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

  // Pintar regilla
  TEntornoPintarRejilla(f, c);

  //inicio del vector de fichas a NULL
  for (int i = 0; i < MAX_FICHAS; i++) {
    sprintf(nomfig, "f%d.bmp", i);  // asigna el nombre de la figura a  cargar
    fichas[i] = load_bitmap(nomfig, NULL);
  }

  // Todas las casillas apagadas
  for (int i = 0; i < f; i++)
	  for (int j = 0; j < c; j++)
		  TEntornoApagarCasilla(i, j);

  return true;
}


void TEntornoTerminar () {

  for (int i = 0; i < MAX_FICHAS; i++)
     if (fichas[i] != NULL)
      destroy_bitmap(fichas[i]);

}


///////////////////////////////// Cargar la configuración inicial desde un archivo///////////////////////////////
bool TEntornoCargarConfiguracion (int     &dimension,
		                          int     &patron,
		                          int     &movs_restantes,
		                          int     &comodin,
		                          int     &aleatorio,
		                          bool     casillas  [MAX_DIMENSION][MAX_DIMENSION]) {

	ifstream  entrada;
	char      cad[MAX_DIMENSION + 1];
	

	entrada.open("luces.cnf");
	if (entrada == 0 ){
		cout << "Fichero de configuración no encontrado (<proyecto>/luces.cnf)." << endl;
		cout << "Formato:"           << endl;
		cout << "\t[Dimension]"      << endl;
		cout << "\t[Patrón]"         << endl;
		cout << "\t[Mov. restantes]" << endl;
		cout << "\t[comodin]"      << endl;
		cout << "\t[Random]"         << endl;
		cout << "\t[Tablero]"        << endl;
		return false;
	}

	entrada.getline(cad, 10);
	dimension = atoi(cad);

	entrada.getline(cad, 10);
	patron = atoi(cad);

	entrada.getline(cad, 10);
	movs_restantes = atoi(cad);

	entrada.getline(cad, 10);
	comodin = atoi(cad);

	entrada.getline(cad, 10);
	aleatorio = atoi(cad);

	if (aleatorio == 0) {

	  for (int i = 0; i < dimension; i++) {
	      entrada.getline(cad, MAX_CADENA);
	      for (int j = 0; j < dimension; j++) {
	    	  casillas[i][j] = cad[j] - 48;
	      }
	  }

	}

	entrada.close();
		
	return true;
}


void TEntornoActivarCasilla (int fila, int columna) {

    char cad[20];
    int  color = COLOR_ROJO;

    InvertirFC (fila, columna);

    sprintf(cad, "%d-%d", fila, columna);

    // Pinta de trazo distinto la fila-columna
    acquire_screen();

    rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS,   ORIGEN_Y + columna*DISTANCIA_COLS,   ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS,   ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS,   makecolor2(color));
    rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+1, ORIGEN_Y + columna*DISTANCIA_COLS+1, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-1, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-1, makecolor2(color));
    rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+2, ORIGEN_Y + columna*DISTANCIA_COLS+2, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-2, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-2, makecolor2(color));
    rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+3, ORIGEN_Y + columna*DISTANCIA_COLS+3, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-3, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-3, makecolor2(color));


    release_screen();
}



void TEntornoDesactivarCasilla(int fila, int columna) {

	int color = COLOR_BLANCO;

	InvertirFC (fila, columna);

  // Pinta de trazo distinto la ficha- columna
  acquire_screen();

  rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS,   ORIGEN_Y + columna*DISTANCIA_COLS,   ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS,   ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS,   makecolor2(color));
  rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+1, ORIGEN_Y + columna*DISTANCIA_COLS+1, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-1, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-1, makecol(0,0,0));
  rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+2, ORIGEN_Y + columna*DISTANCIA_COLS+2, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-2, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-2, makecol(0,0,0));
  rect( screen, ORIGEN_X + fila*DISTANCIA_FILAS+3, ORIGEN_Y + columna*DISTANCIA_COLS+3, ORIGEN_X + fila*DISTANCIA_FILAS+DISTANCIA_FILAS-3, ORIGEN_Y + columna*DISTANCIA_COLS +DISTANCIA_COLS-3, makecol(0,0,0));

  release_screen();
}



void TEntornoEncenderCasilla(int fila, int columna) {

	InvertirFC (fila, columna);

    acquire_screen();

    draw_sprite( screen, fichas[ENCENDIDO],
    					ORIGEN_X + fila    * DISTANCIA_FILAS + 3,
    					ORIGEN_Y + columna * DISTANCIA_COLS  + 3);

    release_screen();
}



void TEntornoApagarCasilla(int fila, int columna) {

	InvertirFC (fila, columna);

    acquire_screen();

    draw_sprite( screen, fichas[APAGADO],
    		             ORIGEN_X + fila    * DISTANCIA_FILAS + 3,
    		             ORIGEN_Y + columna * DISTANCIA_COLS  + 3);

    release_screen();
}


void TEntornoMostrarMensaje (TipoZona zona, TipoMensaje msg) {

	int fila;

	switch (zona) {

		case Zona1: fila = 500; break;
		case Zona2: fila = 520; break;
		case Zona3: fila = 540; break;
		default:  return;

	}

	textout_ex( screen, font, "                                        ",  600,fila , makecol( 255,   0, 0), makecol(0, 0, 0));
	textout_ex( screen, font, msg,                                         600,fila , makecol( 255, 255, 0), makecol(0, 0, 0));

}


void TEntornoMostrarMensajeFin (TipoMensaje cad) {

  int  i, j;

  // Borrar un rectangulo
  rectfill (screen, 200, 200, 620, 440, makecol(0, 0, 0));

  // Efecto
  for (i = 0, j = 0; i < 40 && j < 40; i+=4, j+=4) {
	  rect( screen, i + 220, j + 240, 600 - i, 400 - j, makecol( 255,   0,   0));
	  rect( screen, i + 222, j + 242, 598 - i, 398 - j, makecol( 255, 255, 255));
	  usleep(25000); // 25 milisegundos
  }

  // Mensaje
  textout_ex(screen, font, cad,  280, 320 , makecol( 255, 255, 0), makecol(0, 0, 0));

}


TipoTecla TEntornoLeerTecla (void) {

	TipoTecla tecla = TNada;

	readkey();

	if      (key[KEY_UP])    tecla = TArriba;
	else if (key[KEY_DOWN])  tecla = TAbajo;
	else if (key[KEY_RIGHT]) tecla = TDerecha;
	else if (key[KEY_LEFT])  tecla = TIzquierda;
	else if (key[KEY_ENTER]) tecla = TEnter;
	else if (key[KEY_ESC])   tecla = TSalir;
	else if (key[KEY_C])     tecla = TC;
	else if (key[KEY_X])     tecla = TX;

	clear_keybuf();
	return tecla;

}
