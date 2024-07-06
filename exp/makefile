INC = $(GRAPHE)/lib/
LIB = $(GRAPHE)/lib/
CFLAGS = -Wall -g -I$(INC) -L$(LIB)

expdisjoint.out : expdisjoint.c
	gcc $(CFLAGS) -o expdisjoint.out expdisjoint.c -lgraphe 

clean:
	rm -f *.o expdisjoint.out

