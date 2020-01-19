#include "cartel.h"

Cartel::Cartel(posS mapa){
	_mapa=mapa;
}

void Cartel::dibujar(int color, char* mensaje){
	setcolor(color);
	rectangle(_mapa.izq, _mapa.sup, _mapa.der, _mapa.inf);
	settextjustify(0, 1);
	outtextxy(_mapa.izq+5, (_mapa.inf-_mapa.sup)/2+_mapa.sup, "                                                                            ");
	settextjustify(1, 1);
	outtextxy((_mapa.der-_mapa.izq)/2+_mapa.izq, (_mapa.inf-_mapa.sup)/2+_mapa.sup, mensaje);
}