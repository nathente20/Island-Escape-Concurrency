#include "barrier.h"
#include <mutex>
#include <memory>
#include <iostream>
#include <thread>

Barrier::Barrier() :
	waitingArea(Semaphore(0)),
	entranceLine(Semaphore(1)),
	exit(Semaphore(0)),
	remainingCapacity(Weight::FULL),
	rolesDecided(false)
	{ }

bool Barrier::enter(Person& p) {
	//entranceLine.wait();
	bool retry;
	{
		lock.lock();
		std::cout << "Trying " << p.getName() << std::endl;
		// makes output easier to read
		std::this_thread::sleep_for(std::chrono::microseconds(100000));
		// if there is space left for this person
		if (remainingCapacity >= p.weight) {
			retry = false;

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
			// allow another thread to try to get in 
			//entranceLine.signal();
			// this thread is ready to enter barrier
			waitingArea.wait();
			std::cout << p.getName() << " is verified!!" << std::endl;
			p.printAboutMe();
		}
		else {
			retry = true;

			std::cout << p.getName() << " is too heavy" << std::endl;
			lock.unlock();
			//entranceLine.signal();
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
	}
	return retry;
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
	while (enter(std::ref(p)));
	decideDriverAndPassenger();
	leave(std::ref(p));
}
