#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include "semaphore.h"
#include "world.h"

class World;

// reliant on these values staying this way for how the world tracks stats
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
	void row(World& w, bool driverOnly, bool toMainland);
	void rest();
	bool isTired();

};

#endif
