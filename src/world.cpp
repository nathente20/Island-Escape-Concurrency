#include "world.h"
#include "barrier.h"

World::World() :
	dock(new Barrier) {}


void World::waitForBoat(std::shared_ptr<Person> p) {
	dock->wait(p, *this);
}
