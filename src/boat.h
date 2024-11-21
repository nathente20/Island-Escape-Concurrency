#ifndef _BOAT_H_
#define _BOAT_H_
#include <string>
#include "person.h"
class Person;

class Boat{
private:
	Person* myCreator;
public:
	Boat(Person* P);
	std::string info();
};

#endif
