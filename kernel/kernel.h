#ifndef KERNEL_H
#define KERNEL_H

#include "ddobject.h"
#include "string.h"

class Kernel : Object {
	public:
		Kernel();
		~Kernel();

		void run();

	private:
};

#endif //KERNEL_H
