all : Atmain
Atmain: Atmain.o AtHalSim.o AtOsal.o
	gcc -pthread -o Atmain Atmain.o AtHalSim.o AtOsal.o
Atmain.o: Atmain.c AtOsal.h AtHalSim.h
	gcc -pthread -o Atmain.o -c Atmain.c
AtHalSim.o : AtHalSim.c AtHalSim.h
	gcc -pthread -o AtHalSim.o -c AtHalSim.c
AtOsal.o: AtOsal.c AtOsal.h AtHalSim.h
	gcc -pthread -o AtOsal.o -c AtOsal.c
clean:
	rm Atmain
	rm *.o
