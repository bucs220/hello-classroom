all: test

_functions.o: _functions.c
	$(CC) -c $^

libfunctions.a: _functions.o
	$(AR) -rc $@ $^

test: test.c libfunctions.a
	$(CC) -o $@ test.c functions.c -L. -lfunctions -lcunit

.PHONY: clean
clean:
	rm -fv _functions.o libfunctions.a test *~ 
