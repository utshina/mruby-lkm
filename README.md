mruby-lkm
=========

A set of files to run mruby inside the Linux kernel.

## Preparation

You need a development environment for mruby and Linux kernel modules.

## Compile

Just type 'make'.

It will download the mruby source code, change the branch, compile mruby,
compile rutime to run mruby on host, and make a mruby kernel module.

## Run

    sudo insmod kernel/mruby.ko                # load the mruby kernel module
    sudo sh -c 'cat hello.mrb > /proc/mruby'   # load and execute the mruby bytecode
    dmesg                                      # check the output
