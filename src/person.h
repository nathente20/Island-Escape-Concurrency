#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include "semaphore.h"

#include "boat.h"
#include "barrier.h"
class Boat;
class Barrier;


enum Weight {
	CHILD = 2,
	ADULT = 3,
	FULL = 5
};

class Person{
private:
	std::string name;
	unsigned int energy;
public:
	bool isDriver;
	const enum Weight weight;
	Person(std::string n, enum Weight weight);
	std::string getName();
	void printAboutMe();
	void setRole(bool role);
	void row();
	void rest();
	bool isTired();
	//void escape(Barrier& barrier); // I think this is supposed to be the driver function that is run as its own thread, will add necessary context as needed

};

#endif
