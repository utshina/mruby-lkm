#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ctype.h>
#include <mruby.h>
#include "mruby-lkm.h"

static int lkm_init(void)
{
	pr_info("mruby-lkm: init\n");
	mruby_proc_init();
	return 0;
}

static void lkm_exit(void) {
	mruby_proc_exit();
	pr_info("mruby-lkm: exit\n");
}

module_init(lkm_init);
module_exit(lkm_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("mruby");
MODULE_AUTHOR("Takahiro Shinagawa");
