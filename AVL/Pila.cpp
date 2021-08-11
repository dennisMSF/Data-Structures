#include "pch.h"
#include "Pila.h"
template<class T>
void Pila<T>::push(T d) {
	Nodo<T>* nuevo = new Nodo<T>(d);
	if (!cabeza) {
		cola = nuevo;
		cabeza = nuevo;
		return;
	}
	nuevo->siguiente = cabeza;
	cabeza = nuevo;
}

template<class T>
T Pila<T>::pop() {
	Nodo<T>* temp;
	T val;
	if (cabeza == cola) {
		temp = cabeza;
		val = cabeza->dato;
		cola = 0;
		cabeza = 0;
	}
	else {
		temp = cabeza;
		val = temp->dato;
		cabeza = cabeza->siguiente;
	}
	delete temp;
	return val;
}


template<class T>
bool Pila<T>::vacia() {
	return (cabeza == 0);
}