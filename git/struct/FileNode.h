#pragma once
#include <string>

/**
 * \brief ������File�Ļ�����Ϣ�����������ݿ��н������������������
 * ��Ҫ����Hashֵ���ļ������Լ������������ע�⣬������������ǵ���֧��
 */

using std::string;

class Branch;
class DB_OP;

class FileNode
{
	string file_name_;	// �ļ���������Ϊ���������ļ�������ͬ��hashValue
	string hash_value_;
	string pre_file_ ;		// ���ļ�����Hashֵ�洢��
						// ȫ��Ϊ0��ʾδ����״̬����׼״̬��
	friend Branch;

	void get_hash();

public:
	FileNode() = default;
	FileNode(const string& file_name);
	FileNode(const string& file_name, const string& file_hash);
	void setPreNode(const string& hash_value);	// �����ļ��м�¼��Hashֵ����������

	void write();
	string getName() const;
	string getHash() const;

	// �Ⱥ��ϵ���ж�
	friend bool operator> (const FileNode& left, const FileNode& right);

	friend DB_OP;
};

bool file_name_compare(const FileNode& left, const FileNode& right);