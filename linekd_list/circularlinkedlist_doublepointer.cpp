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
class lista_circular {
public:
	nodo<T>* cabeza;
	C comparador;
	lista_circular() {
		cabeza = nullptr;
	}
	bool buscar(T x, nodo<T>**& p) {
		for (p = &cabeza;comparador((*p)->dato, x) && (*p)->next != cabeza;p = &((*p)->next));
		if (comparador((*p)->dato, x)) p = &((*p)->next);
		return (*p)->dato == x;
	}
	bool insertar(T x) {
		if (!cabeza) {
			cabeza = new nodo<T>(x, nullptr);
			cabeza->next = cabeza;
			return 1;
		}
		nodo<T>**p;
		buscar(x, p);
		if (comparador(x, cabeza->dato) || x == cabeza->dato) {
			nodo<T> *t = new nodo<T>(x, cabeza);
			nodo<T> * q;
			for (q = cabeza; q->next != cabeza; q = q->next);
			q->next = t;
			cabeza = t;
			return 1;
		}
		*p = new nodo<T>(x, *p);
		return 1;
	}
	bool borrar(T x) {
		nodo<T>**p;
		if (!buscar(x, p)) return 0;
		if (*p == cabeza) {
			nodo<T> * q;
			for (q = cabeza; q->next != cabeza; q = q->next);
			q->next = (*p)->next;
			if ((*p)->next == cabeza) {
				cabeza = 0;
				nodo <T>* temp = *p;
				delete temp;
				return 1;
			}
		}
		nodo <T>* temp = *p;
		*p = temp->next;
		delete temp;
		return 1;
	}
	void imprimir() {
		nodo<T>*p = cabeza;
		if (cabeza == nullptr) {
			std::cout << "Lista vacia" << std::endl;
			return;
		}
		if (cabeza->next == cabeza) {
			std::cout << cabeza->dato << " " << cabeza->next->dato<<std::endl;
			return;
		}
		while (p->next != cabeza) {
			std::cout << p->dato << " ";
			p = p->next;
		}
		std::cout << p->dato << " " << p->next->dato << std::endl;
		std::cout << std::endl;
	}
	void erase(nodo<T>* p) {
		if (p == nullptr) {
			return;
		}
		nodo<T>* aux = p;
		nodo<T>* q = p;
		nodo<T>* tmp = p->next;
		while (tmp->next != aux) {
			tmp = tmp->next;
		}
		tmp->next = nullptr;
		while (q != nullptr) {
			q = q->next;
			delete aux;
			aux = q;
		}
		return;
	}
	~lista_circular() {
		erase(cabeza);
		cabeza = nullptr;
	}
};
void iniciar_menu() {
	int opcion;
	lista_circular<int, mayor<int>> l1;
	while (true) {
		std::cout << "////////////////////Lista Enlazada Simple Circular Doble Puntero////////////////////////" << std::endl;
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
			l1.~lista_circular();
			return;
		}
	}
}
int main()
{
	iniciar_menu();
}
