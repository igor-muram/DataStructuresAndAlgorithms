#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <string>
#include <vector>
#include "List.h"

using namespace std;
float max(0);								// Длина максимального простого пути
vector <string> cities;						// Список городов
size_t start, finish;						// Номера городов отправления и назначения в списке

struct wtable								// Список смежности графа
{
	int top;
	float weight;
	wtable *next;
};
vector <wtable*> wmas;

int Input()									// Ввод системы дорог
{
	string dep, dest, road_begin, road_end;
	size_t k, i, count(0);
	float w;								// w - длина текущей дороги
	wtable *p;
	ifstream in("Input.txt");
	if (!in.is_open()) return -1;			// Файл не найден
	if (!(in >> dep)) return -2;			// Файл пуст
	in >> dest;
	if (dep == dest) return -3;				// Города отправления и назначения совпадают 

	// Ввод информации о системе дорог
	for (bool flag; in >> road_begin;)
	{
		// Запись города-начала дороги в список городов
		for (i = 0, flag = 0; i < cities.size() && !flag; i++)
			flag = road_begin == cities[i];

		if (flag)
			i--;
		else
			cities.emplace_back(road_begin);

		// Запись города-конца дороги в список городов
		in >> road_end;
		for (k = 0, flag = 0; k < cities.size() && !flag; k++)
			flag = road_end == cities[k];

		if (flag)
			k--;
		else
			cities.emplace_back(road_end);

		in >> w;
		// Если дорога не петля, не идёт в город отправления, не идёт из города назначения
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

	// Поиск номера города в списке городов
	for (size_t N(cities.size()), i(0); i < N && count != 2; i++)
		cities[i] == dep ? start = i, count++ :
		cities[i] == dest ? finish = i, count++ : 0;

	// Город отправления и/или город назначения не найдены в маршруте
	if (count != 2) return -4;
	return 0;
}

// Поиск нерасcмотренной вершины
int Search(stack *S, wtable *mas, float *dist)
{
	int x, y(-1);								// x - вершина, смежная с текущей вершиной
	bool flag(true);							// для захода в цикл, чтобы искать новые дороги
	float w(0), d(0);							// d - длина дороги до города, если это конец пути
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
			// Проверяем, была ли пройдена найденная вершина в рассматриваемом пути
			for (stack *s(S); s && !flag; s->u == x ? flag = true : s = s->next);
			// Проверяем, был ли рассмотрен путь из пройденной вершины
			for (list *l(S->L); l && !flag; l->v == x ? flag = true : l = l->next);
		}
	}
	flag ? *dist = d : *dist = w;
	return flag ? y : x;
}

// Поиск максимального пути из города start в город finish
list *MaxRoad()
{
	list *Road(NULL); stack *S(NULL);
	int x, y;
	float w, d;
	// Пока существуют вершины, смежные со start, осуществляем их перебор
	for (wtable *use(wmas[start]); use; use = use->next)
	{
		x = use->top;
		w = use->weight;
		// Если start и finish соединены дорогой, проверяем, максимальная ли она
		if (x == finish)
		{
			w > max ? ClearList(Road), max = w : 0;
			// Если другие пути есть, то переходим на новый путь, иначе х = -1
			use->next ? use = use->next, x = use->top, w = use->weight : x = -1;
		}
		if (x != -1) PushStack(S, x, w);
		while (S)
		{
			x = S->u;							// Из стека берём город, в который идём
			w = S->dist;						// Из стека берём расстояние до этого города
			y = Search(S, wmas[x], &d);			// Берём нерасмотренную вершину, смежную с х
			if (y < 0) PopStack(S);
			else
				// Если очередной путь, ведущий в вершину-конец пути, рассмотрен
				if (y == finish)
				{
					// Если он больше записанного, перезаписываем ранее найденный и меняем длину
					if (d + w > max)
					{
						max = d + w;
						ClearList(Road);
						// Запись пути в список
						for (stack *s(S); s; PushList(Road, s->u), s = s->next);
					}
					PopStack(S);
				}
				else
				{
					PushList(S->L, y);			// Пометить вершину y, как рассмотренную
					PushStack(S, y, d + w);
				}
		}
	}
	return Road;
}

// Очищение списка смежности графа
void Clear()
{
	wtable *use, *p;
	for (size_t i(0), N(wmas.size()); i < N; wmas[i] = NULL, i++)
		for (use = wmas[i]; use; p = use, use = use->next, delete p);
}

// Вывод длины самого длинного простого пути
void PrintLength()
{
	ofstream out("LengthOfRoad.txt", ios::app);
	out << "Длина максимального простого пути из города " << cities[start] << " в город " << cities[finish] << " составляет: " << max << endl << endl;
	out.close();
}

// Вывод самого длинного простого пути
void PrintRoad(list *Road)
{
	ofstream out("Road.txt", ios::app);
	out << "Самый длинный простой путь из города " << cities[start] << " в город " << cities[finish] << ": " << cities[start] << " - ";
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
		if (!wmas[start]) cout << "Из города " << cities[start] << " нет простых путей\n\n";
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
				if (!max) cout << "Из города " << cities[start] << " нет пути в город " << cities[finish] << endl << endl;
				else
				{
					PrintLength(); 			// Вывод длины пути 
					PrintRoad(Road); 		// Вывод пути
				}
				ClearList(Road);			// Освобождаем выделенную для дороги память
			}
		break;
	case -1: cout << "Файл с информацией о системе дорог не найден\n\n"; break;
	case -2: cout << "Файл с информацией о системе дорог пуст\n\n"; break;
	case -3: cout << "Город отправления совпадает с городом назначения\n\n"; break;
	case -4: cout << "Город отправления и/или город назначения не найдены в маршруте\n\n"; break;
	}
	Clear();							// Освобождаем выделенную под список смежности память
	cities.~vector();					// Очищаем список городов
	wmas.~vector();						// Очищаем список смежности
	system("pause");
}