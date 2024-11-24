#include "barrier.h"


void Barrier::enter(Person& p) {
	while (true) {
		// if not enough room left you have to try again 
		lk.lock();
		if (p.weight > remainingWeight) {
			lk.unlock();
			continue;
		}
		break;
	}

	remainingWeight -= p.weight;
	occupants.push(p); // TODO: this is not correct api call

	// if we are at capacity
	if (remainingWeight < 2) {
		entranceGate.signal();
		entranceGate.signal();
	}

	// signal other soon-to-be occupant to enter
	lk.unlock();
	entranceGate.wait();
}

void Barrier::determineDriverAndPassenger() {
	lk.lock();
	// if other thread did work already, then move on
	if (rolesDetermined) {
		lk.unlock();
		return;
	}
	// iterate through occupants
	// heaviest is driver
	// lightest is passenger 
	rolesDetermned = true;
	lk.unlock();
}

void Barrier::leave(Person& p) {
	lk.lock();
	// remove one person from the vector of people
	passengersAtExit++;
	// if everyone is waiting at exit
	if (passengersAtExit == 2) {
		// let other person waiting get off
		exitGate.signal();
		// reset state of barrier
		rolesDetermined = false;
		passengersAtExit = 0;
		remainingWeight = 5;
		lock.unlock();
		return;
	}
	lock.unlock();
	exitGate.wait();
}

void Barrier::wait(Person& p) {
	enter(std::ref(p));
	leave(std::ref(p));
}
