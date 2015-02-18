#include <linux/kernel.h>
#include <mruby.h>
#include <mruby/irep.h>
#include <mruby/string.h>
#include "mruby-lkm.h"

static mrb_value
linux_printk(mrb_state *mrb, mrb_value self)
{
	mrb_value retval;
	mrb_value str;

	mrb_get_args(mrb, "S", &str);
	printk(KERN_INFO "mruby: %s\n", RSTRING_PTR(str));
	retval.value.i = 0;
	return retval;
}

mrb_value
mruby_exec(uint8_t *code)
{
	mrb_state *mrb;
	struct RClass *Linux;
	mrb_value ret;

	mrb = mrb_open();
	Linux = mrb_define_class(mrb, "Linux", mrb->object_class);
	mrb_define_class_method(mrb, Linux, "printk",
				linux_printk, ARGS_REQ(1));

	ret = mrb_load_irep(mrb, code);
	mrb_close(mrb);
	return ret;
}
