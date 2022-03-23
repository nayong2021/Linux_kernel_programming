#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/random.h>
#include <linux/slab.h>
#include <linux/ktime.h>

static unsigned int n = 10;

module_param(n, int, 0);
MODULE_PARM_DESC(int_param, "A sample integer kernel module parameter");

unsigned int
is_Prime(unsigned int num)
{
	unsigned int i;
	if(num % 2 == 0){
		if(num == 2) return 1;
		else return 0;
	}
	for(i = 3; i * i <= num; i+=2)
		if(num % i == 0) return 0;
	return 1;
}

static int __init lkp_init(void)
{
	struct timespec64 start, end;
	unsigned long start_time, end_time;
	unsigned int i, result=0;
	unsigned int* arr;
	ktime_get_ts64(&start);
	arr = (unsigned int*)kmalloc(sizeof(unsigned int)*n, GFP_KERNEL);
	get_random_bytes(arr, sizeof(unsigned int)*n);
	for(i = 0; i < n; i++)
		arr[i] = arr[i] % (n - 1) +2;
	for(i = 0; i < n; i++)
		result += is_Prime(arr[i]);
	ktime_get_ts64(&end);
	start_time = start.tv_sec*1000000 + start.tv_nsec/1000;
	end_time = end.tv_sec*1000000 + end.tv_nsec/1000;
	printk(KERN_INFO "The number of Total random numbers: %u\n", n);
	printk(KERN_INFO "The number of Prime number: %u\n", result);
	printk(KERN_INFO "Processing time: %luus\n", end_time - start_time);
	return 0;
}

static void __exit lkp_exit(void)
{
	printk(KERN_INFO "Module exiting ...\n");
}

module_init(lkp_init);
module_exit(lkp_exit);
MODULE_LICENSE("GPL");
