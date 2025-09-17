Nathen Te<br/>
nlt47@drexel.edu

To build this code, call `make obj/main` <br/>
To run this executable call `./obj/main **numAdults** **numChildren**` where numAdults and numChildren are whole arguments<br/>
Or call `make run` to automatically generate the obj/main executable then run it with arguments 7 and 9. <br/>

#1
I mainly used a barrier to protect the boat by ensuring that a valid pair of people board the boat from the island. This involved a mix of locks and semaphores used to block people from entering, make a pair wait at the entrance until it was completely formed, and wait until the roles were determined for the pair in the barrier before waiting at the exit.<br/>
I also represented the boat itself as a lock since it is a resource that can only be used by one rowing group at a time. <br/>
I also use a semaphore to allow the boat and barrier to communicate with one another as to whether or not the pair exiting the barrier has completely entered the boat. This is to prevent an extremely unlikely race condition where the pair exits the barrier, a new pair is formed, and both pairs are now shuffled and could enter the boat in an undesirable configuration. <br/>

#2
Threads decided what role to take in the boat based based on which way they are rowing. When rowing back from the mainland, it is assumed they are alone the previous driver escaped, thus making the passenger take on the role of driver. <br/>
When leaving the island, all of the decision-making is done in the barrier/dock. It is assumed that there will ALWAYS be a pair of people leaving the island together. If this was not the case, it would mean that someone would have rowed to the mainland and returned to the island alone; however, this is already covered as a special case allowing the passenger to escape if they are at the mainland and there is nobody left to save. Back to the barrier, once a pair is determined and inside the barrier, they must decide roles before either can exit. If there is an adult in the pair, they wil ALWAYS be the driver to prevent an edge cases that can softlock the game. For example, if the child drove and the passenger adult escaped to the mainland but the child was exhausted from driving, then the boat will have to wait at the mainland, wasting time at best or stranding everyone left on the island at worst.<br/>

#3
I reset the boat for the next group by releasing the lock on the boat and signaling to the barrier that it can release the next pair of people to board the boat.

#4
I am certain that everyone escapes as I have written the example such that there is always at least one child left until the very end. When rowing from the mainland, the adult is always a driver if they are present to prevent the child from exhausting themselves and having to row to and back. The passenger, always a child, will then row back. This makes it so that there is always at least one child. That child also gets rest before each ride as it either rests on the way to the mainland, or upon returning to to the island, preventing exhaustion. Since I have always have one child, it is always possible to take actions that will move th puzzle closer to a state of completion by having a driver go to the mainland, escape, then having a child row the boat back to save more people. This only is not the case when there are no people left on the island at which point the child will just escape instead of rowing back.

#5
The most challenging part of this assignment was the barrier and making sure that the actions of the pair were synced up in a realistic way. There were also weird interactions between the boat letting people on and the barrier that had to be accounted for.


