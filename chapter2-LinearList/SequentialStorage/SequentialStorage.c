#include <stdio.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct{
	//ElemType *elem;
	int *elem;
	int length;
	int listsize;
}SqList;

int InitList_Sq(SqList *L);
int InsertList_Sq(SqList *L, int i, int number);
int DeleteList_Sq(SqList *L, int i, int *number);
int LocateElem_Sq(SqList L, int number, int *locate);
int MergeList_Sq(SqList L1, SqList L2, SqList *L3);

int main()
{
	SqList l;
	SqList l2;
	SqList l3;

	//1. init sqlist	
	InitList_Sq(&l);
	InitList_Sq(&l2);
	InitList_Sq(&l3);

	//2. insert 
	for(int j = 0;j<113;j++)
	{
		InsertList_Sq(&l, j+1, j);
		InsertList_Sq(&l2, j+1, j+5);
	}
	//printf("The length of sqlist:%d\n", l.length);
	//printf("The listsize of sqlist:%d\n", l.listsize);
	//for(int *p = l.elem;p < &(l.elem[l.length]); p++) printf("Nnumber %d\n", *p);
	//for(int *p = l2.elem;p < &(l2.elem[l2.length]); p++) printf("Nnumber %d\n", *p);

	//3. delete
	int deleteNum;
	DeleteList_Sq(&l, 3, &deleteNum);
	//printf("The length of sqlist:%d\n", l.length);
	//for(int *p = l.elem;p < &(l.elem[l.length]); p++) printf("Nnumber %d\n", *p);
	//printf("The delete Number is:%d\n", deleteNum);

	//4. locate
	int location;
	int locatenumber = 8;
	LocateElem_Sq(l, locatenumber, &location);
	//printf("The location of number %d is %d\n", locatenumber, location);

	//4. Merge two increment Sqlist to a increment Sqlist
	MergeList_Sq(l, l2, &l3);
	printf("The length of sqlist:%d\n", l3.length);
	printf("The listsize of sqlist:%d\n", l3.listsize);
	for(int *p = l3.elem;p < &(l3.elem[l3.length]); p++) printf("Nnumber %d\n", *p);

	return 0;

}

int InitList_Sq(SqList *L)
{
	L->elem = (int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if(!L->elem)
	{
		return -1;
	}
	L->length=0;
	L->listsize = LIST_INIT_SIZE;
	return 0;
}


int InsertList_Sq(SqList *L, int i, int number)
{
	if (i < 1 || i > L->length+1)
		return -1;
	if (L->length >= L->listsize)
	{
		int * newbase=(int *)realloc(L->elem, (L->listsize+LISTINCREMENT)*sizeof(int));
		if(!newbase)   return -1;
		L->elem = newbase;
		L->listsize += LISTINCREMENT;
	}

	int* q = &(L->elem[i-1]);
	
	for(int *p = &(L->elem[L->length-1]);p >= q; --p)   *(p+1) = *p;
	*q = number;
	++L->length;

	//printf("length of list:%d\n", L->length);
	//for(int *p = L->elem;p < &(L->elem[L->length]); p++) printf("Nnumber %d\n", *p);
	
	return 0;

}


int DeleteList_Sq(SqList *L, int i, int *number)
{
	if (i < 1 || i > L->length)  return -1;
	if (L->length == 0) return -1;
	
	int * p = &(L->elem[i-1]);
	*number = *p;

	for(++p; p <= &(L->elem[L->length -1]); ++p) *(p-1) = *p;
	L->length -= 1;
	
	return 0;

}


int LocateElem_Sq(SqList L, int number, int *locate)
{
	int temp = 0;
	for(int i = 0; i < L.length; i++)
	{
		if (L.elem[i] == number)
		{
			*locate = i+1;
			temp = 1;
			break;
		}
	}
	
	if(temp == 0)  *locate = 0;

	return 0;
	
}

int MergeList_Sq(SqList L1, SqList L2, SqList *L3)
{
	int * p1 = L1.elem;
	int * p2 = L2.elem;

	L3->length = L3->listsize = L1.length+L2.length;
	if(!L3->elem) return -1;
	int * pc = L3->elem=(int *)realloc(L3->elem,sizeof(L3->listsize)/sizeof(int));

	while(p1 <= &(L1.elem[L1.length - 1]) && p2 <= &(L2.elem[L2.length - 1]))
	{
		if(*p1 <= *p2)
		{
			*pc = *p1;
			p1++;
		}else{
			*pc = *p2;
			p2++;
		}
		pc++;

	}

	while(p1 <= &(L1.elem[L1.length - 1])) *pc++ = *p1++;
	while(p2 <= &(L2.elem[L2.length - 1])) *pc++ = *p2++;
	
	return 0;
}
