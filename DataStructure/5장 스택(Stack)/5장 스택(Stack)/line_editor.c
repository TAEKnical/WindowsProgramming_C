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
	if (*phead == NULL) { //empty �� ���
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
	if (list->head == NULL) return 1; //�ܼ� ���� ����Ʈ���� ù ��° ��带 ����Ű�� �����Ͱ� head ������. �� ���� NULL�̸� �ּҰ� ���ٴ� ���̹Ƿ� empty ����.
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
		if (node == NULL) error("�޸� �Ҵ翡��");
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
		error("��ġ ����");
	p = get_node_at(list, pos);
	return p->data;
}

void clear(LinkedListType* list) {//��� ��� ����
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
	printf("i: �Է�\n");
	printf("d: ����\n");
	printf("r: �����б�\n");
	printf("w: ���Ͼ���\n");
	printf("q: ����\n");
	printf("**************\n");
}

void read_file(LinkedListType* buffer) {
	char fname[MAX_NAME];
	FILE* fd; //ó���� ������ ����Ű�� ����������
	element p;

	if (!is_empty(buffer)) {
		clear(buffer);
	}
	init(buffer);

	printf("���� �̸�: ");
	scanf("%s", fname);
	if ((fd = fopen(fname, "r")) == NULL) {
		warning("������ �� �� �����ϴ�.");
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

	printf("���� �̸�: ");
	scanf("%s", fname);
	if ((fd = fopen(fname, "w")) == NULL) {
		printf("������ �� �� �����ϴ�.\n");
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
		printf("���� ������ �����ϴ�.\n");
	else {
		printf("����� ���� ���� ��ȣ�� �Է��ϼ���: ");
		scanf("%d", &position);
		adelete(buffer, position);
	}
	display(buffer);
}

void insert_line(LinkedListType* buffer) {
	int position;
	char line[MAX_CHAR_PER_LINE];
	element p;

	printf("�Է����ȣ�� �Է��ϼ���: \n");
	scanf("%d", &position);

	printf("������ �Է��ϼ���: ");
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