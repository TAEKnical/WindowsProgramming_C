#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

typedef int element;
typedef struct DlistNode {
	element data;
	struct DlistNode* llink;
	struct DlistNode* rlink;
}DlistNode;

void init(DlistNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

void display(DlistNode* phead) {
	DlistNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<----| %x | %d | %x | ---->\n", p->llink, p->data, p->rlink);
	}
}

//before와 before+1 사이에 insert
void insert_node(DlistNode* before, DlistNode* new_node) {
	new_node->llink = before;
	new_node->rlink = before->rlink;
	before->rlink->llink = new_node;
	before->rlink = new_node;
}

void remove_node(DlistNode* phead_node, DlistNode* removed) {
	if (removed == phead_node) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}
 
main() {
	DlistNode head_node;
	DlistNode* p[10];
	int i;
	init(&head_node);
	for (i = 0; i < 5; i++) {
		p[i] = (DlistNode*)malloc(sizeof(DlistNode));
		p[i]->data = i;
		insert_node(&head_node, p[i]);
	}
	remove_node(&head_node, p[4]);
	display(&head_node);
}