#include <iostream>
template<class C>
class mayor {
public:
	inline bool operator()(C x, C y) {
		return x < y;
	}
};
template<class C>
class menor {
public:
	inline bool operator()(C x, C y) {
		return x > y;
	}
};
template<class T>
class nodo {
public:
	T dato;
	nodo* next;
	nodo(T x, nodo<T>* p) {
		dato = x;
		next = p;
	}
};
template<class T, class C>
class lista {
public:
	nodo<T>* cabeza;
	C comparador;
	lista() {
		cabeza = nullptr;
	}
	bool buscar(T x, nodo<T>**& p) {
		for (p = &cabeza; *p ; p = &((*p)->next));
		return *p && (*p)->dato == x;
	}
	bool insertar(T x) {
		nodo<T>**p;
		if (buscar(x, p)) {
			return 0;
		}
		nodo<T>* nuevo = new nodo<T>(x, *p);
		nuevo->next = *p;
		*p = nuevo;
		return 1;
	}
	bool borrar(T x) {
		nodo<T>** p;
		if (!buscar(x, p)) {
			return 0;
		}
		nodo<T>* temp = *p;
		*p = temp->next;
		delete temp;
		return 1;
	}
	void imprimir() {
		nodo<T>*p = cabeza;
		if (p == nullptr) {
			std::cout << "lista vacia" << std::endl;
		}
		while (p) {
			std::cout << p->dato << " ";
			p = p->next;
		}
		std::cout << std::endl;
	}
	void erase(nodo<T>* p) {
		if (p) {
			erase(p->next);
			delete p;
		}
	}
	~lista() {
		erase(cabeza);
		cabeza = nullptr;
	}
};

int main()
{
	lista<int, mayor<int>> l1;
	l1.insertar(6);
	l1.insertar(5);
	l1.imprimir();
}
