#include "../stdafx.h"
#include "BasicCommandFunction.h"

bool uncommited_change()
{
	const Branch past(FL_OP::get_current_branch());
	const Branch current;
	
	return current == past;
}

void refresh_file(const string& branch_name)
{
	Branch branch(branch_name);
	
	ofstream out;
	ifstream in;
	for (auto it = branch.getNodeVector().begin(); it != branch.getNodeVector().end(); ++it)
	{
		out.open(GIT_HEAD + it->getName());
		in.open(GIT_OBJECT_HEAD + it->getHash());

		// ֱ�ӻ�ȡinȫ���ļ����ݲ�д�뵽out��
		out << in.rdbuf();

		in.close();
		out.close();
	}
}
