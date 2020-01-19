#ifndef CELDA_H
#define CELDA_H

#include <iostream>
#include "BGI\graphics.h"
#include "Piezas\pieza.h"
#include "com.h"

using namespace std;

#define CC_NEGRO BLACK;
#define CC_BLANCO WHITE;
#define CC_CORRECTO YELLOW;
#define CC_POSICIONADO LIGHTBLUE;
#define CC_SELECCIONADO LIGHTGREEN;

class Celda{
private:
	int _x;
	int _y;
	posS _pos;
	bool _color;
	int _estado;
	Pieza* _pieza;
public:
	Celda(bool color, int posX, int posY, posS* mapa);
	void setEstado(int estado);
	int getEstado();
	void setPieza(Pieza* pieza);
	void recibirPieza(Pieza* pieza);
	void sacarPieza();
	Pieza* getPieza();
	bool hayPieza();
	void dibujar();
};
#endif