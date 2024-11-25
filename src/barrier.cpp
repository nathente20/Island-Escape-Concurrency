#include "barrier.h"
#include <mutex>
#include <memory>
#include <iostream>

Barrier::Barrier() :
	waitingArea(Semaphore(0)),
	//entranceLine(Semaphore(0)),
	exit(Semaphore(0)),
	remainingCapacity(5),
	rolesDecided(false)
	{ }

void Barrier::enter(Person& p) {
	while (true) {
		lock.lock();
		// if there is space left for this person
		if (remainingCapacity >= p.weight) {
			remainingCapacity -= p.weight;
			// add person to collection of next riders
			nextRiders.push_back(std::make_shared<Person>(p));
			// if at full capacity
			if (remainingCapacity <= 1) {
				// signaling pair of people that will get on boat
				std::cout << p.getName() << " releasing the flood gates!!" << std::endl;
				waitingArea.signal();
				waitingArea.signal();
			}
			std::cout << p.getName() << " is verified!!" << std::endl;
			p.printAboutMe();
			lock.unlock();
			// this thread is ready to enter barrier
			waitingArea.wait();
			// let other thread try to get in
			//entranceLine.signal();
			return;
		}
		// failed entry
		lock.unlock();
	}
}

void Barrier::decideDriverAndPassenger() {
	{
		std::lock_guard<std::mutex> lk(lock);
		if (rolesDecided) {
			return;
		}
		
		std::shared_ptr<Person> p1;
		std::shared_ptr<Person> p2;
	}
}

void Barrier::leave(Person& p) {

}

void Barrier::wait(Person& p) {
	enter(std::ref(p));
	decideDriverAndPassenger();
	leave(std::ref(p));
}
