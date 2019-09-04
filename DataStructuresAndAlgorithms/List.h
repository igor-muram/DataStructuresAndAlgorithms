#pragma once
#include <stdio.h>

// Определение типа элемента списка, который будет хранить вершины просмотренных путей
struct list
{
	int v;
	list *next;
};

struct stack
{
	int u;								// Хранение вершины графа
	float dist;							// Расстояние до вершины
	stack *next;						// Указатель на следующее звено в стеке
	list *L;							// Хранение списка L
};

void PushStack(stack *&, int, float);	// Добавить вершину в стек 
void PopStack(stack *&);				// Удаление элемента из стека
void PushList(list *&, int);			// Добавить в список рассмотренную вершину
void ClearList(list *&);				// Очистить список
