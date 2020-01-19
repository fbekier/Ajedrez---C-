#ifndef PIEZA_H
#define PIEZA_H

#include <iostream>

using namespace std;

#include "../BGI/graphics.h"
#include "../com.h"

#define MARGEN_F 5

#define MOV_INCORRECTO 0
#define MOV_CORRECTO 1
#define P_AVANZA1 2
#define P_AVANZA2 3
#define P_COME 4
#define R_NORMAL 5
#define R_ENROQUE 6
#define CABALLO 7

class Pieza{
private:
	int _posX; 
	int _posY; 
	bool _color;
protected:
	posS* _mapa;
public:
	Pieza ();
	Pieza (int posX, int posY, bool color);
	void setPos(int x, int y, posS* mapa){_posX=x; _posY=y, _mapa=mapa;}
	int getPosX();
	int getPosY();
	bool getColor();

	virtual posP* getMovIntermedios(int destX, int destY)=0;
	virtual char tipoPieza()=0;
	virtual void Dibujar()=0;
	virtual void Mover(int x, int y, posS* mapa){_posX=x; _posY=y, _mapa=mapa;}
	virtual int movValido(int destX, int destY)=0;
};
#endif