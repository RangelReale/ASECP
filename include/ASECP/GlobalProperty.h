#ifndef H__ASECP_GLOBALPROPERTY__H
#define H__ASECP_GLOBALPROPERTY__H

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>
#include <Poco/SharedPtr.h>

#include <angelscript.h>

#include <vector>

namespace ASECP {

class Engine;
class GlobalProperty;

class GlobalPropertyList : public std::vector<Poco::AutoPtr<GlobalProperty> > 
{
};

typedef Poco::SharedPtr<GlobalPropertyList> GlobalPropertyListPtr;


class GlobalProperty : public Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<GlobalProperty> Ptr;

	GlobalProperty(Poco::AutoPtr<Engine> engine, asUINT index);
	virtual ~GlobalProperty();

	Poco::AutoPtr<Engine> engine() const;

	asUINT index() const { return _index; }
	const std::string &name() const { return _name; }
	const std::string &nameSpace() const { return _namespace; }
	int typeId() const { return _typeid; }
	bool isConst() const { return _isconst; }
	const std::string &configGroup() const { return _configgroup; }
	void *pointer() const { return _pointer; }
	asDWORD accessMask() const { return _accessmask; }
private:
	void load();

	Poco::AutoPtr<Engine> _engine;
	asUINT _index;
	std::string _name;
	std::string _namespace;
	int _typeid;
	bool _isconst;
	std::string _configgroup;
	void *_pointer;
	asDWORD _accessmask;
};

}

#endif // H__ASECP_GLOBALPROPERTY__H