
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/gol

SRC= main.c

# generic build details

CC =     gcc
CFLAGS = -Wall -O
LIBS =   -lSDL2

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< 

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:  main.c

