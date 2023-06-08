#include "Mapa.h"
using namespace std;

Mapa::Mapa(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, list<Coordenada> paredes,
           list<Coordenada> fantasmas, list<Coordenada> chocolates)
{
    _largo = largo;
    _alto = alto;
    _inicio = inicio;
    _llegada = llegada;
    _paredes = paredes;
    _fantasmas = fantasmas;
    _chocolates = chocolates;

    //Crea una matriz de caracteres donde todos son V(de vacio)
    _tablero = vector<vector<char>>(largo, vector<char>(alto, 'V'));
    
    //Inserta las paredes en sus posiciones correspondientes
    for (Coordenada c : paredes)
    {
        (_tablero)[c.first - 1][c.second-1] = 'P';
    }
    
    //Inserta los fantasmas en sus posiciones correspondientes
    for (Coordenada c : fantasmas)
    {
        (_tablero)[c.first-1][c.second-1] = 'F';
    }
    
    //Inserta los chocolates en sus posiciones correspondientes
    for (Coordenada c : chocolates)
    {
        (_tablero)[c.first-1][c.second-1] = 'C';
    }
    
    if ((_tablero)[inicio.first - 1][inicio.second - 1] == 'C')
    {   
        //Si la casilla de inicio es un chocolate inserta la X para diferenciarla
        (_tablero)[inicio.first - 1][inicio.second - 1] = 'X';
    }
    else 
    {   
        //Sino la I
        (_tablero)[inicio.first - 1][inicio.second - 1] = 'I';
    }
    
    if ((_tablero)[llegada.first - 1][llegada.second - 1] == 'C')
    {   
        //Si la casilla de llegada es un chocolate inserta la Y para diferenciarla
        (_tablero)[llegada.first - 1][llegada.second - 1] = 'Y';
    }
    else 
    {
        //Sino la L
        (_tablero)[llegada.first - 1][llegada.second - 1] = 'L';
    }
    
}

Mapa::Mapa() {};

Mapa::~Mapa() {};

Nat Mapa::largo() const
{
    return _largo;
}

Nat Mapa::alto() const
{
    return this->_alto;
}

Coordenada Mapa::inicio() const
{
    return this->_inicio;
}

Coordenada Mapa::llegada() const
{
    return this->_llegada;
}

list<Coordenada> Mapa::paredes() const
{
    return this->_paredes;
}

list<Coordenada> Mapa::fantasmas() const
{
    return this->_fantasmas;
}

list<Coordenada> Mapa::chocolates() const
{
    return this->_chocolates;
}

list<Coordenada>* Mapa::chocolatesPunt()
{
    list<Coordenada>* res = &_chocolates;
    return res;
}

bool Mapa::hayFantasmaEnAlrededores(Coordenada pos) const
{
	bool res = false;
	for(int i=-3; i<=3; i++)
    {
        //Itera sobre todas las posibles posiciones que estan a 3 o menos de distancia Manhattan
		for(int j=-(3-abs(i)); j<=3-abs(i); j++)
        {
            //Verifica que si la coordenada esta en rango, si es o no un fantasma
            if(enRango(make_pair(pos.first+i, pos.second+j), _largo, _alto))
                res = res || ((_tablero)[pos.first+i-1][pos.second+j-1] == 'F');
        }
    }
    return res;
}

void Mapa::modificarMapa(Coordenada coor, char c)
{
    (_tablero)[coor.first-1][coor.second-1] = c; 
}

vector<vector<char>> Mapa::tablero() const
{
    return (_tablero);
}

Mapa& Mapa::operator=(const Mapa& m)
{
    _largo = m._largo;
    _alto = m._alto;
    _inicio = m._inicio;
    _llegada = m._llegada;
    _paredes = m._paredes;
    _fantasmas = m._fantasmas;
    _chocolates = m._chocolates;
    (_tablero) = (m._tablero);
    return *this;
}

bool Mapa::enRango(Coordenada pos, Nat largo, Nat alto) const
{
    return (pos.first > 0 && pos.first <= largo && pos.second > 0 && pos.second <= alto);
}






