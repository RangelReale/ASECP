#include <ASECP/ObjectType.h>
#include <ASECP/Exceptions.h>

#include <Poco/Format.h>

namespace ASECP {

ObjectType::ObjectType(asIObjectType *objecttype, bool shared) : _objecttype(objecttype, shared)
{

}

ObjectType::~ObjectType()
{

}

AutoPtr<asIObjectType> ObjectType::objectType() const
{
	return _objecttype;
}

std::string ObjectType::name() const
{
	return std::string(_objecttype->GetName());
}

std::string ObjectType::nameSpace() const
{
	return std::string(_objecttype->GetNamespace());
}

ObjectType::Ptr ObjectType::baseType()
{
	asIObjectType *ot = _objecttype->GetBaseType();
	if (!ot)
		return false;
	return new ObjectType(ot, true);
}

bool ObjectType::derivesFrom(ObjectType::Ptr objecttype) const
{
	return _objecttype->DerivesFrom(objecttype->_objecttype);
}

asDWORD ObjectType::flags() const
{
	return _objecttype->GetFlags();
}

asUINT ObjectType::size() const
{
	return _objecttype->GetSize();
}

int ObjectType::typeId() const
{
	return _objecttype->GetTypeId();
}

ObjectTypeListPtr ObjectType::interfaces() const
{
	ObjectTypeListPtr list(new ObjectTypeList);
	for (int i=0; i<_objecttype->GetInterfaceCount(); i++)
	{
		list->push_back(ObjectType::Ptr(new ObjectType(_objecttype->GetInterface(i), true)));
	}
	return list;
}

bool ObjectType::implements(ObjectType::Ptr objecttype) const
{
	return _objecttype->Implements(objecttype->_objecttype);
}

FunctionListPtr ObjectType::factories() const
{
	FunctionListPtr list(new FunctionList);
	for (int i=0; i<_objecttype->GetFactoryCount(); i++)
	{
		list->push_back(new Function(_objecttype->GetFactoryByIndex(i), true));
	}
	return list;
}

Function::Ptr ObjectType::factoryByDecl(const std::string &decl) const
{
	asIScriptFunction *fn = _objecttype->GetFactoryByDecl(decl.c_str());
	if (!fn)
		return NULL;

	return new Function(fn, true);
}

Function::Ptr ObjectType::factoryByParamsDecl(const std::string &paramsDecl) const
{
	return factoryByDecl(Poco::format("%s@ %s(%s)", name(), name(), paramsDecl));
}

FunctionListPtr ObjectType::methods(bool getVirtual) const
{
	FunctionListPtr list(new FunctionList);
	for (int i=0; i<_objecttype->GetMethodCount(); i++)
	{
		list->push_back(new Function(_objecttype->GetMethodByIndex(i, getVirtual), true));
	}
	return list;
}

Function::Ptr ObjectType::methodByName(const std::string &name, bool getVirtual) const
{
	asIScriptFunction *fn = _objecttype->GetMethodByName(name.c_str(), getVirtual);
	if (!fn)
		return NULL;

	return new Function(fn, true);
}

Function::Ptr ObjectType::methodByDecl(const std::string &decl, bool getVirtual) const
{
	asIScriptFunction *fn = _objecttype->GetMethodByDecl(decl.c_str(), getVirtual);
	if (!fn)
		return NULL;

	return new Function(fn, true);
}

ObjectTypePropertyListPtr ObjectType::properties()
{
	ObjectTypePropertyListPtr list(new ObjectTypePropertyList);
	for (int i=0; i<_objecttype->GetPropertyCount(); i++)
	{
		list->push_back(new ObjectTypeProperty(ObjectType::Ptr(this, true), i));
	}
	return list;
}

}
