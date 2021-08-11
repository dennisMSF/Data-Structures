#pragma once
#include "Nodo.h"
#include "NodoArbol.h"

template <class T>
class Cola {
public:
	Nodo<T>*cabeza = 0;
	Nodo<T>*cola = 0;
	void push(T);
	T pop();
	bool vacia();
};
template class Cola<int>;
template class Cola<NodoArbol<int>*>;
