#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ctype.h>

extern int mruby_main(void);

static int lkm_init(void)
{
	printk(KERN_INFO "LKM: init\n");
	return mruby_main();
}

static void lkm_exit(void) {
	printk(KERN_INFO "LKM: exit\n");
}

module_init(lkm_init);
module_exit(lkm_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("mruby");
MODULE_AUTHOR("Takahiro Shinagawa");
