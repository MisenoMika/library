CC = g++
CCFLAG = -g -w

main.exe:main.C Decision.o Group.o Student.o StudentsVector.o Weather.o World.o
	$(CC) $(CCFLAG) -o main.C Decision.o Group.o Student.o StudentsVector.o Weather.o World.o

Decision.o:Decision.C Decision.h 
	$(CC) $(CCFLAG) -o Decision.o Decision.C

Group.o:Group.C Group.h 
	$(CC) $(CCFLAG) -o Group.o Group.C

Weather.o:Weather.C Weather.h 
	$(CC) $(CCFLAG) -o Weather.o Weather.C

World.o:World.C World.h 
	$(CC) $(CCFLAG) -o World.o World.C

StudentsVector.o:StudentsVector.C StudentsVector.h 
	$(CC) $(CCFLAG) -o StudentsVector.o StudentsVector.C

clean:
	rm -rf main.exe *.o
