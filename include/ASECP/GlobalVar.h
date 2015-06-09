#ifndef H__ASECP_GLOBALVAR__H
#define H__ASECP_GLOBALVAR__H

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>
#include <Poco/SharedPtr.h>

#include <angelscript.h>

#include <vector>

namespace ASECP {

class Module;
class GlobalVar;

class GlobalVarList : public std::vector<Poco::AutoPtr<GlobalVar> > 
{
};

typedef Poco::SharedPtr<GlobalVarList> GlobalVarListPtr;

class GlobalVar : public Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<GlobalVar> Ptr;

	GlobalVar(Poco::AutoPtr<Module> module, asUINT index);
	virtual ~GlobalVar();

	Poco::AutoPtr<Module> module() const;

	asUINT index() const { return _index; }
	const std::string &name() const { return _name; }
	const std::string &nameSpace() const { return _namespace; }
	int typeId() const { return _typeid; }
	bool isConst() const { return _isconst; }

	std::string declaration(bool includeNamespace = false) const;
private:
	void load();

	Poco::AutoPtr<Module> _module;
	asUINT _index;
	std::string _name;
	std::string _namespace;
	int _typeid;
	bool _isconst;
};

}

#endif // H__ASECP_GLOBALVAR__H