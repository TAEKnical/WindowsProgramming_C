#include <stdio.h>

#define MAX_SIZE 100

typedef int element;
typedef struct {
	element queue[MAX_SIZE];
	int front, rear;
}QueueType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return (q->front == (q->rear + 1) % MAX_SIZE);
}

void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("큐가 포화상태\n");
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태");
	q->front = (q->front + 1) % MAX_SIZE;
	return q->queue[q->front];
}

element peek(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태");
	return q->queue[(q->front + 1) % MAX_SIZE];
}

element display(QueueType* q) {
	int i = 0;

	if (is_empty(q)) {
		printf("0--1--2--3--4--5--6--7--8--9--10--11\n");
		printf("큐가 공백상태\n");
		printf("------------------------------------\n");
	}
	else if (is_full(q)) {
		printf("0--1--2--3--4--5--6--7--8--9--10--11\n");
		printf("큐가 포화상태\n");
		printf("------------------------------------\n");
	}
	else {
		printf("0--1--2--3--4--5--6--7--8--9--10--11\n");
		printf("   ");
		for (i = q->front + 1; i < q->rear + 1; i++) {
			printf("%d  ", q->queue[i]);
		}
		printf("\n");
		printf("------------------------------------\n");
		printf("front : %d, rear : %d\n", q->front, q->rear);
	}
}

void main() {
	QueueType q;
	init(&q);
	printf("front=%d rear=%d\n", q.front, q.rear);
	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);
	display(&q);
	printf("dequeue()=%d\n", dequeue(&q));
	printf("dequeue()=%d\n", dequeue(&q));
	printf("dequeue()=%d\n", dequeue(&q));
	printf("front=%d rear%d\n", q.front, q.rear);
	display(&q);
}