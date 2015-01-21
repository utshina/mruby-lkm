all: mruby
	cd host; make
	cd kernel; make

mruby:
	git clone https://github.com/mruby/mruby.git
	cd mruby; git checkout f65a39f4d19b1de019b0b805ccfb081757e5b7b5
	cd mruby; patch -p1 < ../mruby.patch
	-cd mruby; make

clean:
	rm -rf mruby
	cd host; make clean
	cd kernel; make clean
