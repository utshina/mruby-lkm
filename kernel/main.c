#include <linux/kernel.h>
#include "mruby.h"
#include "mruby/irep.h"
#include "mruby/string.h"

extern uint8_t code[];

static mrb_value
kernel_printk(mrb_state *mrb, mrb_value self)
{
	mrb_value retval;
	mrb_value str;

	mrb_get_args(mrb, "S", &str);
	printk(KERN_INFO "mruby: %s\n", RSTRING_PTR(str));
	retval.value.i = 0;
	return retval;
}

int
mruby_main(void)
{
	mrb_state *mrb;
	struct RClass *kernel;
	mrb_value ret;

	mrb = mrb_open();
	kernel = mrb_define_module(mrb, "Kernel");
	mrb_define_class_method(mrb, kernel, "printk",
				kernel_printk, ARGS_REQ(1));

	ret = mrb_load_irep(mrb, code);
	printk("mruby: ret = %d\n", ret.value.i);
	return 0;
}
