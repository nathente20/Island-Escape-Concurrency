#ifndef _BARRIER_H_
#define _BARRIER_H_
#include <string>
#include <mutex>
#include <vector>
#include <memory>
#include "semaphore.h"

#include "person.h"
#include "world.h"
class Person;
class World;

class Barrier{
private:
	Semaphore nextToEnter;
	Semaphore entranceLine;
	Semaphore exit;

	std::mutex lock;
	std::vector<std::shared_ptr<Person>> nextRiders;
	int remainingCapacity;
	bool rolesDecided;

	void decideDriverAndPassenger(World& w);
	void leave(std::shared_ptr<Person> p, World& w);

public:
	Barrier();
	void wait(std::shared_ptr<Person> p, World& w);
	void signalNextRiders(World& w);
	bool enter(std::shared_ptr<Person> p, World& w);
};

#endif
