#ifndef TIPOS_H
#define TIPOS_H

#include "string_map.hpp"
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <set>
#include <tuple>
#include <string>
#include <map>
#include <list>
#include <vector>


using namespace std;

using Nat = unsigned int;

using Coordenada = pair<Nat, Nat>;

using Jugador = string;

using Puntaje = Nat;

using Ranking = string_map<Nat>;

enum Direccion {
    ARRIBA, ABAJO, IZQUIERDA, DERECHA
};

enum ResultadoMovimiento {
    SIGUE, GANO, PERDIO
};

#endif // TIPOS_H
