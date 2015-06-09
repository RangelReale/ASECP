#include <ASECP/ObjectProperty.h>
#include <ASECP/Exceptions.h>
#include <ASECP/Object.h>

namespace ASECP {

ObjectProperty::ObjectProperty(Poco::AutoPtr<Object> object, asUINT index) : _object(object), _index(index)
{
	load();
}

ObjectProperty::~ObjectProperty()
{

}

Poco::AutoPtr<Object> ObjectProperty::object() const
{
	return _object;
}

void ObjectProperty::load()
{
	const char* name;
	_typeid = _object->object()->GetPropertyTypeId(_index);
	name = _object->object()->GetPropertyName(_index);
	_pointer = _object->object()->GetAddressOfProperty(_index);
	if (name)
		_name = std::string(name);
}

}
