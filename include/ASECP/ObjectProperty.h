#ifndef H__ASECP_OBJECTPROPERTY__H
#define H__ASECP_OBJECTPROPERTY__H

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>
#include <Poco/SharedPtr.h>

#include <angelscript.h>

#include <vector>

namespace ASECP {

class Object;
class ObjectProperty;

class ObjectPropertyList : public std::vector<Poco::AutoPtr<ObjectProperty> > 
{
};

typedef Poco::SharedPtr<ObjectPropertyList> ObjectPropertyListPtr;


class ObjectProperty : public Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<ObjectProperty> Ptr;

	ObjectProperty(Poco::AutoPtr<Object> object, asUINT index);
	virtual ~ObjectProperty();

	Poco::AutoPtr<Object> object() const;

	asUINT index() const { return _index; }
	const std::string &name() const { return _name; }
	int typeId() const { return _typeid; }
	void *pointer() const { return _pointer; }
private:
	void load();

	Poco::AutoPtr<Object> _object;
	asUINT _index;
	std::string _name;
	int _typeid;
	void *_pointer;
};

}

#endif // H__ASECP_ObjectPROPERTY__H