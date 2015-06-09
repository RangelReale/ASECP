#ifndef H__ASECP_MODULE__H
#define H__ASECP_MODULE__H

#include <ASECP/ObjectType.h>
#include <ASECP/GlobalVar.h>
#include <ASECP/Function.h>

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>

#include <angelscript.h>

namespace ASECP {

class Module : public Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<Module> Ptr;

	Module(asIScriptModule *module);
	virtual ~Module();

	asIScriptModule *module() const;

	void addScriptSectionFromFile(const std::string &filename);
	void addScriptSectionFromMemory(const std::string &sectionname, const std::string &code);
	void build();

	ObjectTypeListPtr objectTypes();
	ObjectType::Ptr objectTypeByName(const std::string &name);
	ObjectType::Ptr objectTypeByDecl(const std::string &decl);

	FunctionListPtr functions();
	Function::Ptr functionByName(const std::string &name) const;
	Function::Ptr functionByDecl(const std::string &decl) const;
	void functionRemove(Function::Ptr function);

	GlobalVarListPtr globalVars();
	GlobalVar::Ptr globalVarByName(const std::string &name);
	GlobalVar::Ptr globalVarByDecl(const std::string &decl);
	void globalVarRemove(GlobalVar::Ptr globalvar);
private:
	asIScriptModule *_module;
};

}

#endif // H__ASECP_MODULE__H