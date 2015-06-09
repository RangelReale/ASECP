#ifndef H__ASECP_ENGINE__H
#define H__ASECP_ENGINE__H

#include <ASECP/AutoPtr.h>
#include <ASECP/MessageEventArgs.h>
#include <ASECP/Module.h>
#include <ASECP/Context.h>
#include <ASECP/ObjectType.h>
#include <ASECP/GlobalProperty.h>
#include <ASECP/Function.h>

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>
#include <Poco/BasicEvent.h>

#include <angelscript.h>

namespace ASECP {

class Engine : public Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<Engine> Ptr;

	Poco::BasicEvent<MessageEventArgs> messageEvent;

	Engine();
	Engine(asIScriptEngine *engine, bool shared = false);
	virtual ~Engine();

	AutoPtr<asIScriptEngine> engine() const;

	Module::Ptr moduleAdd(const std::string &name);
	Module::Ptr moduleGet(const std::string &name);
	void moduleRemove(const std::string &name);
	
	Context::Ptr contextCreate();

	ObjectTypeListPtr objectTypes();
	ObjectType::Ptr objectTypeByName(const std::string &name);
	ObjectType::Ptr objectTypeByDecl(const std::string &decl);
	ObjectType::Ptr objectTypeById(int typeId);

	FunctionListPtr globalFunctions();
	Function::Ptr globalFunctionByDecl(const std::string &decl) const;

	GlobalPropertyListPtr globalProperties();
	GlobalProperty::Ptr globalPropertyByName(const std::string &name);
	GlobalProperty::Ptr globalPropertyByDecl(const std::string &decl);

	Function::Ptr functionById(int funcid) const;
private:
	void init();
	void messageCallback(const asSMessageInfo *msg);

	AutoPtr<asIScriptEngine> _engine;
};

}

#endif // H__ASECP_ENGINE__H