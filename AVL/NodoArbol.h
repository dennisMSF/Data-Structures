#pragma once
template<class T>
class NodoArbol {
public:
	T dato;
	int balance;
	NodoArbol() { dato = 0; balance = 0; }
	NodoArbol(T d) : dato(d) { balance = 0; }
	NodoArbol<T>* links[2] = { 0,0 };
};
template class NodoArbol<int>;