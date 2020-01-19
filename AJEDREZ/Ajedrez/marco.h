#ifndef MARCO_H
#define MARCO_H

#include <iostream>
#include "BGI\graphics.h"
#include "com.h"

class Marco{
private:
	posS _mapa;
	int _ancho;
public:
	Marco(posS mapa, int ancho);
	void dibujar();
};
#endif