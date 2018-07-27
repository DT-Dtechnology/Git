#include "stdafx.h"

int main(int argc, const char* argv[])
{
	try {
		CommandSwitcher(argc, argv);
	} catch(Error e)
	{
		e.print_msg();
	}
	return 0;
}

