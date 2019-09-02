#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101

struct {
	float coef;
	int expon;
}terms[MAX_TERMS] = { {8, 3}, { 7,1 }, { 1,0 }, { 10,3 }, { 3,2 }, { 1,0 } };

int avail = 6;

char compare(int a, int b)
{
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

void attach(float coef, int expon) {
	if (avail > MAX_TERMS) {
		fprintf(stderr, "항의 개수가 너무 많음\n");
		exit(1);
	}
	terms[avail].coef = coef;
	terms[avail++].expon = expon;
}

void poly_add2(int As, int Ae, int Bs, int Be, int* Cs, int* Ce) {
	float tempcoef;
	*Cs = avail;
	while (As <= Ae && Bs <= Be) { //As, Ae, Bs, Be는 계산할 두 다항식의 시작인덱스와 끝 인덱스. terms[]에서 0~2는 A다항식, 3~5는 B다항식
		switch (compare(terms[As].expon, terms[Bs].expon)) {
		case '>':
			attach(terms[As].coef, terms[As].expon);
			As++;
			break;
		case '=':
			tempcoef = terms[As].coef + terms[Bs].coef;
			if (tempcoef)
				attach(tempcoef, terms[As].expon);
			As++;
			Bs++;
		case '<':
			attach(terms[Bs].coef, terms[Bs].expon);
			Bs++;
			break;
		}
		for (; As <= Ae; As++) {
			attach(terms[As].coef, terms[As].expon);
		}
		for (; Bs <= Be; Bs++) {
			attach(terms[Bs].coef, terms[Bs].expon);
		}
	}
}

void main(void) {
	int Cs, Ce;
	poly_add2(0, 2, 3, 5, &Cs, &Ce);
}