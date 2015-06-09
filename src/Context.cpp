#include <ASECP/Context.h>
#include <ASECP/Exceptions.h>

namespace ASECP {

Context::Context(asIScriptContext *context, bool shared) : _context(context, shared)
{

}

Context::~Context()
{

}

AutoPtr<asIScriptContext> Context::context() const
{
	return _context;
}

Context::Ptr Context::activeContext()
{
	asIScriptContext *ctx = asGetActiveContext();
	if (!ctx)
		return NULL;

	return new Context(ctx, true);
}

void Context::prepare(Function::Ptr function)
{
	throwOnError(_context->Prepare(function->function()));
}

void Context::execute()
{
	throwOnError(_context->Execute());
}

void Context::abort()
{
	throwOnError(_context->Abort());
}

void Context::suspend()
{
	throwOnError(_context->Suspend());
}

}
