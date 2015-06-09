template <typename ReturnType>
Execution<ReturnType>::Execution(Context::Ptr context, Function::Ptr function) : _context(context), _function(function), _object(NULL)
{

}

template <typename ReturnType>
Execution<ReturnType>::Execution(Context::Ptr context, Function::Ptr function, void *object) : _context(context), _function(function), _object(object)
{

}

template <typename ReturnType>
Execution<ReturnType>::~Execution()
{

}

template <typename ReturnType>
ReturnType Execution<ReturnType>::execute()
{
	std::vector<Poco::Dynamic::Var> args;
	return execute(args);
}

template <typename ReturnType>
ReturnType Execution<ReturnType>::execute(Poco::Dynamic::Var arg0)
{
	std::vector<Poco::Dynamic::Var> args;
	args.push_back(arg0);
	return execute(args);
}

template <typename ReturnType>
ReturnType Execution<ReturnType>::execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1)
{
	std::vector<Poco::Dynamic::Var> args;
	args.push_back(arg0);
	args.push_back(arg1);
	return execute(args);
}

template <typename ReturnType>
ReturnType Execution<ReturnType>::execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2)
{
	std::vector<Poco::Dynamic::Var> args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	return execute(args);
}

template <typename ReturnType>
ReturnType Execution<ReturnType>::execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2, Poco::Dynamic::Var arg3)
{
	std::vector<Poco::Dynamic::Var> args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	return execute(args);
}

template <typename ReturnType>
ReturnType Execution<ReturnType>::execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2, Poco::Dynamic::Var arg3, Poco::Dynamic::Var arg4)
{
	std::vector<Poco::Dynamic::Var> args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	return execute(args);
}

template <typename ReturnType>
ReturnType Execution<ReturnType>::execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2, Poco::Dynamic::Var arg3, Poco::Dynamic::Var arg4, Poco::Dynamic::Var arg5)
{
	std::vector<Poco::Dynamic::Var> args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	return execute(args);
}

template <typename ReturnType>
ReturnType Execution<ReturnType>::execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2, Poco::Dynamic::Var arg3, Poco::Dynamic::Var arg4, Poco::Dynamic::Var arg5, Poco::Dynamic::Var arg6)
{
	std::vector<Poco::Dynamic::Var> args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	args.push_back(arg6);
	return execute(args);
}

template <typename ReturnType>
ReturnType Execution<ReturnType>::execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2, Poco::Dynamic::Var arg3, Poco::Dynamic::Var arg4, Poco::Dynamic::Var arg5, Poco::Dynamic::Var arg6, Poco::Dynamic::Var arg7)
{
	std::vector<Poco::Dynamic::Var> args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	args.push_back(arg6);
	args.push_back(arg7);
	return execute(args);
}

template <typename ReturnType>
ReturnType Execution<ReturnType>::execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2, Poco::Dynamic::Var arg3, Poco::Dynamic::Var arg4, Poco::Dynamic::Var arg5, Poco::Dynamic::Var arg6, Poco::Dynamic::Var arg7, Poco::Dynamic::Var arg8)
{
	std::vector<Poco::Dynamic::Var> args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	args.push_back(arg6);
	args.push_back(arg7);
	args.push_back(arg8);
	return execute(args);
}

template <typename ReturnType>
ReturnType Execution<ReturnType>::execute(Poco::Dynamic::Var arg0, Poco::Dynamic::Var arg1, Poco::Dynamic::Var arg2, Poco::Dynamic::Var arg3, Poco::Dynamic::Var arg4, Poco::Dynamic::Var arg5, Poco::Dynamic::Var arg6, Poco::Dynamic::Var arg7, Poco::Dynamic::Var arg8, Poco::Dynamic::Var arg9)
{
	std::vector<Poco::Dynamic::Var> args;
	args.push_back(arg0);
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	args.push_back(arg6);
	args.push_back(arg7);
	args.push_back(arg8);
	args.push_back(arg9);
	return execute(args);
}

template <typename ReturnType>
ReturnType Execution<ReturnType>::execute(std::vector<Poco::Dynamic::Var> &args)
{
	_context->prepare(_function);

	if (_object)
		_context->context()->SetObject(_object);

	// set parameters
	FunctionParamListPtr params(_function->params());
	for (int i=0; i<args.size(); i++)
	{
		if (i > params->size()-1)
			throw WrongNumberOfParametersException("Wrong number of parameters");

		setArgValue(i, params->at(i), args.at(i));
	}

	// execute
	int r = _context->context()->Execute();
	if (r == asEXECUTION_FINISHED)
	{
		return typeIdResult();
	}
	else if (r == asEXECUTION_EXCEPTION)
	{
		throw ASECPException(std::string(_context->context()->GetExceptionString()));
	}
	else
	{
		if (r < 0) 
			throwOnError(r);
		throw ExecutionException("Unexpected function result");
	}
}

template <typename ReturnType>
ReturnType Execution<ReturnType>::typeIdResult()
{
	return extractResult(_context->context()->GetAddressOfReturnValue(), Bool2Type<is_void<ReturnType>::value>());
}

template <typename ReturnType>
void Execution<ReturnType>::setArgValue(int index, FunctionParam::Ptr param, Poco::Dynamic::Var &value)
{
	TypeId typeId(param->typeId());
	if (typeId.isPrimitive())
	{
		switch(typeId.typeId())
		{
		case asTYPEID_BOOL:
			_context->context()->SetArgByte(index, value.extract<bool>()); break;
		case asTYPEID_INT8: 
		case asTYPEID_UINT8:
			_context->context()->SetArgByte(index, value.extract<asBYTE>()); break;
		case asTYPEID_INT16:
		case asTYPEID_UINT16:
			_context->context()->SetArgWord(index, value.extract<asWORD>()); break;
		case asTYPEID_INT64:
		case asTYPEID_UINT64:
			_context->context()->SetArgQWord(index, value.extract<asQWORD>()); break;
		case asTYPEID_FLOAT:
			_context->context()->SetArgFloat(index, value.extract<float>()); break;
		case asTYPEID_DOUBLE:
			_context->context()->SetArgDouble(index, value.extract<double>()); break;
		default:
			_context->context()->SetArgDWord(index, value.extract<asDWORD>()); break;
		}
	}
	else
	{
		_context->context()->SetArgObject(index, value.extractPointer());
	}
}
