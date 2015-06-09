#include <ASECP/Object.h>
#include <ASECP/ObjectType.h>
#include <ASECP/Exceptions.h>

namespace ASECP {

Object::Object(asIScriptObject *object, bool shared) : _object(object, shared)
{

}

Object::~Object()
{

}


AutoPtr<asIScriptObject> Object::object() const
{
	return _object;
}

int Object::typeId() const
{
	return _object->GetTypeId();
}

Poco::AutoPtr<ObjectType> Object::objectType()
{
	asIObjectType *ot = _object->GetObjectType();
	if (!ot)
		return NULL;

	return new ObjectType(ot, true);
}

ObjectPropertyListPtr Object::properties()
{
	ObjectPropertyListPtr list(new ObjectPropertyList);
	for (int i=0; i<_object->GetPropertyCount(); i++)
	{
		list->push_back(new ObjectProperty(Object::Ptr(this, true), i));
	}
	return list;
}

void Object::copyFrom(Object::Ptr other)
{
	throwOnError(_object->CopyFrom(other->_object));
}

}
