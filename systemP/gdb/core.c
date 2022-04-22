#include <unistd.h>

int main()
{
	int para;
	int *p = &para;
	int *pp = 0;
	
	*p = 10;
	*pp = 20;

	return 0;
}
