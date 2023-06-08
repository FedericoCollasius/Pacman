#include "Partida.h"
#include "Tipos.h"
using namespace std;

int max(int a, int b){return a > b ? a : b;}
int min(int a, int b){return a < b ? a : b;}

Partida::Partida(Mapa &m) {
    _mapa = &m;
    _jugador = m.inicio();
    _chocolates = _mapa->chocolatesPunt();
    _cantMov = 0;
    _inmunidad = 0;
}

Partida::Partida() {};

Partida::~Partida(){}

Mapa Partida::mapa(){
    Mapa res = *_mapa;
    return res;
}

Coordenada Partida::jugador(){
    Coordenada res = this->_jugador;
    return res;
}

list<Coordenada> Partida::chocolates(){
    list<Coordenada> res = *(_chocolates);
    return res;
}

list<Coordenada> Partida:: chocolatesComidos(){
    list<Coordenada> res = _chocolatesComidos; 
    return res;
}

Nat Partida::cantMov(){
    Nat res = _cantMov;
    return res;
}

Nat Partida::inmunidad(){
    return _inmunidad;
}

void Partida::nuevaPartida(){
    _inmunidad = 0;
    _chocolatesComidos.clear();
    _jugador = (*_mapa).inicio();
    for(Coordenada c : *_chocolates) 
    {
        if (c == (*_mapa).inicio())
        {
            _inmunidad = 10;
            (*_mapa).modificarMapa(c, 'S');
            _chocolatesComidos.push_back(c);
        }
        else if (c == (*_mapa).llegada())
        {
            (*_mapa).modificarMapa(c, 'Y');
        }
        else
        {
           (*_mapa).modificarMapa(c, 'C');
        }
    }
    _cantMov = 0;
}

void Partida::mover(Direccion d){
    if (!(siguienteMovimiento(d) == _jugador))
    {
        Nat sigx = siguienteMovimiento(d).first;
        Nat sigy = siguienteMovimiento(d).second;
        char p = (*_mapa).tablero()[sigx-1][sigy-1];
        if (_inmunidad != 0) {
            _inmunidad--;
        }
        if ( p == 'C') 
        {
            (*_mapa).modificarMapa(this->siguienteMovimiento(d), 'V');
            _inmunidad = 10;
            _chocolatesComidos.push_back(siguienteMovimiento(d));
        }else{
            if ( p == 'Y')
            {
                (*_mapa).modificarMapa(this->siguienteMovimiento(d), 'L');
                _inmunidad = 10;
                _chocolatesComidos.push_back(siguienteMovimiento(d));
            }
        }
        _cantMov++;
        _jugador = siguienteMovimiento(d);
    }
}

bool Partida::gano(){
    bool res = (*_mapa).llegada() == _jugador;
    return res;
}

bool Partida::perdio(){
    bool valor1 = !gano();
    bool valor2 = (mapa().hayFantasmaEnAlrededores(_jugador));
    bool valor3 =_inmunidad == 0;
    return valor1 && valor2 && valor3;
}

Coordenada Partida::siguienteMovimiento(Direccion d){
    bool valor1 = restringirMovimiento(posMovimiento(jugador(), d)) != jugador();
    Nat uno = posMovimiento(jugador(), d).first;
    Nat dos = posMovimiento(jugador(), d).second;
    bool valor2 = valor1 && mapa().tablero()[uno-1][dos-1] != 'P';
    if( valor1 && valor2)
    {
        return posMovimiento(jugador(), d);
    } 
    else 
    {
        return jugador();
    }
}

Coordenada Partida::posMovimiento(Coordenada c, Direccion d){
    Coordenada res = c;
    res.first += d == DERECHA;
    res.first -= d == IZQUIERDA;
    res.second -= d == ABAJO;
    res.second += d == ARRIBA;
    return res;
}

Coordenada Partida::restringirMovimiento(Coordenada c){
    Coordenada res;
    res.first  = max( 1, min( mapa().largo(), c.first ) );
    res.second = max( 1, min( mapa().alto(), c.second ) );
    return res;
}