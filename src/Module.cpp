#include <ASECP/Module.h>
#include <ASECP/Exceptions.h>

#include <fstream>
#include <sstream>

namespace ASECP {

Module::Module(asIScriptModule *module) : _module(module)
{

}

Module::~Module()
{

}

asIScriptModule *Module::module() const
{
	return _module;
}

void Module::addScriptSectionFromFile(const std::string &filename)
{

}

void Module::addScriptSectionFromMemory(const std::string &sectionname, const std::string &code)
{
	throwOnError(_module->AddScriptSection(sectionname.c_str(), code.c_str(), code.size()));
}

void Module::build()
{
	throwOnError(_module->Build());
}

ObjectTypeListPtr Module::objectTypes()
{
	ObjectTypeListPtr list(new ObjectTypeList);
	for (int i=0; i<_module->GetObjectTypeCount(); i++)
	{
		asIObjectType *ot = _module->GetObjectTypeByIndex(i);
		list->push_back(new ObjectType(ot, true));
	}
	return list;
}

ObjectType::Ptr Module::objectTypeByName(const std::string &name)
{
	asIObjectType *ot = _module->GetObjectTypeByName(name.c_str());
	if (!ot)
		return false;

	return new ObjectType(ot, true);
}

ObjectType::Ptr Module::objectTypeByDecl(const std::string &decl)
{
	asIObjectType *ot = _module->GetObjectTypeByDecl(decl.c_str());
	if (!ot)
		return false;

	return new ObjectType(ot, true);
}

FunctionListPtr Module::functions()
{
	FunctionListPtr list(new FunctionList);
	for (int i=0; i<_module->GetFunctionCount(); i++)
	{
		list->push_back(new Function(_module->GetFunctionByIndex(i), true));
	}
	return list;
}

Function::Ptr Module::functionByName(const std::string &name) const
{
	asIScriptFunction *fn = _module->GetFunctionByName(name.c_str());
	if (!fn)
		return NULL;

	return new Function(fn, true);
}

Function::Ptr Module::functionByDecl(const std::string &decl) const
{
	asIScriptFunction *fn = _module->GetFunctionByDecl(decl.c_str());
	if (!fn)
		return NULL;

	return new Function(fn, true);
}

void Module::functionRemove(Function::Ptr function)
{
	_module->RemoveFunction(function->function());
}

GlobalVarListPtr Module::globalVars()
{
	GlobalVarListPtr list(new GlobalVarList);
	for (int i=0; i<_module->GetGlobalVarCount(); i++)
	{
		list->push_back(new GlobalVar(Module::Ptr(this, true), i));
	}
	return list;
}

GlobalVar::Ptr Module::globalVarByName(const std::string &name)
{
	int vi = _module->GetGlobalVarIndexByName(name.c_str());
	if (vi < 0)
		return NULL;

	return new GlobalVar(Module::Ptr(this, true), vi);
}

GlobalVar::Ptr Module::globalVarByDecl(const std::string &decl)
{
	int vi = _module->GetGlobalVarIndexByDecl(decl.c_str());
	if (vi < 0)
		return NULL;

	return new GlobalVar(Module::Ptr(this, true), vi);
}

void Module::globalVarRemove(GlobalVar::Ptr globalvar)
{
	_module->RemoveGlobalVar(globalvar->index());
}

}
