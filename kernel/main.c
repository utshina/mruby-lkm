#include <linux/kernel.h>
#include <mruby.h>
#include <mruby/irep.h>
#include <mruby/string.h>
#include "mruby-lkm.h"

static mrb_state *mrb = NULL;
static mrb_value mrb_ret;

static mrb_value
linux_printk(mrb_state *mrb, mrb_value self)
{
	int ret;
	mrb_value retval;
	mrb_value str;

	mrb_get_args(mrb, "S", &str);
	ret = pr_info("mruby-lkm: %s\n", RSTRING_PTR(str));
	retval.value.i = ret;
	return retval;
}

void
mruby_load(uint8_t *code)
{
	struct RClass *Linux;

	if (mrb)
	    mrb_close(mrb);
	mrb = mrb_open();
	Linux = mrb_define_class(mrb, "Linux", mrb->object_class);
	mrb_define_class_method(mrb, Linux, "printk",
				linux_printk, ARGS_REQ(1));

	mrb_ret = mrb_load_irep(mrb, code);
	pr_info("mruby-lkm: ret = %d\n", mrb_ret.value.i);
}

void
mruby_unload(void)
{
	if (mrb)
		mrb_close(mrb);
}
