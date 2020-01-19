
#include "reina.h"

Reina::Reina(int posX, int posY, bool color):Pieza (posX, posY, color){
	
	for(int i=0; i<MAX_CANTMOV; i++){
		posI[i].x=-1;
		posI[i].y=-1;	
	}
}



void Reina::Dibujar (){
	if (_mapa){	
		if (Pieza::getColor())
			readimagefile ("Piezas\\reina.jpg",_mapa->izq+MARGEN_F, _mapa->sup+MARGEN_F, _mapa->der-MARGEN_F, _mapa->inf-MARGEN_F);
		else
			readimagefile ("Piezas\\reinaNegra.jpg",_mapa->izq+MARGEN_F, _mapa->sup+MARGEN_F, _mapa->der-MARGEN_F, _mapa->inf-MARGEN_F);
	}
}

posP* Reina::getMovIntermedios(int destX, int destY){

	for(int i=0; i<MAX_CANTMOV; i++){ //LOS QUE NO SE USAN SE INICIALIZAN EN -1
		posI[i].x=-1;
		posI[i].y=-1;
	}

	int i=0;

	if((destX==Pieza::getPosX())&&(destY<Pieza::getPosY())){	//mover arriba
		if(Pieza::getPosY()-1!=destY){
			posI[i].x=Pieza::getPosX();
			posI[i].y=Pieza::getPosY()-1;
			i++;
			while((posI[i-1].y)-1!=destY){
				posI[i].x=posI[0].x;
				posI[i].y=posI[i-1].y-1;
				i++;
			}
		}
	}

	if((destX==Pieza::getPosX())&&(destY>Pieza::getPosY())){	//mover abajo
		if(Pieza::getPosY()+1!=destY){
			posI[0].x=Pieza::getPosX();
			posI[0].y=Pieza::getPosY()+1;
			i++;
			while((posI[i-1].y)+1!=destY){
				posI[i].x=posI[0].x;
				posI[i].y=posI[i-1].y+1;
				i++;
			}
		}
	}

	if((destY==Pieza::getPosY())&&destX<Pieza::getPosX()){	//mover izqierda
		if(Pieza::getPosX()-1!=destX){
			posI[0].x=Pieza::getPosX()-1;
			posI[0].y=Pieza::getPosY();
			i++;
			while((posI[i-1].x)-1!=destX){
				posI[i].x=posI[i-1].x-1;
				posI[i].y=posI[0].y;
				i++;
			}
		}			
	}

	if((destY==Pieza::getPosY())&&destX>Pieza::getPosX()){	//mover derecha
		if(Pieza::getPosX()+1!=destX){
			posI[0].x=Pieza::getPosX()+1;
			posI[0].y=Pieza::getPosY();
			i++;
			while((posI[i-1].x)+1!=destX){
				posI[i].x=posI[i-1].x+1;
				posI[i].y=posI[0].y;
				i++;
			}
		}
	}

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

int Reina::movValido(int destX, int destY){

	if((destX==getPosX())&&(destY==Pieza::getPosY())){
		return false;
	}else if((destX==Pieza::getPosX())||(destY==Pieza::getPosY())){
		return true;		
	}else if ((destX>Pieza::getPosX()&& destY<Pieza::getPosY())||
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


char Reina::tipoPieza(){
	return 'r';
}
