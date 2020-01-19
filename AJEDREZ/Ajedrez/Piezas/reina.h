

#include <iostream>
using namespace std;
#ifndef REINA_H
#define REINA_H
#define MAX_CANTMOV 6 //INCLUYE EL ORIGEN Y EL DESTINO
#include "pieza.h"


class Reina: public Pieza{
private:
	posP posI[MAX_CANTMOV];

public:
	Reina(int posX, int posY, bool color);
	
	void Dibujar(); 
	posP* getMovIntermedios(int destX, int destY);
	int movValido(int destX, int destY); 
	char tipoPieza();

};

#endif

