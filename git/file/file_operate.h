#pragma once
#include <string>
#include <vector>
#include <windows.h>

using std::string;
using std::vector;

// ��ȡ��ǰ�ķ�֧����
class FL_OP
{
public:
    static string get_current_branch();

    // �ж��ļ���ͻ
    static void file_conflict(const string& branch1, const string& branch2);

    static string get_branch_file_hash(const string& branch, const string& file);

    static string get_Branch_hash(const string& name);

    // ��ȡ�������������ļ���
    static void get_file_name(const string& path, vector<string>& file);
};

