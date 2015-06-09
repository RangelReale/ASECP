#ifndef H__ASECP_FUNCTION__H
#define H__ASECP_FUNCTION__H

#include <ASECP/AutoPtr.h>
#include <ASECP/FunctionParam.h>

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>
#include <Poco/SharedPtr.h>

#include <angelscript.h>

#include <vector>

namespace ASECP {

class Function;
class ObjectType;

class FunctionList : public std::vector<Poco::AutoPtr<Function> > 
{
};

typedef Poco::SharedPtr<FunctionList> FunctionListPtr;

class Function : public Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<Function> Ptr;

	Function(asIScriptFunction *function, bool shared = false);
	virtual ~Function();

	AutoPtr<asIScriptFunction> function() const;

	asEFuncType funcType() const;
	Poco::AutoPtr<ObjectType> objectType();
	std::string objectName() const;
	std::string name() const;
	std::string nameSpace() const;
	std::string declaration(bool includeObjectName=true, bool includeNamespace=false, bool includeParamNames=false) const;
	bool isReadOnly() const;
	bool isPrivate() const;
	bool isProtected() const;
	bool isFinal() const;
	bool isOverride() const;
	bool isShared() const;
	int typeId() const;
	bool isCompatibleWithTypeId(int typeId) const;

	int returnTypeId() const;
	asDWORD returnFlags() const;
	FunctionParamListPtr params();
private:
	AutoPtr<asIScriptFunction> _function;
};


}

#endif // H__ASECP_FUNCTION__H