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
	std::mutex boat;
	Semaphore everyoneInBoat;
	Semaphore atMainland;

	std::mutex statsLock;
	std::vector<int> stats;

	std::mutex naiLock;
	unsigned long int numAtIsland;

public:
	World(unsigned long int numStranded);
	std::mutex printLock;
	std::mutex randLock;
	void escapeIsland(std::shared_ptr<Person> p);
	void acceptNextRiders();
	void incrementStat(enum Stats stat);
	void printSummary();
	void waitForEveryoneToBoard();
	
};

#endif
