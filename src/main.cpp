#include <iostream>
#include <thread>
#include <string>
#include <memory>
#include "person.h"
#include "world.h"

void triggerEscape(World& w, std::shared_ptr<Person> p) {
	w.escapeIsland(p);
}

int main(int argv, char** argc){
	int numChildren = 10;
	int numAdults = 10;

	std::vector<std::shared_ptr<Person>> stranded;
	for (auto c=1; c<=numChildren; c++) {
		std::string name = "Child " + std::to_string(c);
		stranded.push_back(std::make_shared<Person>(name, Weight::CHILD));
	}
	for (auto a=1; a<=numAdults; a++) {
		std::string name = "Adult " + std::to_string(a);
		stranded.push_back(std::make_shared<Person>(name, Weight::ADULT));
	}
	World w{stranded.size()};
	
	std::vector<std::thread> tStranded{};
	for (auto p : stranded){
		tStranded.push_back(std::thread(triggerEscape, std::ref(w), p));
	}
	for (auto i=0; i< tStranded.size(); i++) {
		tStranded[i].join();
	}
	
	w.printSummary();
	return 0;
}
