
#include "Arbol.h"
#include <iostream>

using namespace std;
int main()
{

	Arbol<int> a;
	a.insertar(1);
	a.insertar(8);
	a.insertar(3);
	a.insertar(9);
	a.insertar(2);
	a.insertar(11);
	a.formaArbol();
	a.eliminar(3);
	a.formaArbol();
	a.eliminar(8);
	a.eliminar(9);
	a.formaArbol();
	a.eliminar(2);
	a.eliminar(1);
	a.formaArbol();
	a.eliminar(11);
	a.formaArbol();
}
