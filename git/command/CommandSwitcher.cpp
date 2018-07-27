#include "../stdafx.h"
#include "CommandSwitcher.h"
#include "Command.h"
#include "HelpMassage.h"
#include "../Error.h"

void CommandSwitcher(int argc, const char* argv[])
{
	if (argc == 1)
		help_message();
	else
	{
		const string instruct(argv[1]);
		if (instruct == "init")
		{
			cout << "init" << endl;
			if (argc == 2)
				init_command();
			else if (argc == 3)
				init_command(argv[2]);
			else
				throw Error("Paraments more than needed.");
		}
		else if (instruct == "add")
		{

		}
		else if (instruct == "commit")
		{

		}
		else if (instruct == "commit-a")
		{
			cout << "commit-add" << endl;
			if (argc == 2)
			{
				commit_add_command();
				branch_refresh();
			}
			else
			{
				for (auto it = 2; it < argc; ++it)
				{
					commit_add_command(argv[it]);
				}
				branch_refresh(argc, argv);
			}
		}
		else if (instruct == "branch")
		{
			cout << "branch" << endl;
			if (argc == 2)
				branch_command();
			else if (argc == 3)
				branch_command(argv[2]);
			else if (argc == 4)
				branch_command(argv[2], argv[3]);
			else
				throw Error("More than needed");
		}
		else if (instruct == "checkout")
		{
			cout << "checkout" << endl;
			if (argc == 3)
				checkout_command(argv[2]);
			else
				throw Error("More than needed");
		}
		else if (instruct == "drop")
		{

		}
		else if (instruct == "reset")
		{

		}
		else if (instruct == "fetch")
		{

		}
		else if (instruct == "merge")
		{
			cout << "merge" << endl;
			if (argc == 3)
				merge_command(argv[2]);
			else if (argc == 4)
				merge_command(argv[2], argv[3]);
			else
				throw Error("More than needed");
		}
		else if (instruct == "diff")
		{
			cout << "diff" << endl;
			if (argc == 3)
				diff_command(argv[2]);
			else if (argc == 4)
				diff_command(argv[2], argv[3]);
			else
				throw Error("More than needed");
		}
		else if (instruct == "push")
		{

		}
		else if (instruct == "pull")
		{

		}
		else if (instruct == "show")
		{
			DB_OP::Print_All_Branch();
			DB_OP::Print_All_File();
		}
		else
			throw Error("No such an instruction.");
	}
}

