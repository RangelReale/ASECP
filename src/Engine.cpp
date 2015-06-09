#include <ASECP/Engine.h>

#include <scriptstdstring/scriptstdstring.h>
#include <scripthandle/scripthandle.h>
#include <scriptany/scriptany.h>

namespace ASECP {

Engine::Engine()
{
	_engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	init();
}

Engine::Engine(asIScriptEngine *engine, bool shared) : _engine(engine, shared)
{
	_engine = engine;
	init();
}

Engine::~Engine()
{

}

AutoPtr<asIScriptEngine> Engine::engine() const
{
	return _engine;
}

Module::Ptr Engine::moduleAdd(const std::string &name)
{
	asIScriptModule* mod = _engine->GetModule(name.c_str(), asGM_CREATE_IF_NOT_EXISTS);
	return new Module(mod);
}

Module::Ptr Engine::moduleGet(const std::string &name)
{
	asIScriptModule* mod = _engine->GetModule(name.c_str(), asGM_ONLY_IF_EXISTS);
	if (!mod)
		return NULL;
	return new Module(mod);
}

void Engine::moduleRemove(const std::string &name)
{
	_engine->DiscardModule(name.c_str());
}

Context::Ptr Engine::contextCreate()
{
	return new Context(_engine->CreateContext(), true);
}

ObjectTypeListPtr Engine::objectTypes()
{
	ObjectTypeListPtr list(new ObjectTypeList);
	for (int i=0; i<_engine->GetObjectTypeCount(); i++)
	{
		asIObjectType *ot = _engine->GetObjectTypeByIndex(i);
		list->push_back(new ObjectType(ot, true));
	}
	return list;
}

ObjectType::Ptr Engine::objectTypeByName(const std::string &name)
{
	asIObjectType *ot = _engine->GetObjectTypeByName(name.c_str());
	if (!ot)
		return false;

	return new ObjectType(ot, true);
}

ObjectType::Ptr Engine::objectTypeByDecl(const std::string &decl)
{
	asIObjectType *ot = _engine->GetObjectTypeByDecl(decl.c_str());
	if (!ot)
		return false;

	return new ObjectType(ot, true);
}

ObjectType::Ptr Engine::objectTypeById(int typeId)
{
	asIObjectType *ot = _engine->GetObjectTypeById(typeId);
	if (!ot)
		return false;

	return new ObjectType(ot, true);
}

FunctionListPtr Engine::globalFunctions()
{
	FunctionListPtr list(new FunctionList);
	for (int i=0; i<_engine->GetGlobalFunctionCount(); i++)
	{
		list->push_back(new Function(_engine->GetGlobalFunctionByIndex(i), true));
	}
	return list;
}

Function::Ptr Engine::globalFunctionByDecl(const std::string &decl) const
{
	asIScriptFunction *fn = _engine->GetGlobalFunctionByDecl(decl.c_str());
	if (!fn)
		return NULL;

	return new Function(fn, true);
}

GlobalPropertyListPtr Engine::globalProperties()
{
	GlobalPropertyListPtr list(new GlobalPropertyList);
	for (int i=0; i<_engine->GetGlobalPropertyCount(); i++)
	{
		list->push_back(new GlobalProperty(Engine::Ptr(this, true), i));
	}
	return list;
}

GlobalProperty::Ptr Engine::globalPropertyByName(const std::string &name)
{
	int vi = _engine->GetGlobalPropertyIndexByName(name.c_str());
	if (vi < 0)
		return NULL;

	return new GlobalProperty(Engine::Ptr(this, true), vi);
}

GlobalProperty::Ptr Engine::globalPropertyByDecl(const std::string &decl)
{
	int vi = _engine->GetGlobalPropertyIndexByDecl(decl.c_str());
	if (vi < 0)
		return NULL;

	return new GlobalProperty(Engine::Ptr(this, true), vi);
}

Function::Ptr Engine::functionById(int funcid) const
{
	asIScriptFunction *fn = _engine->GetFunctionById(funcid);
	if (!fn)
		return NULL;

	return new Function(fn, true);
}

void Engine::init()
{
	_engine->SetMessageCallback(asMETHOD(Engine, messageCallback), this, asCALL_THISCALL);

	RegisterStdString(_engine);
	RegisterScriptHandle(_engine);
	RegisterScriptAny(_engine);
}

void Engine::messageCallback(const asSMessageInfo *msg)
{
	MessageEventArgs args(msg);
	messageEvent.notify(this, args);
}

}
