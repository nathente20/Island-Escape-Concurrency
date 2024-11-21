#include "semaphore.h"

void Semaphore::wait() {
	std::unique_lock ul(l);
	cv.wait(ul, [this] { return count>0; });
	count--;
	ul.unlock();
}

void Semaphore::signal() {
	l.lock();
	count++;
	l.unlock();
	cv.notify_all();
}

