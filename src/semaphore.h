/**
  @file
  @author Nathen Te <nlt47>
  @date November 27, 2024
  @section DESCRIPTION

  This file provides the definition of a semaphore.
*/
/**Start of Cited Code
   Based on the implementation of Semaphore provided by Professor Boady on Blackboard Week 3
*/
#ifndef _H_SEMAPHORE_
#define _H_SEMAPHORE_

#include <mutex>
#include <condition_variable>

/**
 This class represents a semaphore 
*/
class Semaphore {
	private:
		std::mutex l; /**< The lock for the count member */
		std::condition_variable cv; /**< The counter variable used to sleep threads until a signal is given */
		unsigned int count; /**< The count of how many signals remaining that have not been waited on */

	public:
		/**
		 The default constructor for a Semaphore, assumes that the default count is 1.
		*/
		Semaphore() { count = 1; }
		/**
		 The constructor for giving custom starting counts for the Semaphore.
		 @param c The desired starting count
		*/
		Semaphore(unsigned int c) : count(c) {}
		
		/**
		 Used to wait on the semaphore until there is an available signal
		*/
		void wait();
		/**
		 Used to signal availability of the semaphore to anyone waiting.
		*/
		void signal();
};


/** End of Cited Code */

#endif
