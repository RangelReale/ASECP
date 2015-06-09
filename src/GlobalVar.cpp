#include <ASECP/GlobalVar.h>
#include <ASECP/Exceptions.h>
#include <ASECP/Module.h>

namespace ASECP {

GlobalVar::GlobalVar(Poco::AutoPtr<Module> module, asUINT index) : _module(module), _index(index)
{
	load();
}

GlobalVar::~GlobalVar()
{

}

Poco::AutoPtr<Module> GlobalVar::module() const
{
	return _module;
}

std::string GlobalVar::declaration(bool includeNamespace) const
{
	return std::string(_module->module()->GetGlobalVarDeclaration(_index, includeNamespace));
}

void GlobalVar::load()
{
	const char* name, *nameSpace;
	throwOnError(_module->module()->GetGlobalVar(_index, &name, &nameSpace, &_typeid, &_isconst));
	if (name)
		_name = std::string(name);
	if (nameSpace)
		_namespace = std::string(nameSpace);
}

}
