CFLAGS = -g -Wall -pedantic
CC = gcc
OBJECTS = smartuniq_methods.o

all: smartuniq

smartuniq: smartuniq.o $(OBJECTS)
	$(CC) $(CFLAGS) $@.o $(OBJECTS) -o $@


%: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f smartuniq_methods
	rm -f smartuniq
	rm -f core *.o a.out
	rm -rf *.dSYM
