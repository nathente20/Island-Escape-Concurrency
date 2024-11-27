#include <iostream>
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
			{
				std::lock_guard<std::mutex> lk(printLock);
				std::cout << p->getName() << " got into driver's seat of boat." << std::endl;
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
				std::lock_guard<std::mutex> lk(printLock);
				std::cout << p->getName() << " got into passenger seat of boat." << std::endl;
			}
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
			// row back from mainland to island alone
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

void World::printSummary() {
	std::cout <<
	"=================" << std::endl <<
	"Summary of Events" << std::endl <<
	"Boats traveled to mainland: " << stats[Stats::TO_MAINLAND] << std::endl <<
	"Boats returned to island: " << stats[Stats::TO_ISLAND] << std::endl <<
	"Boats with 2 children: " << stats[Stats::TWO_CHILDREN] << std::endl <<
	"Boats with 1 child and 1 adult: " << stats[Stats::ONE_EACH] << std::endl <<
	"Boats with only 1 person (child or adult): " << stats[Stats::DRIVER_ONLY] << std::endl <<
	"Times adults were the driver: " << stats[Stats::ADULT_DROVE] << std::endl <<
	"Times children were the driver: " << stats[Stats::CHILD_DROVE] << std::endl;
}
