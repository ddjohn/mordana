#ifndef DD_OBJECT_H
#define DD_OBJECT_H

class Object {
	public:
		Object();
		int getNumOfObjects();

	private:
		static int objects;
};

#endif //DD_OBJECT_H
