#include "string_map.h"


template <typename T>
string_map<T>::string_map(){
    raiz = nullptr;
    _size = 0;
    _claves;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; }

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    if (d.raiz != nullptr) {
        raiz = new Nodo;
        Nodo* nodo = raiz;
        Nodo* nodoACopiar = d.raiz;
        (*nodo).copiatres(nodoACopiar);
    }
    else {
        raiz = nullptr;
    }
    _size = d._size;
    _claves = d._claves;
    return *this;
}

template <typename T>
void string_map<T>::Nodo::copiatres(Nodo* &nodoACopiar) {
    if (nodoACopiar != nullptr) {
        if (nodoACopiar->definicion != nullptr) {
            T* valor = new T;
            *valor = *nodoACopiar->definicion;
            definicion = valor;
        }
        for (int i = 0; i < siguientes.size(); i++) {
            if (nodoACopiar->siguientes[i] != nullptr) {
                Nodo* nuevoNodo = new Nodo;
                siguientes[i] = nuevoNodo;
                (*nuevoNodo).copiatres(nodoACopiar->siguientes[i]);
            }
        }
    }
}

template <typename T>
string_map<T>::~string_map(){
    while (_size != 0) {
        string palabra = "";
        Nodo* nodo = raiz;
        while (nodo->definicion == nullptr) {
            for (int i = 0; i < 256; i++) {
                if (nodo->siguientes[i] != nullptr) {
                    palabra.push_back(i);
                    nodo = nodo->siguientes[i];
                    break;
                }
            }
        }
        if (nodo == raiz) {
            palabra.push_back('W');
        }
        erase(palabra);
    }
    
}

template<typename T>
inline void string_map<T>::insert(const pair<string, T>&par) {
    Nodo* nodo = raiz;
    bool faltanNodos = false;
    int donde_falta;
    for (int i = 0; i < par.first.size(); i++) {
        if (raiz == nullptr) {
            donde_falta = 0;
            faltanNodos = true;
            break;
        }
        if (nodo->siguientes[par.first[i]] == nullptr) {
            faltanNodos = true;
            donde_falta = i;
            break;
        }
        if (i != par.first.size() - 1) {
            nodo = nodo->siguientes[par.first[i]];
        }
        else {
            nodo = nodo->siguientes[par.first[i]];
        }
    }
    if (faltanNodos) {
        if (raiz == nullptr) {
            Nodo* nodo2 = new Nodo;
            raiz = nodo2;
            nodo = raiz;
        }
        while (donde_falta != par.first.size()) {
            Nodo* agregoNodo = new Nodo;
            nodo->siguientes[par.first[donde_falta]] = agregoNodo;
            nodo = nodo->siguientes[par.first[donde_falta]];
            donde_falta++;
        }
    }
    T* algo = new T;
    *algo = par.second;
    if (nodo->definicion == nullptr) {
        _size++;
        _claves.push_back(par.first);
    }
    delete(nodo->definicion);
    nodo->definicion = algo;
}

template<typename T>
inline vector<string> string_map<T>::claves() const
{
    return _claves;
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    if (raiz == nullptr) { return 0; }
    Nodo* nodo = raiz;
    for (int i = 0; i < clave.size(); i++) {
        nodo = nodo->siguientes[clave[i]];
        if (nodo == nullptr) { return 0; }
    }
    if (nodo->definicion == nullptr) { return 0; }
    else { return 1; }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* nodo = raiz;
    for (int i = 0; i < clave.size(); i++) {
        nodo = nodo->siguientes[clave[i]];
    }
    return *(nodo->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* nodo = raiz;
    for (int i = 0; i < clave.size(); i++) {
        nodo = nodo->siguientes[clave[i]];
    }
    return *(nodo->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* nodo = raiz;
    vector<Nodo*> vecPunteros;
    vecPunteros.push_back(nodo);
    for (int i = 0; i < clave.size(); i++) {
        nodo = nodo->siguientes[clave[i]];
        vecPunteros.push_back(nodo);

    }
    delete(nodo->definicion);
    nodo->definicion = nullptr;
    
    for (int i = vecPunteros.size()-1; i >= 0; i--) {
        nodo = vecPunteros[i];
        Nodo* padre;
        if (i != 0) {
            padre = vecPunteros[i - 1];
        }
        bool deboEliminar = true;
        for (int j = 0; j < nodo->siguientes.size(); j++) {
            if (nodo->siguientes[j] != nullptr || nodo->definicion != nullptr) {
                deboEliminar = false;
                break;
            }
        }
        if (deboEliminar) {
            delete(nodo);
            if (i != 0) {
                padre->siguientes[clave[i - 1]] = nullptr;
            }
            else {
                raiz = nullptr;
            }
        }
        else {
            break;
        }
    }
    _size--;
    //remove(_claves.begin(), _claves.end(), clave);
    for (int i = 0; i < _claves.size(); i++) {
        if (_claves[i] == clave) {
            _claves.erase(_claves.begin() + i);
            break;
        }
    }
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size == 0;
}