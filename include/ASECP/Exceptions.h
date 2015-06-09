#ifndef H__ASECP_EXCEPTIONS__H
#define H__ASECP_EXCEPTIONS__H

#include <Poco/Exception.h>

namespace ASECP {

POCO_DECLARE_EXCEPTION(, ASECPException, Poco::Exception);
POCO_DECLARE_EXCEPTION(, NullPointerException, ASECPException);
POCO_DECLARE_EXCEPTION(, WrongNumberOfParametersException, ASECPException);
POCO_DECLARE_EXCEPTION(, ExecutionException, ASECPException);

bool throwOnError(int resultCode, const std::string &message = "");

}

#endif // H__ASECP_EXCEPTIONS__H