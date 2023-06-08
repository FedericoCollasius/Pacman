#if !defined(Partida_H)
#define Partida_H
#include "Tipos.h"
#include "Mapa.h"

class Partida
{
public:
    Partida(Mapa &m);

    ~Partida();

    Partida();

    //Devuelve el mapa
    Mapa mapa();

    //Devuelve las coordenadas del jugador
    Coordenada jugador();

    //Devuelve la lista de Chocolates
    list<Coordenada> chocolates();

    //Devuelve la lista de coordenandas de los chocolates comidos
    list<Coordenada> chocolatesComidos();

    //Devuelve la cantidad de movimientos efectuados en la partida hasta el momento
    Nat cantMov();

    //Devuelve los turnos de inmunidad restantes que tiene el jugador
    Nat inmunidad();

    //Setea una nueva partida
    void nuevaPartida();

    //Efectua un moviemient
    void mover(Direccion d);

    //Devuelve si el jugador gano la partida
    bool gano();

    //Devuelve si el jugador perdio la partida
    bool perdio();

private:

    //Devuelve la coordenanda del siguiente movimiento del jugador
    Coordenada siguienteMovimiento(Direccion d);

    //Devuelve la coordenanda del siguiente movimiento del jugador sin tomar en cuenta
    //las cosas que evitan que se mueva
    Coordenada posMovimiento(Coordenada c, Direccion d);

    //Evita que el jugador se vaya del mapa
    Coordenada restringirMovimiento(Coordenada c);

    Mapa *_mapa;
    Coordenada _jugador;
    list<Coordenada> *_chocolates;
    Nat _cantMov;
    Nat _inmunidad;
    list<Coordenada> _chocolatesComidos;
};

#endif