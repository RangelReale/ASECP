#ifndef H__ASECP_MESSAGEEVENTARGS__H
#define H__ASECP_MESSAGEEVENTARGS__H

#include <angelscript.h>

#include <string>

namespace ASECP {

class MessageEventArgs
{
public:
	MessageEventArgs(const asSMessageInfo *info);
	virtual ~MessageEventArgs();

	const std::string &section() const;
	int row() const;
	int col() const;
	asEMsgType msgType() const;
	const std::string &message() const;
private:
	MessageEventArgs();

	std::string _section;
	int _row;
	int _col;
	asEMsgType  _type;
	std::string _message;
};

}

#endif // H__ASECP_MESSAGEEVENTARGS__H