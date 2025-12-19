CC = g++
CCFLAGS = -g 
CCLIBS = -lncurses
mygame: main.o Gui.o Game.o Grass.o Rabbit.o Animal.o Entity.o Wolf.o Predator.o Tiger.o
	$(CC) $(CCFLAGS) -o mygame main.o Gui.o Game.o Grass.o Rabbit.o Animal.o Entity.o Wolf.o Predator.o Tiger.o $(CCLIBS) 

Gui.o: Gui.h Gui.cpp
	$(CC) $(CCFLAGS) -c -o Gui.o Gui.cpp

Game.o: Game.h Game.cpp
	$(CC) $(CCFLAGS) -c -o Game.o Game.cpp

main.o: main.cpp
	$(CC) $(CCFLAGS) -c -o main.o main.cpp

Entity.o: Entity.cpp Entity.h
	$(CC) $(CCFLAGS) -c -o Entity.o Entity.cpp

Grass.o: Grass.cpp Grass.h
	$(CC) $(CCFLAGS) -c -o Grass.o Grass.cpp

Animal.o: Animal.h Animal.cpp
	$(CC) $(CCFLAGS) -c -o Animal.o Animal.cpp

Rabbit.o: Rabbit.h Rabbit.cpp
	$(CC) $(CCFLAGS) -c -o Rabbit.o Rabbit.cpp

Wolf.o: Wolf.h Wolf.cpp
	$(CC) $(CCFLAGS) -c -o Wolf.o Wolf.cpp

Predator.o: Predator.h Predator.cpp
	$(CC) $(CCFLAGS) -c -o Predator.o Predator.cpp

Tiger.o: Tiger.h Tiger.cpp
	$(CC) $(CCFLAGS) -c -o Tiger.o Tiger.cpp

clean:
	rm -rf mygame *.o
