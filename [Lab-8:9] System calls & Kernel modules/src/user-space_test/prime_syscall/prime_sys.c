#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/random.h>
#include <linux/slab.h>
#include <linux/uaccess.h>


unsigned int
is_Prime(unsigned int num)
{
	unsigned int i;
	if(num % 2 == 0){
		if(num == 2) return 1;
		else return 0;
	}
	for(i = 3; i * i <= num; i+=2)
		if(num % i ==0) return 0;
	return 1;
}

SYSCALL_DEFINE1(prime_syscall, const unsigned int __user *, n)
{
	unsigned int i, n_kernel, result = 0;
	unsigned int* arr;
	if(copy_from_user(&n_kernel, n, sizeof(unsigned int)))
		return -EFAULT;
	arr = (unsigned int*)kmalloc(sizeof(unsigned int)*n_kernel, GFP_KERNEL);
	get_random_bytes(arr, sizeof(unsigned int)*n_kernel);
	for(i = 0; i < n_kernel; i++)
		arr[i] = arr[i] % (n_kernel - 1) + 2;
	for(i = 0; i < n_kernel; i++)
		result += is_Prime(arr[i]);
	return result;
}
