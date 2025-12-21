#define _CRT_SECURE_NO_WARNINGS
#define START_CAP 10
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
typedef struct
{
	int key;
	const char* inf;
} item;


typedef struct
{
	const char* name;
	item* list;
	int size;
	int capacity;
} table;



void init(table* t,const char* n)
{
	t->list = (item*)malloc(START_CAP*sizeof(item));
	t->capacity = START_CAP;
	t->size = 0;
	t->name = n;
	printf("Initialization table: %s\n", n);
}
void resize(table* t, int new_cop)
{
	item* temp = t->list;
	t->list = (item*)realloc(t->list,new_cop*sizeof(item));
	if (t->list)
	{
		t->capacity = new_cop; printf("succes resize %s to %d", t->name, new_cop);
	}
	else
	{
		t->list = temp; printf("resize error %s", t->name); exit(1);
	}
}
void add(table* t, int k, const char* in)
{
	if (t->size >= t->capacity)
	{
		resize(t, t->capacity * 2);
	}
	t->list[t->size] = item { k,in };
	t->size++;
	printf("add key:%d inf:%s in table %s\n",k,in,t->name);
}
int find(table* t, int key)
{
	for (int i = 0; i < t->size; i++)
	{
		if (t->list[i].key == key) 
		{
			printf("key %d found in table %s [%d]: info {%s}\n",key,t->name,i,t->list[i].inf);
			return i;
		}
	}
	printf("key %d not found in table %s\n",key,t->name);
	return -1;
}
bool del(table* t,int key)
{
	printf("del: ");
	int ind = find(t, key);
	if (ind != -1)
	{
		t->list[ind] = t->list[t->size - 1];
		t->size--;
		printf("delete key %d in table %s\n", key, t->name);
		return true;
	}
	return false;
}
bool empty(table* t)
{
	if (t->size)
	{
		printf("table %s not empty\n", t->name); return 1;
	}
	else
	{
		printf("table %s empty\n", t->name);
	}
}
void freet(table* t)
{
	printf("free table %s\n", t->name);
	t->name = NULL;
	t->size = 0;
	t->capacity = START_CAP;
	free(t->list);
	t->list = NULL;
}

void outtable(table * t)
{
	printf("-----------TABLE %s----------\n", t->name);
	int mlk = 0,l,k;
	for (int i = 0; i < t->size; i++) {
		k = t->list[i].key;
		if (k == 0)
			l = 1;
		else
		{
			l = (int)log10(abs(k)) + 1;
			if (k < 0) l++;
		}

		if (l > mlk) mlk = l;
	}
	for (int i = 0; i < t->size; i++)
	{
		printf("key: %*d info: %s\n",mlk,t->list[i].key,t->list[i].inf);
	}
	printf("-------------------\n");
}



int main()
{
	table* A=(table*)malloc(sizeof(table));
	init(A,"ovoshi");
	empty(A);
	add(A,3, "apple");
	empty(A);
	add(A, 4, "ananas");
	add(A, -1, "grusha");
	add(A, 1, "arbuz");
	add(A, 5, "amogus");
	add(A, 11, "pomidor");
	add(A, 999, "ogurez");
	printf("f %d\n", find(A, 4));
	outtable(A);
	
	del(A,1);

	outtable(A);

	del(A, 11);

	outtable(A);


	freet(A);
	free(A);
}
