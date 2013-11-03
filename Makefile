YACC = java.y
SRC = y.tab.c main.c
OBJ = $(SRC:.c=.o)
PROG = jcom

CFLAGS = -Wall -g
LDFLAGS =

all: yacc $(PROG)

$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

yacc:
	bison -y $(YACC)


%.o: %c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f a.out $(PROG) $(OBJ)
