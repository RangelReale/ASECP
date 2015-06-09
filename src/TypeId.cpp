#include <ASECP/TypeId.h>

#include <sstream>

namespace ASECP {

TypeId::TypeId(int typeId, asDWORD flags, Engine::Ptr engine) : _typeid(typeId), _flags(flags)
{
	loadEngine(engine);
}

TypeId::TypeId(Function::Ptr function, Engine::Ptr engine) : _typeid(function->returnTypeId()), _flags(function->returnFlags())
{
	loadEngine(engine);
}

TypeId::TypeId(FunctionParam::Ptr param, Engine::Ptr engine) : _typeid(param->typeId()), _flags(param->flags())
{
	loadEngine(engine);
}

TypeId::~TypeId()
{

}

int TypeId::typeId() const
{
	return _typeid;
}

asDWORD TypeId::flags() const
{
	return _flags;
}

void TypeId::setFlags(asDWORD flags)
{
	_flags = flags;
}

const std::string &TypeId::name() const
{
	return _name;
}

bool TypeId::isPrimitive() const
{
	return !isObject();
}

bool TypeId::isObject() const
{
	return (_typeid & asTYPEID_MASK_OBJECT) != 0;
}

bool TypeId::isHandle() const
{
	return (_typeid & asTYPEID_OBJHANDLE) != 0;
}

bool TypeId::isHandleToConst() const
{
	return (_typeid & asTYPEID_HANDLETOCONST) != 0;
}

bool TypeId::isAppObject() const
{
	return (_typeid & asTYPEID_APPOBJECT) != 0;
}

bool TypeId::isScriptObject() const
{
	return (_typeid & asTYPEID_SCRIPTOBJECT) != 0;
}

bool TypeId::isTemplate() const
{
	return (_typeid & asTYPEID_TEMPLATE) != 0;
}

bool TypeId::isSimpleValue() const
{
	return !(_typeid & ~asTYPEID_MASK_SEQNBR);
}

TypeId::modifier_t TypeId::modifier() const
{
	switch (_flags)
	{
	case asTM_INREF:
		return MOD_INREF;
	case asTM_OUTREF:
		return MOD_OUTREF;
	case asTM_INOUTREF:
		return MOD_INOUTREF;
	case asTM_CONST:
		return MOD_CONST;
	default:
		return MOD_NONE;
	}
}

std::string TypeId::description() const
{
	std::stringstream ss;

	if (!_name.empty())
		ss << _name << " ";

	switch (_flags)
	{
	case asTM_INREF:
		ss << "{inref}"; break;
	case asTM_OUTREF:
		ss << "{outref}"; break;
	case asTM_INOUTREF:
		ss << "{inoutref}"; break;
	case asTM_CONST:
		ss << "{const}"; break;
	}
	if (isPrimitive())
		ss << "[primitive]";
	else
		ss << "[object]";
	if (isHandle())
		ss << "[handle]";
	if (isHandleToConst())
		ss << "[handle to const]";
	if (isAppObject())
		ss << "[app object]";
	if (isScriptObject())
		ss << "[script object]";
	if (isTemplate())
		ss << "[template]";
	if (isSimpleValue())
		ss << "[simple value]";

	return ss.str();
}

void TypeId::loadPrimitiveName()
{
	if (isPrimitive())
	{
		switch (_typeid)
		{
		case asTYPEID_VOID:
			_name = "void"; break;
		case asTYPEID_BOOL:
			_name = "bool"; break;
		case asTYPEID_INT8:
			_name = "int8"; break;
		case asTYPEID_INT16:
			_name = "int16"; break;
		case asTYPEID_INT32:
			_name = "int32"; break;
		case asTYPEID_INT64:
			_name = "int64"; break;
		case asTYPEID_UINT8:
			_name = "uint8"; break;
		case asTYPEID_UINT16:
			_name = "uint16"; break;
		case asTYPEID_UINT32:
			_name = "uint32"; break;
		case asTYPEID_UINT64:
			_name = "uint64"; break;
		case asTYPEID_FLOAT:
			_name = "float"; break;
		case asTYPEID_DOUBLE:
			_name = "double"; break;
		default:
			_name = "enum"; break;
		}
	}
}

void TypeId::loadEngine(Engine::Ptr engine)
{
	if (engine && !isPrimitive())
	{
		ObjectType::Ptr ot(engine->objectTypeById(_typeid));
		if (ot)
		{
			loadObjectType(ot);
			return;
		}
	}

	loadPrimitiveName();
}

void TypeId::loadObjectType(ObjectType::Ptr objecttype)
{
	_name = objecttype->name();
}

}
