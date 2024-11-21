#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>

#include "boat.h"
class Boat;

class Person{
private:
	std::string name;
	Boat* myBoat;
public:
	Person(std::string n);
	std::string getName();
	void printAboutMe();
};

#endif
