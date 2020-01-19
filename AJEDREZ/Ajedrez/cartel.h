#ifndef CARTEL_H
#define CARTEL_H

#include <iostream>
#include "BGI\graphics.h"
#include "com.h"

class Cartel{
private:
	posS _mapa;
public:
	Cartel(posS mapa);
	void dibujar(int color, char* mensaje);
};
#endif