#include <stdio.h>

#include "ArrayList.h"

void test_al_init();
void test_al_append();

int main()
{

	test_al_init(16);

}

void test_al_init(int n)
{

	int cases = 0, total_cases = n*n;

	printf("> Testing ArrayList Initialization\n");
	printf("> \n");

	for(int i = 1; i < n + 1; i++)
	{
		for(int j = 8; j <= n * 8; j += 8)
		{

			ArrayList* arr = al_initsize(i, j);
			if(arr == NULL)
			{
				printf(">>> FAILURE\n");
				printf(">>> Failed to allocate ArrayList\n");
			
				printf(">>> Data\n");
				printf(">>> elem_size = %d\n", i);
				printf(">>> Length = %d\n", j);

			}else cases++;

		}
	}

	printf("> Initialization Testing Completed!\n");
	printf("> Cases Passed: [%d/%d]\n", cases, total_cases);

}
