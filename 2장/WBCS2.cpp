#include <stdio.h>
#include <string.h>
#include <locale.h>

int main(void)
{
	wchar_t str[] = L"ABC�ѱ�";
	int size = sizeof(str);
	int len = wcslen(str);

	_wsetlocale(LC_ALL, L"korean");

	wprintf(L"�迭�� ũ��: %d\n", size);
	wprintf(L"���ڿ� ���� : %d \n", len);

	return 0;
}