#pragma once
#include "Nodo.h"
#include "NodoArbol.h"

template <class T>
class Pila {
public:
	Nodo<T>*cabeza = 0;
	Nodo<T>*cola = 0;
	void push(T);
	T pop();
	bool vacia();
};
template class Pila <NodoArbol<int>*>;
