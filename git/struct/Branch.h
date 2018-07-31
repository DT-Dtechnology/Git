#pragma once
#include <string>
#include <vector> 
#include "FileNode.h"
#include "../DefineSetting.h"

using std::string;

typedef std::vector<FileNode> NodeVector;

class DB_OP;

/**
 * \brief ��¼��֧�Ļ�����Ϣ��������������Hashֵ���������֣������FileNode��vector
 * Ҫ�����ʱ�����ֵ�����ӣ�ע��Ҫ�����Ѿ�ɾ���Ľڵ���Ϣ��Ϊ�˷��������ԭ����
 */
class Branch
{
	string branch_name_;
	string hash_value_;
	NodeVector node_vector_{};
	string pre_branch_ = NONE_FILE_HASH;

	void sort_file();

public:

	// ����Branch_Name����Branch
	Branch(const string& name);

	// ���ڹ���������Branch
	Branch();

	/**
	 * \brief ���ڼ�¼��֧��Ϣ������Headָ��λ�ã��Լ��ļ�����ʷ�ظ����¼�ļ���������Hash
	 * ��֧����Ϊ����ṹ���ļ��汾Ϊ����ṹ��
	 * ��֧���ӵ������ļ���Ҫ��������Hash
	 */
	void get_hash();
	void write();
	void addFile(const FileNode& file);
	void insert();
	void set_start(const string& new_name);
	void set_pre();
	
	string getPre() const;
	string getHash() const;
	NodeVector& getNodeVector();

	void reset_branch(const string& name);

	// ���½ڵ���Ϣ
	void update_file(const string& file_name, const string& new_hash);

	string get_file_hash(const string& file_name);

	// �жϷ�֧�Ƿ���ͬ
	friend bool operator==(const Branch& left, const Branch& right);

	// �жϷ�֧�Ƿ����
	friend bool operator>=(const Branch& left, const Branch& right);

	friend DB_OP;
};

