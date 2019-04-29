#include <stdio.h>
#include <string.h>
#include <locale.h>

int main(void)
{
	wchar_t str[] = L"ABC한글";
	int size = sizeof(str);
	int len = wcslen(str);

	_wsetlocale(LC_ALL, L"korean");

	wprintf(L"배열의 크기: %d\n", size);
	wprintf(L"문자열 길이 : %d \n", len);

	return 0;
}