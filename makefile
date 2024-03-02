CC = gcc
DEPS = solver.h interface.h
OBJ = main.o solver.o interface.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<
main: $(OBJ)
	$(CC) -lcurses -o $@ $^
clean:
	rm -f *o
	rm -f main