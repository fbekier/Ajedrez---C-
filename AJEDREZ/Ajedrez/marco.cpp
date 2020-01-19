#include "marco.h"

Marco::Marco(posS mapa, int ancho){
	_mapa=mapa;
	_ancho=ancho;
}

void Marco::dibujar(){
	int margen=5;
	for(int i=1; _mapa.sup+margen*i<_ancho; i++){
		setcolor(i);
		rectangle(_mapa.izq+margen*i, _mapa.sup+margen*i, _mapa.der-margen*i, _mapa.inf-margen*i);
	}
	setcolor(CYAN);
	settextjustify(1, 1);
	outtextxy((_mapa.der-_mapa.izq)/2+_mapa.izq, _mapa.sup+_ancho/2, "AJEDREZ");
	setcolor(MAGENTA);
	outtextxy((_mapa.der-_mapa.izq)/2+_mapa.izq, _mapa.inf-_ancho/2, "IN TECHNICOLOR(R)");
}