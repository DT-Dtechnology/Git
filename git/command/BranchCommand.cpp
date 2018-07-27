#include "../stdafx.h"
#include "BranchCommand.h"


void branch_command()
{
	const string current = FL_OP::get_current_branch();
	cout << "Current Branch is: <"<<current <<">" << endl;
	// TODO:Arthur
	// TODO:�������ݿ�ʵ�ֻ�ȡ���з�֧���Ƶ�ָ��

}

void branch_command(const string& to_branch)
{
	// ��ȡ��ǰ��֧��
	const string from_branch = FL_OP::get_current_branch();

	branch_command(from_branch, to_branch);
}

void branch_command(const string& from_branch, const string& to_branch)
{
	// TODO:Arthur
	// TODO:����֧������

	// ����ԭ��֧�����·�֧(ע����ķ�֧���ƺ�his_id)
	Branch new_branch(from_branch);
	new_branch.set_start(to_branch);

	// ����Branch_Match��Ϣ
	DB_OP::Branch_Match_Insert(new_branch);

	// TODO:Scott
	// TODO:���Branch��GIT_REF ����ʱ��֪����ʲô�ã���
}
