#include <iostream>
#include <thread>
#include <string>
#include <memory>
#include "person.h"
#include "world.h"

void triggerEscape(World& w, std::shared_ptr<Person> p) {
	w.escapeIsland(p);
}

int parseNumber(std::string numStr) {
	try {
		unsigned int parsed = stoi(numStr);
		if (parsed < 1) {
			return -1;
		}
		return parsed;
	}
	catch (std::exception) {
		return -1;
	}
}

int main(int argc, char** argv){
	if (argc != 3) {
		std::cout << "Unable to run race. Please provide two whole number arguments. First for number adults. Second for number of children" << std::endl;
		return -1;
	}

	int numAdults = parseNumber(std::string{argv[1]});
	int numChildren = parseNumber(std::string{argv[2]});
	if (numChildren == -1 || numAdults == -1) {
		std::cout << "Unable to run race. Please provide two whole number arguments. First for number adults. Second for number of children" << std::endl;
		return -1;
	}

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
