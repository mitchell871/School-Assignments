CC = g++

EXE = main

OBJ = main.o sorting.o

CFLAGS =

DEPS =


%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY : clean

clean:
	rm -f $(OBJ) $(EXE)