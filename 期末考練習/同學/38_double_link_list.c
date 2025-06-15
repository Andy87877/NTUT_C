#if 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dnode_s {
	int data;
	struct dnode_s* front;
	struct dnode_s* back;
} node_t;
typedef node_t* nodep_t;

void AddFront(nodep_t* linkList, int data)
{
	nodep_t node = (nodep_t)malloc(sizeof(node_t));
	node->data = data;

	if ((*linkList) == NULL)
	{
		(*linkList) = node;
		node->front = node->back = NULL;
		return;
	}

	node->front = NULL;
	node->back = *linkList;
	(*linkList)->front = node;

	*linkList = node;
}
void AddBack(nodep_t* linkList, int data)
{
	nodep_t node = (nodep_t)malloc(sizeof(node_t));
	node->data = data;

	if ((*linkList) == NULL)
	{
		(*linkList) = node;
		node->front = node->back = NULL;
		return;
	}

	nodep_t temp = *linkList;
	while (temp->back != NULL) temp = temp->back;
	node->front = temp;
	node->back = NULL;
	temp->back = node;
}
void RemoveFront(nodep_t* linkList)
{
	if ((*linkList) == NULL)
	{
		printf("Double link list is empty\n");
		return;
	}

	nodep_t node = (*linkList)->back;
	node->front = NULL;
	free(*linkList);

	*linkList = node;
}
void RemoveBack(nodep_t* linkList)
{
	if ((*linkList) == NULL)
	{
		printf("Double link list is empty\n");
		return;
	}

	nodep_t temp = *linkList;
	while (temp->back != NULL) temp = temp->back;

	if (temp->front == NULL)
	{
		free(temp);
		*linkList = NULL;
		return;
	}
	temp->front->back = NULL;
	free(temp);
}
void Empty(nodep_t* linkList)
{
	if ((*linkList) == NULL)
	{
		printf("Double link list is empty\n");
		return;
	}

	nodep_t temp = (*linkList)->back;
	while (temp != NULL)
	{
		free(temp->front);
		temp = temp->back;
	}
	free(temp);

	(*linkList) = NULL;
}
void Insert(nodep_t* linkList, int index, int data)
{
	if (linkList == NULL)
	{
		printf("Invalid command\n");
		return;
	}

	nodep_t temp = *linkList;
	for (int i = 0; i < index-1; i++)
	{
		if (temp == NULL)
		{
			printf("Invalid command\n");
			return;
		}
		temp = temp->back;
	}
	if (temp == NULL)
	{
		printf("Invalid command\n");
		return;
	}

	nodep_t node = (nodep_t)malloc(sizeof(node_t));
	node->data = data;

	if (temp->back == NULL)
	{
		temp->back = node;
		node->back = NULL;
		node->front = temp;

		return;
	}

	node->front = temp;
	node->back = temp->back;

	temp->back->front = node;
	temp->back = node;
}
void Remove(nodep_t* linkList, int index)
{
	if (linkList == NULL)
	{
		printf("Invalid command\n");
		return;
	}

	nodep_t temp = *linkList;
	for (int i = 0; i < index-1; i++)
	{
		if (temp == NULL)
		{
			printf("Invalid command\n");
			return;
		}
		temp = temp->back;
	}
	if (temp == NULL || temp->back==NULL)
	{
		printf("Invalid command\n");
		return;
	}


	temp->back->front = temp->front;
	temp->front->back = temp->back;
	free(temp);
}
void Print(nodep_t* linkList)
{
	nodep_t temp = *linkList;

	if ((*linkList) == NULL)
	{
		printf("Double link list is empty\n");
		return;
	}

	while (temp != NULL)
	{
		printf("%d\n", temp->data);
		temp = temp->back;
	}
}

int main()
{
	int n;
	scanf("%d", &n);

	nodep_t linkList = NULL;
	for (int i = 0; i < n; i++)
	{
		char command[16];
		scanf("%s", command);

		if (!strcmp(command, "addFront"))
		{
			int data;
			scanf("%d", &data);
			AddFront(&linkList, data);
		}
		if (!strcmp(command, "addBack"))
		{
			int data;
			scanf("%d", &data);
			AddBack(&linkList, data);
		}

		if (!strcmp(command, "removeFront"))
		{
			RemoveFront(&linkList);
		}
		if (!strcmp(command, "removeBack"))
		{
			RemoveBack(&linkList);
		}
		if (!strcmp(command, "empty"))
		{
			Empty(&linkList);
		}

		if (!strcmp(command, "insert"))
		{
			int index, data;
			scanf("%d%d", &index, &data);
			Insert(&linkList, index, data);
		}
		if (!strcmp(command, "remove"))
		{
			int index;
			scanf("%d", &index);
			Remove(&linkList, index);
		}
	
		if (!strcmp(command, "print"))
		{
			Print(&linkList);
		}

	}
}

#endif
