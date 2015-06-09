#ifndef H__ASECP_CONTEXT__H
#define H__ASECP_CONTEXT__H

#include <ASECP/AutoPtr.h>
#include <ASECP/Function.h>

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>

#include <angelscript.h>

namespace ASECP {

class Context : public Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<Context> Ptr;

	Context(asIScriptContext *context, bool shared = false);
	virtual ~Context();

	static Context::Ptr activeContext();

	AutoPtr<asIScriptContext> context() const;

	void prepare(Function::Ptr function);
	void execute();
	void abort();
	void suspend();
private:
	AutoPtr<asIScriptContext> _context;
};

}

#endif // H__ASECP_CONTEXT__H