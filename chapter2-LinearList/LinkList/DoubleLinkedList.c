#include<stdio.h>
#include<stdlib.h>

typedef struct DuLNode{
	int data;
	struct DuLNode * prev;
	struct DuLNode * next;

}DuLNode, *DuLNodeList;

void CreateDoubleLinkedList(DuLNodeList * L, int n);
void InsertDoubleLinkedList(DuLNodeList * L, int n, int number);
void DeleteDoubleLinkedList(DuLNodeList * L, int n, int * number);

int main()
{
	DuLNodeList l1;
	int deleteNumber;

	CreateDoubleLinkedList(&l1, 10);
	InsertDoubleLinkedList(&l1, 10, 55);
	DeleteDoubleLinkedList(&l1, 2, &deleteNumber);

	
	DuLNodeList temp = l1->next;
	while(temp != NULL){
		printf("data l1: %d\n", temp->data);
		temp = temp->next;
	}

	return 0;
}

void CreateDoubleLinkedList(DuLNodeList *L, int n)
{
	DuLNodeList p;

	p = (DuLNodeList)malloc(sizeof(DuLNode));
	if(!p) exit(-1);
	p->next = NULL;
	p->prev = NULL;
	
	while(n > 0)
	{
		DuLNodeList temp = (DuLNodeList)malloc(sizeof(DuLNode));
		if(!temp) exit(-1);
		
		temp->data = n;
		temp->next = p->next;
		temp->prev = p;
		if(p->next)  p->next->prev = temp;
		p->next = temp;
		n--;
		//printf("temp %d\n", p->next->data);
	}

	*L = p;
}

void InsertDoubleLinkedList(DuLNodeList * L, int n, int number)
{
	DuLNodeList p = (*L)->next;
	int i = 0;

	while(i < n-1 && p != NULL)
	{
		p = p->next;
		i++;
	}

	if(!p) exit(-1);
	
	DuLNodeList temp = (DuLNodeList)malloc(sizeof(DuLNode));
	temp->data  = number;
	temp->next = p;
	temp->prev = p->prev;
	p->prev->next = temp;
	p->prev = temp;
}

void DeleteDoubleLinkedList(DuLNodeList * L, int n, int * number)
{
	DuLNodeList p = (*L)->next;
	int i = 0;

	while(i < n-1 && p != NULL)
	{
		p = p->next;
		i++;
	}

	if(!p) exit(-1);

	*number = p->data;
	DuLNodeList temp = p;
	p->prev->next = p->next;
	p->next->prev = p->prev;

	free(temp);
}
