#include <string>
#include "semaphore.h"
#include "boat.h"

Boat::Boat() :
	nextDriver(Semaphore(0)),
	nextPassenger(Semaphore(0)),
	numOccupants(0) {}

void Boat::setDriver(Person P) {

}

std::string Boat::info() {
	return "";
}
