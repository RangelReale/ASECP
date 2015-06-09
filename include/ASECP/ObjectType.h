#ifndef H__ASECP_OBJECTTYPE__H
#define H__ASECP_OBJECTTYPE__H

#include <ASECP/AutoPtr.h>
#include <ASECP/ObjectTypeProperty.h>
#include <ASECP/Function.h>

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>
#include <Poco/SharedPtr.h>

#include <angelscript.h>

#include <vector>

namespace ASECP {

class ObjectType;

class ObjectTypeList : public std::vector<Poco::AutoPtr<ObjectType> > 
{
};

typedef Poco::SharedPtr<ObjectTypeList> ObjectTypeListPtr;

class ObjectType : public Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<ObjectType> Ptr;

	ObjectType(asIObjectType *objecttype, bool shared = false);
	virtual ~ObjectType();

	AutoPtr<asIObjectType> objectType() const;

	std::string name() const;
	std::string nameSpace() const;
	ObjectType::Ptr baseType();
	bool derivesFrom(ObjectType::Ptr objecttype) const;
	asDWORD flags() const;
	asUINT size() const;
	int typeId() const;

	ObjectTypeListPtr interfaces() const;
	bool implements(ObjectType::Ptr objecttype) const;

	FunctionListPtr factories() const;
	Function::Ptr factoryByDecl(const std::string &decl) const;
	Function::Ptr factoryByParamsDecl(const std::string &paramsDecl) const;

	FunctionListPtr methods(bool getVirtual = true) const;
	Function::Ptr methodByName(const std::string &name, bool getVirtual = true) const;
	Function::Ptr methodByDecl(const std::string &decl, bool getVirtual = true) const;

	ObjectTypePropertyListPtr properties();
private:
	AutoPtr<asIObjectType> _objecttype;
};


}

#endif // H__ASECP_OBJECTTYPE__H