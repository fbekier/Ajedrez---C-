#ifndef REY_H
#define REY_H

#define MAX_CANTMOV 2

#include "Pieza.h"
#include <iostream>

using namespace std;

class Rey: public Pieza{
private:
	bool _primerMov;
	posP posI[MAX_CANTMOV];
public:
	Rey (int posX, int posY, bool color);
	~Rey();
	void Dibujar();
	posP* getMovIntermedios(int destX, int destY);
	void Mover(int destX, int destY, posS* mapa);
	int movValido(int destX, int destY);
	char tipoPieza();
	bool getPrimerMov(){return _primerMov;}
};
#endif
