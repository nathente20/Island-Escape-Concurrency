#include "world.h"
#include "barrier.h"

World::World(unsigned int numStranded) :
	dock(new Barrier),
	everyoneInBoat(0),
	numPeopleLeft(numStranded) {}


void World::waitForBoat(std::shared_ptr<Person> p) {
	dock->wait(p, *this);
}
