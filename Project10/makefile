CC = g++
CCFLAGS = -g 
CCLIBS = -lncurses
mygame: main.o PlayerShip.o Weapon.o Shell.o Missile.o Gui.o Game.o \
	EnemyShip.o GunBoat.o Bomber.o Torpedo.o Destroyer.o Explosion.o Curiser.o \
	Item.o MedicalPack.o WeaponPack.o Obstacle.o
	$(CC) $(CCFLAGS) -o mygame main.o PlayerShip.o Weapon.o Shell.o \
	Gui.o Game.o Missile.o EnemyShip.o GunBoat.o Bomber.o Torpedo.o \
	Destroyer.o Cruiser.o Explosion.o Item.o MedicalPack.o WeaponPack.o Obstacle.o $(CCLIBS) 

main.o: main.cpp
	$(CC) $(CCFLAGS) -c -o main.o main.cpp

PlayerShip.o: PlayerShip.cpp PlayerShip.h
	$(CC) $(CCFLAGS) -c -o PlayerShip.o PlayerShip.cpp

Weapon.o: Weapon.cpp Weapon.h
	$(CC) $(CCFLAGS) -c -o Weapon.o Weapon.cpp

Missile.o: Missile.cpp Missile.h
	$(CC) $(CCFLAGS) -c -o Missile.o Missile.cpp

Shell.o: Shell.cpp Shell.h
	$(CC) $(CCFLAGS) -c -o Shell.o Shell.cpp

Game.o: Game.cpp Game.h
	$(CC) $(CCFLAGS) -c -o Game.o Game.cpp

Gui.o: Gui.cpp Gui.h
	$(CC) $(CCFLAGS) -c -o Gui.o Gui.cpp

EnemyShip.o: EnemyShip.cpp EnemyShip.h
	$(CC) $(CCFLAGS) -c -o EnemyShip.o EnemyShip.cpp

GunBoat.o: GunBoat.cpp GunBoat.h
	$(CC) $(CCFLAGS) -c -o GunBoat.o GunBoat.cpp

Bomber.o: Bomber.cpp Bomber.h
	$(CC) $(CCFLAGS) -c -o Bomber.o Bomber.cpp

Destroyer.o: Destroyer.cpp Destroyer.h
	$(CC) $(CCFLAGS) -c -o Destroyer.o Destroyer.cpp

Curiser.o: Cruiser.cpp Cruiser.h
	$(CC) $(CCFLAGS) -c -o Cruiser.o Cruiser.cpp

Torpedo.o: Torpedo.cpp Torpedo.h
	$(CC) $(CCFLAGS) -c -o Torpedo.o Torpedo.cpp

Explosion.o: Explosion.cpp Explosion.h
	$(CC) $(CCFLAGS) -c -o Explosion.o Explosion.cpp

Item.o: Item.cpp Item.h
	$(CC) $(CCFLAGS) -c -o Item.o Item.cpp

MedicalPack.o: MedicalPack.cpp MedicalPack.h
	$(CC) $(CCFLAGS) -c -o MedicalPack.o MedicalPack.cpp

WeaponPack.o: WeaponPack.cpp WeaponPack.h
	$(CC) $(CCFLAGS) -c -o WeaponPack.o WeaponPack.cpp

Obstacle.o: Obstacle.cpp Obstacle.h
	$(CC) $(CCFLAGS) -c -o Obstacle.o Obstacle.cpp


clean:
	rm -rf mygame *.o 