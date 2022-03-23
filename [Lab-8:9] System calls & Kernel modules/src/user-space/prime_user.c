#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>

int
is_Prime(int num)
{
  if(num % 2 == 0){
    if(num == 2) return 1;
    else return 0;
  }
  for(int i = 3; i * i <= num; i+=2)
    if(num % i ==0) return 0;
  return 1;
}

int main(int argc, char **argv)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	srand((unsigned int) time(NULL));
	int opt;
	int n, result = 0, i;
	int *arr;

	while((opt=getopt(argc,argv,"n:")) != -1)
		if(opt == 'n')
			n = atoi(optarg);
	arr = (int*)malloc(sizeof(int)*n);
	for(i = 0; i < n; i++)
		arr[i] = rand() % (n - 1) + 2;
	for(i = 0; i < n; i++)
		result += is_Prime(arr[i]);
	gettimeofday(&end, NULL);
	unsigned long start_time, end_time;
	start_time = start.tv_sec * 1000000 + start.tv_usec;
	end_time = end.tv_sec * 1000000 + end.tv_usec;
	printf("The number of total random numbers: %d\n", n);
	printf("The number of prime number: %d\n", result);
	printf("Processing time: %luus\n", end_time - start_time);
	return 0;
}
