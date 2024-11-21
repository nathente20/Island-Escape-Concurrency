#include <iostream>
#include "person.h"

int main() {
	Person p{"Jan", Age::CHILD};
	p.printAboutMe();
	std::cout << p.getName() << " now rowing" << std::endl;
	p.row();
	std::cout << p.getName() << " done rowing" << std::endl;

	return 0;
}
