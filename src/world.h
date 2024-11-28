/**
  @file
  @author Nathen Te <nlt47>
  @date November 27, 2024
  @section DESCRIPTION

  This file provides the definition of the World context for which there is a group of people trying to escape an island with only one boat.
*/
#ifndef _H_WORLD_
#define _H_WORLD_

#include <mutex>
#include <memory>
#include "semaphore.h"
#include "person.h"
#include "barrier.h"
class Person;
class Barrier;

/**
 This defines the different stats being tracked to printed out later. It is laid out in a way that is closely tied in with the Weight enum and how it is used.
**/
enum Stats {
	TO_MAINLAND,
	TO_ISLAND,
	CHILD_DROVE, // lines up with Child weight 2
	ADULT_DROVE, // lines up with Adult weight 3
	TWO_CHILDREN,// lines up with 2*Child weight 4
	ONE_EACH,	 // lines up with Adult+Child weight 5
	DRIVER_ONLY,

	NUM_STATS
};


/**
  This defines the World context for the toy example of people trying to escape an island with only one boat.
**/
class World {
private:
	Barrier* dock; /**< Used to sort people into pair that can ride the boat and block everyone trying to escape*/
	std::mutex boat; /**< Represents usage of the boat*/
	Semaphore everyoneInBoat; /**< Used to signal to the barrier once the pair that exited has claimed control of the boat*/
	Semaphore atMainland; /**< Used to allow the driver to communicate to the passenger that the boat has arrived at the mainland*/

	std::mutex statsLock; /**< Used to ensure only one process is modifying stats at a time*/
	std::vector<int> stats; /**< Counts of the stats outlined in the Stats enum*/

	std::mutex naiLock; /**< Used to ensure only one process is modifying numAtIsland at a time*/
	unsigned long int numAtIsland; /**< Total number of people that are stranded at the island*/

public:
	/**
	  Constructor of the world.
	  @param numStranded The number of people starting off at the island since the world does not store the threads/Person objects representing stranded people
	**/
	World(unsigned long int numStranded);
	std::mutex printLock; /**< Used to ensure only one process is printing to the console at a time*/
	std::mutex randLock; /**< Used to ensure only one process is taking from the randomizer at a time*/
	/**
	  Used to simulate a person trying to escape the island
	  @param p The person trying to escape
	**/
	void escapeIsland(std::shared_ptr<Person> p);
	/**
	  Interface that wraps around the dock's method to signal release of a pair of people waiting at the exit
	**/
	void acceptNextRiders();
	/**
	  Increments the count in the category specified by the user with thread safety
	  @param stat The category to be incremented
	**/
	void incrementStat(enum Stats stat);
	/**
	  Used to print the stat totals after everyone has escaped the island. Assumes there is only one thread running at this point.
	**/
	void printSummary();
	/**
	  Interface for waiting at everyoneInBoat. Used to prevent driver from rowing until both threads in a pair are "in the boat"
	**/
	void waitForEveryoneToBoard();
};

#endif
