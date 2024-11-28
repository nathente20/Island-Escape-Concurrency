/**
  @file
  @author Nathen Te <nlt47>
  @date November 27, 2024
  @section DESCRIPTION

  This file provides the definition of a Person trying to escape the deserted island in the toy problem. It also defines weight classes which are relevant to Person and other related classes such Barrier and World.
*/

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
