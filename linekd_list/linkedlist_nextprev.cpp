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
	nodo* prev;
	nodo(T x, nodo<T>* p, nodo<T>* q) {
		dato = x;
		next = p;
		prev = q;
	}
};
template<class T, class C>
class lista_doble {
public:
	nodo<T>* cabeza;
	nodo<T>* cola;
	C comparador;
	lista_doble() {
		cabeza = nullptr;
		cola = nullptr;
	}
	bool buscar(T x, nodo<T>**& p, nodo<T>**& q) {
		for (p = &cabeza; *p && comparador((*p)->dato, x); p = &((*p)->next));
		for (q = &cola; *q && comparador(x, (*q)->dato); q = &((*q)->prev));
		return *p && (*p)->dato == x;
	}
	bool insertar(T x) {
		nodo<T>**p;
		nodo<T>**q;
		if (buscar(x, p, q)) {
			return 0;
		}
		nodo<T>*nuevo = new nodo<T>(x, *p, *q);
		nuevo->next = *p;
		nuevo->prev = *q;
		*p = nuevo;
		*q = nuevo;
		return 1;
	}
	bool borrar(T x) {
		nodo<T>** p;
		nodo<T>** q;
		if (!buscar(x, p, q)) {
			return 0;
		}
		nodo<T>* temp = *p;
		nodo<T>* aux = *q;
		*p = temp->next;
		*q = aux->prev;
		delete temp;
		return 1;
	}
	void imprimir() {
		nodo<T>*p = cabeza;
		nodo<T>*q = cola;
		if (cabeza == nullptr && cola == nullptr) {
			std::cout << "lista vacia" << std::endl;
			return;
		}
		while (p->next) {
			std::cout << p->dato << " ";
			p = p->next;
		}
		std::cout << p->dato << std::endl;
		while (q->prev) {
			std::cout << q->dato << " ";
			q = q->prev;
		}
		std::cout << q->dato << std::endl;
	}
	void erase(nodo<T>* p) {
		if (p) {
			erase(p->next);
			delete p;
		}
	}
	~lista_doble() {
		erase(cabeza);
		cabeza = nullptr;
		cola = nullptr;
	}
};
void iniciar_menu() {
	int opcion;
	lista_doble<int, mayor<int>> l1;
	while (true) {
		std::cout << "////////////////////Lista Enlazada Simple Next y Prev////////////////////////" << std::endl;
		std::cout << "1.- Insertar elemento" << std::endl;
		std::cout << "2.- Eliminar elemento" << std::endl;
		std::cout << "3.- Imprimir lista" << std::endl;
		std::cout << "4.- Salir" << std::endl;
		std::cout << "ingrese opcion: ";
		std::cin >> opcion;
		if (opcion == 1) {
			int elemento;
			std::cout << "ingrese elemento: ";
			std::cin >> elemento;
			l1.insertar(elemento);
			system("cls");
		}
		else if (opcion == 2) {
			int elemento;
			std::cout << "ingrese elemento a borrar: ";
			std::cin >> elemento;
			l1.borrar(elemento);
			system("cls");
		}
		else if (opcion == 3) {
			l1.imprimir();
			system("pause");
			system("cls");
		}
		else if (opcion == 4) {
			l1.~lista_doble();
			return;
		}
	}
}
int main()
{
	iniciar_menu();
}
