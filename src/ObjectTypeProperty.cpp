#include <ASECP/ObjectTypeProperty.h>
#include <ASECP/Exceptions.h>
#include <ASECP/ObjectType.h>

namespace ASECP {

ObjectTypeProperty::ObjectTypeProperty(Poco::AutoPtr<ObjectType> objecttype, asUINT index) : _objecttype(objecttype), _index(index)
{
	load();
}

ObjectTypeProperty::~ObjectTypeProperty()
{

}

Poco::AutoPtr<ObjectType> ObjectTypeProperty::objectType() const
{
	return _objecttype;
}

void ObjectTypeProperty::load()
{
	const char* name;
	throwOnError(_objecttype->objectType()->GetProperty(_index, &name, &_typeid, &_isprivate, &_isprotected, &_offset, &_isreference, &_accessmask));
	if (name)
		_name = std::string(name);
}

}
