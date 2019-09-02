#include <stdio.h>

void swap(int *pa, int *pb) {
	int tmp;
	tmp = *pa;
	printf("*pa : %d, *pb : %d, tmp : %d\n", *pa, *pb, tmp);
	printf("pa : %d, pb : %d, tmp : %d\n", pa, pb, &tmp);
	*pa = *pb;
	printf("*pa : %d, *pb : %d, tmp : %d\n", *pa, *pb, tmp);
	printf("pa : %d, pb : %d, tmp : %d\n", pa, pb, &tmp);
	*pb = tmp;
	printf("*pa : %d, *pb : %d, tmp : %d\n", *pa, *pb, tmp);
	printf("pa : %d, pb : %d, tmp : %d\n", pa, pb, &tmp);
}

main() {
	int a = 1, b = 2;
	printf("바꾸기 전 : a=%d,b=%d\n", a, b);
	swap(&a, &b);
	printf("바꾸기 후 : a=%d,b=%d\n", a, b);
}