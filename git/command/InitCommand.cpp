#include "../stdafx.h"
#include "InitCommand.h"
#include <io.h>
#include "Init.h"

void init_command()
{
	if (_access(".kit", 0) != -1)
		return;
	else
		initial_all();
}

void init_command(const std::string& path)
{
	std::string search_path = path + "\\.kit";
	if (_access(search_path.c_str(), 0) != -1)
		return;
	else
		initial_all();
}
