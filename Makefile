all: mruby/build/kernel/lib/libmruby.a
	cd host; make
	cd kernel; make

mruby/build/kernel/lib/libmruby.a: mruby
	cd mruby; make

mruby:
	git clone https://github.com/mruby/mruby.git
	cd mruby; git checkout 1.1.0
	cd mruby; patch -p1 < ../mruby.patch
	cd mruby; make

clean:
	if [ -d mruby ]; then cd mruby; make clean; fi
	cd host; make clean
	cd kernel; make clean

distclean: clean
	rm -rf mruby
