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
	nodo(T x) {
		dato = x;
		next = nullptr;
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
	bool buscar(T x, nodo<T>*& p, nodo<T>*& q) {
		p = cabeza;
		if (!p) {
			return 0;
		}
		if (comparador(x, p->dato)) {
			q = cabeza;
			while ((q->next) != cabeza) {
				q = q->next;
			}
			return 0;
		}
		q = p->next;
		if (cabeza->dato == x) {
			while (q != cabeza) {
				p = q;
				q = q->next;
			}
			return 1;
		}
		while (q != cabeza && comparador(q->dato, x)) {
			p = q;
			q = q->next;
		}
		return q != cabeza && q->dato == x;
	}
	bool insertar(T x) {
		nodo<T>*p;
		nodo<T>*q;
		if (buscar(x, p, q)) {
			return 0;
		}
		if (!p) {
			cabeza = new nodo<T>(x);
			cabeza->next = cabeza;
		}
		else if(comparador(x,p->dato)){
			cabeza = new nodo<T>(x);
			cabeza->next = p;
			q->next = cabeza;
		}
		else if (p && q == cabeza) {
			p->next = new nodo<T>(x);
			p->next->next = cabeza;
		}
		else if (p && q != cabeza) {
			p->next = new nodo<T>(x);
			p->next->next = q;
		}
		return 1;
	}
	bool borrar(T x) {
		nodo<T>* p;
		nodo<T>* q;
		if (!buscar(x, p, q)) {
			return 0;
		}
		if (p != cabeza && q == cabeza) {
			cabeza = cabeza->next;
			p->next = cabeza;
			delete[]q;
		}
		else if (p == cabeza && q == cabeza) {
			cabeza->next = nullptr;
			cabeza = nullptr;
			delete[]q;
		}
		else if (q->next != cabeza && q != cabeza) {
			p->next = q->next;
			delete[]q;
		}
		else if (q->next == cabeza && q != cabeza) {
			p->next = cabeza;
			delete[]q;
		}
		return 1;
	}
	void imprimir() {
		nodo<T>*p = cabeza;
		if (cabeza == nullptr) {
			std::cout << "lista vacia" << std::endl;
			return;
		}
		if (cabeza->next == cabeza) {
			std::cout << cabeza->dato<<" "<<cabeza->next->dato << std::endl;
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
		std::cout << "////////////////////Lista Enlazada Simple Circular////////////////////////" << std::endl;
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
int main() {

	iniciar_menu();
	return 0;
}
