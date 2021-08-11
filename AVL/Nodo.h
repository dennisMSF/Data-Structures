#pragma once
#include "NodoArbol.h"
template<class T>
class Nodo {
public:
	T dato;
	Nodo<T>* siguiente;
	Nodo(T d) {
		dato = d;
		siguiente = 0;
	}
};
template class Nodo<int>;
template class Nodo<NodoArbol<int>*>;
