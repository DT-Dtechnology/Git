#pragma once
#include <string>

/**
 * \brief 包含了File的基本信息，用于向数据库中进行内容输入与输出。
 * 需要包含Hash值，文件名，以及链接情况。（注意，链接情况仅考虑单分支）
 */

using std::string;

class Branch;
class DB_OP;

class FileNode
{
	string file_name_;	// 文件名，这里为工作区中文件名，不同于hashValue
	string hash_value_;
	string pre_file_ ;		// 在文件中以Hash值存储，
						// 全部为0表示未创建状态（基准状态）
	friend Branch;

	void get_hash();

public:
	FileNode() = default;
	FileNode(const string& file_name);
	FileNode(const string& file_name, const string& file_hash);
	void setPreNode(const string& hash_value);	// 基于文件中记录的Hash值来创建链接

	void write();
	void insert();
	string getName() const;
	string getHash() const;

	// 先后关系的判断
	friend bool operator> (const FileNode& left, const FileNode& right);

	friend DB_OP;
};

bool file_name_compare(const FileNode& left, const FileNode& right);