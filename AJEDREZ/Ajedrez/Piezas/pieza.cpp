#include "pieza.h"

Pieza::Pieza (int posX, int posY, bool color){
	_posX=posX;
	_posY=posY;
	_color=color;
	_mapa=NULL;
}

int Pieza::getPosX(){
	return _posX;
}

int Pieza::getPosY(){
	return _posY;
}

bool Pieza::getColor(){
	return _color;
}