#include <iostream>
using namespace std;
////////////////////////////////////
template<typename T>
struct node
{
	T valor;
	node * next;
	node(T _valor, node* _next = nullptr)
	{
		valor = _valor; next = _next;
	};
};
/////////////////////////
template <class T>
class nodo {
public:
	T dato;
	nodo<T>* hijos[2];
	nodo(T data) {
		dato = data;
		hijos[0] = nullptr;
		hijos[1] = nullptr;
	}
};
/////////////////////////
template<typename T>
class pila
{
public:
	node<T>* top = nullptr;
	T &tops() {
		return top->valor;
	}
	bool vacio() {
		if (top)
			return false;
		else
			return true;
	}
	void push(T elemento) {
		top = new node<T>(elemento, top);
	}
	T pop() {
		node<T>* aux = top;
		top = top->next;
		return aux->valor;
	}
	void erase(node<T>* p) {
		if (p) {
			erase(p->next);
			delete p;
		}
	}
	~pila() {
		erase(top);
		top = nullptr;
	}
};
///////////////////////////////////
template <class T>
class identificador {
public:
	int estado;
	nodo<T>* p;
};
template <class T>
class tree {
public:
	std::pair<int, nodo<T>*> mi_pair;
	pila < std::pair<int, nodo<T>*>> mi_pila;
	nodo<T>* raiz;
	tree() {
		raiz = nullptr;
	}
	bool busca(T data, nodo<T>**&p) {
		for (p = &raiz; (*p) && (*p)->dato != data; p = &(*p)->hijos[(*p)->dato < data]);
		return (*p);
	}
	bool insertar(T dato) {
		nodo<T>** p;
		if (busca(dato, p)) {
			return 0;
		}
		*p = new nodo<T>(dato);
		return 1;
	}
	bool saca(T dato) {
		nodo<T>** p;
		nodo<T>* temp;
		if (!busca(dato, p)) {
			return 0;
		}
		temp = *(p);
		if ((*p)->hijos[0] && (*p)->hijos[1]) {
			for (p = &((*p)->hijos[0]); (*p)->hijos[1]; p = &((*p)->hijos[1]));
			swap((*p)->dato, temp->dato);
		}
		temp = (*p);
		(*p) = (*p)->hijos[!!(*p)->hijos[1]];
		return 1;
	}
	void imprimir_inorder(nodo<T>* p) {
		int estado=0;
		if (!p) {
			if (raiz == nullptr) {
				cout << "arbol vacio" << std::endl;
			}
			return;
		}
		mi_pair = std::make_pair(estado, p);
		mi_pila.push(mi_pair);
		while (!mi_pila.vacio()) {
			if (mi_pila.tops().first == 3) {
				mi_pila.pop();
			}
			else if (mi_pila.tops().second->hijos[0] != nullptr && mi_pila.tops().first != 1) {
				mi_pila.tops().first = 1;
				mi_pair = make_pair(0, mi_pila.tops().second->hijos[0]);
				mi_pila.push(mi_pair);
			}
			else {
				std::cout << mi_pila.tops().second->dato << " ";
				mi_pila.tops().first = 2;
				if (mi_pila.tops().second->hijos[1] != nullptr) {
					mi_pila.tops().first = 3;
					mi_pair = make_pair(0, mi_pila.tops().second->hijos[1]);
					mi_pila.push(mi_pair);
				}
				else {
					mi_pila.pop();
				}
			}
		}
	}
	void imprimir_postorder(nodo<T>* p) {
		int estado = 0;
		if (!p) {
			if (raiz == nullptr) {
				cout << "arbol vacio" << std::endl;
			}
			return;
		}
		mi_pair = std::make_pair(estado, p);
		mi_pila.push(mi_pair);
		while (!mi_pila.vacio()) {
			if (mi_pila.tops().first == 3) {
				std::cout << mi_pila.tops().second->dato << " ";
				mi_pila.pop();
			}
			else if (mi_pila.tops().second->hijos[0] != nullptr && mi_pila.tops().first != 1) {
				mi_pila.tops().first = 1;
				mi_pair = make_pair(0, mi_pila.tops().second->hijos[0]);
				mi_pila.push(mi_pair);
			}
			else {
				if (mi_pila.tops().second->hijos[1] != nullptr) {
					mi_pila.tops().first = 3;
					mi_pair = make_pair(0, mi_pila.tops().second->hijos[1]);
					mi_pila.push(mi_pair);
				}
				else {
					std::cout << mi_pila.tops().second->dato << " ";
					mi_pila.pop();
				}
			}
		}
	}
	void imprimir_preorder(nodo<T>* p) {
		int estado = 0;
		if (!p) {
			if (raiz == nullptr) {
				cout << "arbol vacio" << std::endl;
			}
			return;
		}
		mi_pair = std::make_pair(estado, p);
		mi_pila.push(mi_pair);
		while (!mi_pila.vacio()) {
			if (mi_pila.tops().first == 3) {
				mi_pila.pop();
			}
			else if (mi_pila.tops().second->hijos[0] != nullptr && mi_pila.tops().first != 1) {
				std::cout << mi_pila.tops().second->dato << " ";
				mi_pila.tops().first = 1;
				mi_pair = make_pair(0, mi_pila.tops().second->hijos[0]);
				mi_pila.push(mi_pair);
			}
			else {
				if (mi_pila.tops().first != 1) {
					std::cout << mi_pila.tops().second->dato << " ";
				}
				mi_pila.tops().first = 2;
				if (mi_pila.tops().second->hijos[1] != nullptr) {
					mi_pila.tops().first = 3;
					mi_pair = make_pair(0, mi_pila.tops().second->hijos[1]);
					mi_pila.push(mi_pair);
				}
				else {
					mi_pila.pop();
				}
			}
		}
	}
	void imprimir_reverse(nodo<T>* p) {
		int estado = 0;
		if (!p) {
			if (raiz == nullptr) {
				cout << "arbol vacio" << std::endl;
			}
			return;
		}
		mi_pair = std::make_pair(estado, p);
		mi_pila.push(mi_pair);
		while (!mi_pila.vacio()) {
			if (mi_pila.tops().first == 3) {
				mi_pila.pop();
			}
			else if (mi_pila.tops().second->hijos[1] != nullptr && mi_pila.tops().first != 1) {
				mi_pila.tops().first = 1;
				mi_pair = make_pair(0, mi_pila.tops().second->hijos[1]);
				mi_pila.push(mi_pair);
			}
			else {
				std::cout << mi_pila.tops().second->dato << " ";
				mi_pila.tops().first = 2;
				if (mi_pila.tops().second->hijos[0] != nullptr) {
					mi_pila.tops().first = 3;
					mi_pair = make_pair(0, mi_pila.tops().second->hijos[0]);
					mi_pila.push(mi_pair);
				}
				else {
					mi_pila.pop();
				}
			}
		}
	}
	void borra(nodo<T>* p) {
		if (p) {
			borra(p->hijos[0]);
			borra(p->hijos[1]);
			delete p;
		}
	}
	~tree() {
		borra(raiz);
	}
};
void iniciar_menu() {
	int opcion;
	tree<int> tree1;
	while (true) {
		std::cout << "////////////////////Arbol Binario - Recorrido con pila////////////////////////" << std::endl;
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
			tree1.insertar(elemento);
			system("cls");
		}
		else if (opcion == 2) {
			int elemento;
			std::cout << "ingrese elemento a borrar: ";
			std::cin >> elemento;
			tree1.saca(elemento);
			system("cls");
		}
		else if (opcion == 3) {
			std::cout << "Recorrido inorder: ";
			tree1.imprimir_inorder(tree1.raiz);
			std::cout << std::endl;
			std::cout << "Recorrido preorder: ";
			tree1.imprimir_preorder(tree1.raiz);
			std::cout << std::endl;
			std::cout << "Recorrido postorder: ";
			tree1.imprimir_postorder(tree1.raiz);
			std::cout << std::endl;
			std::cout << "Recorrido reverse: ";
			tree1.imprimir_reverse(tree1.raiz);
			std::cout << std::endl;
			system("pause");
			system("cls");
		}
		else if (opcion == 4) {
			return;
		}
	}
}
int main() {
	iniciar_menu();
}
