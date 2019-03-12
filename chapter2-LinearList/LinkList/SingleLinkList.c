#include<stdio.h>
#include<stdlib.h>

typedef struct LNode{
	int data;
	struct LNode * next;
}LNode, *LinkList;

void CreateList(LinkList *L, int n);
void InsertList(LinkList *L, int n, int number);
void GetList(LinkList *L, int i, int *number);
void DeleteList(LinkList *L, int i, int *number);
void MergeList(LinkList *L1, LinkList *L2, LinkList *L3);

int main()
{
	LinkList l1, l2, l3;
	int  n = 3;

	//1. Create Link List
	CreateList(&l1, n);
	CreateList(&l2, 6);

	//2. Insert a Node
	InsertList(&l1, 2, 1);

	//3. Get List element
	int number = 0;
	GetList(&l1, 2, &number);
	printf("Get the second element's data is %d\n", number);

	//3. Delete node
	DeleteList(&l1, 3, &number);
	//printf("Delete the %d element's data is %d\n", 3, number);

	//print all datas of linklist l1	
	LinkList p = l1->next;
	while(p != NULL)
	{
		printf("l1 data: %d\n", p->data);
		p = p->next;
	}

	//print all datas of linklist l2
	p = l2->next;
	while(p != NULL)
	{
		printf("l2 data: %d\n", p->data);
		p = p->next;
	}

	//4. Merge two list
	MergeList(&l1, &l2, &l3);

	//print all datas of linklist l3 after merged
	printf("merge l1 and l2 into l3...\n");
	p = l3->next;
	while(p != NULL)
	{
		printf("l3 data: %d\n", p->data);
		p = p->next;
	}

	return 0;
}

void CreateList(LinkList* L, int n)
{
	*L = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;
		
	for(int i = n; i > 0; --i)
	{
		LinkList p = (LinkList)malloc(sizeof(LNode));
		if(!p) printf("failed to malloc space!!");
		p->data = i;
		p->next = (*L)->next;
		(*L)->next = p;
	}

}

void InsertList(LinkList *L, int n, int number)
{
	LinkList p = *L;

	for(int i = 0; i < n-1 && p != NULL; i++) p = p->next;

	if(!p) exit(-1);

	LinkList newLink = (LinkList)malloc(sizeof(LNode));
	newLink->data = number;
	newLink->next = p->next;
	p->next = newLink;
}

void GetList(LinkList *L, int i, int *number)
{
	LinkList p = *L;

	for(int j = 0;j <= i-1 && p != NULL; j++) p = p->next;

	if(!p) exit(-1);

	*number = p->data;
}

void DeleteList(LinkList *L, int i, int *number)
{
	LinkList p = *L;

	for(int j = 0; j < i-1 && p != NULL; j++) p = p->next;

	if(!p) 
	{
		printf("The length of the link list is less than %d\n", i);
		exit(-1);
	}

	*number = p->next->data;

	LinkList temp = p->next;
	p->next = p->next->next;
	free(temp);
}


void MergeList(LinkList *L1, LinkList *L2, LinkList *L3)
{
	LinkList p1 = (*L1)->next;
	LinkList p2 = (*L2)->next;
	LinkList p3 = *L3 = *L1;
	
	while(p1 && p2)
	{
		if (p1->data <= p2->data)
		{
			p3->next = p1;
			p3 = p1;
			p1 = p1->next;
		}else{
			p3->next = p2;
			p3 = p2;
			p2 = p2->next;
		}
	}

	p3->next = p1?p1:p2;
	//while(p1) p3->next = p1;
	//while(p2) p3->next = p2;
	LinkList temp = *L2;
	free(temp);

}
