#include "rey.h"

Rey::Rey(int x, int y, bool color):Pieza (x, y, color){
	_primerMov=true;
	for (int i=0; i<MAX_CANTMOV; i++){
		posI[i].x = -1;
		posI[i].y = -1;
	}
}

Rey::~Rey(){
	for (int i=0; i<MAX_CANTMOV; i++){
		posI[i].x = -1;
		posI[i].y = -1;
	}
}

void Rey::Dibujar(){
	if (_mapa){	
		if (Pieza::getColor())
			readimagefile ("Piezas\\rey.jpg",_mapa->izq+MARGEN_F, _mapa->sup+MARGEN_F, _mapa->der-MARGEN_F, _mapa->inf-MARGEN_F);
		else
			readimagefile ("Piezas\\reyNegro.jpg", _mapa->izq+MARGEN_F, _mapa->sup+MARGEN_F, _mapa->der-MARGEN_F, _mapa->inf-MARGEN_F);
	}
}

posP* Rey::getMovIntermedios(int destX, int destY){

	if (abs(destX-Pieza::getPosX()) == 1 || abs(destY-Pieza::getPosY()) == 1){ //si es un movimiento normal de rey
		for (int i=0; i<MAX_CANTMOV; i++){
		posI[i].x = -1;
		posI[i].y = -1;
		}
	}else if(abs(destX-Pieza::getPosX()) == 2 && (destY==Pieza::getPosY())){ //si es un moviminto tipo ENROQUE
		posI[1].x=-1;
		posI[1].y=-1;		
		if (destX < Pieza::getPosX()){
			posI[0].x = destX +1; 
			posI[0].y = Pieza::getPosY();
		
		}else if (destX > Pieza::getPosX()){
			posI[0].x = destX -1; 
			posI[0].y = Pieza::getPosY();
		}
	}
	return posI;
}

void Rey::Mover(int destX, int destY, posS* mapa){
		Pieza::Mover (destX, destY, mapa);
		if (_primerMov){
			_primerMov = false;
		}
}

int Rey::movValido(int destX, int destY){

	bool enroque = false;
	int x = Pieza::getPosX();
	int y = Pieza::getPosY();
	
	if (_primerMov){ // si es el primer movimiento
		if(abs(destX-Pieza::getPosX()) == 2 && (destY==Pieza::getPosY())){ //y es movimiento tipo enroque
			return R_ENROQUE;
			enroque = true;
		}
	}

	if (!enroque){
	 if  (destY+1==y) // si el destino es hacia arriba
		if (destX+1==x) // y en diagonal izquierda
			return R_NORMAL;
		else if (destX==x)//misma columna
			return R_NORMAL;
		else if (destX-1==x) // en diagonal derecha
			return R_NORMAL;
		else
			return MOV_INCORRECTO;
	else if (destY==y) //si el destino es en la misma fila
		if (destX+1==x) //hacia la izquierda
			return R_NORMAL;
		else if (destX-1==x)//hacia la derecha
			return R_NORMAL;
		else 
			return MOV_INCORRECTO;
	else if (destY-1==y) //si el destino es hacia abajo 
		if (destX+1==x)//hacia la izquierda
			return R_NORMAL;
		else if (destX==x)
			return R_NORMAL;
		else if (destX-1==x)
			return R_NORMAL;
		else
			return MOV_INCORRECTO;
	else
		return MOV_INCORRECTO;
	}
}

char Rey::tipoPieza(){
	return 'R';
}