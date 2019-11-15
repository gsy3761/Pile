#include "myAssert.h"

CmdResalt::CmdResalt(bool success, std::string msg):success(success),msg(msg)
{
}

CmdResalt::operator bool() const
{
	return success;
}

CmdResalt::operator const std::string& () const
{
	return msg;
}

