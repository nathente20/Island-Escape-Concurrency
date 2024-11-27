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

void Barrier::enter(std::shared_ptr<Person> p, World& w) {
	bool retry = true;
	while (retry) {
		entranceLine.wait();
		lock.lock();
		// if there is space left for this person
		if (remainingCapacity >= p->weight) {
			retry = false;

			remainingCapacity -= p->weight;
			// add person to collection of next riders
			nextRiders.emplace_back(p);
			// if at full capacity
			if (remainingCapacity <= 1) {
				// increment counters for trips where a pair riding
				auto whichPairInBoat = static_cast<Stats>(Weight::FULL - remainingCapacity);
				w.incrementStat(static_cast<Stats>(whichPairInBoat));
				// signaling pair of people that will get on together 
				nextToEnter.signal();
				nextToEnter.signal();
				// not signaling entranceLine since we are no longer accepting people
			}
			// still need one more rider
			else {
				// allow another thread to try entry
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
			// prevents issue where this thread cuts to the front of line on retry
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
	}
}

void Barrier::decideDriverAndPassenger(World& w) {
	{
		std::lock_guard<std::mutex> lk(lock);
		if (rolesDecided) {
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

		rolesDecided = true;
		nextRiders.clear();
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
	// waiting for signalNextRiders to be called
	// we do not know for sure if boat is ready for more passengers
	exit.wait();
}

void Barrier::signalNextRiders(World& w) {
	exit.signal();
	exit.signal();
	w.waitForEveryoneToBoard();
	// can start looking for the next pair of people
	entranceLine.signal();
}

void Barrier::wait(std::shared_ptr<Person> p, World& w) {
	enter(p, std::ref(w));
	decideDriverAndPassenger(std::ref(w));
	leave(p, std::ref(w));
}
