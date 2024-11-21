#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include "semaphore.h"

#include "boat.h"
class Boat;

class Person{
private:
	std::string name;
	unsigned int age_class;
public:
	Person(std::string n);
	std::string getName();
	void printAboutMe();

	void waitToBe(Semaphore line, void* roleBehavior);
};

#endif
