#include "barrier.h"
#include "person.h"
#include <iostream>
#include <thread>

/*
void TestBarrier::run(Barrier& brr, Person& p) {
	brr.enter(std::ref(p));
}
*/

void run(Barrier& brr, Person& p) {
	brr.wait(std::ref(p));
}

int main() {
	Person a{"Jerry", Weight::ADULT};
	Person b{"Morty", Weight::CHILD};
	Person c{"Summer", Weight::CHILD};
	Person d{"Beth", Weight::ADULT};
	Person e{"Rick", Weight::ADULT};
	std::vector<Person> fam{
		b, c, d, e, a
	};
	std::vector<std::thread> tFam{};
	
	Barrier brr;
	for (auto j=0; j<fam.size(); j++) {
		//std::thread t(TestBarrier::run, std::ref(brr), std::ref(p));
		//std::thread t(run, std::ref(brr), std::ref(fam[j]));
		tFam.push_back(std::thread(run, std::ref(brr), std::ref(fam[j])));
	}

	for (auto i=0; i< tFam.size(); i++) {
		tFam[i].join();
	}

	return 0;
}
