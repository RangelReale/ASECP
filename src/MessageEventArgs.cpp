#include <ASECP/MessageEventArgs.h>

namespace ASECP {


MessageEventArgs::MessageEventArgs()
{

}

MessageEventArgs::MessageEventArgs(const asSMessageInfo *info)
{
	_section = info->section;
	_row = info->row;
	_col = info->col;
	_type = info->type;
	_message = info->message;
}

MessageEventArgs::~MessageEventArgs()
{

}

const std::string &MessageEventArgs::section() const
{
	return _section;
}

int MessageEventArgs::row() const
{
	return _row;
}

int MessageEventArgs::col() const
{
	return _col;
}

asEMsgType MessageEventArgs::msgType() const
{
	return _type;
}

const std::string &MessageEventArgs::message() const
{
	return _message;
}


}
