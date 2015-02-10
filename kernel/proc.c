#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <mruby.h>
#include "mruby-lkm.h"

static uint8_t *code = NULL;
static size_t size = 0;
static int written = 0;

ssize_t
mruby_proc_read(struct file *filp, char *buf, size_t count, loff_t *offp)
{
	if (*offp >= size)
		return 0;

	if (*offp + count > size || *offp + count < *offp)
		count = size - *offp;
	count -= copy_to_user(buf, code + *offp, count);
	*offp += count;
	return count;
}

ssize_t
mruby_proc_write(struct file *filp, const char *buf, size_t count, loff_t *offp)
{
	if (*offp + count < *offp)
		return 0;

	if (*offp + count > size) {
		void *new_ptr;
		int new_size = *offp + count;

		new_ptr = krealloc(code, new_size, GFP_KERNEL);
		if (new_ptr == NULL)
			return -ENOMEM;
		code = new_ptr;
		size = new_size;
	}
	count -= copy_from_user(code + *offp, buf, count);
	*offp += count;
	if (count > 0)
	    written++;
	return count;
}

int
mruby_proc_open(struct inode *inode, struct file *file)
{
	try_module_get(THIS_MODULE);
	return 0;
}

int
mruby_proc_release(struct inode *inode, struct file *file)
{
    	mrb_value ret;

	if (written) {
	    ret = mruby_exec(code);
	    printk("mruby: ret = %d\n", ret.value.i);
	    written = 0;
	}
    
	module_put(THIS_MODULE);
	return 0;
}

static const struct file_operations
proc_fops = {
	.owner = THIS_MODULE,
	.read = mruby_proc_read,
	.write =  mruby_proc_write,
	.open = mruby_proc_open,
	.release = mruby_proc_release,
};
struct proc_dir_entry *proc_entry;

int mruby_proc_init(void)
{
	proc_entry = proc_create("mruby", 0644, NULL, &proc_fops);
	if (proc_entry == NULL) {
		printk(KERN_INFO "mruby: can't create proc entry\n");
		return -ENOMEM;
	}
	return 0;
}

int mruby_proc_exit(void)
{
	remove_proc_entry("mruby", NULL);
	if (code != NULL)
		kfree(code);
	return 0;
}
