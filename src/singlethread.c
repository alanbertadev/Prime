// gcc -std=c99 -o singlethread singlethread.c -lm -fopenmp

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
	unsigned long primes;

	//Find primes between a and b. pf(a,b)
	primes = pf(atoi(argv[1]), q);

	printf("Primes found: %lu in %.2f seconds.\n\n", primes, omp_get_wtime() - startTime);
	return 0;
}

int pf(unsigned long limit, unsigned int q) {

	unsigned int xisprime = 1, yisprime = 1;
	unsigned long primes = 2, i, n, x, y, twinprimes = 0;

	//implement filter for x = 6n+1 | 6n-1...
	for(n = 1; n < (limit+6)/6; n++)
	{
		x = 6*n-1;
		y = x+2;

		if(x > 3 && x % 2 == 0){
			n++;
			continue;
		} else if(x > 3 && x % 3 == 0){
			n++;
			continue;
		}

		if(y > 3 && y % 2 == 0){
			n++;
			continue;
		} else if(y > 3 && y % 3 == 0){
			n++;
			continue;
		}

		for(i = 4; i <= sqrt(x); i++)
		{
			if(x % i == 0){
				xisprime = 0;
				break;
			}
		}
		for(i = 4; i <= sqrt(y); i++)
		{
			if(y % i == 0){
				yisprime = 0;
				break;
			}
		}

		if(xisprime){
			if(q) printf("%lu is a prime number!\n", x);
			primes++;
		}
		if(yisprime){
			if(q) printf("%lu is a prime number!\n", y);
			primes++;
			if(xisprime)
                        	twinprimes++;
		}
		xisprime = 1;
		yisprime = 1;
	}
	printf("Twin prime pairs found: %lu\n", twinprimes);
	return primes;
}
