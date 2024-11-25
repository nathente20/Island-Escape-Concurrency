#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "person.h"

Person::Person(std::string n, enum Weight weight_class) : 
	energy(4),
	weight(weight_class),
	name(n) {}

std::string Person::getName(){
	return name;
}
void Person::printAboutMe(){
	std::cout << 
		"My name is " <<
		name << 
		". My age classification is " <<
		weight <<
		std::endl;
}

void Person::setRole(bool role) {
	this->isDriver = role;
}

void Person::row(){
	// lock randomizer later
	int waitTime;
	// [1 000 000, 4 000 000]
	waitTime = (std::rand() % 3000000) + 1000000; 
	std::this_thread::sleep_for(std::chrono::microseconds(waitTime));

}

void Person::rest(){
	if (energy == 0) {
		energy++;
	}
}

//void Person::escape(World& w) {
//}

