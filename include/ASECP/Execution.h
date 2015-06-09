#ifndef H__ASECP_EXECUTION__H
#define H__ASECP_EXECUTION__H

#include <ASECP/Context.h>
#include <ASECP/Function.h>
#include <ASECP/Exceptions.h>
#include <ASECP/TypeId.h>

#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>
#include <Poco/Dynamic/Var.h>

#include <angelscript.h>

#include <vector>
#include <type_traits>

namespace ASECP {

template <typename ReturnType>
class Execution : public Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<Execution> Ptr;

	Execution(Context::Ptr context, Function::Ptr function);
	Execution(Context::Ptr context, Function::Ptr function, void *object);
	virtual ~Execution();

	ReturnType execute();
	ReturnType execute(Poco::Dynamic::Var arg0);
	ReturnType execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1);
	ReturnType execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2);
	ReturnType execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2, Poco::Dynamic::Var arg3);
	ReturnType execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2, Poco::Dynamic::Var arg3, Poco::Dynamic::Var arg4);
	ReturnType execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2, Poco::Dynamic::Var arg3, Poco::Dynamic::Var arg4, Poco::Dynamic::Var arg5);
	ReturnType execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2, Poco::Dynamic::Var arg3, Poco::Dynamic::Var arg4, Poco::Dynamic::Var arg5, Poco::Dynamic::Var arg6);
	ReturnType execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2, Poco::Dynamic::Var arg3, Poco::Dynamic::Var arg4, Poco::Dynamic::Var arg5, Poco::Dynamic::Var arg6, Poco::Dynamic::Var arg7);
	ReturnType execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2, Poco::Dynamic::Var arg3, Poco::Dynamic::Var arg4, Poco::Dynamic::Var arg5, Poco::Dynamic::Var arg6, Poco::Dynamic::Var arg7, Poco::Dynamic::Var arg8);
	ReturnType execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2, Poco::Dynamic::Var arg3, Poco::Dynamic::Var arg4, Poco::Dynamic::Var arg5, Poco::Dynamic::Var arg6, Poco::Dynamic::Var arg7, Poco::Dynamic::Var arg8, Poco::Dynamic::Var arg9);

	ReturnType execute(std::vector<Poco::Dynamic::Var> &args);

	template<typename T>
	struct is_pointer { static const bool value = false; };

	template<typename T>
	struct is_pointer<T*> { static const bool value = true; };

	template<typename T>
	struct is_void { static const bool value = false; };

	template<>
	struct is_void<void> { static const bool value = true; };

	template <bool v> struct Bool2Type { static const bool value = v; };
private:
	ReturnType typeIdResult();
	void setArgValue(int index, FunctionParam::Ptr param, Poco::Dynamic::Var &value);

	ReturnType extractResult(void *result, Bool2Type<false>) const
	{
		return *(ReturnType*)result;
	}

	ReturnType extractResult(void *result, Bool2Type<true>) const
	{
		return void();
	}

	Context::Ptr _context;
	Function::Ptr _function;
	void *_object;
};

#include "Execution.tpp"

}

#endif // H__ASECP_EXECUTION__H