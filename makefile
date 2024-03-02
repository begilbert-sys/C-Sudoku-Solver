CC = gcc
CFLAGS = -lcurses
DEPS = solver.h interface.h
OBJ = main.o solver.o interface.o
    
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
      
main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm -f *.o
	rm -f main