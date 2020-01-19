#include "peon.h"

Peon::Peon(int posX, int posY, bool color):Pieza(posX, posY, color){
	_primerMov=true;
	for(int i=0; i<MAX_CANTMOV;i++){
		_posI[i].x = -1;
		_posI[i].y = -1;
	}
}

Peon::~Peon(){
	for (int i=0; i<MAX_CANTMOV;i++){
		_posI[i].x = -1;
		_posI[i].y = -1;	
	}
}

void Peon::Dibujar(){
	if (_mapa){	
		if (Pieza::getColor()){
			readimagefile ("Piezas\\peon.jpg",_mapa->izq+MARGEN_F, _mapa->sup+MARGEN_F, _mapa->der-MARGEN_F, _mapa->inf-MARGEN_F);
		}else{
			readimagefile ("Piezas\\peonNegro.jpg", _mapa->izq+MARGEN_F, _mapa->sup+MARGEN_F, _mapa->der-MARGEN_F, _mapa->inf-MARGEN_F);
		}
	}
}

void Peon::Mover(int x, int y, posS* mapa){
		Pieza::Mover(x, y, mapa);
		if(_primerMov){
		_primerMov=false;
		}
}

posP* Peon::getMovIntermedios(int destX, int destY){
	switch (movValido (destX, destY)){
	case (P_AVANZA1):		
		for (int i=0; i<MAX_CANTMOV;i++){
			_posI[i].x = -1;
			_posI[i].y = -1;
		}			
		break;

	case (P_AVANZA2):
		_posI[1].x = -1;
		_posI[1].y = -1;
		if (Pieza::getColor()){
			_posI[0].x = destX;
			_posI[0].y = destY+1;
		}else{
			_posI[0].x = destX;
			_posI[0].y = destY-1;
		}break;

	case (P_COME):
		for (int i=0; i<MAX_CANTMOV;i++){
			_posI[i].x = -1;
			_posI[i].y = -1;
			break;
		}

		
	}return _posI;
}

int Peon::movValido(int destX, int destY){

	if (Pieza::getColor()){ //Si el Peon es Blanco
		if (_primerMov){            //Si es el primer Movimiento
			if ((destX==Pieza::getPosX()) && (destY == Pieza::getPosY()-1))//si el destino es en la misma columna, avanzando una fila	
				{return P_AVANZA1; }
			else if ((destX==Pieza::getPosX()) && (destY == Pieza::getPosY()-2)) // si el destino es en la misma columna, avanzando dos filas.
				{return P_AVANZA2;} 
			else if(((destX==Pieza::getPosX()-1)&&(destY==Pieza::getPosY()-1))|| //si el destino es comer hacia la izquierda
				((destX==Pieza::getPosX()+1)&&(destY==Pieza::getPosY()-1))) //si el destino es comer hacia la derecha
				{return P_COME;}
			else return MOV_INCORRECTO;												 
		}else if								//Si ya hizo el primer movimiento
			((destX==Pieza::getPosX()) &&(destY == Pieza::getPosY()-1)) // si el destino es en la misma columna, avanzando una fila.
				{return P_AVANZA1;}
		else if(((destX==Pieza::getPosX()-1)&&(destY==Pieza::getPosY()-1))|| //si el destino es comer hacia su izquierda 
			((destX==Pieza::getPosX()+1)&&(destY==Pieza::getPosY()-1))){ //si el destino es comer hacia su derecha)  
				{return P_COME;}
		}else return MOV_INCORRECTO;
	}else if(_primerMov){					// SI el Peon es negro
		//_primerMov = false;				//Si es el primer Movimiento  
		if ((destX==Pieza::getPosX()) && (destY == Pieza::getPosY()+1))// si el destino es en la misma columna, avanzando una fila.
			{return P_AVANZA1;}
		else if ((destX==Pieza::getPosX()) && (destY == Pieza::getPosY()+2))// si el destino es en la misma columna, avanzando dos filas.
			{return P_AVANZA2;}
		else if(((destX==Pieza::getPosX()+1)&&(destY==Pieza::getPosY()+1))|| //si el destino es comer hacia SU izquierda
			((destX==Pieza::getPosX()-1)&&(destY==Pieza::getPosY()+1))) //si el destino es comer hacia SU derecha) 
			{return P_COME;}
		else return MOV_INCORRECTO;
	}else if                                     //Si ya hizo el primer movimiento
		((destX==Pieza::getPosX()) &&(destY == Pieza::getPosY()+1))// SI el destino es en la misma columna, avanzando una fila.
			{return P_AVANZA1;}
	else if(((destX==Pieza::getPosX()+1)&&(destY==Pieza::getPosY()+1))|| //si el destino es comer hacia SU izquierda
		((destX==Pieza::getPosX()-1)&&(destY==Pieza::getPosY()+1))) //si el destino es comer hacia SU derecha)
			{return P_COME;}										
	else return MOV_INCORRECTO;
}

char Peon::tipoPieza (){
	return 'P';
}
