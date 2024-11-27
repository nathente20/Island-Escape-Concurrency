#ifndef _H_WORLD_
#define _H_WORLD_

#include <mutex>
#include <memory>
#include "semaphore.h"
#include "person.h"
#include "barrier.h"
class Person;
class Barrier;

enum Stats {
	TO_MAINLAND,
	TO_ISLAND,
	CHILD_DROVE, // lines up with Child weight 2
	ADULT_DROVE, // lines up with Adult weight 3
	TWO_CHILDREN,// lines up with 2*Child weight 4
	ONE_EACH,	 // lines up with Adult+Child weight 5
	DRIVER_ONLY,

	NUM_STATS
};

class World {
private:
	Barrier* dock;
	Semaphore everyoneInBoat;
	Semaphore atMainland;
	std::mutex boat;
	std::mutex naiLock;
	unsigned int numAtIsland;
	std::vector<int> stats;
	std::mutex statLock;

public:
	World(unsigned int numStranded);
	void escapeIsland(std::shared_ptr<Person> p);
	void acceptNextRiders();
	void incrementStat(enum Stats stat);
	std::mutex printLock;
	void printSummary();
	
};

#endif
