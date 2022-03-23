#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/time.h>

int main(int argc, char **argv)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	int opt;
	unsigned int n, result;

	while((opt=getopt(argc,argv,"n:")) != -1)
		if(opt == 'n')
			n = (unsigned int)atoi(optarg);
	result = syscall(548, &n);
	gettimeofday(&end, NULL);
	unsigned long start_time, end_time;
	start_time = start.tv_sec * 1000000 + start.tv_usec;
	end_time = end.tv_sec * 1000000 + end.tv_usec;
	printf("The number of total random numbers: %d\n", n);
	printf("The number of prime number: %d\n", result);
	printf("Processing time: %luus\n", end_time - start_time);
	return 0;
}
