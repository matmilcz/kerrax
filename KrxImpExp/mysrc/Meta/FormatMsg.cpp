///////////////////////////////////////////////////////////////////////////////
// Name:        FormatMsg.cpp
// Purpose:     Formatting of messages.
// Author:      Vitaly Baranov
// Created:     January 14, 2009
// Modified by:  
// Licence:     GNU General Public License
///////////////////////////////////////////////////////////////////////////////

#ifndef FORMAT_MSG_CPP
#define FORMAT_MSG_CPP

#include "Meta.h"

// Format message. The function replaces %1 in fmt with the first element of array args,
// %2 in fmt with the second element of array args, and so on.
TSTRING FormatMsg(TSTRING fmt, std::vector<TSTRING> args)
{
	TSTRING msg = fmt;
	for (int i = 0; i < 9; ++i)
	{
		TSTRING argtempl = T("%") + IntToString(i + 1);
		int argpos = msg.find(argtempl);

		if (argpos != NOT_FOUND)
		{
			msg = SUBSTR(msg, 0, argpos) + args[i] + SUBSTR(msg, argpos + 2, STRLEN(msg))
			//ASSIGN(msg, SUBSTR(msg, 0, argpos) + GET_ELEM(args, i) + SUBSTR(msg, argpos + 2, STRLEN(msg)))
		}
	}
	return msg;
}

TSTRING FormatMsg0(TSTRING fmt)
{
	std::vector<TSTRING> args;
	return FormatMsg(fmt, args);
}

TSTRING FormatMsg1(TSTRING fmt, TSTRING arg1)
{
	std::vector<TSTRING> args{ arg1 };
	return FormatMsg(fmt, args);
}

TSTRING FormatMsg2(TSTRING fmt, TSTRING arg1, TSTRING arg2)
{
	std::vector<TSTRING> args{ arg1, arg2 };
	return FormatMsg(fmt, args);
}

TSTRING FormatMsg3(TSTRING fmt, TSTRING arg1, TSTRING arg2, TSTRING arg3)
{
	std::vector<TSTRING> args{ arg1, arg2, arg3 };
	return FormatMsg(fmt, args);
}

TSTRING FormatMsg4(TSTRING fmt, TSTRING arg1, TSTRING arg2, TSTRING arg3, TSTRING arg4)
{
	std::vector<TSTRING> args{ arg1, arg2, arg3, arg4 };
	return FormatMsg(fmt, args);
}

TSTRING FormatMsg5(TSTRING fmt, TSTRING arg1, TSTRING arg2, TSTRING arg3, TSTRING arg4, TSTRING arg5)
{
	std::vector<TSTRING> args{ arg1, arg2, arg3, arg4, arg5 };
	return FormatMsg(fmt, args);
}

TSTRING FormatMsg5(TSTRING fmt, TSTRING arg1, TSTRING arg2, TSTRING arg3, TSTRING arg4, TSTRING arg5, TSTRING arg6)
{
	std::vector<TSTRING> args{ arg1, arg2, arg3, arg4, arg5, arg6 };
	return FormatMsg(fmt, args);
}

#endif // FORMAT_MSG_CPP