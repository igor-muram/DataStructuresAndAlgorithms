#include "List.h"

// �������� � ������ ������������� ������� u
void PushList(list *&L, int u)
{
	list *temp = L;
	L = new list;
	L->v = u;
	L->next = temp;
}

// �������� ������
void ClearList(list *&L)
{
	if (!L) return;										// ������ ����
	for (list *l; L; l = L, L = L->next, delete l);		// ������ �� ����
	L = NULL;
}

// ���������� � ���� �������
void PushStack(stack *&top, int u, float w)
{
	stack *ptr = top;
	top = new stack;
	top->L = NULL;
	top->u = u;
	top->dist = w;
	top->next = ptr;
}

// �������� �������� �� �����
void PopStack(stack *&top)
{
	if (!top) return;
	stack *ptr = top;
	top = ptr->next;
	ClearList(ptr->L);
	delete ptr;
}
