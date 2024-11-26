#include "world.h"
#include "barrier.h"

World::World(unsigned int numStranded) :
	dock(new Barrier),
	everyoneInBoat(0),
	numAtIsland(numStranded),
	stats(std::vector(Stats::NUM_STATS, 0)) {}


void World::escapeIsland(std::shared_ptr<Person> p) {
	while (true) {
		// await barrier before entering boat
		dock->wait(p, *this);
		// if you are the designated driver
		if (p->isDriver) {
			everyoneInBoat.wait();
			{
				std::lock_guard<std::mutex> lk(naiLock);
				numAtIsland--;
			}
			// you never end up leaving the dock alone
			p->row(*this, false, true);
			atMainland.signal();
			return;
		}
		// if you are the designated passenger
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
			// nobody left to escape don't go back for pickup
			if (numAtIsland == 0) {
				naiLock.unlock();
				return;
			}
			//  row back from mainland to island alone
			else {
				naiLock.unlock();
				p->row(*this, true, false);

				boat.unlock();
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
	}
}

void World::acceptNextRiders() {
	dock->signalNextRiders(*this);
}

void World::incrementStat(enum Stats s) {
	std::lock_guard<std::mutex> lk(statLock);
	stats[s]++;
}

