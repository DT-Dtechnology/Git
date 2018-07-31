#include "../stdafx.h"
#include "CommitAddCommand.h"

void commit_add_command(const string& file_name)
{
	if(file_name == "*")
	{
		commit_add_command();
		return;
	}
	
	ofstream out;
	ifstream in;
	
	// �����ļ�����ӦHash��ȷ��ǰ�̽ڵ�
	const string hash = FL_OP::get_branch_file_hash(FL_OP::get_current_branch(), file_name);
	// �ж�Hashֵ�Ƿ���ͬ����ֱͬ�ӷ��أ��������

	FileNode file(file_name);

	if(file.getHash() == hash)
		return;
	file.setPreNode(hash);
	file.write();
	
	// д�������ͬʱ�������ݿ����ݣ�ע�����ǰ�̽ڵ�
	DB_OP::File_Match_Insert(file);

}

void commit_add_command()
{
	vector<string> file_name;
	char *buf = new char[1000];
	int i = 1000;
	GetCurrentDirectoryA(1000, buf);
	string path = buf;
	FL_OP::get_file_name(path, file_name);
	for (auto i = file_name.begin(); i != file_name.end(); ++i)
		(*i) = (*i).substr(path.length() + 1);
	for (auto i = file_name.begin(); i != file_name.end(); ++i)
	{
		commit_add_command((*i));
	}
	delete[] buf;
}

void branch_refresh(int argc, const char* argv[] )
{
	// �½���֧
	Branch branch(FL_OP::get_current_branch());

	// ����ļ�
	for(auto it = 2 ; it < argc ; ++it)
	{
		FileNode file(argv[it]);
		branch.update_file(file.getName(), file.getHash());
	}

	branch.get_hash();

	if(branch.getHash() == branch.getPre())
		return;

	branch.write();
	DB_OP::Branch_Match_Insert(branch);
}

void branch_refresh()
{
	Branch branch;

	if(branch.getHash() == branch.getPre())
		return;

	branch.write();
	DB_OP::Branch_Match_Insert(branch);
}

