#include <stdio.h>
int main()
{
	int c;
	do
	{
		c = getchar();
		if (c != EOF)		
			putchar(c);
	} while (c != EOF);
}
