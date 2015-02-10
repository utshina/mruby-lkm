all: mruby/build/kernel/lib/libmruby.a hello.mrb
	cd host; make
	cd kernel; make

hello.mrb: hello.rb mruby
	mruby/bin/mrbc $<

mruby/build/kernel/lib/libmruby.a: mruby
	cd mruby; make

mruby:
	git clone https://github.com/mruby/mruby.git
	cd mruby; git checkout 4957c852696c9559bfbea988325fd9bf94fc34bc
	cd mruby; patch -p1 < ../mruby.patch
	cd mruby; make

clean:
	if [ -d mruby ]; then cd mruby; make clean; fi
	cd host; make clean
	cd kernel; make clean
	rm -f hello.mrb

distclean: clean
	rm -rf mruby
