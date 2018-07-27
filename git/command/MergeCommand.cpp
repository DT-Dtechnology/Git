#include "../stdafx.h"
#include "MergeCommand.h"
#include "BasicCommandFunction.h"


void merge_command(const string& from_branch)
{
	const string to_branch = FL_OP::get_current_branch();

	merge_command(from_branch, to_branch);
}

void merge_command(const string& from_branch, const string& to_branch)
{
	// �ж�δ�ύ����
	if (uncommited_change())
		throw Error("Unsummited change");

	Branch branch_from(from_branch);
	Branch branch_to(to_branch);

	// �ж��Ƿ�汾����
	if (!(from_branch > to_branch))
	{
		// ��Ǹ��£��������ͻ
		FL_OP::file_conflict(from_branch, to_branch);
		return;
	}

	// ����to_branch
	for(auto it:branch_from.getNodeVector())
	{
		branch_to.update_file(it.getName(), it.getHash());
	}
	
	// �ļ�д��
	branch_to.write();

	// ���µ����ݿ���
	DB_OP::Branch_Match_Insert(branch_to);

	// TODO:Scott
	// TODO:���������£����ֱ��д��һ��������file_operate�У��õ��������Ǻܶ��
}
