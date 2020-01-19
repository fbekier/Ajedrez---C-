#ifndef TORRE_H
#define TORRE_H

#define MAX_CANTMOV 7 //NO INCLUYE EL ORIGEN Y EL DESTINO

#include <iostream>
#include "pieza.h"

using namespace std;

class Torre: public Pieza{
private:
	bool _primerMov;
	posP posI[MAX_CANTMOV];
public:
	Torre (int posX, int posY, bool color);
	void Dibujar();
	posP* getMovIntermedios(int destX, int destY);
	void Mover(int destX, int destY, posS* mapa);
	int movValido(int destX, int destY);
	char tipoPieza();
	bool getPrimerMov(){return _primerMov;}
};
#endif

