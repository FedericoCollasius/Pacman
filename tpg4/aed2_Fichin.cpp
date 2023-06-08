#include "aed2_Fichin.h"


aed2_Fichin::aed2_Fichin(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, set<Coordenada> paredes,
                         set<Coordenada> fantasmas, set<Coordenada> chocolates)
{   
    list<Coordenada> paredesLista;
    list<Coordenada> fantasmasLista;
    list<Coordenada> chocolatesLista;
    for(Coordenada c : paredes) 
    {
        paredesLista.push_back(c);
    }
    for(Coordenada c : fantasmas) 
    {
        fantasmasLista.push_back(c);
    }
    for(Coordenada c : chocolates) 
    {
        chocolatesLista.push_back(c);
    }
    //_flechazo = 
    _fichin = new Fichin(largo, alto, inicio, llegada, paredesLista, fantasmasLista, chocolatesLista);
}
///Default constructor?

aed2_Fichin::~aed2_Fichin() {
    delete _fichin;
}

void aed2_Fichin::nuevaPartida(Jugador j)
{
    (*_fichin).nuevaPartida(j);
}

// IMPORTANTE: Debe devolver:
// - GANO si al mover se gana la partida
// - PERDIO si al mover se pierde la partida
// - SIGUE en cualquier otro caso
ResultadoMovimiento aed2_Fichin::mover(Direccion d)
{
    return (*_fichin).mover(d);
}

bool aed2_Fichin::alguienJugando() const
{
    return (*_fichin).alguienJugando();
}

Jugador aed2_Fichin::jugadorActual() const
{
    return (*_fichin).jugadorActual();
}

map<Jugador, Puntaje> aed2_Fichin::ranking() const
{
    return (*_fichin).rankingMap();
}

pair<Jugador, Puntaje> aed2_Fichin::objetivo() const
{
    return (*_fichin).objetivo();
}


Coordenada aed2_Fichin::jugador() const
{
    return (*_fichin).jugador();
}

Nat aed2_Fichin::cantidadMovimientos() const
{
    return (*_fichin).cantMov();
}

Nat aed2_Fichin::inmunidad() const
{
    return (*_fichin).inmunidad();
}

Nat aed2_Fichin::largo() const
{
    //Partida p = _fichin.partidaActual();
    //Mapa m = (p).mapa();
    //Nat res = (m).largo();
    
    return (*_fichin).largo();
}

Nat aed2_Fichin::alto() const
{
    return (*_fichin).alto();
}

Coordenada aed2_Fichin::inicio() const
{
    return (*_fichin).salida();
}

Coordenada aed2_Fichin::llegada() const
{
    return (*_fichin).llegada();
}

set<Coordenada> aed2_Fichin::paredes() const
{
    set<Coordenada> res;
    for (Coordenada e : (*_fichin).paredes())
    {
        res.insert(e);
    }
    return res;
}

set<Coordenada> aed2_Fichin::fantasmas() const
{
    set<Coordenada> res;
    for (Coordenada e : ((*_fichin).fantasmas()))
    {
        res.insert(e);
    }
    return res;
}

set<Coordenada> aed2_Fichin::chocolatesIniciales() const
{
    set<Coordenada> res;
    for (Coordenada e : ((*_fichin).chocolatesIniciales()))
    {
        res.insert(e);
    }
    return res;
}

set<Coordenada> aed2_Fichin::chocolatesActuales() const
{
    set<Coordenada> res = chocolatesIniciales();
    for(Coordenada e : ((*_fichin).partidaActual()).chocolatesComidos())
    {
        res.erase(e);
    }
    return res;
}
