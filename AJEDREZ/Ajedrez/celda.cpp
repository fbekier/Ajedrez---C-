#include "celda.h"

Celda::Celda(bool color, int posX, int posY,  posS* mapa){
	_x=posX;
	_y=posY;
	_color=color;
	int anchoC=(mapa->der-mapa->izq)/8;
	int altoC=(mapa->inf-mapa->sup)/8;

	_pos.izq=mapa->izq+anchoC*_x;
	_pos.sup=mapa->sup+altoC*_y;
	_pos.der=_pos.izq+anchoC;
	_pos.inf=_pos.sup+altoC;

	_estado=0;
	_pieza=NULL;
}

void Celda::setEstado(int estado){
	_estado=estado;
}

int Celda::getEstado(){
	return _estado;
}

void Celda::setPieza(Pieza* pieza){
	if(pieza){
		_pieza=pieza;
		_pieza->setPos(_x, _y, &_pos);
	}
}

void Celda::recibirPieza(Pieza* pieza){
	if(pieza){
		_pieza=pieza;
		_pieza->Mover(_x, _y, &_pos);
	}
}

void Celda::sacarPieza(){
	if(_pieza){
		_pieza->setPos(-1, -1, NULL);
		_pieza=NULL;
	}
}

Pieza* Celda::getPieza(){
	return _pieza;
}

bool Celda::hayPieza(){
	if(_pieza){
		return true;
	}else{
		return false;
	}
}

void Celda::dibujar(){
	int color;
	switch (_estado){
	case 1:
		color=CC_CORRECTO;
		setfillstyle(1, color);
		break;
	case 2:
		color=CC_POSICIONADO;
		setfillstyle(1, color);
		break;
	case 3:
		color=CC_SELECCIONADO;
		setfillstyle(1, color);
		break;
	default:
		if (_color){
			color=CC_BLANCO;
			setfillstyle(1, color);
		}else{
			color=CC_NEGRO;
			setfillstyle(1, color);
		}
		break;	
	}
	bar(_pos.izq, _pos.sup, _pos.der, _pos.inf);

	if (_pieza){
		_pieza->Dibujar();
	}

	if(_x==0){
		char grillaX[2];
		grillaX[1]='\0';
		grillaX[0]='A'+_y;
		settextjustify(1, 1);
		setcolor(4);
		outtextxy(_pos.izq-10,_pos.sup+(_pos.inf-_pos.sup)/2, grillaX);
	}
	if(_y==0){
		char grillaY[2];
		grillaY[1]='\0';
		grillaY[0]='1'+_x;
		settextjustify(1, 1);
		setcolor(4);
		outtextxy(_pos.izq+(_pos.der-_pos.izq)/2,_pos.sup-10, grillaY);
	}
}