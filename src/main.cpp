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
	std::vector<std::shared_ptr<Person>> stranded;
	for (auto j=0; j<50; j++) {
		std::string name = "Person " + std::to_string(j);
		stranded.push_back(std::make_shared<Person>(name, Weight::ADULT));
	}
	stranded.push_back(std::make_shared<Person>("Sole Child", Weight::CHILD));
	
	std::vector<std::thread> tStranded{};
	World w{stranded.size()};
	
	for (auto p : stranded){
		tStranded.push_back(std::thread(triggerEscape, std::ref(w), p));
	}

	for (auto i=0; i< tStranded.size(); i++) {
		tStranded[i].join();
	}

	return 0;
}
