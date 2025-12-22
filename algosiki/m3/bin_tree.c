#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct NODE
{
	int data;
	struct NODE* left;
	struct NODE* right;

} node;
typedef struct
{
	const char* name;
	NODE* root;
} tree;


tree* create_tree(const char * n)
{
	tree* t = (tree*)malloc(sizeof(tree));
	t->name = n;
	t->root = NULL;
	return t;

}
node* create_node(int data)
{
	node* n = (node*)malloc(sizeof(node));
	n->left = NULL;
	n->right = NULL;
	n->data = data;
	return n;
}

node* add_h(node * n,int d)
{
	if (n == NULL) return create_node(d);
	if (n->data < d) n->right = add_h(n->right, d);
	else if (n->data > d) n->left = add_h(n->left, d);
	return n;
}
void add_t(tree * t,int d)
{
	t->root = add_h(t->root,d);
}

node* search_h(node* n, int d)
{
	if (n == NULL || n->data == d) return n;
	if (n->data > d) return search_h(n->left,d);
	else return search_h(n->right,d);
}
node* search_t(tree* t, int d)
{
	return search_h(t->root, d);
}
node* find_min(node* n)
{
	node* t = n;
	if (t != NULL)
		while (t->left != NULL) t = t->left;
	return t;
}
node* del_h(node * n, int d)
{
	if (n == NULL) return n;
	if (d < n->data) n->left = del_h(n->left,d);
	else if (d > n->data) n->right = del_h(n->right,d);
	else
	{
		if (n->right == NULL)
		{
			node* t = n->left;
			free(n);
			return t;
			
		}
		if (n->left == NULL)
		{
			node* t = n->right;
			free(n);
			return t;
		}
		node* t = find_min(n->right);
		n->data = t->data;
		n->right=del_h(n->right,t->data);
	}
	return n;

}
void del_t(tree* t, int d)
{
	t->root = del_h(t->root, d);
}

bool is_empty(tree* t)
{
	return t->root == NULL;
}

void free_nodes(node* n)
{
	if (n != NULL)
	{
		free_nodes(n->left);
		free_nodes(n->right);
		free(n);
		n = NULL;
	}
}
void free_t(tree* t)
{
	free_nodes(t->root);
	free(t);
	t = NULL;
}
void print_tree_with_levels(node* n, int level) {
	if (n == NULL) return;

	print_tree_with_levels(n->right, level + 1);

	for (int i = 0; i < level; i++) {
		printf("   ");
	}
	printf("L%d:%d\n", level, n->data);

	print_tree_with_levels(n->left, level + 1);
}
bool is_root(tree* t)
{
	return (t->root != NULL && t->root->left == NULL && t->root->right == NULL);
}
void root(tree* t, tree* lt, tree* rt)
{
	lt->root = t->root->left;
	rt->root = t->root->right;
	t->root->left = NULL;
	t->root->right = NULL;
}
void LKP_h(node* n)
{
	if (n->left) LKP_h(n->left);
	printf("%d ", n->data);
	if (n->right) LKP_h(n->right);
}
void LKP_t(tree* t)
{
	LKP_h(t->root);
	putchar('\n');
}
int main()
{
	tree* T = create_tree("zxc");
	add_t(T,10);
	add_t(T, 6);
	add_t(T, 2);
	add_t(T, 15);
	add_t(T, 13);
	add_t(T, 17);
	add_t(T, -1);
	print_tree_with_levels(T->root, 0);
	LKP_t(T);
	node* f = search_t(T, 2);
	printf("f ptr: %d, data: %d\n", f, f->data);
	del_t(T, 6);
	LKP_t(T);
	tree* l = create_tree("lt");
	tree* r = create_tree("rt");
	root(T,l,r);
	print_tree_with_levels(T->root, 0);
	print_tree_with_levels(l->root, 0);
	print_tree_with_levels(r->root, 0);
	free_t(T);
	free_t(r);
	free_t(l);
}
