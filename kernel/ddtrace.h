#ifndef TRACE_H
#define TRACE_H

#include "ddstring.h"
#include "ddobject.h"

#define CLASS(CLASS) \
	static const char* abcClass = CLASS; 

#define METHOD(METHOD) \
	Trace abcTrace(abcClass, METHOD, __FILE__, __LINE__);

#define INFO(MSG) \
	{ \
		std::stringstream str; \
		str << MSG; \
		abcTrace.log(str.str()); \
	}

#define EXCEPTION(EXCEPTION) \
	throw std::logic_error(EXCEPTION);

class Trace {

public:
	Trace(String clazz, String meths, String file, int line);
	~Trace();
	void log(String msg);

private:
	String clazz;
	String method;
	static int scope;
};

#endif
