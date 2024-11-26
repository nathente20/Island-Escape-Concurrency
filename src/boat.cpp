#include <string>
#include "semaphore.h"

Boat::Boat() :
	nextDriver(Semaphore(0)),
	nextPassenger(Semaphore(0)),
	twoPeopleOn(Semaphore(0)),
	arrival(Semaphore(0)),
	numOccupants(0) {}

void Boat::boardDriver(Person p) {
	inUse.lock();
	numOccupants++;
	if (numOccupants < 2) {
		inUse.unlock();
		// wait until passenger is found
		twoPeopleOn.wait();
	}
	else {
		twoPeopleOn.signal();
	}
	// start rowing
	p.row();
	// done rowing
	arrival.signal();
	// get off island (kill thread)

}

void Boat::boardPassenger(Person p) {
	inUse.lock();
	if (numOccupants < 2) {
		inUse.unlock();
		// wait until driver is found
		twoPeopleOn.wait();
	}
	else {
		twoPeopleOn.signal();
	}
	p.rest();
	// wait for driver to finish rowing
	arrival.wait();
	// start rowing back
	p.row();
	// done rowing back
	// passenger will release the lock ALWAYS
	inUse.unlock();
	// person returns to appropriate queue based on classification
}

std::string Boat::info() {
	return "";
}
