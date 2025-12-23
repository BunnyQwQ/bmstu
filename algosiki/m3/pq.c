#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 100
typedef struct
{
	int data;
	int prior;
} el;

typedef struct
{
	el* list;
	int size;
} pq;

pq* init_pq()
{
	pq* q = (pq*)malloc(sizeof(pq));
	q->size = 0;
	q->list = (el*)malloc(MAX_SIZE * sizeof(el));
	return q;
}
bool is_empty(pq* q)
{
	return q->size == 0;
}

int get_size(pq* q)
{
	return q->size;
}
void copy_el(el* a, el* b)
{
	a->data = b->data;
	a->prior = b->prior;
}
bool pop(pq* q,int* v)
{
	if (is_empty(q)) { printf("pop error. q empty\n"); return false; }
	*v = q->list[0].data;
	printf("pop el %d[%d]\n", *v, q->list[0].prior);
	for (int i = 0; i < q->size - 1; i++)
	{
		copy_el(&q->list[i],&q->list[i+1]);
	}
	q->size--;
	return true;
}
void push(pq* q, int d, int p)
{
	if (is_empty(q)) { q->list[0].data = d; q->list[0].prior = p; q->size++; return; }
	int ind = 0;
	while (ind < q->size && p<=q->list[ind].prior) { ind++; }
	for (int j = q->size; j > ind; j--)
	{
		copy_el(&q->list[j], &q->list[j - 1]);
	}
	q->list[ind].data = d;
	q->list[ind].prior = p;
	q->size++;
}

bool peek_top(pq* q,int *v)
{
	if (is_empty(q)) { printf("peek error. q empty\n"); return false; }
	*v = q->list[0].data;
	printf("peek_t el %d[%d]\n", *v, q->list[0].prior);
	return true;
}
bool peek_end(pq* q,int *v)
{
	if (is_empty(q)) { printf("peek error. q empty\n"); return false; }
	*v = q->list[q->size-1].data;
	printf("peek_t el %d[%d]\n", *v, q->list[q->size-1].prior);
	return true;
}
void print_pq(pq* q)
{
	printf("pq: ");
	el* ar = q->list;
	for (int i = 0; i < q->size; i++)
	{
		printf("%d[%d] ",ar[i].data,ar[i].prior);
	}
	putchar('\n');
}


void free_pq(pq* q)
{
	free(q->list);
	free(q);
	q = NULL;
}

int main()
{
	int v;
	pq* q = init_pq();
	push(q,1,1);
	push(q,10,1);
	push(q, 6, 1);
	print_pq(q);
	push(q, 2, 1);
	push(q, 3, 2);
	push(q, -7, 2);
	push(q, 100, 1);
	push(q, 4, 2);
	print_pq(q);
	pop(q,&v);
	pop(q, &v);
	peek_end(q,&v);
	push(q, 8, 4);
	print_pq(q);
	free_pq(q);
}
