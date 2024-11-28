/**
  @file
  @author Nathen Te <nlt47>
  @date November 27, 2024
  @section DESCRIPTION

  This file provides the definition of a Barrier. 
*/
#ifndef _BARRIER_H_
#define _BARRIER_H_
#include <string>
#include <mutex>
#include <vector>
#include <memory>
#include "semaphore.h"

#include "person.h"
#include "world.h"
class Person;
class World;

/**
 This is provides an interface for multiple to people to wait before getting on a boat. It controls the flow of threads that represent people trying to enter the boat. These threads all must start by waiting at the entrance. A pair that that does not exceed the weight limit of the boat is then determined and allowed to enter the barrier. Upon entry, the pair determine who will be driver and passenger before waiting at the exit.
 **/
class Barrier{
private:
	Semaphore nextToEnter; /**< The semaphore blocking the next pair of threads allowed to enter the barrier and only those threads*/
	Semaphore entranceLine; /**< The semaphore blocking everyone waiting to pair up to enter*/
	Semaphore exit; /**< The semaphore blocking the next pair of threads allowed to exit the barrier and only those threads*/

	std::mutex nextPairWaiting; /**< The lock used to prevent multiple simultaneous calls to signalNextRiders from allowing multiple pairs of people at the exit*/
	std::mutex lock; /**< The lock used to control modifications to remainingCapacity, prevents multiple people from trying to pair up with the same person simultaneously*/
	std::vector<std::shared_ptr<Person>> nextRiders; /**< Used to store the Person objects associated with a pair of threads passing through the barrier*/
	int remainingCapacity; /** Used to indicate permissible weight for next person in pair being formed, ties heavily into the Weight enum declared in Person*/
	bool rolesDecided; /** Used to track whether or not the Person objects in nextRiders have had roles assigned yet*/

	/**
	  p will repeatedly try to join the pair being formed outside the barrier that will the barrier. Used to ensure that a pair of people either has one child and one adult or two children. Prevents pair from forming while there are people already inside the barrier. Called by the wait function.
	  @param p The Person associated with the thread calling enter
	  @param w The context of the world, necessary for updating stats and proper timing
	*/
	void enter(std::shared_ptr<Person> p, World& w);
	/**
	  Updates the Person objects stored in nextRiders such that one is assigned driver and the other assigned passenger if not assigned already
	  @param w The context of the world, necessary for updating stats
	*/
	void decideDriverAndPassenger(World& w);
	/**
	  p will wait at the exit semaphore until signalNextRiders is called
	  @param p The Person associated with the thread calling exit 
	*/
	void waitAtExit(std::shared_ptr<Person> p);

public:
	/**
	  Constructor for the barrier
	*/
	Barrier();
	/**
	  Interface for a Person to wait for their turn at the boat (stored in w)
	  @param p The Person trying to pair up and pass through
	  @param w The context of the world, necessary for updating stats and proper timing
	*/
	void wait(std::shared_ptr<Person> p, World& w);
	/**
	  Interface for someone no longer using to boat to let the barrier know that the boat is free. Simultaneous calls will block on previous calls until said calls have been resolved. A call is resolved once the pair waiting at the exit is released and are no longer waiting to get on the boat.
	  @param w The context of the world, necessary for tracking state of boat and proper timing
	*/
	void signalNextRiders(World& w);
};

#endif
