

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0;
#define TRUE 1;

typedef int element;
typedef struct {
	element data;
	struct ListNode* link;
} ListNode;
typedef struct {
	ListNode* head;
	int length;
} LinkedListType;

void error(char *message){
	fprintf(stderr,"%s\n",message);
	exit(1);
}

void insert_node(ListNode** phead, ListNode* p, ListNode* new_node) {
	if (*phead == NULL) { //empty 인 경우
		new_node->link = NULL;
		*phead = new_node; 
	}
	else if (p == NULL) {
		new_node->link = *phead;
		*phead = new_node;
	}
	else {
		new_node->link = p->link;
		p->link = new_node; 
	}
}


void init(LinkedListType* list) {
	if (list == NULL) return;
	list->length = 0;
	list->head = NULL;
}
int is_empty(LinkedListType* list) {
	if (list->head == NULL) return 1; //단순 연결 리스트에서 첫 번째 노드를 가리키는 포인터가 head 포인터. 이 값이 NULL이면 주소가 없다는 뜻이므로 empty 상태.
	else return 0;
}

int get_length(LinkedListType* list) {
	return list->length;
}

ListNode* get_node_at(LinkedListType* list, int pos) {
	int i;
	ListNode* tmp_node = list->head;

	if (pos < 0) return NULL;
	for (i = 0; i < pos; i++) {
		tmp_node = tmp_node->link;
	}

	return tmp_node;
}


void remove_node(ListNode** phead, ListNode* p, ListNode* removed)
{
	if (p == NULL)
		* phead = (*phead)->link;
	else
		p->link = removed->link;
	free(removed);
}

void adelete(LinkedListType *list, int pos)
{
	if (!is_empty(list) && (pos >= 0) && (pos < list->length)){
	 ListNode *p = get_node_at(list, pos-1);
	 remove_node(&(list->head),p,(p!=NULL)?p->link:NULL);
	 list->length--;
	}
}  

void add(LinkedListType* list, int position, element data) {
	ListNode* p;
	if ((position >= 0) && (position <= list->length)) {
		ListNode* node = (ListNode*)malloc(sizeof(ListNode));
		if (node == NULL) error("메모리 할당에러");
		node->data = data;
		p = get_node_at(list, position - 1);
		insert_node(&(list->head), p, node);
		list->length++;
	}
}

void add_first(LinkedListType* list, element data) {
	/*ListNode* new_node;
	new_node->data = data;
	new_node->link = list->head->link;
	list->head = new_node;
	list->length++;*/
	add(list, 0, data);
}

void add_last(LinkedListType* list, element data) {
	add(list, get_length(list), data);
}

element get_data(LinkedListType* list, int pos) {
	ListNode* p;
	if (pos >= list->length)
		error("위치 오류");
	p = get_node_at(list, pos);
	return p->data;
}

void clear(LinkedListType* list) {//모든 노드 삭제
	int i;
	for (i = 0; i < list->length; i++) {
		adelete(list, i);
	}
}

void display(LinkedListType* list) {
	int i;
	ListNode* node = list->head;
	printf("(");
	for (i = 0; i < list->length; i++) {
		printf("%d ", node->data);
		node = node->link;
	}
	printf(")\n");
}

int is_in_list(LinkedListType* list, element item) {
	ListNode* p;
	p = list->head;
	while ((p != NULL)) {
		if (p->data == item)
			break;
		p = p->link;
	}
	if (p == NULL){
		return FALSE;
	}
	else
		return TRUE;

}

int main(void) {
	LinkedListType list1;

	init(&list1);
	add(&list1, 0, 20);
	add_last(&list1, 30);
	add_first(&list1, 10);
	add_last(&list1, 40);
	//list1 = (10,20,30,40)
	display(&list1);

	//list1=(10,20,30)
	adelete(&list1, 3);
	display(&list1);

	//list1 = (20,30)
	adelete(&list1, 0);
	display(&list1);

	printf("%s\n", (is_in_list(&list1, 20) == 1)? "성공" : "실패");//1은 TRUE 대신. 왜 오류나는지는 모르겠다.
	printf("%d\n", get_data(&list1, 0));
}