#include "../stdafx.h"
#include "file_operate.h"

string FL_OP::get_current_branch()
{
	ifstream in;
	in.open(CURRENT_BRANCH);
	string name;
	in >> name;
	in.close();
	return name;
}

void FL_OP::file_conflict(const string& branch_name1, const string& branch_name2)
{
	Branch branch1(branch_name1);
	Branch branch2(branch_name2);

	if(branch1.getHash() == branch2.getHash())
		cout << "Same!" << endl;
	else
		// TODO:计算出具体的不同信息
		cout << "Different!" << endl;
}

string FL_OP::get_branch_file_hash(const string& branch, const string& file)
{
	Branch branch_data(branch);
	return branch_data.get_file_hash(file);
}

string FL_OP::get_Branch_Latest_Hash(const string& name)
{
	ifstream in;
	string hash;
	in.open(GIT_REF + name);
	in >> hash;
	in.close();
	return hash;
}

void FL_OP::get_file_name(const string& path, vector<string>& files)
{	
	//�ļ����  
	long   hFile = 0;
	//�ļ���Ϣ  
	_finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮  
			//�������,�����б�  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0 && fileinfo.name[0] != '.')
					get_file_name(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

string FL_OP::get_Branch_hash(const string& name)
{
	ifstream in;
	in.open(GIT_REF + name);
	if(!in)
		return NONE_FILE_HASH;
	string hash;
	in >> hash;
	return hash;
}

