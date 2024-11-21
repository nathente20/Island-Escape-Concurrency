#include "semaphore.h"
#include "boat.h"
#include <string>

Boat::Boat() :
	nextDriver(Semaphore(0)),
	nextPassenger(Semaphore(0)),
	numOccupants(0) {}

std::string Boat::info() {
	return "";
}
