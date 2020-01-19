
#ifndef JUEGO_H
#define JUEGO_H
#include <iostream>
#include "celda.h"
#include "tablero.h"
#include "menu.h"
#include "cartel.h"
#include "marco.h"

using namespace std;

class Juego{
private:
	posS _mapa;
	Tablero* _tablero;
	Menu* _menu;
	Cartel*  _cartelSup;
	Cartel* _cartelInf;
	Marco* _marco;
	void getMousePos(int &mx, int &my);
	void marco(posS mapaM, int ancho, char* mensaje);
public:
	Juego(); 
	~Juego();
	void run ();
};

#endif 