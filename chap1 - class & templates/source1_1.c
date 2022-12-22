// source code 1.1 random number generator
#include <stdio.h>
#include <stdlib.h>
static unsigned long int next = 1;

int rand1(void)
{
	// static unsigned long int next = 1;
	printf("rand1()::next = %ld\n", next);
	next = next * 110351245 + 12345;
	return (unsigned int)(next / 65536) % 32768;
}

void srand1(unsigned int seed)
{
	next = seed;
}

int main(void)
{
	int count;
	unsigned seed;

	printf("Please enter your choice for seed.\n");
	while (scanf_s("%u", &seed) == 1)
	{
		srand1(seed);
		// srand1((unsigned int) time(0));

		for (count = 0; count < 5; count++)
			printf("%d\n", rand1());
		printf("Please enter next seed (q to quit):\n");
	}
	printf("Done\n");
	return 0;
}