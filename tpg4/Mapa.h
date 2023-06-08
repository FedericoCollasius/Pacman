#if !defined(Mapa_H)
#define Mapa_H
#include "Tipos.h"

class Mapa
{
public:
    //Genera un nuevo mapa.
    Mapa(Nat largo, Nat alto, Coordenada inicio, Coordenada llegada, list<Coordenada> paredes,
         list<Coordenada> fantasmas, list<Coordenada> chocolates);

    //Constructor del mapa por default
    Mapa();

    //Destructor del mapa
    ~Mapa();

    //Devuelve el largo del mapa. 
    Nat largo () const;

    //Devuelve el alto del mapa. 
    Nat alto () const; 

    //Devuelve la coordenada de inicio. 
    Coordenada inicio () const;

    //Devuelve la coordenada de inicio. 
    Coordenada llegada () const;

    //Devuelve el conjunto de coordenadas donde se encuentran paredes.
    list<Coordenada> paredes () const; 

    //Devuelve el conjunto de coordenadas donde se encuentran los fantasmas.
    list<Coordenada> fantasmas () const; 

    //Devuelve el conjunto de coordenadas donde se encuentran los chocolates.
    list<Coordenada> chocolates () const;

    //Devuelve un puntereo al conjunto de chocolates
    list<Coordenada>* chocolatesPunt();

    //Devuelve true si hay fantasmas a menos de 3 casillas de distancia Manhattan
    bool hayFantasmaEnAlrededores(Coordenada pos) const; 

    //Permite modificar una posicion del tablero
    void modificarMapa(Coordenada coor, char c);

    //Devuelve una copia del tablero
    vector<vector<char>> tablero() const;

    //Sobrecarga el operador igual para que se pueda usar con mapa
    Mapa& operator=(const Mapa& m);

private:
    Nat _largo;
    Nat _alto;
    Coordenada _inicio;
    Coordenada _llegada;
    list<Coordenada> _paredes;
    list<Coordenada> _fantasmas;
    list<Coordenada> _chocolates;
    vector<vector<char>> _tablero;

    //Devuelve si una coordenada esta dentro de los limites del tablero
    bool enRango(Coordenada pos, Nat largo, Nat alto) const;

    
    
};

#endif // Mapa_H
