#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define FALSE 0;
#define TRUE 1;
#define MAX_CHAR_PER_LINE 1000
#define MAX_NAME 256

#pragma warning(disable: 4996)


void warning(char*);
void error(char*);

typedef struct {
	char a[MAX_CHAR_PER_LINE];
}element;

typedef struct {
	element data;
	struct ListNode* link;
} ListNode;

typedef struct {
	ListNode* head;
	int length;
} LinkedListType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
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

void adelete(LinkedListType* list, int pos)
{
	if (!is_empty(list) && (pos >= 0) && (pos < list->length)) {
		ListNode* p = get_node_at(list, pos - 1);
		remove_node(&(list->head), p, (p != NULL) ? p->link : NULL);
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

void display(LinkedListType* buffer) {
	int i;
	ListNode* tmp_node;
	tmp_node = buffer->head;
	
	printf("**************\n");
	for (i = 0; i < buffer->length; i++) {
		printf("%s", tmp_node->data.a);
		tmp_node = tmp_node->link;
	}
	printf("**************\n");
}

void warning(char* message) {
	fprintf(stderr, "%s\n", message);
}

void help() {
	printf("**************\n");
	printf("i: 입력\n");
	printf("d: 삭제\n");
	printf("r: 파일읽기\n");
	printf("w: 파일쓰기\n");
	printf("q: 종료\n");
	printf("**************\n");
}

void read_file(LinkedListType* buffer) {
	char fname[MAX_NAME];
	FILE* fd; //처리할 파일을 가리키는 파일포인터
	element p;

	if (!is_empty(buffer)) {
		clear(buffer);
	}
	init(buffer);

	printf("파일 이름: ");
	scanf("%s", fname);
	if ((fd = fopen(fname, "r")) == NULL) {
		warning("파일을 열 수 없습니다.");
		return;
	}
	while (fgets(p.a, MAX_CHAR_PER_LINE, fd)) {
		add_last(buffer, p);
	}
	fclose(fd);
	display(buffer);
}

void write_file(LinkedListType* buffer) {
	FILE* fd;
	char fname[MAX_NAME];
	element p;
	int i;

	printf("파일 이름: ");
	scanf("%s", fname);
	if ((fd = fopen(fname, "w")) == NULL) {
		printf("파일을 열 수 없습니다.\n");
		return;
	}
	for (i = 0; i < get_length(buffer); i++) {
		p = get_data(buffer, i);
		fputs(p.a, fd);
	}
	display(buffer);
	fclose(fd);
}

void delete_line(LinkedListType* buffer) {
	int position;

	if (is_empty(buffer))
		printf("지울 라인이 없습니다.\n");
	else {
		printf("지우고 싶은 라인 번호를 입력하세요: ");
		scanf("%d", &position);
		adelete(buffer, position);
	}
	display(buffer);
}

void insert_line(LinkedListType* buffer) {
	int position;
	char line[MAX_CHAR_PER_LINE];
	element p;

	printf("입력행번호를 입력하세요: \n");
	scanf("%d", &position);

	printf("내용을 입력하세요: ");
	while (getchar() != '\n');
	fgets(line, MAX_CHAR_PER_LINE, stdin);
	strcpy(p.a, line);
	add(buffer, position, p);
	display(buffer);
}

void do_command(LinkedListType* buffer, char command) {
	switch (command) {
	case 'd':
		delete_line(buffer);
		break;
	case 'i':
		insert_line(buffer);
		break;
	case 'r':
		read_file(buffer);
		break;
	case 'w':
		write_file(buffer);
		break;
	case 'q':
		break;
	}
}

int main(void) {
	char command;
	LinkedListType buffer;

	init(&buffer);
	do {
		help();
		command = getchar();
		do_command(&buffer, command);
		fflush(stdin);
		
	} while (command != 'q');
}