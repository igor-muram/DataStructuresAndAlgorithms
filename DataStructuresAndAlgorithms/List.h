#pragma once
#include <stdio.h>

// ����������� ���� �������� ������, ������� ����� ������� ������� ������������� �����
struct list
{
	int v;
	list *next;
};

struct stack
{
	int u;								// �������� ������� �����
	float dist;							// ���������� �� �������
	stack *next;						// ��������� �� ��������� ����� � �����
	list *L;							// �������� ������ L
};

void PushStack(stack *&, int, float);	// �������� ������� � ���� 
void PopStack(stack *&);				// �������� �������� �� �����
void PushList(list *&, int);			// �������� � ������ ������������� �������
void ClearList(list *&);				// �������� ������
