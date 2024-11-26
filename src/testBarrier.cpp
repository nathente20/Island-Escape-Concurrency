#include "barrier.h"
#include "person.h"
#include <iostream>
#include <thread>

/*
void TestBarrier::run(Barrier& brr, Person& p) {
	brr.enter(std::ref(p));
}
*/

void run(World& w, std::shared_ptr<Person> p) {
	//w.waitForBoat(p);
	w.escapeIsland(p);
}

int main() {

	std::shared_ptr<Person> a = std::make_shared<Person>("Jerry", Weight::ADULT);
	std::shared_ptr<Person> b = std::make_shared<Person>("Morty", Weight::CHILD);
	std::shared_ptr<Person> c = std::make_shared<Person>("Summer", Weight::CHILD);
	std::shared_ptr<Person> d = std::make_shared<Person>("Beth", Weight::ADULT);
	std::shared_ptr<Person> e = std::make_shared<Person>("Rick", Weight::ADULT);
	std::vector<std::shared_ptr<Person>> fam{
		//a, b, c, d, e
		a, d, e, b
	};
	std::vector<std::thread> tFam{};
	World w{fam.size()};
	
	for (auto j=0; j<fam.size(); j++) {
		//tFam.push_back(std::thread(run, std::ref(brr), fam[j]));
		tFam.push_back(std::thread(run, std::ref(w), fam[j]));
	}

	for (auto i=0; i< tFam.size(); i++) {
		tFam[i].join();
	}

	return 0;
}
