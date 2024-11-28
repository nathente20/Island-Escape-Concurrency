/**
  @file
  @author Nathen Te <nlt47>
  @date November 27, 2024
  @section DESCRIPTION

  This file provides the definition of a Barrier. This is provides an interface for multiple to people to wait before getting on a boat. It  controls the flow of threads that represent people trying to enter the boat. These threads all must start by waiting at the entrance. A pair that that does not exceed the weight limit of the boat is then determined and allowed to enter the barrier. Upon entry, the pair determine who will be driver and passenger before waiting at the exit.
*/
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

	std::mutex nextPairWaiting;
	std::mutex lock;
	std::vector<std::shared_ptr<Person>> nextRiders;
	int remainingCapacity;
	bool rolesDecided;

	void enter(std::shared_ptr<Person> p, World& w);
	void decideDriverAndPassenger(World& w);
	void waitAtExit(std::shared_ptr<Person> p, World& w);

public:
	Barrier();
	void wait(std::shared_ptr<Person> p, World& w);
	void signalNextRiders(World& w);
};

#endif
