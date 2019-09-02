#include <stdio.h>
#include <malloc.h>

typedef int element;
typedef struct {
	element item;
	struct QueueNode* link;
}QueueNode;

typedef struct {
	QueueNode* front, * rear;
}QueueType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	//exit(1);
}

void init(QueueType* q) {
	q->front = q->rear = NULL;
}

int is_empty(QueueType* q) {
	return (q->front == NULL && q->rear == NULL);
}

void enqueue(QueueType* q, element item) {
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	if (temp == NULL)
		error("메모리 할당 에러");
	else {
		temp->item = item;
		temp->link = NULL;
		if (is_empty(q)) {
			q->front = temp;
			q->rear = temp;
		}
		else {
			q->rear->link = temp;
			q->rear = temp;
		}
	}
}

element dequeue(QueueType* q) {
	QueueNode* temp = q->front;
	element item;
	if (is_empty(q))
		error("큐가 공백 상태");
	else {
		item = temp->item;
		q->front = q->front->link;
		if (q->front == NULL)
			q->rear = NULL;
		free(temp);
		return item;
	}
}

void display(QueueType* q) {
		int i = 0;

		if (is_empty(q)) {
			printf("0--1--2--3--4--5--6--7--8--9--10--11\n");
			printf("큐가 공백상태\n");
			printf("------------------------------------\n");
		}

		else {
			printf("0--1--2--3--4--5--6--7--8--9--10--11\n");
			printf("   ");
			QueueNode* temp = q->front;
			while(1){
				printf("%d  ", temp->item);
				if (temp->link == NULL)
					break;
				temp = temp->link;
			} 
			printf("\n");
			printf("------------------------------------\n");
			printf("front : %d, rear : %d\n", q->front, q->rear);
		}
}

void main() {
	QueueType q;

	init(&q);
	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);
	display(&q);
	printf("dequeue() = %d\n", dequeue(&q));
	printf("dequeue() = %d\n", dequeue(&q));
	printf("dequeue() = %d\n", dequeue(&q));
	display(&q);
}