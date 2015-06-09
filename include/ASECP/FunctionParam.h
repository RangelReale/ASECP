#ifndef H__ASECP_FUNCTIONPARAM__H
#define H__ASECP_FUNCTIONPARAM__H

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>
#include <Poco/SharedPtr.h>

#include <angelscript.h>

#include <vector>

namespace ASECP {

class Function;
class FunctionParam;

class FunctionParamList : public std::vector<Poco::AutoPtr<FunctionParam> > 
{
};

typedef Poco::SharedPtr<FunctionParamList> FunctionParamListPtr;


class FunctionParam : public Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<FunctionParam> Ptr;

	FunctionParam(Poco::AutoPtr<Function> function, asUINT index);
	virtual ~FunctionParam();

	Poco::AutoPtr<Function> function() const;

	asUINT index() const { return _index; }
	int typeId() const { return _typeid; }
	asDWORD flags() const { return _flags; }
	const std::string &name() const { return _name; }
	const std::string &defaultArg() const { return _defaultarg; }
private:
	void load();

	Poco::AutoPtr<Function> _function;
	asUINT _index;
	int _typeid;
	asDWORD _flags;
	std::string _name;
	std::string _defaultarg;
};

}

#endif // H__ASECP_FUNCTIONPARAM__H