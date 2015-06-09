#include <ASECP/Exceptions.h>

#include <Poco/Format.h>

namespace ASECP {

POCO_IMPLEMENT_EXCEPTION(ASECPException, Poco::Exception, "ASECP exception");
POCO_IMPLEMENT_EXCEPTION(NullPointerException, ASECPException, "Null pointer");
POCO_IMPLEMENT_EXCEPTION(WrongNumberOfParametersException, ASECPException, "Wrong number of parameters");
POCO_IMPLEMENT_EXCEPTION(ExecutionException, ASECPException, "Error executing function");

bool throwOnError(int resultCode, const std::string &message)
{
	if (resultCode < 0)
	{
		throw ASECPException(Poco::format("ASECP error code %?d", resultCode));
		return true;
	}
	return false;
}

}
