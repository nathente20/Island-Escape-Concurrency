#include "world.h"
#include "barrier.h"

World::World(unsigned int numStranded) :
	dock(new Barrier),
	everyoneInBoat(0),
	numAtIsland(numStranded) {}


void World::escapeIsland(std::shared_ptr<Person> p) {
	while (true) {
		dock->wait(p, *this);
		if (p->isDriver) {
			everyoneInBoat.wait();
			{
				std::lock_guard<std::mutex> lk(naiLock);
				numAtIsland--;
			}
			p->row();
			atMainland.signal();
			return;
		}
		else {
			std::lock_guard<std::mutex> lk(boat);
			{
				std::lock_guard<std::mutex> lk(naiLock);
				numAtIsland--;
			}
			everyoneInBoat.signal();
			p->rest();
			atMainland.wait();
			naiLock.lock();
			if (numAtIsland == 0) {
				naiLock.unlock();
				return;
			}
			else {
				naiLock.unlock();
				p->row();
				boat.unlock();
			}
		}
		// returning to island
		{
			std::lock_guard<std::mutex> lk(naiLock);
			numAtIsland++;
		}
		acceptNextRiders();
		if (p->isTired()) {
			p->rest();
		}
	}
}

void World::acceptNextRiders() {
	dock->signalNextRiders(*this);
}

