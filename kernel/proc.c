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
	return simple_read_from_buffer(buf, count, offp, code, size);
}

ssize_t
mruby_proc_write(struct file *filp, const char *buf, size_t count, loff_t *offp)
{
	ssize_t ret;
	loff_t off = *offp;

	if (off < 0)
		return -EINVAL;
	if (count > size - off) {
		void *new_code;
		int new_size = count + off;

		new_code = krealloc(code, new_size, GFP_KERNEL);
		if (new_code == NULL)
			return -ENOMEM;
		code = new_code;
		size = new_size;
	}
	ret = simple_write_to_buffer(code, size, offp, buf, count);
	if (ret > 0)
		written = 1;
	return ret;
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
