#if !defined(Fichin_H)
#define Fichin_H
#include "Tipos.h"
#include "Partida.h"
#include "Mapa.h"
using namespace std;


class Fichin
{
public:
    // Constructor de fichin.
    Fichin(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, list<Coordenada> paredes,
                list<Coordenada> fantasmas, list<Coordenada> chocolates);

    // Constructor por default de fichin.
    Fichin();

    // Destructor de fichin. 
    ~Fichin();

    // Devuelve el mapa de la partida.  
    Mapa& mapa();    

    // Devuelve si hay un jugador actualmente jugando.
    bool alguienJugando() const;

    // Devuelve al jugador actual.
    //PRE: no hay alguien jugando
    Jugador jugadorActual() const;

    // Devuelve la partida actual.
    // PRE: hay alguien jugando 
    Partida partidaActual() const;

    // Devuelve el ranking de puntajes de todos los jugadores que hayan pasado por el sistema. (Ranking se representa con diccTrie/string map)
    Ranking ranking() const;
    
    // Devuelve la coordenada donde está parado el jugador actual en la partida. 
    Coordenada jugador() const;

    // Inicia una nueva partida con el jugador J. Resetea los chocolates y pone al pacman en la posicion de inicio.
    // PRE: no hay alguien jugando
    void nuevaPartida(Jugador j);
    
    // Mueve al pacman en el tablero segun la direccion indicada y me devuelve el estado de la partida despues de haberse movido. Los posibles estados son: sigue, perdio o gano.
    // PRE: hay alguien jugando
    ResultadoMovimiento mover(Direccion j); 

    // Devuelve una tupla que contiene al jugador con puntaje mas proximo al actual junto con su puntaje.
    // PRE: hay alguien jugando y el jugador actual ya esta en el ranking.
    pair<Jugador, Nat> objetivo() const;

    // Devuelve el conjunto de coordenadas dónde están ubicadas las paredes. (Conjunto se representa con lista enlzada)
    list<Coordenada> paredes() const;

    // Devuelve el conjunto de coordenadas que contienen fantasmas. (Conjunto se representa con lista enlazada)
    list<Coordenada> fantasmas() const;

    // Devuelve el conjunto de coordenadas que contienen los chocolates que hay antes de arrancar una partida.
    list<Coordenada> chocolatesIniciales() const;

    // Devuelve la cantidad de movimientos que hizo el pacman hasta el momento.
    Nat cantMov() const;

    // Devuelve la cantidad restante de movimientos inmunizados que tiene el pacman actualmente.
    Nat inmunidad() const;

    // Devuelve el conjunto de chocolates restantes en la partida, aquellos que el pacman no se comio.
    set<Coordenada> chocolatesActuales() const;

    // Devuelve el alto del mapa de la partida actual. 
    Nat alto() const;

    // Devuelve el largo del mapa de la partida actual. 
    Nat largo() const;

    // Devuelve la coordenada donde el jugar empieza en el mapa. 
    Coordenada salida() const;

    // Devuelve la coordenada dónde el jugar tiene que llegar para ganar. 
    Coordenada llegada() const;


    // Devuelve el ranking, Jugador-Puntaje, del fichin. Cuanto menos puntaje mejor posicionado el jugador. El ranking está representado como un diccionario. (Diccionario se representa con Trie)
    map<Jugador,Puntaje> rankingMap() const;
    
    
private: 
    Mapa* _mapa;
    bool _alguienJugando;
    Jugador _jugadorActual;
    Partida* _partidaActual;
    Ranking _ranking;

    // Devuelve el nombre de uno de los jugadores que tiene mejor puntaje que el actual. 
    // PRE: hay alguien jugando y el jugador actual ya esta en el ranking.
    Jugador oponente() const;

    // Devuelve el conjunto con todos los jugadores del ranking que tienen mejor puntaje que el natural pasado por parametro. (Conjunto es representado por una lista enlazada)
    list<Jugador> mejoresQue(Ranking r, vector<Jugador> cj, Nat p) const;

    // Devuelve el conjunto de jugadores con el peor puntaje del conjunto ingresado. (Conjunto es representado por una lista enlazada)
    list<Jugador> peoresJugadores(Ranking r, list<Jugador> cj) const;
    
    // Devuelve el conjunto de jugadores con puntaje inmediatamente superior al jugador actual. (Conjunto es representado por una lista enlazada)
    // PRE: hay alguien jugando y el jugador actual ya esta en el ranking.    
    list<Jugador> oponentes() const; 

    // Devuelve el conjunto de jugadores con un puntaje igual al pasado por parámetro.
    list<Jugador> jugadoresConPuntaje(Ranking r, list<Jugador> cj, Nat p) const;

    // Devuelve el puntaje más bajo del conjunto de jugadores del ranking. 
    // PRE: el conjunto cj debe ser no vacio y pertenecer a las claves del ranking
    Nat peorPuntaje(Ranking r, list<Jugador> cj) const;



};
#endif // Fichin_H




