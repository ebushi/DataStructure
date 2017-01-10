/* Sequence Table */

#include "stdafx.h"
#define TableSize 100

struct SeqTable
{
	int Table[TableSize];
	int length;
};

typedef struct SeqTable SeqT;

void InitTable(SeqT *T)
{
	T->length = 0;
}

int EmptyTable(SeqT *T)
/* return 1: Empty Table; return 0: not empty */
{
	if (T->length == 0)
		return 1;
	return 0;
}

int GetElem(SeqT *T, int i)
{
	if (i<0 || i>T->length)
	{
		printf("can not find\n");
		return -1;
	}
	else
		return T->Table[i-1];
}

int InsertTable(SeqT *T, int i, int Elem)
/* return 1: insert success; return -1: insert fail */
{
	if (T->length == TableSize)
	{
		printf("Table full\n");
		return -1;
	}
	if (i<0 || i>T->length)
	{
		printf("wrong place\n");
		return -1;
	}

	if (i == T->length)
	{
		T->Table[i] = Elem;
		T->length++;
		return 1;
	}

	if (i >= 0 && i < T->length)
	{
		int j;

		for (j = T->length; j >= i; j--)
		{
			T->Table[j] = T->Table[j-1];
		}

		T->Table[i] = Elem;
		T->length++;

		return 1;
	}

}

int LocatElem(SeqT *T, int Elem)
/*return i-1: founded; return -1: not founded */
{
	int i;

	for (i = 0; i < T->length; i++)
	{
		if (T->Table[i] == Elem)
			return i+1;
	}

	return -1;
}

int DeleteElem(SeqT *T, int i)
/* return -1: delete fail; return 1: delete success */
{
	if (i<0 || i>T->length)
	{
		printf("wrong place\n");
		return -1;
	}

	if (i == T->length)
	{
		T->length = T->length - 1;
		return 1;
	}

	if (i < T->length)
	{
		int j;

		for (j = i; j < T->length; j++)
		{
			T->Table[j - 1] = T->Table[j];
		}

		T->length = T->length - 1;

		return 1;
	}

}

void ShowTable(SeqT *T)
{
	int i;
	for (i = 0; i < T->length; i++)
		printf("%2d", T->Table[i]);
}
int Length(SeqT *T)
{
	return T->length;
}

void ClearTable(SeqT *T)
{
	T->length = 0;
}

int main()
{
	SeqT T;
	InitTable(&T);
	
	for (int i = 0; i < 10; i++)
	{
		InsertTable(&T, i, i);		// test InsertTable
	}
	ShowTable(&T);					// test ShowTable
	printf("\nTable length = %d\n", Length(&T));

	DeleteElem(&T, 5);				// test DeleteElem
	ShowTable(&T);
	printf("\nTable length = %d\n", Length(&T));
	
	DeleteElem(&T, -1);

	printf("\n%d\n", GetElem(&T, 3)); 	// test GetElem

	printf("\n%d\n", LocatElem(&T, 7));	// test LocatElem

	ClearTable(&T);					// test ClearTable
	ShowTable(&T);
	printf("\nTable length = %d\n", Length(&T));

	return 0;
}