#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <Windows.h>
using namespace std;
void swap(int *x, int *y);
class ptree{
public:
	int *harr;
	int capacity;
	int heap_size;
	ptree(int capacity);
	void MinHeapify(int);
	int parent(int i) { return (i - 1) / 2; }
	int left(int i) { return (2 * i + 1); }
	int right(int i) { return (2 * i + 2); }
	int pop();
	int getMin() { return harr[0]; }
	void insert(int k);
	void gotoxy(int x, int y)
	{
		HANDLE hcon;
		hcon = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD dwPos;
		dwPos.X = x;
		dwPos.Y = y;
		SetConsoleCursorPosition(hcon, dwPos);
	}
	void print(int pos_y)
	{
		int aux_X = 0;
		int aux_Y = pos_y;

		int lvl = 0;
		int i = 1;
		int lvl_pow = heap_size;
		int m_height = 0;

		while (!(lvl_pow && (!(lvl_pow & (lvl_pow - 1)))))
			lvl_pow++;

		lvl_pow = log(lvl_pow) / log(2) - 1;

		int aux_XX = 0;
		while (i <= heap_size)
		{
			aux_X = 2 * pow(2, lvl_pow);
			aux_XX = 2 * pow(2, lvl_pow + 1);
			for (int j = 0; i <= heap_size && j < pow(2, lvl); j++)
			{
				gotoxy(aux_X, aux_Y);
				std::cout <<harr[i-1];
				aux_X += aux_XX;
				i++;
			}
			lvl_pow--;
			aux_Y++;
			lvl++;
		}
		cout <<endl<<lvl;
		cout << endl;
	}
};
ptree::ptree(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new int[cap];
}
void ptree::insert(int k)
{
	if (heap_size == capacity)
	{
		cout << "\nOverflow: Could not insertKey\n";
		return;
	}
	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;
	while (i != 0 && harr[parent(i)] < harr[i])
	{
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}
int ptree::pop()
{
	if (heap_size <= 0)
		return INT_MAX;
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}
	int root = harr[0];
	harr[0] = harr[heap_size - 1];
	heap_size--;
	MinHeapify(0);

	return root;
}
void ptree::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l] > harr[i])
		smallest = l;
	if (r < heap_size && harr[r] > harr[smallest])
		smallest = r;
	if (smallest != i)
	{
		swap(&harr[i], &harr[smallest]);
		MinHeapify(smallest);
	}
}
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
int main()
{
	ptree h(20);
	h.insert(1);
	h.insert(2);
	h.insert(3);
	h.insert(4);
	h.insert(5);
	h.insert(6);
	h.insert(7);
	h.insert(8);
	h.insert(9);
	h.insert(10);
	h.print(0);
	h.pop();
	h.pop();
	h.pop();
	h.pop();
	h.pop();
	//h.print(0);
	return 0;
}
