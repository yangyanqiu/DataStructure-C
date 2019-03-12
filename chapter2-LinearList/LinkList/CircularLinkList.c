#include<stdio.h>
#include<stdlib.h>

typedef struct LNode{
	int data;
	struct LNode * next;
}LNode, *LinkList;

void CreateList(LinkList * L, int n);
void MergeList(LinkList * L1, LinkList * L2, LinkList *L3);

int main()
{
	LinkList l1;
	LinkList l2;
	LinkList l3;

	CreateList(&l1, 3);
	CreateList(&l2, 1);

	LinkList p = l2->next;
	while(p != l2)
	{
		printf("data2: %d\n", p->data);
		p = p->next;
	}

	MergeList(&l1, &l2, &l3);
	p = l3->next;
	while(p != l3)
	{
		printf("data: %d\n", p->data);
		p = p->next;
	}

	return 0;

}

void CreateList(LinkList * L, int n)
{
	*L = (LinkList)malloc(sizeof(LNode));
	(*L)->next = *L;
	
	LinkList p = *L;
	LinkList tail = p;
	LinkList temp;

	for(int i = n; i > 0; i--)
	{
		temp = (LinkList)malloc(sizeof(LNode));
		temp->data = i;
		temp->next = p;
		tail->next = temp;
		p = temp;
	}

	*L = tail;
}

void MergeList(LinkList * L1, LinkList * L2, LinkList *L3)
{
	 LinkList p1 = (*L1)->next;
	 LinkList p2 = *L2;

	 *L3 = p2;

	 while(p1->next != *L1) p1 = p1->next;

	p1->next = p2->next;
	p2->next = (*L1)->next;
	
	free(*L1);
}
