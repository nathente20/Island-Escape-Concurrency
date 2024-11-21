#include <iostream>
#include "person.h"

Person::Person(std::string n){
	name=n;
}
std::string Person::getName(){
	return name;
}
void Person::printAboutMe(){
	std::cout << name;
	if(myBoat!=nullptr){
		std::cout << " has a boat with "
		<< myBoat ->info();
	}
	std::cout << std::endl;
}
