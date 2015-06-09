#ifndef H__ASECP_OBJECTTYPEPROPERTY__H
#define H__ASECP_OBJECTTYPEPROPERTY__H

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>
#include <Poco/SharedPtr.h>

#include <angelscript.h>

#include <vector>

namespace ASECP {

class ObjectType;
class ObjectTypeProperty;

class ObjectTypePropertyList : public std::vector<Poco::AutoPtr<ObjectTypeProperty> > 
{
};

typedef Poco::SharedPtr<ObjectTypePropertyList> ObjectTypePropertyListPtr;


class ObjectTypeProperty : public Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<ObjectTypeProperty> Ptr;

	ObjectTypeProperty(Poco::AutoPtr<ObjectType> objecttype, asUINT index);
	virtual ~ObjectTypeProperty();

	Poco::AutoPtr<ObjectType> objectType() const;

	asUINT index() const { return _index; }
	const std::string &name() const { return _name; }
	int typeId() const { return _typeid; }
	bool isPrivate() const { return _isprivate; }
	bool isProtected() const { return _isprotected; }
	int offset() const { return _offset; }
	bool isReference() const { return _isreference; }
	asDWORD accessMask() const { return _accessmask; }
private:
	void load();

	Poco::AutoPtr<ObjectType> _objecttype;
	asUINT _index;
	std::string _name;
	int _typeid;
	bool _isprivate;
	bool _isprotected;
	int _offset;
	bool _isreference;
	asDWORD _accessmask;
};

}

#endif // H__ASECP_OBJECTTYPEPROPERTY__H