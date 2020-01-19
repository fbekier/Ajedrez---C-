#include "juego.h"

void Juego::getMousePos(int &mx, int &my){
	mx=mousex();
	my=mousey();
}

Juego::Juego(){
	const int anchoW=getmaxheight();
	const int altoW=getmaxwidth();
	int barraDeHerramientasDeWindows=50;	
	int tama�o;
	if(anchoW<altoW){
		tama�o=anchoW-barraDeHerramientasDeWindows;
	}else{
		tama�o=altoW-barraDeHerramientasDeWindows;
	}
	int seccion=tama�o*1/80;
	posS mapaW={0, 0, tama�o, tama�o};
	posS mapaT={seccion*20, seccion*20, seccion*60, seccion*60};
	posS mapaM={seccion*65, seccion*20, seccion*75, seccion*60};
	posS mapaCI={seccion*20, seccion*65, seccion*60, seccion*75};
	posS mapaCS={seccion*20, seccion*5, seccion*60, seccion*15};

	_mapa=mapaW;
	_tablero=new Tablero(mapaT);
	_menu=new Menu(mapaM, _tablero);
	_cartelSup=new Cartel(mapaCS);
	_cartelInf=new Cartel(mapaCI);
	_marco=new Marco(mapaW, mapaCS.sup-10);
}

Juego::~Juego(){
	if(_tablero){
		delete _tablero;
		_tablero=NULL;
	}
	if(_menu){
		delete _menu;
		_menu=NULL;	
	}
	if(_cartelSup){
		delete _cartelSup;
		_cartelSup=NULL;
	}
	if(_cartelInf){
		delete _cartelInf;
		_cartelInf=NULL;
	}
	if(_marco){
		delete _marco;
		_marco=NULL;
	}
}

void Juego::run(){
	posS* mapaT=_tablero->getMapa();
	posS* mapaM=_menu->getMapa();
	
	initwindow(_mapa.der, _mapa.inf, "TP  FINAL");

	int x;
	int y;
	int xa=mapaT->izq+1;
	int ya=mapaT->sup+1;
	int EC;

	bool click=false;
	bool hayP;
	int hayMov;
	int xpa=-1;	//posicion x de la pieza anterior
	int ypa=-1;	//posicion y de la pieza anterior

	_marco->dibujar();
	_tablero->comenzar();
	_tablero->dibujar();
	_menu->dibujar();
	_cartelSup->dibujar(LIGHTBLUE, "Bienvenido a Ajedrez");
	_cartelInf->dibujar(LIGHTBLUE, "Elija una opcion");

	bool terminar=false;
	while(!terminar){	//Incio juego-----------------------------------------------------------------------

		getMousePos(x, y);
		if(!((x>mapaM->izq)&&(x<mapaM->der)&&(y>mapaM->sup)&&(y<mapaM->inf))&&!((x>mapaT->izq)&&(x<mapaT->der)&&(y>mapaT->sup)&&(y<mapaT->inf))){
			clearmouseclick(WM_LBUTTONDOWN);
		}

		if(!_tablero->hayJM()){
		if((x>mapaT->izq)&&(x<mapaT->der/*se puede corrige un resto acumulado*/)&&(y>mapaT->sup)&&(y<mapaT->inf)){	//interfaz tablero----------------------
			if(x!=xa||y!=ya){	//Seguimiento de mouse------------------------------
				EC=_tablero->getEstadoC(xa, ya);
				if(EC!=3&&EC!=1){
					_tablero->setEstadoC(xa, ya, 0);
					_tablero->refrescar(xa, ya);
				}
				EC=_tablero->getEstadoC(x, y);
				if(EC!=3&&EC!=1){
					_tablero->setEstadoC(x, y, 2);
					_tablero->refrescar(x, y);
				}
				xa=x;
				ya=y;
			}	//---------------------------------------------------
			if (ismouseclick(WM_LBUTTONDOWN)){	//Movimieto de piezas--------------------------------
				if(!click){
					hayP=_tablero->seleccionarP(x, y);
					if(hayP){
						_tablero->setEstadoC(x, y, 3);
						_tablero->refrescar(x, y);
						xpa=x;
						ypa=y;
						click=true;
						clearmouseclick(WM_LBUTTONDOWN);
					}
				}else{
					hayMov=_tablero->moverP(xpa, ypa, x, y);
					_tablero->setEstadoC(xpa, ypa, 0);
					_tablero->refrescar(xpa, ypa);
					_tablero->refrescar(x, y);
					click=false;
					clearmouseclick(WM_LBUTTONDOWN);

					if(_tablero->hayJaque()){
						_cartelInf->dibujar(YELLOW, "JAQUE!");
					}else{
						switch(hayMov){	//Cartel informacion-------------------------------
						case 0:
							_cartelInf->dibujar(RED, "Movimiento Invalido");
							break;
						case 1:
							_cartelInf->dibujar(GREEN, "Movimiento Correcto");
							break;
						case 2:
							_cartelInf->dibujar(YELLOW, "Esta en Jaque!");
							break;
						}
					}

					if(_tablero->getTurno()){		//Cartel te turno-----------------------------------
						_cartelSup->dibujar(WHITE, "Juegan Blancas");			
					}else{
						_cartelSup->dibujar(DARKGRAY, "Juegan Negras");	
					}
				}
				clearmouseclick(WM_LBUTTONDOWN);
			}	//---------------------------------------------------
		}
		}else{
			_cartelSup->dibujar(MAGENTA, "JAQUE MATE");
			delay(400);
		}	//Fin interfaz tablero------------------------------------------------------------------


		if((x>mapaM->izq)&&(x<mapaM->der)&&(y>mapaM->sup)&&(y<mapaM->inf)){	//Interfax menu-------------------------------
			if (ismouseclick(WM_LBUTTONDOWN)){
				terminar=_menu->setOpcion(x, y);
				if(xpa!=-1){
					_tablero->setEstadoC(xpa, ypa, 0);
					_tablero->refrescar(xpa, ypa);
				}				
				click=false;
				clearmouseclick(WM_LBUTTONDOWN);

				if(_tablero->getTurno()){	//Cartel te turno-----------------------------------
					_cartelSup->dibujar(WHITE, "Juegan Blancas");	
				}else{
					_cartelSup->dibujar(DARKGRAY, "Juegan Negras");	
				}	//Fin cartel turno-------------------------------------
				_cartelInf->dibujar(YELLOW, "Mueva un pieza");
			}
		}	//fin interfaz menu-------------------------------------------------------------------------------------


	}	//fin Juego-----------------------------------------
	closegraph();		
}

