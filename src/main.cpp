
#include "person.h"
#include "boat.h"

void escape(std::shared_ptr<Person> p, Barrier& dock);

int main(int argv, char** argc){
	Person* A = new Person("Mike", Age::ADULT);
	Person* B = new Person("Ted", Age::ADULT);

	std::shared_ptr<Person> a = std::make_shared<Person>("Jerry", Weight::ADULT);

	Boat* bt = new Boat();
	A->printAboutMe();
	B->printAboutMe();
	return 0;
}

void escape(std::shared_ptr<Person> p, Barrier& dock) {
	while (true) {
		dock.wait(p);
		if (p->isDriver) {
			everyoneInBoat.wait();
			p->row();
			w->arrivedAtMainland.signal();
			break;
		}
		else {
			boat.lock();
			everyoneInBoat.signal();
			p->rest();
			w->arrivedAtMainland.wait();
			p->row();
			boat.unlock();
		}
	}
}

