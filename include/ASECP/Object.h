#ifndef H__ASECP_OBJECT__H
#define H__ASECP_OBJECT__H

#include <ASECP/AutoPtr.h>
#include <ASECP/ObjectProperty.h>

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>
#include <Poco/SharedPtr.h>

#include <angelscript.h>

#include <vector>

namespace ASECP {

class Object;
class ObjectType;

class ObjectList : public std::vector<Poco::AutoPtr<Object> > 
{
};

typedef Poco::SharedPtr<ObjectList> ObjectListPtr;

class Object : public Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<Object> Ptr;

	Object(asIScriptObject *object, bool shared = false);
	virtual ~Object();

	AutoPtr<asIScriptObject> object() const;

	int typeId() const;
	Poco::AutoPtr<ObjectType> objectType();

	ObjectPropertyListPtr properties();

	void copyFrom(Object::Ptr other);
private:
	AutoPtr<asIScriptObject> _object;
};


}

#endif // H__ASECP_OBJECT__H