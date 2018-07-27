#pragma once
#include <string>

using std::string;

// FILE_MATCH �� BRANCH_MATCH�Ľṹ����
// FILR_MATCH: Hash�Ͷ�Ӧ���ļ���Name
// BRANCH_MATCH: Hash�Ͷ�Ӧ�����·�֧��Branch
// ��ʱû�п���Զ�����ݿ������


class DB_OP //���ݿ������
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