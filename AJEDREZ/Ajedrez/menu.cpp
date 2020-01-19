#include "menu.h"	

#define CANT_OP 4

Menu::Menu(posS mapa, Tablero* tablero){
	_mapa=mapa;
	_mapaD.izq=mapa.izq;
	_mapaD.sup=mapa.sup;
	_mapaD.ancho=mapa.der-mapa.izq;
	_mapaD.alto=mapa.inf-mapa.sup;
	_tablero=tablero;
}

bool Menu::setOpcion(int x, int y){
	if(x>=_mapaD.izq&&x<=_mapaD.izq+_mapaD.ancho){
		int opcion=((y-_mapaD.sup)/(_mapaD.alto/CANT_OP))+1;
		switch (opcion){
		case 1:
			_tablero->comenzar();
			_tablero->dibujar();
			return false;
			break;
		case 2:
			_tablero->continuar();
			_tablero->dibujar();
			return false;
			break;
		case 3:
			_tablero->grabar();
			return false;
			break;
		case 4:
			return true;
			break;
		}
	}
}

void Menu::dibujar(){
	int margen=5;
	int izq;
	int sup;
	int der;
	int inf;

	izq=_mapaD.izq;
	sup=_mapaD.sup+margen;
	der=_mapaD.izq+_mapaD.ancho;
	inf=_mapaD.sup+_mapaD.alto/CANT_OP;
	setcolor(3);
	rectangle(izq , sup+margen, der, inf-margen);
	settextjustify(1, 1);
	outtextxy(izq+_mapaD.ancho/2, sup+margen+(inf-sup)/2, "NUEVO");

	sup=inf;
	inf=_mapaD.sup+(2*_mapaD.alto)/CANT_OP;
	setcolor(4);
	rectangle(izq , sup+margen, der, inf-margen);
	settextjustify(1, 1);
	outtextxy(izq+_mapaD.ancho/2, sup+margen+(inf-sup)/2, "CONTINUAR");

	sup=inf;
	inf=_mapaD.sup+(3*_mapaD.alto)/CANT_OP;
	setcolor(5);
	rectangle(izq , sup+margen, der, inf-margen);
	settextjustify(1, 1);
	outtextxy(izq+_mapaD.ancho/2, sup+margen+(inf-sup)/2, "GRABAR");

	sup=inf;
	inf=_mapaD.sup+(4*_mapaD.alto)/CANT_OP;
	setcolor(6);
	rectangle(izq , sup+margen, der, inf-margen);
	settextjustify(1, 1);
	outtextxy(izq+_mapaD.ancho/2, sup+margen+(inf-sup)/2, "SALIR");
}