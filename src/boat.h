#ifndef _BOAT_H_
#define _BOAT_H_
#include <string>
#include <mutex>
#include "semaphore.h"

#include "person.h"
class Person;

class Boat{
private:
	Semaphore nextDriver;
	Semaphore nextPassenger;
	int numOccupants;
	std::mutex ocLk;

public:
	Boat();
	std::string info();

	void setDriver(Person p);
};

#endif
