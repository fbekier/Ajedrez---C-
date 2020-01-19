#include "torre.h"

Torre::Torre(int x, int y, bool color):Pieza (x, y, color){
	_primerMov=true;
	for(int i=0; i<MAX_CANTMOV; i++){
		posI[i].x=-1;
		posI[i].y=-1;	
	}
}

posP* Torre::getMovIntermedios(int destX, int destY){

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
	return posI;
}



void Torre::Dibujar(){
	if(_mapa){	
		if(Pieza::getColor()){
			readimagefile("Piezas\\torre.jpg", _mapa->izq+MARGEN_F, _mapa->sup+MARGEN_F, _mapa->der-MARGEN_F, _mapa->inf-MARGEN_F);
		}else{
			readimagefile("Piezas\\torreNegra.jpg", _mapa->izq+MARGEN_F, _mapa->sup+MARGEN_F, _mapa->der-MARGEN_F, _mapa->inf-MARGEN_F);
		}
	}
}

void Torre::Mover(int x, int y, posS* mapa){
	Pieza::Mover (x, y, mapa);
	if (_primerMov){
		_primerMov=false;
	}
}

int Torre::movValido(int destX, int destY){
	if((destX==Pieza::getPosX())&&(destY==Pieza::getPosY())){
		return false;
	}else{
		if((destX==Pieza::getPosX())||(destY==Pieza::getPosY())){
			return true;		
		}else{
			return false;
		}	
	}
}

char Torre::tipoPieza(){
	return 'T';
}