#include "ddtrace.h"

int Trace::scope = 0;

Trace::Trace(String clazz, String method, String file, int line) {
	this->clazz = clazz;
	this->method = method;

//	char buf[256];
//	sprintf(buf, "--> (%d) %s::%s (%s, line %d)", ++scope, clazz.c_str(), method.c_str(), file.c_str(), line);
//	std::cerr << buf << std::endl;
}

Trace::~Trace() {
//	char buf[256];
//	sprintf(buf, "<-- (%d) %s::%s", scope--, clazz.c_str(), method.c_str());
//	std::cerr << buf << std::endl;
}
	
void Trace::log(String msg) {
//	char buf[256];
//	sprintf(buf, "### (%d) %s::%s %s", scope, clazz.c_str(), method.c_str(), msg.c_str());
//	std::cerr << buf << std::endl;
}

