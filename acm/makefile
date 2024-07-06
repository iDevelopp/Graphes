INC = $(GRAPHE)/lib/
LIB = $(GRAPHE)/lib/
FLAGS = -Wall -g -I$(INC) -L$(LIB)
OBJ= nuage.o acm.o main.o

main.out: $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $@ -lgraphe -lm

main.o: main.c acm.h nuage.h
	gcc $(FLAGS) -c main.c

nuage.o: nuage.c nuage.h
	gcc $(FLAGS) -c $^

acm.o: acm.c acm.h
	gcc $(FLAGS) -c $^

clean:
	rm -f *.o main.exe
