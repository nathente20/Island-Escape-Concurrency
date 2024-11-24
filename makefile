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
obj/boat.o: src/boat.cpp src/boat.h
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${GCC} ${STD} -c -o $@ $<
bin/main: obj/semaphore.o obj/boat.o obj/person.o src/main.cpp
	[ -d $(BIN) ] || mkdir -p $(BIN)
	${GCC} ${STD} -o $@ $^
run: bin/main
	./$<
bin/testPeople: obj/semaphore.o obj/boat.o obj/person.o src/testPeople.cpp
	[ -d $(BIN) ] || mkdir -p $(BIN)
	${GCC} ${STD} -o $@ $^
testPeople: bin/testPeople
	./$<
clean:
	rm -f obj/*.o
	rm -f bin/main
	rm -r -f bin
	rm -r -f obj
