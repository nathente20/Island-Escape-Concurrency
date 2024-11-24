class Barrier{

private:
	// used to keep track of threads that will be guaranteed next onto the boat
	Semaphore entranceGate;
	Semaphore exitGate;
	// actually do not need this AND remainingWeight, remainingWeight keeps and implicit total of people
	//unsigned int numPeopleWaiting; // number of people outside of barrier that have been verified to be next to get into the boat
	unsigned int remainingWeight; // emtpy 5, adults weight 3, children weight 2
	unsigned int passengersAtExit;
	bool rolesDetermined;
	std::vector<Person> occupants;
	std::mutex lk;
	
	// order of exit does not matter so long as we set the states of the people before they all exit
	void enter(Person& p);
	void determineDriverAndPassenger();
	void leave(Person& p);

public:
	void wait(Person& p);

};
