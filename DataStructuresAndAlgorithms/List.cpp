#include "List.h"

// Добавить в список рассмотренную вершину u
void PushList(list *&L, int u)
{
	list *temp = L;
	L = new list;
	L->v = u;
	L->next = temp;
}

// Очистить список
void ClearList(list *&L)
{
	if (!L) return;										// Список пуст
	for (list *l; L; l = L, L = L->next, delete l);		// Список не пуст
	L = NULL;
}

// Добавление в стек вершины
void PushStack(stack *&top, int u, float w)
{
	stack *ptr = top;
	top = new stack;
	top->L = NULL;
	top->u = u;
	top->dist = w;
	top->next = ptr;
}

// Удаление элемента из стека
void PopStack(stack *&top)
{
	if (!top) return;
	stack *ptr = top;
	top = ptr->next;
	ClearList(ptr->L);
	delete ptr;
}
