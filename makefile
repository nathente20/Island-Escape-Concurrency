STD=--std=c++17 -pthread
GCC=g++
OBJ=obj
BIN=bin

obj/semaphore.o: src/semaphore.cpp src/semaphore.h
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${GCC} ${STD} -c -o $@ $<
obj/barrier.o: src/barrier.cpp src/barrier.h
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${GCC} ${STD} -c -o $@ $<
obj/person.o: src/person.cpp src/person.h 
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${GCC} ${STD} -c -o $@ $<
obj/world.o: src/world.cpp src/world.h
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${GCC} ${STD} -c -o $@ $<

bin/main: obj/semaphore.o obj/person.o obj/barrier.o obj/world.o src/main.cpp
	[ -d $(BIN) ] || mkdir -p $(BIN)
	${GCC} ${STD} -o $@ $^
run: bin/main
	./$< 7 9
clean:
	rm -f obj/*.o
	rm -f bin/*
	rm -r -f bin
	rm -r -f obj
