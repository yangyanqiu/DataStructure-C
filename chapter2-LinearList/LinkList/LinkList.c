#include<stdio.h>
#include<stdlib.h>

typedef struct LNode{
	int data;
	struct LNode * next;
}LNode, *LinkList;

void CreateList(LinkList *L, int n);
void InsertList(LinkList L, int n, int number);
void GetList(LinkList L, int i, int *number);

int main()
{
	LinkList l1;
	int  n = 3;

	//1. Create Link List
	CreateList(&l1, n);

	//2. Insert a Node
	//InsertList(l1, 2, 55);

	//3. Get List element
	//int number = 0;
	//GetList(l1, 2, &number);

	//printf("Get the second element's data is %d\n", number);

	LinkList p = l1;
	while(p != NULL)
	{
		printf("data: %d\n", p->data);
		p = p->next;
	}

	return 0;
}

void CreateList(LinkList* L, int n)
{
	*L = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;
		
	for(int i = n; i > 0; i--)
	{
		LinkList p = (LinkList)malloc(sizeof(LNode));
		if(!p) printf("failed to malloc space!!");
		p->data = i;
		//printf("p->data: %d\n", p->data);
		p->next = (*L)->next;
		(*L)->next = p;
	}

}

void InsertList(LinkList L, int n, int number)
{
	LinkList p = L;

	for(int i = 0; i < n-1 && p != NULL; i++) p = p->next;

	if(!p) exit(-1);

	LinkList newLink = (LinkList)malloc(sizeof(LNode));
	newLink->data = number;
	newLink->next = p->next;
	p->next = newLink;
}

void GetList(LinkList L, int i, int *number)
{
	LinkList p = L;

	for(int j = 0;j < i && p != NULL; j++) p = p->next;

	if(!p) exit(-1);

	*number = p->data;
}
