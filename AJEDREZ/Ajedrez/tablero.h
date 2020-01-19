#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
#include "celda.h"
#include "Piezas\pieza.h"
#include "Piezas\alfil.h"
#include "Piezas\caballo.h"
#include "Piezas\peon.h"
#include "Piezas\reina.h"
#include "Piezas\rey.h"
#include "Piezas\torre.h"
#include "com.h"

const int CANT_X=8;
const int CANT_Y=8;
const int CANT_P=32;

typedef struct RegSave{
	int x;
	int y;
	bool color;
	char tipo;
};

class Tablero{
private:
	posS _mapa;
	Celda* _tablero[CANT_X][CANT_Y];
	Pieza* _piezas[CANT_P];
	bool _turno;
	void mapear(int &x, int &y);
	bool verificarMov(int xo, int yo, int xd, int yd);
	Pieza* buscarRey(bool color);
	bool hayJaque(int xd, int yd, bool color);
public:
	Tablero(posS mapa);
	~Tablero();
	posS* getMapa();
	void comenzar(); //inica un juego nuevo
	void continuar();
	void grabar();
	bool getTurno(){return _turno;}
	bool Tablero::hayJaque();
	bool hayJM();
	void setEstadoC(int x, int y, int estado);	//cambia estado de una celda (su color)
	int getEstadoC(int x, int y); //devuelve el estado de una celda (sirve para respetar jeraquias de color)
	bool seleccionarP(int x, int y);	//devuelve si true si hay una pieza en esa posicion
	int moverP(int xo, int yo, int xd, int yd);	//mueve una pieza y develve tru si lo hizo
	void refrescar(int x, int y);	//*dibuja solo la celda de esa posicion (y su pieza si hay una)
	void dibujar(); //dibuja todo el tablero
};
#endif