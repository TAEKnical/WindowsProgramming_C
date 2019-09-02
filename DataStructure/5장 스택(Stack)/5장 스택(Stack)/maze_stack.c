#include <stdio.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6

typedef struct {
	short r;
	short c;
}element;

element here = { 1,0 }, entry = { 1,0 };


typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

void init(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == MAX_STACK_SIZE - 1);
}

void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}

	else
		s->stack[++(s->top)] = item;
}

element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->stack[(s->top)--];
}

element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		return s->stack[s->top];
}



char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}
};

void push_loc(StackType* s, int r, int c) {
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

void display_maze(char maze[MAZE_SIZE][MAZE_SIZE]) {
	int i, j;
	for (i = 0; i < MAZE_SIZE; i++) {
		printf("|");
		for (j = 0; j < MAZE_SIZE; j++) {
			printf("%c|", maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void main() {
	int r, c;
	StackType s;
	init(&s);
	here = entry;
	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;
		maze[r][c] = '.';
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);
		if (is_empty(&s)) {
			printf("실패\n");
			return;
		}
		else
			here = pop(&s);
		display_maze(maze);
		Sleep(1000);
	}
	printf("성공\n");
}