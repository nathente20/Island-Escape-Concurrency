#include "barrier.h"
#include <mutex>
#include <memory>
#include <iostream>
#include <thread>

Barrier::Barrier() :
	nextToEnter(Semaphore(0)),
	entranceLine(Semaphore(1)),
	exit(Semaphore(2)),
	remainingCapacity(Weight::FULL),
	rolesDecided(false)
	{ }

bool Barrier::enter(std::shared_ptr<Person> p, World& w) {
	entranceLine.wait();
	bool retry;
	{
		lock.lock();
		std::cout << "Trying " << p->getName() << std::endl;
		// makes output easier to read
		std::this_thread::sleep_for(std::chrono::microseconds(100000));
		// if there is space left for this person
		if (remainingCapacity >= p->weight) {
			retry = false;

			remainingCapacity -= p->weight;
			// add person to collection of next riders
			nextRiders.emplace_back(p);
			// if at full capacity
			if (remainingCapacity <= 1) {
				// signaling pair of people that will get on boat
				nextToEnter.signal();
				nextToEnter.signal();
				// not calling entranceLine.signal since we are no longer accepting people
			}
			else {
				// allow another thread to try to get in if incomplete pair 
				entranceLine.signal();
			}
			lock.unlock();
			// this thread is ready to enter barrier
			nextToEnter.wait();
		}
		else {
			retry = true;
			lock.unlock();
			entranceLine.signal();
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
	}
	return retry;
}

void Barrier::decideDriverAndPassenger(World& w) {
	{
		std::lock_guard<std::mutex> lk(lock);
		if (rolesDecided) {
			// no longer need to store Person objects associated with desired threads
			nextRiders.clear();
			//std::cout << "No work for me!" << std::endl;
			return;
		}
		
		std::shared_ptr<Person> p1 = nextRiders[0];
		std::shared_ptr<Person> p2 = nextRiders[1];

		if (p1->weight > p2->weight) {
			p1->isDriver = true;
			p2->isDriver = false;
		}
		else {	
			p1->isDriver = false;
			p2->isDriver = true;
		}

		std::cout << "===============================" << std::endl;
		std::cout << "Determined roles" << std::endl;
		std::cout << p1->getName() << " is ";
		if (!(p1->isDriver)) {
			std::cout << "not";
		}
		std::cout << " driver" << std::endl;
		std::cout << p2->getName() << " is ";
		if (!(p2->isDriver)) {
			std::cout << "not";
		}
		std::cout << " driver" << std::endl;

		rolesDecided = true;
	}
}

void Barrier::leave(std::shared_ptr<Person> p, World& w) {
	{
		std::lock_guard<std::mutex> lk(lock);
		// reset Barrier internal state
		remainingCapacity += p->weight;
		if (remainingCapacity == Weight::FULL) {
			rolesDecided = false;
		}
	}
	// waiting for signalNextRiders to be 
	// we do not know for sure if boat is ready for more passengers
	exit.wait();
}

void Barrier::signalNextRiders(World& w) {
	exit.signal();
	exit.signal();
	// do I need a wait here that links to a semaphore the boat keeps track of?
	// can start looking for the next pair of people
	entranceLine.signal();
}

void Barrier::wait(std::shared_ptr<Person> p, World& w) {
	while (enter(p, std::ref(w)));
	decideDriverAndPassenger(std::ref(w));
	leave(p, std::ref(w));
}
