#include "../stdafx.h"
#include "CheckoutCommand.h"
#include "BasicCommandFunction.h"
#include <io.h>

void checkout_command(const string& branch_name)
{
	string path_name = GIT_REF + branch_name;
	if (DB_OP::get_Branch_Hash(branch_name) != NONE_FILE_HASH)
	{
		if (uncommited_change())
			throw Error("Unsummited change");
		
		ofstream out;
		out.open(CURRENT_BRANCH);
		out << branch_name << endl;
		out.close();

		refresh_file(branch_name);
	}
	else
		throw Error("You don not have this branch");
}
