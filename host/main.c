#include "mruby.h"
#include "mruby/proc.h"
#include "mruby/string.h"

extern uint8_t code[];

static mrb_value
kernel_printk(mrb_state *mrb, mrb_value self)
{
        mrb_value retval;
        mrb_value str;

        mrb_get_args(mrb, "S", &str);
        printf("%s", RSTRING_PTR(str));
        retval.value.i = 0;
        return retval;
}

int
main(int argc, char **argv)
{
        mrb_state *mrb;
        struct RClass *kernel;
        mrb_value ret;

        mrb = mrb_open();
        kernel = mrb_define_module(mrb, "Kernel");
        mrb_define_class_method(mrb, kernel, "printk",
                                kernel_printk, ARGS_REQ(1));

        ret = mrb_load_irep(mrb, code);
        return ret.value.i;
}
