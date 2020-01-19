#include "tablero.h"

void Tablero::mapear(int &x, int &y){
	int px=x;
	int py=y;
	x=(px-_mapa.izq)/((_mapa.der-_mapa.izq)/CANT_X);
	y=(py-_mapa.sup)/((_mapa.inf-_mapa.sup)/CANT_Y);
}

bool Tablero::verificarMov(int xo, int yo, int xd, int yd){
	posP* posC;
	Pieza* piezaO;
	Pieza* piezaD;
	int tipoM;
	bool ok;

	piezaO=_tablero[xo][yo]->getPieza();
	piezaD=_tablero[xd][yd]->getPieza();
	tipoM=piezaO->movValido(xd, yd);

	switch(tipoM){
	case 0:
		return false;
		break;
	case 1:
		ok=true;
		posC=piezaO->getMovIntermedios(xd, yd);
		while(posC->x!=-1&&ok){
			ok=!_tablero[posC->x][posC->y]->hayPieza();
			posC++;
		}
		if(ok){
			if(piezaD){
				if(piezaO->getColor()==piezaD->getColor()){
					ok=false;
				}
			}
		}
		return ok;
		break;
	case 2:
		if(_tablero[xd][yd]->hayPieza()){
			return false;		
		}else{
			return true;
		}
		return true;
		break;
	case 3:
		ok=true;
		posC=piezaO->getMovIntermedios(xd, yd);
		while(posC->x!=-1&&ok){
			ok=!_tablero[posC->x][posC->y]->hayPieza();
			posC++;
		}
		if(ok && !_tablero[xd][yd]->hayPieza()){
			return true;	
		}else{
			return false;

		}
		break;
	case 4:
		if(_tablero[xd][yd]->hayPieza()){
			piezaD=_tablero[xd][yd]->getPieza();
			if(_turno!=piezaD->getColor()){
				return true;
			}
		}else{return false;}
		break;
	case 5:
		if(!hayJaque(xd, yd, piezaO->getColor())){
			if(piezaD){
				if(piezaO->getColor()!=piezaD->getColor()){
					return true;
				}else{return false;}
			}else{return true;}
		}else{return false;}
		break;
	case 6:
		return false;
		break;	
	case 7:
		
		if (!_tablero[xd][yd]->hayPieza()){
			return true;
		}else if (_tablero[xd][yd]->hayPieza() && piezaD->getColor() != piezaO->getColor()){
			return true;
		}else 
			return false;
		break;
	}
}

Pieza* Tablero::buscarRey(bool color){
	bool encontro=false;
	int i=0;
	while(!encontro, i<CANT_P){
		if(_piezas[i]&&_piezas[i]->tipoPieza()=='R'&&_piezas[i]->getColor()==color){
			return _piezas[i];
			encontro=true;
		}
		i++;
	}
}

bool Tablero::hayJaque(){
	Pieza* rey;
	rey=buscarRey(_turno);
	return hayJaque(rey->getPosX(), rey->getPosY(), _turno);
}

bool Tablero::hayJaque(int xd, int yd, bool color){
	bool semaforo=false;
	bool hay=false;
	Pieza* pieza;
	Pieza* rey;
	int xr,yr=-1;
	rey=buscarRey(color);
	xr=rey->getPosX();
	yr=rey->getPosY();
	_tablero[xr][yr]->sacarPieza();
	for(int y=0; y<CANT_Y; y++){
		for(int x=0; x<CANT_X; x++){
			if(_tablero[x][y]){
				pieza=_tablero[x][y]->getPieza();
				if(pieza){
					if(pieza->getColor()!=color){
						if(pieza->tipoPieza()=='P'){
							if(color){
								hay=((yd==pieza->getPosY()+1)&&((xd==pieza->getPosX()+1)||(xd==pieza->getPosX()-1)));
							}else{
								hay=((yd==pieza->getPosY()-1)&&((xd==pieza->getPosX()+1)||(xd==pieza->getPosX()-1)));
							}
						}else{
							hay=verificarMov(pieza->getPosX(), pieza->getPosY(), xd, yd);
						}
						if(hay&&!semaforo){
							semaforo=true;
						}
					}
				}
			}
		}
	}
	_tablero[xr][yr]->setPieza(rey);
	return semaforo;
}

bool Tablero::hayJM(){
	Pieza* rey;
	Pieza* pieza;
	posP* movInt;

	int xr;
	int yr;
	bool hayJ;
	bool hayJM = false;

	rey=buscarRey(_turno);
	xr=rey->getPosX();
	yr=rey->getPosY();
	if (hayJaque(xr, yr, _turno)){
		hayJM = false;
		for (int i=0; i<CANT_P; i++){
			if ((_piezas[i])&&(_piezas[i]->getColor()!=_turno)&&(_piezas[i]->getPosY()!=-1)&&(verificarMov(_piezas[i]->getPosX(),_piezas[i]->getPosY(), xr, yr))){
				hayJ = true;
				//---------------------
				for(int o=0; o<CANT_P; o++){
					if ((_piezas[o])&&(_piezas[o]->getColor()==_turno)&&(_piezas[o]->getPosY()!=-1)&&(verificarMov(_piezas[o]->getPosX(),_piezas[o]->getPosY(), _piezas[i]->getPosX(), _piezas[i]->getPosY()))){
						hayJ=false;
						break;
					}
				}
					//---------------------
				movInt = _piezas[i]->getMovIntermedios(xr, yr);

				while ((movInt->x!=-1)&& hayJ){
					for (int u=0; u<CANT_P; u++){
						if ((_piezas[u])&&(_piezas[u]->getColor()==_turno)&&(_piezas[u]->tipoPieza()!='R')&&(_piezas[u]->getPosY()!=-1)
							&&(verificarMov(_piezas[u]->getPosX(),_piezas[u]->getPosY(), movInt->x, movInt->y))){
								hayJ=false;
								break;
						}
					}
					movInt ++;
				}
				if(hayJ){
					hayJM=true;
				}
			}
		}

		if(hayJM){

			if(!(xr-1<0)&&!(yr-1<0)){
				if(_tablero[xr-1][yr-1]->hayPieza()){	//izq-sup
					pieza=_tablero[xr-1][yr-1]->getPieza();
					if(pieza->getColor()!=rey->getColor()){
						hayJM=false;
					}
				}else{
					if(!hayJaque(xr-1, yr-1, _turno)){
						hayJM=false;
					}
				}
			}

			if(!(yr-1<0)){
				if(_tablero[xr][yr-1]->hayPieza()){	//cent-sup
					pieza=_tablero[xr][yr-1]->getPieza();
					if(pieza->getColor()!=rey->getColor()){
						hayJM=false;
					}
				}else{
					if(!hayJaque(xr, yr-1, _turno)){
						hayJM=false;
					}
				}
			}

			if(!(xr+1>7)&&!(yr-1<0)){
				if(_tablero[xr+1][yr-1]->hayPieza()){	//der-sup
					pieza=_tablero[xr+1][yr-1]->getPieza();
					if(pieza->getColor()!=rey->getColor()){
						hayJM=false;
					}
				}else{
					if(!hayJaque(xr+1, yr-1, _turno)){
						hayJM=false;
					}
				}
			}

			if(!(xr-1<0)){
				if(_tablero[xr-1][yr]->hayPieza()){	//cent-izq
					pieza=_tablero[xr-1][yr]->getPieza();
					if(pieza->getColor()!=rey->getColor()){
						hayJM=false;
					}
				}else{
					if(!hayJaque(xr-1, yr, _turno)){
						hayJM=false;
					}
				}
			}

			if(!(xr+1>7)){
				if(_tablero[xr+1][yr]->hayPieza()){	//cent-der
					pieza=_tablero[xr+1][yr]->getPieza();
					if(pieza->getColor()!=rey->getColor()){
						hayJM=false;
					}
				}else{
					if(!hayJaque(xr+1, yr, _turno)){
						hayJM=false;
					}
				}
			}

			if(!(xr-1<0)&&!(yr+1>7)){
				if(_tablero[xr-1][yr+1]->hayPieza()){	//izq-inf
					pieza=_tablero[xr-1][yr+1]->getPieza();
					if(pieza->getColor()!=rey->getColor()){
						hayJM=false;
					}
				}else{
					if(!hayJaque(xr-1, yr+1, _turno)){
						hayJM=false;
					}
				}
			}

			if(!(yr+1>7)){
				if(_tablero[xr][yr+1]->hayPieza()){	//cent-inf
					pieza=_tablero[xr][yr+1]->getPieza();
					if(pieza->getColor()!=rey->getColor()){
						hayJM=false;
					}
				}else{
					if(!hayJaque(xr, yr+1, _turno)){
						hayJM=false;
					}
				}
			}

			if(!(xr+1>7)&&!(yr-1<0)){
				if(_tablero[xr+1][yr-1]->hayPieza()){	//der-inf
					pieza=_tablero[xr+1][yr-1]->getPieza();
					if(pieza->getColor()!=rey->getColor()){
						hayJM=false;
					}
				}else{
					if(!hayJaque(xr+1, yr-1, _turno)){
						hayJM=false;
					}
				}
			}


		}
	}
	return hayJM;
}

Tablero::Tablero(posS mapa){
	_mapa=mapa;
	bool color=true;
	for(int y=0; y<CANT_Y; y++){
		for(int x=0; x<CANT_X; x++){
			_tablero[x][y]=NULL;
			_tablero[x][y]=new Celda(color, x, y, &_mapa);
			color=!color;
		}
		color=!color;
	}

	for(int i=0; i<CANT_P; i++){
		_piezas[i]=NULL;
	}
}

Tablero::~Tablero(){
	for(int y=0; y<CANT_Y; y++){
		for(int x=0; x<CANT_X; x++){
			if(_tablero[x][y]){
				delete _tablero[x][y];
				_tablero[x][y]=NULL;
			}
		}
	}
	for(int i=0; i<CANT_P; i++){
		if(_piezas[i]){
			delete _piezas[i];
			_piezas[i]=NULL;
		}
	}
}

posS* Tablero::getMapa(){
	return &_mapa;
}

void Tablero::comenzar(){
	_turno=true;
	for(int y=0; y<CANT_Y; y++){
		for(int x=0; x<CANT_X; x++){
			_tablero[x][y]->sacarPieza();
		}
	}

	for(int i=0; i<CANT_P; i++){
		if(_piezas[i]){
			delete _piezas[i];
			_piezas[i]=NULL;
		}
	}

	int i=0;
	bool color=false;
	_piezas[i]=new Torre(-1, -1, color);
	i++;
	//_piezas[i]=new Caballo(-1, -1, color);
	i++;
	_piezas[i]=new Alfil(-1, -1, color);
	i++;
	_piezas[i]=new Reina(-1, -1, color);
	i++;
	_piezas[i]=new Rey(-1, -1, color);
	i++;
	_piezas[i]=new Alfil(-1, -1, color);
	i++;
	//_piezas[i]=new Caballo(-1, -1, color);
	i++;
	_piezas[i]=new Torre(-1, -1, color);
	i++;
	for(i; i<=15; i++){
		_piezas[i]=new Peon(-1, -1, color);
	}
	color=true;
	for(i; i<=23; i++){
		_piezas[i]=new Peon(-1, -1, color);
	}
	_piezas[i]=new Torre(-1, -1, color);
	i++;
	//_piezas[i]=new Caballo(-1, -1, color);
	i++;
	_piezas[i]=new Alfil(-1, -1, color);
	i++;
	_piezas[i]=new Reina(-1, -1, color);
	i++;
	_piezas[i]=new Rey(-1, -1, color);
	i++;
	_piezas[i]=new Alfil(-1, -1, color);
	i++;
	//_piezas[i]=new Caballo(-1, -1, color);
	i++;
	_piezas[i]=new Torre(-1, -1, color);

	i=0;
	for(int y=0; y<2; y++){
		for(int x=0; x<CANT_X; x++){
			if(_piezas[i]){
				_tablero[x][y]->setPieza(_piezas[i]);
			}
			i++;
		}
	}
	for(int y=6; y<8; y++){
		for(int x=0; x<CANT_X; x++){
			if(_piezas[i]){
				_tablero[x][y]->setPieza(_piezas[i]);
			}
			i++;
		}
	}
}

void Tablero::continuar(){
	for(int y=0; y<CANT_Y; y++){
		for(int x=0; x<CANT_X; x++){
			_tablero[x][y]->sacarPieza();
		}
	}
	for(int i=0; i<CANT_P; i++){
		if(_piezas[i]){
			delete _piezas[i];
			_piezas[i]=NULL;
		}
	}
	
	RegSave reg;
	FILE* pSave=NULL;
	pSave=fopen("save.txt", "rb");
	if(pSave!=NULL){
		if(!feof(pSave)){
			fread(&reg, sizeof(RegSave), 1, pSave);
			_turno=reg.color;
		}
		int i=0;
		while(!feof(pSave)){
			fread(&reg, sizeof(RegSave), 1, pSave);
			switch(reg.tipo){
			case 'A':
				_piezas[i]=new Alfil(reg.x, reg.y, reg.color);
				break;
			case 'C':
				//_piezas[i]=new Caballo(reg.x, reg.y, reg.color);
				break;

			case 'P':
				_piezas[i]=new Peon(reg.x, reg.y, reg.color);
				break;
			case 'r':
				_piezas[i]=new Reina(reg.x, reg.y, reg.color);
				break;
			case 'R':
				_piezas[i]=new Rey(reg.x, reg.y, reg.color);
				break;
			case 'T':
				_piezas[i]=new Torre(reg.x, reg.y, reg.color);
				break;
			}
			if(_piezas[i]){
				if(_piezas[i]->getPosX()!=-1){
					_tablero[reg.x][reg.y]->setPieza(_piezas[i]);
				}				
			}
			i++;
		}
	}
	fclose(pSave);
}

void Tablero::grabar(){
	RegSave reg;
	FILE* pSave=NULL;
	pSave=fopen("save.txt", "wb");
	if(pSave!=NULL){
		reg.x=-1;
		reg.y=-1;
		reg.color=_turno;
		reg.tipo='x';
		fwrite(&reg, sizeof(RegSave), 1, pSave);
		for(int i=0; i<CANT_P; i++){
			if(_piezas[i]){
				reg.x=_piezas[i]->getPosX();
				reg.y=_piezas[i]->getPosY();
				reg.color=_piezas[i]->getColor();
				reg.tipo=_piezas[i]->tipoPieza();
				fwrite(&reg, sizeof(RegSave), 1, pSave);
			}
		}
		fclose(pSave);
	}
}

void Tablero::setEstadoC(int x, int y, int estado){
	mapear(x, y);
	_tablero[x][y]->setEstado(estado);
}

int Tablero::getEstadoC(int x, int y){
	mapear(x, y);
	return _tablero[x][y]->getEstado();
}

bool Tablero::seleccionarP(int x, int y){
	mapear(x, y);
	Pieza* pieza;
	Pieza* rey;
	pieza=_tablero[x][y]->getPieza();
	if(pieza){
		rey=buscarRey(_turno);
		if(pieza->getColor()==_turno/*&&!hayJaque(rey->getPosX(), rey->getPosY(), _turno)*/){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}

int Tablero::moverP(int xo, int yo, int xd, int yd){
	mapear(xo, yo);
	mapear(xd, yd);

	Pieza* piezaO;
	Pieza* piezaD;
	Pieza* rey;
	rey=buscarRey(_turno);
	if(verificarMov(xo, yo, xd, yd)){
		piezaO=_tablero[xo][yo]->getPieza();
		piezaD=_tablero[xd][yd]->getPieza();
		_tablero[xd][yd]->sacarPieza();
		_tablero[xo][yo]->sacarPieza();
		_tablero[xd][yd]->setPieza(piezaO);
		if(!hayJaque(rey->getPosX(), rey->getPosY(), rey->getColor())){
			_tablero[xd][yd]->recibirPieza(piezaO);
			_turno=!_turno;
			return 1;
		}else{
			_tablero[xd][yd]->sacarPieza();
			_tablero[xo][yo]->setPieza(piezaO);
			_tablero[xd][yd]->setPieza(piezaD);
			return 2;
		}
	}else{
		return 0;
	}
}

void Tablero::refrescar(int x, int y){
	mapear(x, y);
	_tablero[x][y]->dibujar();
}

void Tablero::dibujar(){
	for(int y=0; y<CANT_Y; y++){
		for(int x=0; x<CANT_X; x++){
			if(_tablero[x][y]){
				_tablero[x][y]->dibujar();
			}
		}
	}
	setcolor(3);
	rectangle(_mapa.izq-1, _mapa.sup-1, _mapa.der+1, _mapa.inf+1);
}