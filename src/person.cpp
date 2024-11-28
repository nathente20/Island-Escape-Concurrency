#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <stdexcept>
#include "person.h"
#include "barrier.h"

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
		". My energy level is " <<
		energy <<
		std::endl;
}

void Person::row(World& w, bool driverOnly, bool toMainland){
	if (isTired()){
		throw std::runtime_error("Exception caught: Exhausted person assigned as driver. Simulation failed");
	}

	// stat tracking
	if (toMainland) {
		w.incrementStat(Stats::TO_MAINLAND);
		{
			std::lock_guard<std::mutex> lk(w.printLock);
			std::cout << "Boat is traveling from island to mainland." << std::endl;
		}
	}
	else {
		w.incrementStat(Stats::TO_ISLAND);
		{
			std::lock_guard<std::mutex> lk(w.printLock);
			std::cout << "Boat is traveling from mainland to island." << std::endl;
		}
	}
	if (driverOnly) {
		w.incrementStat(Stats::DRIVER_ONLY);
	}
	// increment CHILD_DROVE or ADULT_DROVE
	auto whichDriver = static_cast<Stats>(weight);
	w.incrementStat(whichDriver);

	// simulate time doing work 
	int waitTime;
	{
		std::lock_guard<std::mutex> lk(w.randLock);
		// [1 000 000, 4 000 000]
		waitTime = (std::rand() % 3000000) + 1000000; 
	}
	std::this_thread::sleep_for(std::chrono::microseconds(waitTime));
	energy--;
}

void Person::rest(){
	std::this_thread::sleep_for(std::chrono::microseconds(1000000));
	if (energy == 0) {
		energy++;
	}
}

bool Person::isTired() {
	return energy == 0;
}


