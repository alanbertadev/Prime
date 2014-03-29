// gcc -std=c99 -o multithread multithread.c -fopenmp -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int pf(unsigned long limit, unsigned int q);

int main(int argc, char *argv[])
{
	unsigned int q = 0;
	if(argv[2] && atoi(argv[2]) == 1) q = 1;
	printf("Prime Finder\n");
	if(q) printf("1 is a prime number!\n3 is a prime number!\n");

	double startTime = omp_get_wtime();
	unsigned long primes = 2, limit = atoi(argv[1]), i = 1, j = 0, a, b, twinprimes = 0;

	//Find primes pf(max,print)
#pragma omp parallel for schedule(dynamic) reduction(+ : primes, twinprimes) private (j, a, b)
	for(i = 1; i < (limit+6)/6; i++) {
		j = 6 * i;
		a = pf(j + 1, q);
		b = pf(j - 1, q);
		primes += a+b;
		if(a && b) twinprimes++;
	}
	printf("Twin prime pairs found: %lu\n", twinprimes);
	printf("Primes found: %lu in %.2f seconds.\n\n", primes, omp_get_wtime() - startTime);
	return 0;
}

int pf(unsigned long x, unsigned int q) {

	if(x > 3)
		if(x % 2 == 0 || x % 3 == 0)
			return 0;

	for(unsigned long i = 4; i <= sqrt(x); i++)
		if(x % i == 0)
			return 0;

	if(q) printf("%lu is a prime number!\n", x);
	return 1;
}
