all: libfunctions.a test

functions.o: _functions.c

libfunctions.a: functions.o

test: test.c libfunctions.a

.PHONY: clean
clean:
	rm -fv functions.o libfunctions.a test *~ 
