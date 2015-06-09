#include <ASECP/Function.h>
#include <ASECP/ObjectType.h>
#include <ASECP/Exceptions.h>

namespace ASECP {

Function::Function(asIScriptFunction *function, bool shared) : _function(function, shared)
{

}

Function::~Function()
{

}


AutoPtr<asIScriptFunction> Function::function() const
{
	return _function;
}

asEFuncType Function::funcType() const
{
	return _function->GetFuncType();
}

Poco::AutoPtr<ObjectType> Function::objectType()
{
	asIObjectType *ot = _function->GetObjectType();
	if (!ot)
		return NULL;

	return new ObjectType(ot, true);
}

std::string Function::objectName() const
{
	const char* ob = _function->GetObjectName();
	if (!ob)
		return "";

	return std::string(ob);
}

std::string Function::name() const
{
	const char* on = _function->GetName();
	if (!on)
		return "";

	return std::string(on);
}

std::string Function::nameSpace() const
{
	const char* on = _function->GetNamespace();
	if (!on)
		return "";

	return std::string(on);
}

std::string Function::declaration(bool includeObjectName, bool includeNamespace, bool includeParamNames) const
{
	const char* on = _function->GetDeclaration(includeObjectName, includeNamespace, includeParamNames);
	if (!on)
		return "";

	return std::string(on);
}

bool Function::isReadOnly() const
{
	return _function->IsReadOnly();
}

bool Function::isPrivate() const
{
	return _function->IsPrivate();
}

bool Function::isProtected() const
{
	return _function->IsProtected();
}

bool Function::isFinal() const
{
	return _function->IsFinal();
}

bool Function::isOverride() const
{
	return _function->IsOverride();
}

bool Function::isShared() const
{
	return _function->IsShared();
}

int Function::typeId() const
{
	return _function->GetTypeId();
}

bool Function::isCompatibleWithTypeId(int typeId) const
{
	return _function->IsCompatibleWithTypeId(typeId);
}

int Function::returnTypeId() const
{
	asDWORD flags;
	return _function->GetReturnTypeId(&flags);
}

asDWORD Function::returnFlags() const
{
	asDWORD flags;
	_function->GetReturnTypeId(&flags);
	return flags;
}

FunctionParamListPtr Function::params()
{
	FunctionParamListPtr list(new FunctionParamList);
	for (int i=0; i<_function->GetParamCount(); i++)
	{
		list->push_back(new FunctionParam(Function::Ptr(this, true), i));
	}
	return list;
}

}
