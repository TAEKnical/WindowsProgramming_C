#include <stdio.h>
#include <string.h>
int wmain(int argc, wchar_t* argv[])
{
	int i;
	for(i=-0; i<argc; i++)
		fputws(argv[i], stdout);
		fputws(L"\n", stdout);

	return 0;
}