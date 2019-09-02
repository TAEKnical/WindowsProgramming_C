#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
	int coef;
	int expon;
	struct ListNode* link;
}ListNode;

typedef struct ListHeader {
	int length;
	ListNode* head;
	ListNode* tail;
}ListHeader;

void init(ListHeader* plist) {
	plist->length = 0;
	plist->head = plist->tail = NULL;
}

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void insert_node_last(ListHeader* plist, int coef, int expon) {
	ListNode* tmp = (ListNode*)malloc(sizeof(ListNode));
	if (tmp == NULL) error("메모리 할당 에러");
	tmp->coef = coef;
	tmp->expon = expon;
	tmp->link = NULL;
	if (plist->tail == NULL) {
		plist->head = plist->tail = tmp;
	}
	else {
		plist->tail->link = tmp;
		plist->tail = tmp;
	}
	plist->length++;
}

void poly_add(ListHeader* plist1, ListHeader* plist2, ListHeader* plist3) {
	ListNode* a = plist1->head;
	ListNode* b = plist2->head;
	
	int sum;
	while (a != NULL && b != NULL) {
		if (a->expon == b->expon) {
			sum = a->coef + b->coef;
			if (sum != 0)
				insert_node_last(plist3, sum, a->expon);
			a = a->link;
			b = b->link;
		}
		else if (a->expon > b->expon) {
			insert_node_last(plist3, a->coef, a->expon);
			a = a->link;
		}

		else {
			insert_node_last(plist3, b->coef, b->expon);
			b = b->link;
		}
	}

	if (a != NULL) {
		for (; a != NULL; a = a->link) {
			insert_node_last(plist3, a->coef, a->expon);
		}
	}

	if (b != NULL) {
		for (; b != NULL; b = b->link) {
			insert_node_last(plist3, b->coef, b->expon);
		}
	}
}

void display(ListHeader* plist) {
	ListNode* p = plist->head;
	for (; p; p = p->link) {
		printf("%d %d\n", p->coef, p->expon);
	}
}

main() {
	ListHeader list1, list2, list3;

	init(&list1);
	init(&list2);
	init(&list3);

	insert_node_last(&list1, 3, 12);
	insert_node_last(&list1, 2, 8);
	insert_node_last(&list1, 1, 0);

	insert_node_last(&list2, 8, 12);
	insert_node_last(&list2, -3, 10);
	insert_node_last(&list2, 10, 6);

	poly_add(&list1, &list2, &list3);
	display(&list3);
}