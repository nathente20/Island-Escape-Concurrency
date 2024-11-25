#include "barrier.h"
#include <mutex>
#include <memory>
#include <iostream>

Barrier::Barrier() :
	waitingArea(Semaphore(0)),
	//entranceLine(Semaphore(0)),
	exit(Semaphore(0)),
	remainingCapacity(Weight::FULL),
	rolesDecided(false)
	{ }

void Barrier::enter(Person& p) {
	while (true) {
		lock.lock();
		p.row();
		// if there is space left for this person
		if (remainingCapacity >= p.weight) {
			remainingCapacity -= p.weight;
			std::cout << "Capacity is " << remainingCapacity << std::endl;
			// add person to collection of next riders
			nextRiders.push_back(std::make_shared<Person>(p));
			// if at full capacity
			if (remainingCapacity <= 1) {
				// signaling pair of people that will get on boat
				std::cout << p.getName() << " has made boat reach full capacity!!" << std::endl;
				waitingArea.signal();
				waitingArea.signal();
			}
			lock.unlock();
			// this thread is ready to enter barrier
			waitingArea.wait();
			// let other thread try to get in
			//entranceLine.signal();
			std::cout << p.getName() << " is verified!!" << std::endl;
			p.printAboutMe();
			return;
		}
		// failed entry
		std::cout << p.getName() << " is too heavy" << std::endl;
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
