
#include <iostream>
#include "juego.h"

void main(){
	
	Juego *juego;
	juego= new Juego;
	if (juego)
		juego->run();
	if (juego)
		delete juego;

}