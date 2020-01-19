#include "alfil.h"

Alfil::Alfil(int posX, int posY, bool color):Pieza (posX, posY, color){
	for (int i=0; i<MAX_CANTMOV; i++){
		posI[i].x = -1;
		posI[i].y = -1;	
	}
}

void Alfil::Dibujar(){
	if (_mapa){	
		if (Pieza::getColor())
			readimagefile ("Piezas\\alfil.jpg",_mapa->izq+MARGEN_F, _mapa->sup+MARGEN_F, _mapa->der-MARGEN_F, _mapa->inf-MARGEN_F);
		else
			readimagefile ("Piezas\\alfilNegro.jpg", _mapa->izq+MARGEN_F, _mapa->sup+MARGEN_F, _mapa->der-MARGEN_F, _mapa->inf-MARGEN_F);
	}
}

posP* Alfil::getMovIntermedios(int destX, int destY){ //27/11 Ver las modificaciones de los news

	for(int i=0; i<MAX_CANTMOV; i++){ //LOS QUE NO SE USAN SE INICIALIZAN EN -1
		posI[i].x=-1;
		posI[i].y=-1;
	}

	int i=0;

	if(destX>Pieza::getPosX()&&destY<Pieza::getPosY()){ //Si el movimiento es arriba a la derecha
		if(Pieza::getPosX()+1!=destX&&Pieza::getPosY()-1!=destY){ //verifica que haylla movimientos itermedios q crear
			posI[i].x=Pieza::getPosX()+1;
			posI[i].y=Pieza::getPosY()-1;
			i++;
			while((posI[i-1].x)+1!=destX&&(posI[i-1].y)-1!=destY){
				posI[i].x=(posI[i-1].x)+1;
				posI[i].y=(posI[i-1].y)-1;
				i++;
			}
		}
	}

	if(destX<Pieza::getPosX()&&destY>Pieza::getPosY()){ //Si el movimiento es abajo a la izquierda
		if(Pieza::getPosX()-1!=destX&&Pieza::getPosY()+1!=destY){
			posI[0].x=Pieza::getPosX()-1;
			posI[0].y=Pieza::getPosY()+1;
			i++;
			while((posI[i-1].x)-1!=destX&&(posI[i-1].y)+1!=destY){
				posI[i].x=(posI[i-1].x)-1;
				posI[i].y=(posI[i-1].y)+1;
				i++;
			}
		}
	}

	if(destX<Pieza::getPosX()&&destY<Pieza::getPosY()){//Si el movimiento es arriba a la izquierda
		if(Pieza::getPosX()-1!=destX&&Pieza::getPosY()-1!=destY){
			posI[0].x=Pieza::getPosX()-1;
			posI[0].y=Pieza::getPosY()-1;
			i++;
			while((posI[i-1].x)-1!=destX&&(posI[i-1].y)-1!=destY){
				posI[i].x=(posI[i-1].x)-1;
				posI[i].y=(posI[i-1].y)-1;
				i++;
			}
		}
	}

	if(destX>Pieza::getPosX()&&destY>Pieza::getPosY()){ //Si el movimiento es abajo a la derecha
		if(Pieza::getPosX()+1!=destX&&Pieza::getPosY()+1!=destY){
			posI[0].x=Pieza::getPosX()+1;
			posI[0].y=Pieza::getPosY()+1;
			i++;
			while((posI[i-1].x)+1!=destX&&(posI[i-1].y)+1!=destY){
				posI[i].x=(posI[i-1].x)+1;
				posI[i].y=(posI[i-1].y)+1;
				i++;
			}
		}
	}

	return posI; 		
}

int Alfil::movValido(int destX, int destY){

	if ((destX>Pieza::getPosX()&& destY<Pieza::getPosY())||
		(destX<Pieza::getPosX()&& destY>Pieza::getPosY())){ //si el movimiento es arriba a la derecha o abajo a la izquierda
			if ((destX+destY) == (Pieza::getPosX()+Pieza::getPosY()))
				return MOV_CORRECTO;
			else
				return MOV_INCORRECTO;
	}else if ((destX<Pieza::getPosX()&& destY<Pieza::getPosY())||
		     (destX>Pieza::getPosX()&& destY>Pieza::getPosY())){			//si el movimiento es arriba a la izquierda o abajo a la derecha
			if ((destY-destX) == (Pieza::getPosY()-Pieza::getPosX()))
				return MOV_CORRECTO;
			else
				return MOV_INCORRECTO;
	}else 
		return MOV_INCORRECTO;
}

char Alfil::tipoPieza(){
	return 'A';
}