INC = $(GRAPHE)/lib/
LIB = $(GRAPHE)/lib/
CFLAGS = -Wall -g -I$(INC) -L$(LIB)

test.out : test.c
	gcc $(CFLAGS) -o test.out test.c -lgraphe

clean:
	rm -f *.out *.png *.dot

#sur le system, toute les librairies sont de type lib****.a, on fait appel avec -l***
