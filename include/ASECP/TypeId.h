#ifndef H__ASECP_TYPEID__H
#define H__ASECP_TYPEID__H

#include <ASECP/AutoPtr.h>
#include <ASECP/FunctionParam.h>
#include <ASECP/ObjectType.h>
#include <ASECP/Engine.h>

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>

#include <angelscript.h>

namespace ASECP {

class TypeId : public Poco::RefCountedObject
{
public:
	typedef enum {
		MOD_NONE		= 0,
		MOD_INREF		= 1,
		MOD_OUTREF		= 2,
		MOD_INOUTREF	= 3,
		MOD_CONST		= 4
	} modifier_t;

	typedef Poco::AutoPtr<TypeId> Ptr;

	TypeId(int typeId, asDWORD flags = 0, Engine::Ptr engine = NULL);
	TypeId(Function::Ptr function, Engine::Ptr engine = NULL);
	TypeId(FunctionParam::Ptr param, Engine::Ptr engine = NULL);
	virtual ~TypeId();

	int typeId() const;
	asDWORD flags() const;
	void setFlags(asDWORD flags);
	const std::string &name() const;

	bool isPrimitive() const;
	bool isObject() const;
	bool isHandle() const;
	bool isHandleToConst() const;
	bool isAppObject() const;
	bool isScriptObject() const;
	bool isTemplate() const;
	bool isSimpleValue() const; // primitive or enum

	modifier_t modifier() const;

	std::string description() const;
private:
	void loadPrimitiveName();
	void loadEngine(Engine::Ptr engine);
	void loadObjectType(ObjectType::Ptr objecttype);

	int _typeid;
	asDWORD _flags;
	std::string _name;
};


}

#endif // H__ASECP_TYPEID__H