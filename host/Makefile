CFLAGS = -I../mruby/include -g
LDFLAGS = -lm
OBJS = main.o hello.o
LIBS = ../mruby/build/kernel/lib/libmruby.a

main: $(OBJS) $(LIBS)
	$(CC) $(OBJS) $(LIBS) $(LDFLAGS) -o $@

hello.c: hello.rb
	../mruby/bin/mrbc -Bcode $<

clean:
	rm -f main $(OBJS) hello.c .hello.o.cmd
