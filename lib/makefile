CC=gcc
CFLAGS = -Wall -g
OBJ= graphe.o connexe.o init.o disjoint.o

libgraphe.a: $(OBJ)
	ar -r libgraphe.a $(OBJ)

#on compile tous les fichiers objets



graphe.o : graphe.c graphe.h
	$(CC) $(CFLAGS) -c graphe.c

disjoint.o : disjoint.c disjoint.h graphe.h
		$(CC) $(CFLAGS) -c disjoint.c

connexe.o : connexe.c connexe.h graphe.h
	$(CC) $(CFLAGS) -c connexe.c

init.o : init.c init.h graphe.h
	$(CC) $(CFLAGS) -c init.c

clean:
	rm -f prog *.o

cleanlib:
	rm -f prog libgraphe.a
