#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "tablero.h"
#include "BGI/graphics.h"
#include "com.h"

class Menu{
private:
	posD _mapaD;
	posS _mapa;
	Tablero* _tablero;
public:
	Menu(posS mapa, Tablero* tablero);
	posS* getMapa(){return &_mapa;}
	bool setOpcion(int x, int y);
	void dibujar();
};
#endif