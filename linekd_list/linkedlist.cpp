#include <iostream>
template <class C>
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
template <class T>
class nodo {
public:
	T valor;
	nodo* next;
	nodo(T, nodo<T>*p = nullptr);
};
template <class T>
nodo<T>::nodo(T a, nodo<T>*p) {
	next = p;
	valor = a;
}
template <class T,class C>
class lista_simple {
public:
	nodo<T>* H;
	C comparador;
	lista_simple();
	bool buscar(T, nodo <T> * &);
	void add(T);
	void out(T);
	void imprimir();
	void eraser(nodo<T>*p);
	~lista_simple();
};
template <class T,class C>
lista_simple<T,C>::lista_simple() {
	H = nullptr;
}
template <class T, class C>
bool lista_simple<T,C>::buscar(T a, nodo<T> * & p) {
	nodo<T> *i = H;
	nodo<T> *y = i;
	while (i && comparador(i->valor,a)) {
		y = i;
		i = i->next;
	}
	p = y;
	return i && (i->valor) == a;
}
template <class T, class C>
void lista_simple<T,C>::add(T a) {
	nodo<T> *p;
	if (!buscar(a, p)) {
		if (p == H && !p) {
			H = new nodo<T>(a);
		}
		else if (p == H & (p->valor) > a) {
			H = new nodo<T>(a, H);
		}
		else {
			p->next = new nodo<T>(a, p->next);
		}
	}
}
template <class T, class C>
void lista_simple<T,C>::out(T a) {
	nodo<T>*p;
	if (buscar(a, p)) {
		nodo<T>*u;
		if (p == H && H->valor == a) {
			u = H->next;
			delete(H);
			H = u;
		}
		else {
			u = p->next->next;
			delete(p->next);
			p->next = u;
		}
	}
}
template <class T, class C>
void lista_simple<T,C>::imprimir() {
	nodo<T>* p = H;
	if (p == nullptr) {
		std::cout << "lista vacia" << std::endl;
	}
	while (p!= nullptr) {
		std::cout << p->valor << " ";
		p = p->next;
	}
	std::cout << std::endl;
}
template <class T, class C>
void lista_simple<T,C>::eraser(nodo<T>*p) {
	if (p) {
		eraser(p->next);
		delete p;
	}
}
template <class T, class C>
lista_simple<T,C>::~lista_simple() {
	eraser(H);
	H = nullptr;
}

int main()
{
	
	lista_simple<int, mayor<int>> l1;
	l1.add(1);
	l1.add(7);
	l1.add(8);
	l1.add(15);
	l1.add(31);
	l1.add(50);
	l1.imprimir();
}
