#include <ASECP/FunctionParam.h>
#include <ASECP/Exceptions.h>
#include <ASECP/Function.h>

namespace ASECP {

FunctionParam::FunctionParam(Poco::AutoPtr<Function> function, asUINT index) : _function(function), _index(index)
{
	load();
}

FunctionParam::~FunctionParam()
{

}

Poco::AutoPtr<Function> FunctionParam::function() const
{
	return _function;
}

void FunctionParam::load()
{
	const char* name;
	const char* defaultarg;
	throwOnError(_function->function()->GetParam(_index, &_typeid, &_flags, &name, &defaultarg));
	if (name)
		_name = std::string(name);
	if (defaultarg)
		_defaultarg = std::string(defaultarg);
}

}
