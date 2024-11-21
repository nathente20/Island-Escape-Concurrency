#ifndef _BOAT_H_
#define _BOAT_H_
#include <string>
#include <mutex>
#include "semaphore.h"

#include "person.h"
class Person;

class Boat{
private:
	// these should be moved to a separate barrier class
	Semaphore nextDriver;
	Semaphore nextPassenger;
	int numOccupants;

	Semaphore twoPeopleOn;
	Semaphore arrival;
	std::mutex inUse;

public:
	Boat();
	std::string info();

	void boardDriver(Person p);
	void boardPassenger(Person p);
	
};

#endif
