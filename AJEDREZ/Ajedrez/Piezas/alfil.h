#ifndef ALFIL_H
#define ALFIL_H

#define MAX_CANTMOV 7

#include "pieza.h"
#include <iostream>

using namespace std;

class Alfil: public Pieza{
private:
	posP posI[MAX_CANTMOV];
public:
	Alfil (int posX, int posY, bool color);
	void Dibujar();
	posP* getMovIntermedios(int destX, int destY);
	int movValido(int destX, int destY);
	char tipoPieza();
};
#endif
