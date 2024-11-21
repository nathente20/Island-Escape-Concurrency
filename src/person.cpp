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
	std::cout << std::endl;
}
