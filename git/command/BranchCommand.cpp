#include "../stdafx.h"
#include "BranchCommand.h"


void branch_command()
{
	const string current = FL_OP::get_current_branch();
	cout << "Current Branch is: <"<<current <<">" << endl;
}

void branch_command(const string& to_branch)
{
	const string from_branch = FL_OP::get_current_branch();
	branch_command(from_branch, to_branch);
}

void branch_command(const string& from_branch, const string& to_branch)
{
	if(DB_OP::get_Branch_Hash(from_branch) == NONE_FILE_HASH)
		throw Error("No such branch.\n");

	Branch new_branch(from_branch);
	new_branch.set_start(to_branch);

	DB_OP::Branch_Match_Insert(new_branch);

	new_branch.write();
}
