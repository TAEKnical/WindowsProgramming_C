#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Example {
	int number;
	char name[10];
};
void main() {
	struct Example* p = NULL;
	p = (struct Example*)malloc(2 * sizeof(struct Example));
	if (p == NULL) {
		fprintf(stderr, "can't allocate memory");
		exit(1);
	}
	p->number = 1;
	strcpy_s(p->name,sizeof("Park"),"Park");
	(p + 1)->number = 2;
	strcpy_s((p + 1)->name,sizeof("Kim"),"Kim");
	free(p);
}