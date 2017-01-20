#include <stdio.h>
#include <stdlib.h>


struct List {
	struct List* next;
	struct List* last;
};

struct Student {
	int key0;
	int key1;
	int key2;
	int key3;
	struct List list;
	int key4;
	int key5;
};

void test() {
	struct Student s1;
	struct Student s2;
	s1.list.next = &s2.list;
	s2.list.last = &s1.list;
	s2.key0 = 999;

	struct List *ptr = s1.list.next;

	int offset = &((struct Student*)0)->list;
	printf("%d\n", offset);
	struct Student *s3 = (struct Student*)((char*)ptr - &((struct Student*)0)->list);
	printf("%d\n", s3->key0);
}


void main() {
	int *a, b;
	test();
}