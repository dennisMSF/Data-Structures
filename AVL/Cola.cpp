#include "pch.h"
#include "Cola.h"

template<class T>
void Cola<T>::push(T d) {
	Nodo<T>* nuevo = new Nodo<T>(d);
	if (!cola) {
		cola = nuevo;
		cabeza = nuevo;
		return;
	}
	cola->siguiente = nuevo;
	cola = nuevo;
}

template<class T>
T Cola<T>::pop() {
	Nodo<T>* temp;
	T val;
	if (cabeza == cola) {
		temp = cola;
		val = cola->dato;
		cola = 0;
		cabeza = 0;
	}
	else {
		temp = cabeza;
		val = cabeza->dato;
		cabeza = cabeza->siguiente;
	}
	delete temp;
	return val;
}

template<class T>
bool Cola<T>::vacia() {
	return (cabeza == 0);
}
