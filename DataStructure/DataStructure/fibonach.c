#include <stdio.h>
#include <time.h>
int fib(int n) {
	if (n == 0) return 0;
	else if (n == 1) return 1;
	else return (fib(n - 1) + fib(n - 2));
}

int fib_iter(int n) {
	if (n < 2) return n;
	else {
		int i, tmp, current = 1, last = 0;
		for (i = 2; i <= n; i++) {
			tmp = current;
			current += last;
			last = tmp;
		}
		return current;
	}
}

void main(void) {
	clock_t start, finish;
	double duration;

	start = clock();
	fib(30);
	finish = clock();
	duration = ((double)(finish - start) / CLOCKS_PER_SEC);
	printf("%f 초입니다.\n", duration);

	start = clock();
	fib_iter(30);
	finish = clock();
	duration = ((double)(finish - start) / CLOCKS_PER_SEC);
	printf("%f 초입니다.\n", duration);



}