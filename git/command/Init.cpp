#include "../stdafx.h"
#include "Init.h"
#include <direct.h>
#include <string>
#include <fstream>
#include <iostream>
#include "../db/sqlite3.h"
#include "../db/callback.h"

using std::string;
using std::ofstream;
using std::endl;

void init_folder()
{
	string main_fold_name = ".git";
	string ref_folder = ".git\\ref";
	string db_folder = ".git\\db";
	string object_folder = ".git\\object";
	string object_local_folder = ".git\\object\\local";
	string status_folder = ".git\\status";
	
	_mkdir(main_fold_name.c_str());
	_mkdir(ref_folder.c_str());
	_mkdir(db_folder.c_str());
	_mkdir(object_folder.c_str());
	_mkdir(object_local_folder.c_str());
	_mkdir(status_folder.c_str());
}

void init_file()
{
	ofstream out;

	out.open(CURRENT_BRANCH);
	out.close();
}

void init_db()
{
	sqlite3* db;
	char *zErrMsg = nullptr;
	int  rc;

	// ����Ƿ���ȷ����
	rc = sqlite3_open(INFO_DB, &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		fprintf(stdout, "Opened database successfully\n");
	}

	// ����Branch�Ķ�Ӧ��
	auto sql = "CREATE TABLE BRANCH_MATCH("  \
		"NAME TEXT NOT NULL,"		\
		"HASH TEXT NOT NULL,"		\
		"PRE_HASH TEXT NOT NULL,"	\
		"DISC	TEXT)";

	rc = sqlite3_exec(db, sql, callback, nullptr, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Table created successfully\n");
	}

	// ����File�Ķ�Ӧ��
	sql = "CREATE TABLE FILE_MATCH("  \
		"NAME TEXT NOT NULL,"		\
		"HASH TEXT NOT NULL,"	\
		"PRE_HASH TEXT NOT NULL)";

	rc = sqlite3_exec(db, sql, callback, nullptr, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Table created successfully\n");
	}

	sqlite3_close(db);
}

void create_master()
{
	ofstream out;

	out.open(CURRENT_BRANCH);
	out << "master" << endl;
	out.close();
	Branch master;
	
	// �������е�Branch���ݱ�������µĶ�Ӧ

	_mkdir(GIT_REF);
	out.open(GIT_REF + string("master"));
	out << NONE_FILE_HASH;
	out.close();

	// Write Log 

}

void initial_all()
{
	init_folder();
	init_file();
	init_db();
	create_master();
	std::cout << "Initial All" << endl;
}

void initial_all(const std::string& path)
{
	string cmd = "cd " + path;
	system(cmd.c_str());
	initial_all();
}
