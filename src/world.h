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
	std::mutex boat;
	std::mutex nplLock;
	unsigned int numPeopleLeft;

public:
	World();
	void waitForBoat(std::shared_ptr<Person> p);
	
};

#endif
