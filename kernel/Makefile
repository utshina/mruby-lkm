ccflags-y += -DDISABLE_STDIO -I$(PWD)/../mruby/include -I$(PWD)
obj-m := mruby.o
mruby-objs := lkm.o main.o proc.o libc.o ../mruby/build/kernel/lib/libmruby.a

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) CFLAGS_MODULE=$(CFLAGS) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
