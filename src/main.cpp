
#include "person.h"
#include "boat.h"

int main(int argv, char** argc){
	Person* A = new Person("Mike", Age::ADULT);
	Person* B = new Person("Ted", Age::ADULT);
	Boat* bt = new Boat();
	A->printAboutMe();
	B->printAboutMe();
	return 0;
}
