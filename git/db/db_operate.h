#pragma once
#include <string>

using std::string;

// FILE_MATCH 和 BRANCH_MATCH的结构如下
// FILR_MATCH: Hash和对应的文件名Name
// BRANCH_MATCH: Hash和对应的最新分支名Branch
// 暂时没有考虑远程数据库的问题


class DB_OP //数据库操作类
{
public:
	//test func
	static void Print_All_Branch();
	static void Print_All_File();

	//---------------------------------------------------
	static void File_Match_Insert(const FileNode& file);
	static void Branch_Match_Insert(const Branch& branch);

	static string get_File_Hash(const string& name);
	static string get_File_Pre_Hash(const string& hash);

	static string get_Branch_Hash(const string& name);

	//---------------------------------------------------


};