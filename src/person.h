/**
  @file
  @author Nathen Te <nlt47>
  @date November 27, 2024
  @section DESCRIPTION

  This file provides the definition of a Person trying to escape the deserted island in the toy problem. It also defines weight classes which are relevant to Person and other related classes such Barrier and World.
*/

#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include "semaphore.h"
#include "world.h"

class World;

// reliant on these values staying this way for how the world tracks stats
enum Weight {
	CHILD = 2,
	ADULT = 3,
	FULL = 5
};

/**
 This class represents a person trying to escape the island as defined in the toy example
*/
class Person{
private:
	const std::string name; /**< Used to label the associated person*/
	unsigned int energy; /**< Used to ensure that the conditions of the toy problem are satisfied. Purely for testing and never truly used.*/
public:
	bool isDriver; /**< Used to determine if this person will take on the role of driver when boarding the boat as a pair*/
	const enum Weight weight; /**< Identifies the weight class of the person. Necessary for ensuring the boat does not have too many adults/people*/

	/**
	  Constructor for person.
	  @param n Name assigned
	  @param weight Weight class assigned
	*/
	Person(std::string n, enum Weight weight);
	/**
	  Getter for the name

	*/
	std::string getName();
	/**
	  Test function to print identifying information on person
	*/
	void printAboutMe();
	/**
	  Used to simulate rowing by sleeping for 1-4 seconds at random. Prints out relevant information and updates statistics. Throws error if person has no energy.
	  @param w The context of the world
	  @param driverOnly Determines whether or now person is rowing alone or in a pair
	  @param w Determines whether or not person is rowing to or from the mainland
	*/
	void row(World& w, bool driverOnly, bool toMainland);
	/**
	  Used to simulate any scenario where a person is resting. This occurs upon return to the island or while as a passenger. Mainly for testing.
	*/
	void rest();
	/**
	  Used to determine whether or not a person can row or now. Usd mainly for testing.
	*/
	bool isTired();

};

#endif
