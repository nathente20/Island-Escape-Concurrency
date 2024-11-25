#ifndef _BARRIER_H_
#define _BARRIER_H_
#include <string>
#include <mutex>
#include <vector>
#include "semaphore.h"

#include "person.h"
class Person;

class Barrier{
private:
	Semaphore waitingArea;
	Semaphore entranceLine;
	Semaphore exit;

	std::mutex lock;
	std::vector<std::shared_ptr<Person>> nextRiders;
	int remainingCapacity;
	bool rolesDecided;

	//void enter(Person& p);
	void decideDriverAndPassenger();
	void leave(Person& p);

public:
	Barrier();
	void wait(Person& p);

	bool enter(Person& p);
	//friend class TestBarrier;
};

/*
class TestBarrier {
public:
	static void run(Barrier& brr, Person& p);
};
*/

#endif
