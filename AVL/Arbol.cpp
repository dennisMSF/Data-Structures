#include "pch.h"
#include "Arbol.h"
#include "Nodo.h"
#include "Cola.h"
#include <iostream>
#include <climits>
#include <sstream>
#include <stdlib.h>
#include <math.h>
using namespace std;

template <class T>
bool Arbol<T>::buscar(T valor, NodoArbol<T> **&pNodo) {
	pNodo = &raiz;
	while (*pNodo) {
		if ((*pNodo)->dato == valor)
			return 1;
		rotaciones.push(*pNodo);
		pNodo = &(*pNodo)->links[valor > (*pNodo)->dato];
	}
	return 0;
}

template <class T>
bool Arbol<T>::insertar(T valor) {
	NodoArbol<T>** pNodo;
	if (buscar(valor, pNodo))
		return 0;
	NodoArbol<T>* n = new NodoArbol<T>(valor);
	*pNodo = n;
	balancear();
	return 1;
}

template <class T>
bool Arbol<T>::eliminar(T valor)
{
	NodoArbol<T>** pNodo;
	NodoArbol<T>* temp;

	if (!buscar(valor, pNodo))
		return 0;
	temp = (*pNodo);
	rotaciones.push(*pNodo);
	if ((*pNodo)->links[0] && (*pNodo)->links[1]) {
		for (pNodo = &((*pNodo)->links[0]); (*pNodo)->links[1]; pNodo = &((*pNodo)->links[1]))
			rotaciones.push(*pNodo);
		temp->dato = (*pNodo)->dato;
	}
	temp = (*pNodo);
	(*pNodo) = (*pNodo)->links[!(*pNodo)->links[0]];
	if (temp == rotaciones.cabeza->dato)
	{
		rotaciones.pop();
	}
	delete temp;
	balancear();
	return 1;
}

template<class T>
void Arbol<T>::anchura() {
	NodoArbol<T>* pNodo = raiz;
	Cola<NodoArbol<T>*> col;
	if (pNodo)
		col.push(pNodo);
	while (!col.vacia()) {
		pNodo = col.pop();
		cout << pNodo->dato << " ";
		if (pNodo->links[0])
			col.push(pNodo->links[0]);
		if (pNodo->links[1])
			col.push(pNodo->links[1]);
	}
	cout << endl;
	return;
}

template <class T>
void Arbol<T>::formaArbol(NodoArbol<T>* node) {
	// get height first
	int height = altura(node);

	// perform  level order traversal
	Cola<NodoArbol<T>*> queue;

	int level = 0;
	const int SPACE = 2;
	int nodePrintLocation = 0;
	int cnt = 0;
	// special node for pushing when a node has no left or right child (assumption, say this node is a node with value Integer.MIN_VALUE)
	NodoArbol<T>* special = new NodoArbol<T>(0);
	queue.push(node);
	cout << endl << "                                                 " << endl;
	while (!queue.vacia()) {
		node = queue.pop();
		cnt++;
		nodePrintLocation = ((int)pow(2, height - level)) * SPACE;
		cout << imprimirLinea(node, nodePrintLocation);
		if (level < height) {
			// only go till last level
			queue.push(node->links[0] != 0 ? node->links[0] : special);
			queue.push(node->links[1] != 0 ? node->links[1] : special);
		}
		if (cnt == (int)pow(2, level)) {
			cout << endl;
			cnt = 0;
			level++;
		}
	}
	delete special;
}

template <class T>
void Arbol<T>::formaArbol() {
	formaArbol(raiz);
}

template <class T>
string Arbol<T>::imprimirLinea(NodoArbol<T>* node, int spaces) {
	stringstream sb, sv;
	if (raiz == nullptr) {
		return "arbol vacio";
	}
	if (node->dato == 0) {
		// for child nodes, print spaces
		for (int i = 0; i < 2 * spaces; i++) {
			sb << " ";
		}

		return sb.str();
	}
	int i = 0;
	int to = spaces / 2;
	for (; i < spaces / 2; i++) {
		sb << " ";
	}
	to += spaces / 2;
	char ch = ' ';
	if (node->links[0]) {
		ch = ' ';
	}
	for (; i < to; i++) {
		sb << ch;
	}
	sv << node->dato;
	to += spaces / 2;
	ch = ' ';
	if (node->links[1]) {
		ch = ' ';
	}
	sb << sv.str();
	for (i += sv.str().length(); i <= to; i++) {
		sb << ch;
	}

	to += spaces / 2;
	for (; i < to; i++) {
		sb << " ";
	}

	return sb.str();
}

template <class T>
int Arbol<T>::altura(NodoArbol<T>*  node) {
	if (!node) {
		return -1;
	}

	if (!node->links[0] && !node->links[1]) {
		return 0;
	}
	return 1 + mayor(altura(node->links[0]), altura(node->links[1]));
}

template <class T>
int Arbol<T>::mayor(int a, int b) {
	return a > b ? a : b;
}

template <class T>
void Arbol<T>::RR(NodoArbol<T> **&pNodo) {
	T tempval;
	NodoArbol<T>* tempNode;
	//A con B
	tempval = (*pNodo)->dato;
	(*pNodo)->dato = (*pNodo)->links[1]->dato;
	(*pNodo)->links[1]->dato = tempval;
	//B apunta a C (derecha) y a A (izquierda)
	tempNode = (*pNodo)->links[1];
	(*pNodo)->links[1] = (*pNodo)->links[1]->links[1];
	tempNode->links[1] = (*pNodo)->links[0];
	(*pNodo)->links[0] = tempNode;
	//bl con al
	tempNode = (*pNodo)->links[0]->links[0];
	(*pNodo)->links[0]->links[0] = (*pNodo)->links[0]->links[1];
	(*pNodo)->links[0]->links[1] = tempNode;
}

template <class T>
void Arbol<T>::LL(NodoArbol<T> **&pNodo) {
	T tempval;
	NodoArbol<T>* tempNode;
	//A con B
	tempval = (*pNodo)->dato;
	(*pNodo)->dato = (*pNodo)->links[0]->dato;
	(*pNodo)->links[0]->dato = tempval;
	//B apunta a C (izquierda) y a A (derecha)
	tempNode = (*pNodo)->links[0];
	(*pNodo)->links[0] = (*pNodo)->links[0]->links[0];
	tempNode->links[0] = (*pNodo)->links[1];
	(*pNodo)->links[1] = tempNode;
	//ar con br
	tempNode = (*pNodo)->links[1]->links[1];
	(*pNodo)->links[1]->links[1] = (*pNodo)->links[1]->links[0];
	(*pNodo)->links[1]->links[0] = tempNode;
}

template <class T>
void Arbol<T>::balancear() {
	NodoArbol<T> **temp;
	NodoArbol<T> **temp3;
	NodoArbol<T> *temp2;
	int izq, der;
	while (!rotaciones.vacia()) {
		izq = 0;
		der = 0;
		temp2 = rotaciones.pop();
		temp = &temp2;
		if ((*temp)->links[0])
			izq = (*temp)->links[0]->balance + 1;
		if ((*temp)->links[1])
			der = (*temp)->links[1]->balance + 1;
		(*temp)->balance = mayor(der, izq);
		if (der - izq == 2) {
			if (!(*temp)->links[1]->links[1] || ((*temp)->links[1]->links[0] && (*temp)->links[1]->links[0]->balance > (*temp)->links[1]->links[1]->balance)) {
				temp3 = &((*temp)->links[1]);
				LL(temp3);
			}
			RR(temp);
			rotaciones.push(temp2);
			rotaciones.push(temp2->links[0]);
			balancear();
			return;
		}
		if (der - izq == -2) {
			if (!(*temp)->links[0]->links[0] || ((*temp)->links[0]->links[1] && (*temp)->links[0]->links[1]->balance > (*temp)->links[0]->links[0]->balance)) {
				temp3 = &((*temp)->links[0]);
				RR(temp3);
			}
			LL(temp);
			rotaciones.push(temp2);
			rotaciones.push(temp2->links[1]);
			balancear();
			return;
		}
	}
}
