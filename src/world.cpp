#include "world.h"
#include "barrier.h"

World::World(unsigned int numStranded) :
	dock(new Barrier),
	everyoneInBoat(0),
	numPeopleLeft(numStranded) {}


void World::escapeIsland(std::shared_ptr<Person> p) {
	while (true) {
		dock->wait(p, *this);
		if (p->isDriver) {
			everyoneInBoat.wait();
			p->row();
			atMainland.signal();
			{
				std::lock_guard<std::mutex> lk(nplLock);
				numPeopleLeft--;
			}
			return;
		}
		else {
			std::lock_guard<std::mutex> lk(boat);
			everyoneInBoat.signal();
			p->rest();
			atMainland.wait();
			p->row();
			boat.unlock();
		}
		// returning to island
		acceptNextRiders();
		p->rest();
	}
}

void World::acceptNextRiders() {
	dock->signalNextRiders(*this);
}

