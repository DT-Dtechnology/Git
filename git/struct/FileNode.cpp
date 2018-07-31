#include "../stdafx.h"
#include "FileNode.h"

void FileNode::get_hash()
{
	md5wrapper md5;
	hash_value_ = md5.getHashFromFile(file_name_);
}

FileNode::FileNode(const string& file_name):file_name_(file_name)
{
	get_hash();
	pre_file_ = FL_OP::get_branch_file_hash(FL_OP::get_current_branch(), file_name);
}

FileNode::FileNode(const string& file_name, const string& file_hash)
	:file_name_(file_name), hash_value_(file_hash) { }

void FileNode::setPreNode(const string& hash_value)
{
	pre_file_ = hash_value;
}

void FileNode::write()
{
	get_hash();

	if (_access((GIT_OBJECT_HEAD + hash_value_).c_str(), 0) != -1)
		return;

	ofstream out;
	out.open(GIT_OBJECT_HEAD + hash_value_);
	
	ifstream in;
	in.open(file_name_);
	out << in.rdbuf();
	in.close();
	out.close();

}

inline string FileNode::getName() const
{
	return file_name_;
}

string FileNode::getHash() const
{
	return hash_value_;
}

bool file_name_compare(const FileNode& left, const FileNode& right)
{
	return left.getName() > right.getName();
}

bool operator>(const FileNode& left, const FileNode& right)
{
	// TODO:�жϹ�ϵ�����Ƿ���leftΪright�ĺ��
	string pre = left.pre_file_;
	if (right.file_name_ == "")
		return true;
	while(pre != NONE_FILE_HASH)
	{
		if (pre == right.file_name_)
			return true;
		else
			// ����ǰ�̽ڵ�
			pre = DB_OP::get_File_Pre_Hash(pre);
	}
	return false;
}
