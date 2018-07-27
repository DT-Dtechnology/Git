#include "../stdafx.h"
#include "DiffCommand.h"

void diff_command(const string& branch)
{
	const string branch2 = FL_OP::get_current_branch();
	diff_command(branch, branch2);
}

void diff_command(const string& branch1, const string& branch2)
{
	cout << "The difference between this two Branch:" << endl;

	// TODO:Scott
	// TODO:�ж��ļ�֮��Ĳ�ͬ������Hashֵ�жϼ��ɣ�����Ҫ�ҵ���ͬ�Ĳ���
}

