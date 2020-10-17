#include <stdio.h>
#include<Windows.h>
#include<process.h>

unsigned __stdcall ThreadFunc1(void* data)
{
	int v = (int)data;
	for (int i = 2; i <= 9; i++) 
	{
		printf("%d * %d = %d\n", i, v, i * v);
		Sleep(1);
	}
	return 0;
}
int main()
{
	for (int i = 1; i <= 9; i++) {
		_beginthreadex(NULL, 0, &ThreadFunc1, (void*)i, 0, NULL);
		Sleep(1);
	}
		
	Sleep(100000);
}