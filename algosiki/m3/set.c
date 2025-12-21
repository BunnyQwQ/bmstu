#define _CRT_SECURE_NO_WARNINGS
#define START_COP 10
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct {
	const char* name;
	int* slist;
	int size;
	int copacity;
} dset;




void indset(dset* s,const char* n)
{
	s->slist = (int*)malloc(sizeof(int)*START_COP);
	s->size = 0;
	s->copacity = START_COP;
	s->name = n;
	printf("initialization dset: %s\n",s->name);
}
void resizedset(dset *s,int new_cap)
{
	int* temp = s->slist;
	s->slist = (int*)realloc(s->slist,sizeof(int)*new_cap);
	if (s->slist)
	{
		s->copacity = new_cap;
		printf("resize dset: %s new cap: %d\n",s->name,new_cap);
	}
	else
	{
		printf("resize error\n");
		s->slist = temp;
	}
}
void Nulldset(dset* s)
{
	free(s->slist);
	printf("Null dset: %s\n", s->name);
	s->slist = NULL;
	s->size = 0;
	s->copacity = START_COP;
	s->name = NULL;
}
bool emptydset(dset* s)
{
	if (s->size == 0) { printf("dset %s - empty\n", s->name); return true; }
	else { printf("dset %s - not empty\n", s->name); return false; }
}
bool findeldset(dset* s,int el)
{
	for (int i = 0; i< s->size; i++)
		if (s->slist[i] == el) { printf("find el %d in dset %s\n", el, s->name); return true; }
	printf("not find el %d in dset %s\n", el, s->name); return false; 
}
void uaddeldset(dset* s, int el)
{
	if (s->size >= s->copacity)
	{
		resizedset(s, s->copacity * 2);
	}
	s->slist[s->size] = el;
	s->size++;
	printf("el %d add in dset: %s\n", el, s->name);
}
bool addeldset(dset* s, int el)
{
	if (findeldset(s,el)) { printf("el %d not add, already exist in dset: %s\n",el,s->name); return false; }
	uaddeldset(s, el);
	return true;
}
bool deleldset(dset * s, int el)
{
	for (int i = 0; i < s->size; i++)
	{
		if (s->slist[i] == el)
		{
			for (int j = i; j < s->size - 1; j++)
				s->slist[j] = s->slist[j + 1];
			s->size--;
			printf("del %d in dset: %s\n", el, s->name);
			return true;
		}
	}
	printf("del not found el %d in dset: %s\n", el, s->name);
	return false;
}
void showset(dset* s)
{
	printf("dset %s: ",s->name);
	for (int i = 0; i < s->size; i++) printf("%d ", s->slist[i]);
	putchar('\n');
}

dset *undset(dset * a,dset * b,const char* name)
{ 
	printf("\ndsets %s & %s union create\n----------------------\n",a->name,b->name);
	dset * u = (dset*)malloc(sizeof(dset));
	dset *maxs,*mins;
	if (a->size > b->size)
	{
		maxs = a; mins = b;
	}
	else
	{
		maxs = b; mins = a;
	}
	u->name = name;
	u->copacity = maxs->copacity;
	u->size = maxs->size;
	u->slist = (int*)malloc(maxs->copacity*sizeof(int));
	printf("initialization dset: %s\n", u->name);
	memcpy(u->slist,maxs->slist,u->size*sizeof(int));
	printf("copy els in %s from: %s",u->name,maxs->name);
	printf("add els in %s from: %s", u->name, mins->name);
	for (int i = 0; i < mins->size; i++)
	{
		addeldset(u, mins->slist[i]);
	}
	printf("-----------------------\n");
	return u;
	
}
dset *intersectdset(dset* a, dset* b, const char* name)
{
	printf("\ndsets %s & %s intersection create\n----------------------\n", a->name, b->name);
	dset* t = (dset*)malloc(sizeof(dset));
	indset(t, name);
	for (int i = 0; i < a->size; i++)
	{
		if (findeldset(b, a->slist[i])) uaddeldset(t, a->slist[i]);
	}
	printf("-----------------------\n");
	return t;

}
dset *diffdset(dset* base, dset* deduct, const char* name)
{
	printf("\ndsets %s - %s diffirence create\n----------------------\n", base->name, deduct->name);
	dset* d = (dset*)malloc(sizeof(dset));
	indset(d, name);
	for (int i = 0; i < base->size; i++)
	{
		if (!findeldset(deduct, base->slist[i])) uaddeldset(d, base->slist[i]);
	}
	printf("-----------------------\n");
	return d;

}


int main()
{
	dset *M = (dset*)malloc(sizeof(dset));
	dset *N = (dset*)malloc(sizeof(dset));
	indset(M,"Mn1");
	emptydset(M);
	addeldset(M,3);
	emptydset(M);
	deleldset(M,2);
	addeldset(M, 4);
	addeldset(M, 5);
	addeldset(M, 4);
	addeldset(M, 6);
	addeldset(M, 7);
	addeldset(M, -8);
	addeldset(M, 9);
	addeldset(M, 12);
	addeldset(M, 1);
	addeldset(M, -5);
	addeldset(M, 6);
	deleldset(M, 7);
	showset(M);
	addeldset(M, 18);
	addeldset(M, 999);
	addeldset(M, -4);
	showset(M);
	indset(N,"Nn1");
	addeldset(N, 15);
	addeldset(N, 16);
	addeldset(N, 17);
	addeldset(N, 18);
	addeldset(N, 19);
	addeldset(N, 20);
	addeldset(N, 21);
	addeldset(N, 22);
	addeldset(N, 7);
	addeldset(N, 24);
	addeldset(N, 25);
	addeldset(N, 9);
	addeldset(N, 1001);
	showset(N);
	dset *U = undset(M,N,"Umn");
	showset(U);
	dset* I = intersectdset(M, N, "Imn");
	showset(I);
	dset* D = diffdset(M, N, "Dmn");
	showset(D);
	dset* A = diffdset(N, M, "Amn");
	showset(A);

	Nulldset(M);
	Nulldset(N);
	Nulldset(U);
	Nulldset(I);
	Nulldset(D);
	Nulldset(A);
	free(M);free(N);free(U);free(I);free(D);free(A);
}
