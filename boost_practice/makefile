CC = g++
EXE1 = database
OBJ1 = database.o
EXE2 = example
OBJ2 = example.o
CFLAGS = -g -std=c++11 -lboost_serialization

all : $(EXE1) $(EXE2)

%.o : %.c
	$(CC) -c  -o $@ $< $(CFLAGS)

$(EXE1): $(OBJ1)
	$(CC) -o $@ $^ $(CFLAGS)
$(EXE2): $(OBJ2)
	$(CC) -o $@ $^ $(CFLAGS)
   
clean:
	rm -f $(OBJ1) $(EXE1) $(OBJ2) $(EXE2)