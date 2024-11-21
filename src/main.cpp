
#include "person.h"
#include "boat.h"

int main(int argv, char** argc){
	Person* A = new Person("Mike");
	Person* B = new Person("Ted");
	Boat* bt = new Boat(B);
	A->printAboutMe();
	B->printAboutMe();
	return 0;
}
