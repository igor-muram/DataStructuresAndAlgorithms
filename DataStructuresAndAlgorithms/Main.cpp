#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <string>
#include <vector>
#include "List.h"

using namespace std;
float max(0);								// ����� ������������� �������� ����
vector <string> cities;						// ������ �������
size_t start, finish;						// ������ ������� ����������� � ���������� � ������

struct wtable								// ������ ��������� �����
{
	int top;
	float weight;
	wtable *next;
};
vector <wtable*> wmas;

int Input()									// ���� ������� �����
{
	string dep, dest, road_begin, road_end;
	size_t k, i, count(0);
	float w;								// w - ����� ������� ������
	wtable *p;
	ifstream in("Input.txt");
	if (!in.is_open()) return -1;			// ���� �� ������
	if (!(in >> dep)) return -2;			// ���� ����
	in >> dest;
	if (dep == dest) return -3;				// ������ ����������� � ���������� ��������� 

	// ���� ���������� � ������� �����
	for (bool flag; in >> road_begin;)
	{
		// ������ ������-������ ������ � ������ �������
		for (i = 0, flag = 0; i < cities.size() && !flag; i++)
			flag = road_begin == cities[i];

		if (flag)
			i--;
		else
			cities.emplace_back(road_begin);

		// ������ ������-����� ������ � ������ �������
		in >> road_end;
		for (k = 0, flag = 0; k < cities.size() && !flag; k++)
			flag = road_end == cities[k];

		if (flag)
			k--;
		else
			cities.emplace_back(road_end);

		in >> w;
		// ���� ������ �� �����, �� ��� � ����� �����������, �� ��� �� ������ ����������
		if (road_begin != road_end && road_end != dep && road_begin != dest)
			if (i < wmas.size())
			{
				for (p = wmas[i]; p && p->top != k; p = p->next);
				if (!p)
				{
					p = wmas[i];
					wmas[i] = new wtable;
					wmas[i]->top = k;
					wmas[i]->weight = w;
					wmas[i]->next = p;
				}
				else w > p->weight ? p->weight = w : 0;
			}
			else
			{
				for (; wmas.size() < i; wmas.push_back(NULL));
				wmas.push_back(new wtable);
				wmas[i]->top = k;
				wmas[i]->weight = w;
				wmas[i]->next = NULL;
			}
	}
	for (in.close(); wmas.size() < cities.size(); wmas.push_back(NULL));
	wmas.shrink_to_fit();
	cities.shrink_to_fit();

	// ����� ������ ������ � ������ �������
	for (size_t N(cities.size()), i(0); i < N && count != 2; i++)
		cities[i] == dep ? start = i, count++ :
		cities[i] == dest ? finish = i, count++ : 0;

	// ����� ����������� �/��� ����� ���������� �� ������� � ��������
	if (count != 2) return -4;
	return 0;
}

// ����� �����c��������� �������
int Search(stack *S, wtable *mas, float *dist)
{
	int x, y(-1);								// x - �������, ������� � ������� ��������
	bool flag(true);							// ��� ������ � ����, ����� ������ ����� ������
	float w(0), d(0);							// d - ����� ������ �� ������, ���� ��� ����� ����
	for (; flag && mas; mas = mas->next)
	{
		flag = false;
		x = mas->top;
		w = mas->weight;
		if (x == finish)
		{
			y = x;
			d = w;
			flag = true;
		}
		else
		{
			// ���������, ���� �� �������� ��������� ������� � ��������������� ����
			for (stack *s(S); s && !flag; s->u == x ? flag = true : s = s->next);
			// ���������, ��� �� ���������� ���� �� ���������� �������
			for (list *l(S->L); l && !flag; l->v == x ? flag = true : l = l->next);
		}
	}
	flag ? *dist = d : *dist = w;
	return flag ? y : x;
}

// ����� ������������� ���� �� ������ start � ����� finish
list *MaxRoad()
{
	list *Road(NULL); stack *S(NULL);
	int x, y;
	float w, d;
	// ���� ���������� �������, ������� �� start, ������������ �� �������
	for (wtable *use(wmas[start]); use; use = use->next)
	{
		x = use->top;
		w = use->weight;
		// ���� start � finish ��������� �������, ���������, ������������ �� ���
		if (x == finish)
		{
			w > max ? ClearList(Road), max = w : 0;
			// ���� ������ ���� ����, �� ��������� �� ����� ����, ����� � = -1
			use->next ? use = use->next, x = use->top, w = use->weight : x = -1;
		}
		if (x != -1) PushStack(S, x, w);
		while (S)
		{
			x = S->u;							// �� ����� ���� �����, � ������� ���
			w = S->dist;						// �� ����� ���� ���������� �� ����� ������
			y = Search(S, wmas[x], &d);			// ���� �������������� �������, ������� � �
			if (y < 0) PopStack(S);
			else
				// ���� ��������� ����, ������� � �������-����� ����, ����������
				if (y == finish)
				{
					// ���� �� ������ �����������, �������������� ����� ��������� � ������ �����
					if (d + w > max)
					{
						max = d + w;
						ClearList(Road);
						// ������ ���� � ������
						for (stack *s(S); s; PushList(Road, s->u), s = s->next);
					}
					PopStack(S);
				}
				else
				{
					PushList(S->L, y);			// �������� ������� y, ��� �������������
					PushStack(S, y, d + w);
				}
		}
	}
	return Road;
}

// �������� ������ ��������� �����
void Clear()
{
	wtable *use, *p;
	for (size_t i(0), N(wmas.size()); i < N; wmas[i] = NULL, i++)
		for (use = wmas[i]; use; p = use, use = use->next, delete p);
}

// ����� ����� ������ �������� �������� ����
void PrintLength()
{
	ofstream out("LengthOfRoad.txt", ios::app);
	out << "����� ������������� �������� ���� �� ������ " << cities[start] << " � ����� " << cities[finish] << " ����������: " << max << endl << endl;
	out.close();
}

// ����� ������ �������� �������� ����
void PrintRoad(list *Road)
{
	ofstream out("Road.txt", ios::app);
	out << "����� ������� ������� ���� �� ������ " << cities[start] << " � ����� " << cities[finish] << ": " << cities[start] << " - ";
	for (; Road; out << cities[Road->v] << " - ", Road = Road->next);
	out << cities[finish] << endl << endl;
	out.close();
}

void main()
{
	setlocale(LC_ALL, "Russian");
	switch (Input())
	{
	case 0:
		if (!wmas[start]) cout << "�� ������ " << cities[start] << " ��� ������� �����\n\n";
		else
			if (cities.size() == 2)
			{
				max = wmas[start]->weight;
				PrintLength();
				PrintRoad(NULL);
			}
			else
			{
				list *Road = MaxRoad();
				if (!max) cout << "�� ������ " << cities[start] << " ��� ���� � ����� " << cities[finish] << endl << endl;
				else
				{
					PrintLength(); 			// ����� ����� ���� 
					PrintRoad(Road); 		// ����� ����
				}
				ClearList(Road);			// ����������� ���������� ��� ������ ������
			}
		break;
	case -1: cout << "���� � ����������� � ������� ����� �� ������\n\n"; break;
	case -2: cout << "���� � ����������� � ������� ����� ����\n\n"; break;
	case -3: cout << "����� ����������� ��������� � ������� ����������\n\n"; break;
	case -4: cout << "����� ����������� �/��� ����� ���������� �� ������� � ��������\n\n"; break;
	}
	Clear();							// ����������� ���������� ��� ������ ��������� ������
	cities.~vector();					// ������� ������ �������
	wmas.~vector();						// ������� ������ ���������
	system("pause");
}