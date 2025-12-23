#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NODE
{
	int data;
	NODE* next;
} node;

typedef struct
{
	node* top;
	int size;
} stack;

stack* init()
{
	stack* t = (stack*)malloc(sizeof(stack));
	t->size = 0;
	t->top = NULL;
	return t;
}
bool is_empty(stack* s)
{
	return (s->size == 0);
}
void push(stack * s, int d)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->data = d;
	new_node->next = s->top;
	s->top = new_node;
	s->size++;
}
bool pop(stack* t,int* v)
{
	if (is_empty(t)) { printf("pop error. stack empty\n"); return false; }
	node* temp = t->top;
	*v = temp->data;
	t->top = temp->next;
	t->size--;
	free(temp);
	return true;
}

bool peek(stack* s, int* v)
{
	if (is_empty(s))
	{
		printf("peek error. stack empty\n"); return false;
	}
	*v = s->top->data;
	return true;
}


int get_size(stack * s)
{
	return s->size;
}

void print_stack(stack * s)
{
	if (is_empty(s)) { printf("stack empty\n"); return; }
	node* temp = s->top;
	while (temp != NULL)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
	putchar('\n');
}
void free_stack(stack * s)
{
	node* n = s->top;
	node* temp;
	while (n != NULL)
	{
		temp = n->next;
		free(n);
		n = temp;
	}
	free(s);
}
int main()
{
	stack* a = init();
	push(a,10);
	push(a,5);
	push(a,3);
	push(a,-10);
	int p;
	pop(a, &p);
	printf("pop %d\n", p);
	push(a, 3);
	push(a, 1000);
	printf("size:%d\n", get_size(a));
	push(a, 1);
	peek(a, &p);
	printf("peek %d\n", p);
	push(a, 11);
	print_stack(a);
	free(a);

}
