#include "Fichin.h"

Fichin::Fichin(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, list<Coordenada> paredes,
               list<Coordenada> fantasmas, list<Coordenada> chocolates)
{
    _mapa = new Mapa(largo, alto, inicio, llegada, paredes, fantasmas, chocolates);
    _partidaActual = new Partida(*_mapa); 
    _alguienJugando = false;
    _ranking = string_map<Nat>();      
    _jugadorActual = "";
}

Fichin::Fichin() {
    _ranking = string_map<Nat>();
};


Fichin::~Fichin() {
    delete _partidaActual;
    delete (_mapa);
}

Mapa &Fichin::mapa()
{
    return *(this->_mapa);
}


bool Fichin::alguienJugando() const
{
    return this->_alguienJugando;
}

Jugador Fichin::jugadorActual() const
{
    return this->_jugadorActual;
}

Partida Fichin::partidaActual() const
{
    return *_partidaActual;
}

Ranking Fichin::ranking() const
{
    return this->_ranking;
}

void Fichin::nuevaPartida(Jugador j)
{
    _partidaActual->nuevaPartida();
    _alguienJugando = true;
    _jugadorActual = j;
}


ResultadoMovimiento Fichin::mover(Direccion d)
{   
    (*_partidaActual).mover(d); //Modifica la posicion actual del jugador

    //Segun el estado de la partida lo devuelve
    if ((*_partidaActual).gano())
    {
        _alguienJugando = false; //Pasa a no haber nadie jugando
        //Segun el puntaje y si el jugador estaba o no en el ranking lo agrega o cambia el puntaje
        if ((_ranking.count(jugadorActual()) != 0 && _ranking.at(jugadorActual()) > (_partidaActual->cantMov())) || _ranking.count(jugadorActual()) == 0) 
        {
            int a = _partidaActual->cantMov();
            _ranking.insert(make_pair((jugadorActual()), a));
        }
        return GANO;
    }
    else
    {
        if ((*_partidaActual).perdio())
        {
            _alguienJugando = false; //Pasa a no haber nadie jugando
            return PERDIO;
        }
        else
        {
            return SIGUE;
        }
    }
}

pair<Jugador, Nat> Fichin::objetivo() const
{
    return make_pair(this->oponente(), this->ranking().at(this->oponente()));
}

Jugador Fichin::oponente() const
{
    if (oponentes().size() == 0)
        return _jugadorActual;
    else
        return oponentes().front();
}

list<Jugador> Fichin::mejoresQue(Ranking r, vector<Jugador> cj, Nat p) const
{
    list<Jugador> res;
    for (Jugador j : cj)
    {
        if (this->ranking().at(j) < p)
        {
            res.push_back(j);
        }
    }
    return res;
}

list<Jugador> Fichin::oponentes() const
{
    int p = _ranking.at(_jugadorActual);
    if (this->mejoresQue(_ranking, _ranking.claves(), p).size() == 0)
    {
        list<Jugador> res;
        return res;
    }
    else
    {
        return this->peoresJugadores(_ranking, mejoresQue(_ranking, _ranking.claves(), p));
    }
}


list<Jugador> Fichin::peoresJugadores(Ranking r, list<Jugador> cj) const
{
    return this->jugadoresConPuntaje(r, cj, this->peorPuntaje(r, cj));
}

list<Coordenada> Fichin::paredes() const
{
    return _mapa->paredes();
}
list<Coordenada> Fichin::fantasmas() const
{
    return _mapa->fantasmas();
}
list<Coordenada> Fichin::chocolatesIniciales() const
{
    return _mapa->chocolates();
}

list<Jugador> Fichin::jugadoresConPuntaje(Ranking r, list<Jugador> cj, Nat p) const
{
    list<Jugador> res;
    for (Jugador j : cj)
    {
        if (this->ranking().at(j) == p)
        {
            res.push_back(j);
        }
    }
    return res;
}

Nat Fichin::peorPuntaje(Ranking r, list<Jugador> cj) const
{
    Jugador peor = cj.front();
    for (Jugador j : cj)
    {
        if (this->ranking().at(j) > this->ranking().at(peor))
        {
            peor = j;
        }
    }
    return _ranking.at(peor);
}

Nat Fichin::alto() const {
    return _mapa->alto();
}

Nat Fichin::largo() const {
    return _mapa->largo();
}

Coordenada Fichin::salida() const {
    return _mapa->inicio();
}

Coordenada Fichin::llegada() const {
    return _mapa->llegada();
}

map<Jugador,Puntaje> Fichin::rankingMap() const {
    vector<string> claves = _ranking.claves();
    map<Jugador, Puntaje> res;
    for (int i = 0; i < claves.size(); i++) {
        res[claves[i]] = _ranking.at(claves[i]);
    }
    return res;
}

Coordenada Fichin::jugador() const {
    return _partidaActual->jugador();
}

Nat Fichin::cantMov() const {
    return _partidaActual->cantMov();
}

Nat Fichin::inmunidad() const {
    return _partidaActual->inmunidad();
}

set<Coordenada> Fichin::chocolatesActuales() const {
    list<Coordenada> lista = chocolatesIniciales();
    set<Coordenada> res;
    for (Coordenada e : lista) {
        res.insert(e);
    }

    for (Coordenada e : (_partidaActual->chocolatesComidos()))
    {
        res.erase(e);
    }
    return res;
}