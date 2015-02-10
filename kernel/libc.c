#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

typedef unsigned long size_t;
void *realloc(void *ptr, size_t size);
void free(void *ptr);

int * __errno_location(void);

long int strtol(const char *nptr, char **endptr, int base);
unsigned long int strtoul(const char *nptr, char **endptr, int base);

void abort(void);
void exit(int status);


void *realloc(void *ptr, size_t size)
{
	return krealloc(ptr, size, GFP_KERNEL);
}

void free(void *ptr)
{
	kfree(ptr);
}

int * __errno_location(void)
{
	static int errno;
	return &errno;
}

long int strtol(const char *nptr, char **endptr, int base)
{
	printk("%s: %s\n", __FUNCTION__, nptr);
	return 0;
}

unsigned long int strtoul(const char *nptr, char **endptr, int base)
{
	printk("%s: %s\n", __FUNCTION__, nptr);
	return 0;
}

void abort()
{
	printk("%s\n", __FUNCTION__);
}

void exit(int status)
{
	printk("%s\n", __FUNCTION__);
}
