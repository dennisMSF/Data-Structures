#pragma once
#include "NodoArbol.h"
#include "Pila.h"
#include <string>
template <class T>
class Arbol
{
	void formaArbol(NodoArbol<T>*);
	std::string imprimirLinea(NodoArbol<T>*, int);
	int altura(NodoArbol<T>*);
	int mayor(int, int);
	void balancear();
	void RR(NodoArbol<T>**&);
	void LL(NodoArbol<T>**&);
public:
	Pila<NodoArbol<T>*> rotaciones;
	NodoArbol<T>* raiz = 0;
	bool buscar(T, NodoArbol<T>**&);
	bool insertar(T dato);
	bool eliminar(T dato);
	void anchura();
	void formaArbol();
};
template class Arbol<int>;
