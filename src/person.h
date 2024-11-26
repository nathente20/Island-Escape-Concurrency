#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include "semaphore.h"
#include "world.h"

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
	void row(World& w);
	void rest();
	bool isTired();

};

#endif
