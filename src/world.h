#ifndef _H_WORLD_
#define _H_WORLD_

#include <mutex>
#include <memory>
#include "semaphore.h"
#include "person.h"
#include "barrier.h"
class Person;
class Barrier;

class World {
private:
	Barrier* dock;
	Semaphore everyoneInBoat;
	Semaphore atMainland;
	std::mutex boat;
	std::mutex naiLock;
	unsigned int numAtIsland;
	bool driverOnly;

public:
	World(unsigned int numStranded);
	void escapeIsland(std::shared_ptr<Person> p);
	void acceptNextRiders();
	
};

#endif
