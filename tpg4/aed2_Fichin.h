#ifndef AED2_FICHIN_H
#define AED2_FICHIN_H

#include "Tipos.h"
#include "Mapa.h"
#include "Fichin.h"
#include "Partida.h"

class aed2_Fichin {
public:
    // Constructor de aed2_fichin
    aed2_Fichin(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, set<Coordenada> paredes,
                set<Coordenada> fantasmas, set<Coordenada> chocolates);

    // Inicia una nueva partida con el jugador J. Resetea los chocolates y pone al pacman en la posicion de inicio.
    // PRE: no hay alguien jugando
    void nuevaPartida(Jugador j);

    // Destructor de aed2_fichin
    ~aed2_Fichin();

    // Mueve al pacman en el tablero segun la direccion indicada y me devuelve el estado de la partida despues de haberse movido. Los posibles estados son: sigue, perdio o gano.
    // Devuelve:
    // - GANO si al mover se gana la partida
    // - PERDIO si al mover se pierde la partida
    // - SIGUE en cualquier otro caso
    // PRE: hay alguien jugando
    ResultadoMovimiento mover(Direccion d);

    // Devuelve si hay un jugador actualmente jugando.
    bool alguienJugando() const;

    // Devuelve al jugador actual.
    //PRE: no hay alguien jugando
    Jugador jugadorActual() const;

    // Devuelve el ranking de puntajes de todos los jugadores que hayan pasado por el sistema. (Ranking se representa con diccTrie/string map)
    map<Jugador, Puntaje> ranking() const;

    // Devuelve una tupla que contiene al jugador con puntaje mas proximo al actual junto con su puntaje.
    // PRE: hay alguien jugando y el jugador actual ya esta en el ranking.
    pair<Jugador, Puntaje> objetivo() const;

    // Devuelve la coordenada donde está parado el jugador actual en la partida. 
    Coordenada jugador() const;

    // Devuelve la cantidad de movimientos que hizo el pacman hasta el momento.
    Nat cantidadMovimientos() const;

    // Devuelve la cantidad restante de movimientos inmunizados que tiene el pacman actualmente.
    Nat inmunidad() const;

    // Devuelve el largo del mapa de la partida actual. 
    Nat largo() const;

    // Devuelve el alto del mapa de la partida actual. 
    Nat alto() const;

    // Devuelve la coordenada donde el jugar empieza en el mapa. 
    Coordenada inicio() const;

    // Devuelve la coordenada dónde el jugar tiene que llegar para ganar.
    Coordenada llegada() const;

    // Devuelve el conjunto de coordenadas dónde están ubicadas las paredes. (Conjunto se representa con lista enlzada)
    set<Coordenada> paredes() const;

    // Devuelve el conjunto de coordenadas que contienen fantasmas. (Conjunto se representa con lista enlazada)
    set<Coordenada> fantasmas() const;

    // Devuelve el conjunto de coordenadas que contienen los chocolates que hay antes de arrancar una partida.
    set<Coordenada> chocolatesIniciales() const;

    // Devuelve el conjunto de chocolates restantes en la partida, aquellos que el pacman no se comio.
    set<Coordenada> chocolatesActuales() const; 


private:
    Fichin* _fichin;
};

#endif // AED2_FICHIN_H
