#include "../stdafx.h"
#include "Branch.h"
#include <algorithm>

#define BRANCH_TEMP "Branch_Temp"

void Branch::write()
{
	// ��д���ļ���������
	get_hash();
	
	ofstream out;

	if (_access((GIT_OBJECT_HEAD + hash_value_).c_str(), 0) != -1)
		return;

	out.open(GIT_OBJECT_HEAD + hash_value_);
	for (auto it = node_vector_.begin(); it != node_vector_.end(); ++it)
		out << (*it).file_name_ << ' ' << (*it).hash_value_ << "\n";
	out.close();

	// ����ref����Ϣ
	out.open(GIT_REF + branch_name_);
	out << hash_value_;
	out.close();
}

void Branch::get_hash()
{
	// For a better search.
	sort_file();

	ofstream out;
	out.open(BRANCH_TEMP);
	for (auto it = node_vector_.begin(); it != node_vector_.end(); ++it)
		out << (*it).file_name_ << ' ' << (*it).hash_value_ << "\n";
	out.close();

	md5wrapper md5;
	hash_value_ = md5.getHashFromFile(BRANCH_TEMP);

	remove(BRANCH_TEMP);
}

void Branch::sort_file()
{
	// ���ļ�����������
	std::sort(node_vector_.begin(), node_vector_.end(), file_name_compare);
}

Branch::Branch(const string& name):branch_name_(name)
{
	// ͨ�����ݿ��ȡHashֵ��Ӧ��������
	hash_value_ = FL_OP::get_Branch_hash(branch_name_);
	pre_branch_ = FL_OP::get_Branch_hash(branch_name_);

	// ��ȡNodeVector
	string file_name;
	string file_hash;

	ifstream in;
	in.open(GIT_OBJECT_HEAD + hash_value_);
	while(in >> file_name >> file_hash)
	{
		const FileNode file(file_name, file_hash);
		node_vector_.push_back(file);
	}
}

Branch::Branch()
{
	// �ӵ�ǰ�������л�ȡһ��Branch
	branch_name_ = FL_OP::get_current_branch();
	pre_branch_ = FL_OP::get_Branch_hash(branch_name_);
	
	// TODO:Scott
	// TODO:ͨ����ȡ�ļ�����Branch��ע��ڵ�����
	vector<string> file_name;
	char *buf = new char[1000];
	int i = 1000;
	GetCurrentDirectoryA(1000, buf);
	string path = buf;
	FL_OP::get_file_name(path, file_name);
	for (auto i = file_name.begin(); i != file_name.end(); ++i)
	{
		(*i) = (*i).substr(path.length() + 1);
		node_vector_.push_back(*i);
	}
	delete[] buf;

	// Get the hash.
	get_hash();
}

void Branch::addFile(const FileNode& file)
{
	node_vector_.push_back(file);
}

void Branch::insert()
{
	// ������Ϣ���ݿ�
	get_hash();

	// TODO:Arthur
	// TODO:�����ݿ��������Ϣ
}


void Branch::set_start(const string& new_name)
{
	branch_name_ = new_name;
	pre_branch_ = NONE_FILE_HASH;
}

void Branch::set_pre()
{
	pre_branch_ = hash_value_;
}

string Branch::getPre() const
{
	return pre_branch_;
}

string Branch::getHash() const
{
	return hash_value_;
}

NodeVector& Branch::getNodeVector()
{
	return node_vector_;
}

void Branch::reset_branch(const string& name)
{
	branch_name_ = name;
	pre_branch_ = NONE_FILE_HASH;
}

auto find_node(NodeVector& node_vector, const string& name)
{
	for(auto it = node_vector.begin() ; it!=node_vector.end() ; ++it)
	{
		if ((*it).getName() == name)
		{
			return it;
		}
	}
	return node_vector.end();
}

void Branch::update_file(const string& file_name, const string& new_hash)
{
	auto it = find_node(node_vector_, file_name);
	if (it == node_vector_.end())
	{
		node_vector_.push_back(FileNode(file_name, new_hash));
		return;
	}
	if(it->hash_value_ == NONE_FILE_HASH)
		node_vector_.erase(it);
	else	
		it->hash_value_ = new_hash;
}

string Branch::get_file_hash(const string& file_name)
{
	auto it = find_node(node_vector_, file_name);
	if (it == node_vector_.end())
		return NONE_FILE_HASH;
	return it->getHash();
}


bool operator==(const Branch& left, const Branch& right)
{
	// ??? �Ƿ���Ҫ��֤pre_hashͬ����ͬ ???
	return (left.branch_name_ == right.branch_name_) &&
		(left.hash_value_ == right.hash_value_);
}

bool operator>=(const Branch& left, const Branch& right)
{
	// TODO:判断left上的全部文件节点是否均比right上对应结点新，注意，当right对应为空节点时，永远为新
	
	// TODO:为此，需要构建right的对应关系的map

	// TODO:依次判断各个节点的更新情况
}
