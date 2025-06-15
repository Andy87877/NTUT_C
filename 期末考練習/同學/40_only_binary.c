#if 0

#include <Stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
	char data;
	struct node_s* right, * left;
} tree_t;
typedef tree_t* btree;


btree AddNode(char data)
{
	btree node = (btree)malloc(sizeof(tree_t));
	node->data = data;
	node->left = node->right = NULL;
	return node;
}

int FindIndex(char* str, int left, int right, char data)
{
	for (int i = left; i <= right; i++)
	{
		if (str[i] == data)
			return i;
	}
	return -1;
}

btree BuildFromPreIn(char* pre, int preL, int preR, char* in, int inL, int inR)
{
	if (preL > preR || inL > inR) return NULL;

	btree root = AddNode(pre[preL]);
	int mid = FindIndex(in, inL, inR, pre[preL]);
	int leftSize = mid - inL;

	root->left = BuildFromPreIn(pre, preL + 1, preL + leftSize, in, inL, mid - 1);
	root->right = BuildFromPreIn(pre, preL + leftSize + 1, preR, in, mid + 1, inR);

	return root;
}
btree BuildFromPostIn(char* post, int postL, int postR, char* in, int inL, int inR)
{
	if (postL > postR || inL > inR) return NULL;

	btree root = AddNode(post[postR]);
	int mid = FindIndex(in, inL, inR, post[postR]);
	int leftSize = mid - inL;

	root->left = BuildFromPostIn(post, postL, postL + leftSize - 1, in, inL, mid - 1);
	root->right = BuildFromPostIn(post, postL + leftSize, postR - 1, in, mid + 1, inR);

	return root;
}

void PrintTree(btree tree)
{
	if (tree == NULL) return;

	btree queue[100];
	int front = 0, rear = 0;
	queue[rear++] = tree;

	while (front < rear)
	{
		btree node = queue[front++];
		printf("%c", node->data);
		if (node->left) queue[rear++] = node->left;
		if (node->right) queue[rear++] = node->right;
	}
}

int main()
{
	btree tree = NULL;

	char type1[2], data1[21], type2[2], data2[21];
	scanf("%s%s %s%s", type1, data1, type2, data2);

	char pre[21] = { 0 }, post[21] = { 0 }, in[21] = { 0 };
	if (type1[0] == 'P') strcpy(pre, data1);
	if (type1[0] == 'I') strcpy(in, data1);
	if (type1[0] == 'O') strcpy(post, data1);
	if (type2[0] == 'P') strcpy(pre, data2);
	if (type2[0] == 'I') strcpy(in, data2);
	if (type2[0] == 'O') strcpy(post, data2);

	if (pre[0] == 0) tree = BuildFromPostIn(post, 0, strlen(post)-1, in, 0, strlen(in)-1);
	if (post[0] == 0) tree = BuildFromPreIn(pre, 0, strlen(pre)-1, in, 0, strlen(in)-1);

	PrintTree(tree);
}

#endif
