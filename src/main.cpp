/**
  @mainpage CS 361 - Homework 7
  @section DESCRIPTION

  This program simulates a toy problem of adults and children trying to escape an island. It takes two whole (positive integer) arguments specifying (1) the number adults and (2) the number of children stranded on an island. All are trying to escape using one boat. The boat can only allow either one person of any age, two children, or a child and adult. It cannot support two adults. A person that rows 4 or more times must rest before rowing again. To rest, they either are a passenger in the boat while someone else drives, or they wait on the island and do not pair up. These constraints were used to motivate this simulation.

*/

/**
  @file
  @author Nathen Te <nlt47>
  @date November 27, 2024
  @section DESCRIPTION

  This file is the driver simulating a number of adults and children escaping from a remote island with one boat.
*/


#include <iostream>
#include <thread>
#include <string>
#include <memory>
#include "person.h"
#include "world.h"

/**
  This is used to seed a thread that is simulating a person trying to escape from the island.
  @param w The world context
  @param p The person trying to escape
**/
void triggerEscape(World& w, std::shared_ptr<Person> p) {
	w.escapeIsland(p);
}

/**
  This is used to parse command line integers. If the argument passed is a valid positive integer, then that number is returned. If not, -1 is returned.
  @param numStr String representation of the number being parsed
  @return Returns an integer that either represents failure (-1) or the parsed whole number
**/
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
