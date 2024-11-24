#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include "semaphore.h"

#include "boat.h"
class Boat;

enum Age {
	CHILD,
	ADULT
};

class Person{
private:
	std::string name;
	enum Age age;
	unsigned int energy;
public:
	Person(std::string n, enum Age age);
	std::string getName();
	void printAboutMe();
	void row();
	void rest();
	void escape(); // I am not sure about the purpose of this function other than just being a readable way of saying I'm out!!

};

#endif
