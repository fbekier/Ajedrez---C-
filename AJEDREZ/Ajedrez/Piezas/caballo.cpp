/*
#include "caballo.h"

Caballo::Caballo(int posX, int posY, bool color):Pieza (posX, posY, color){
	
	posI.x=-1;
	posI.y=-1;	
	
}


void Caballo::Dibujar(){

	if (_mapa){	
		if (Pieza::getColor())
			readimagefile ("Piezas\\caballo.jpg",_mapa->izq+MARGEN_F, _mapa->sup+MARGEN_F, _mapa->der-MARGEN_F, _mapa->inf-MARGEN_F);
		else
			readimagefile ("Piezas\\caballoNegro.jpg",_mapa->izq+MARGEN_F, _mapa->sup+MARGEN_F, _mapa->der-MARGEN_F, _mapa->inf-MARGEN_F);
	}
}

posP* Caballo::getMovIntermedios(int destX, int destY){ 
	posI.x=-1;
	posI.y=-1;	

	return &posI;
}



int Caballo::movValido(int destX, int destY){

	if (((abs(getPosX()-destX) == 1) && (abs(getPosY()-destY) == 2)) ||((abs(getPosX()-destX) == 2) && (abs(getPosY()-destY == 1))))
		return CABALLO;
	else
		return MOV_INCORRECTO;
}

char Caballo::tipoPieza(){

	return 'C';
}
}*/

