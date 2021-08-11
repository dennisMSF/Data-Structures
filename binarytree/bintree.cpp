#include <iostream>
#include <stack>
using namespace std;
template<class T>
struct c_Node {
	T m_data;
	c_Node<T>* m_child[2];

	c_Node(T dato) {

		m_data = dato;
		m_child[0] = nullptr;
		m_child[1] = nullptr;
	}
};
/// //////////////////////////////////////////////////////////////////////
class preorderit {
public:
	void operator() (int& a, int arr[]) {
		a = 1;
		arr[0] = 0;
		arr[1] = 1;
	}
};
class inorderit {
public:
	void operator() (int& a, int arr[]) {
		a = 0;
		arr[0] = 0;
		arr[1] = 1;
	}
};
class postorederit {
public:
	void operator() (int& a, int arr[]) {
		a = 2;
		arr[0] = 0;
		arr[1] = 1;
	}
};
class reverseit {
public:
	void operator() (int& a, int arr[]) {
		a = 0;
		arr[0] = 1;
		arr[1] = 0;
	}
};
/// ////////////////////////////////////////////////////////////////////////////

template<class T, class R>
class c_BT_Iterator {
public:
	c_BT_Iterator() {
		myiterator(m_id, ayuda);
	}
	pair<c_Node<T>*, int> m_pair;
	int m_id;
	int ayuda[2];
	R myiterator;
	stack<pair<c_Node<T>*, int> > m_stack;
	c_BT_Iterator<T, R> operator=(c_BT_Iterator<T, R> x) {
		m_stack = x.m_stack;
		return *this;
	}
	bool operator!=(c_BT_Iterator<T, R> x) {
		return m_stack != x.m_stack;
	}
	c_BT_Iterator<T, R> operator++(int) {
		m_pair = m_stack.top();
		do {
			m_stack.pop();
			if (m_pair.second == m_id) {
				m_stack.push(make_pair(m_pair.first, (m_id + 1) % 3));
				if (m_pair.first->m_child[ayuda[0]]) m_stack.push(make_pair(m_pair.first->m_child[ayuda[0]], m_id));
			}
			else if (m_pair.second == (m_id + 1) % 3) {
				m_stack.push(make_pair(m_pair.first, (m_id + 2) % 3));
				if (m_pair.first->m_child[ayuda[1]]) m_stack.push(make_pair(m_pair.first->m_child[ayuda[1]], m_id));
			}
			if (!m_stack.empty())m_pair = m_stack.top();
		} while (m_pair.second != 1 && !m_stack.empty());
		return *this;
	}
	T operator*() {
		m_pair = m_stack.top();
		return m_pair.first->m_data;
	}
};

template<class T, class R>
class c_BinTRee {
public:
	typedef c_BT_Iterator<T, R> alliterator;
	c_BinTRee();
	bool busca(T, c_Node<T>**&);
	bool inserta(T);
	bool saca(T);
	void inorden(c_Node<T>*);
	alliterator endd() {
		return alliterator();
	}
	alliterator beginn() {
		c_Node<T>* p = m_root;
		alliterator t;
		t.m_stack.push(make_pair(p, t.m_id));
		t++;
		return t;
	}
	c_Node<T>*m_root;
};
template<class T, class R>
c_BinTRee<T, R>::c_BinTRee() {
	m_root = nullptr;
}
template<class T, class R>
bool c_BinTRee<T, R>::busca(T x, c_Node<T>**&p)
{
	for (p = &m_root; (*p) && (*p)->m_data != x; p = &(*p)->m_child[(*p)->m_data < x]);
	return (*p);
}
template<class T, class R>

bool c_BinTRee<T, R>::inserta(T x)
{
	c_Node<T>**p;

	if (busca(x, p)) return 0;

	*p = new c_Node<T>(x);

	return 1;
}
template<class T, class R>

bool c_BinTRee<T, R>::saca(T x)
{
	c_Node<T>** p;
	c_Node<T>* temp;

	if (!busca(x, p)) return 0;
	temp = (*p);
	if ((*p)->m_child[0] && (*p)->m_child[1]) {

		for (p = &((*p)->m_child[0]); (*p)->m_child[1]; p = &((*p)->m_child[1]));
		swap((*p)->m_data, temp->m_data);
	}
	temp = (*p);
	(*p) = (*p)->m_child[!!(*p)->m_child[1]];
	return 1;
}

int main()
{
	c_BinTRee<int, reverseit> tree;
	c_BinTRee<int, reverseit>::alliterator i;
	tree.inserta(4);
	tree.inserta(9);
	tree.inserta(14);
	tree.inserta(2);
	tree.inserta(7);
	tree.inserta(8);

	for (i = tree.beginn(); i != tree.endd(); i++)
	{

		cout << *i << " ";
	}
	cout << endl;
	
}
