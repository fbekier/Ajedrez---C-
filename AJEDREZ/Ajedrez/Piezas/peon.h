#ifndef PEON_H
#define PEON_H

#define MAX_CANTMOV 2
#include <iostream>
#include "pieza.h"

using namespace std;

class Peon: public Pieza{

private:
	bool _primerMov;
	posP _posI[MAX_CANTMOV];
public:
	Peon(int posX, int posY, bool color);
	~Peon();
	void Dibujar(); 
	void Mover(int x, int y,  posS* mapa); 
	posP* getMovIntermedios(int destX, int destY);
	int movValido(int destX, int destY); 
	char tipoPieza();
	bool getPrimerMov(){return _primerMov;}
};
#endif
