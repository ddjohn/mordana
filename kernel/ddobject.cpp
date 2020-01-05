#include "ddobject.h"

int Object::objects = 0;

Object::Object() {
    objects++;
}

int Object::getNumOfObjects() {
    return objects;
}
