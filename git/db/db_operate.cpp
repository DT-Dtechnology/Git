#include "../stdafx.h"
#include "sqlite3.h"
#include "callback.h" 
#include "db_operate.h"

void DB_OP::Print_All_Branch()
{
	sqlite3* db;
	int rc;
	char *zErrMsg = nullptr;

	rc = sqlite3_open(INFO_DB, &db);
	if (! rc)
	{
		string sql = "SELECT * FROM BRANCH_MATCH";
		cout << "Branch Table:" << endl;
		rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		sqlite3_close(db);
		cout << endl;
		return;
	}
	throw Error("###ERROR_OPEN_DATABASE###");
}

void DB_OP::Print_All_File()
{
	sqlite3* db;
	int rc;
	char *zErrMsg = nullptr;

	rc = sqlite3_open(INFO_DB, &db);
	if (!rc)
	{
		string sql = "SELECT * FROM FILE_MATCH";
		cout << "File Table:" << endl;
		rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		sqlite3_close(db);
		cout << endl;
		return;
	}
	throw Error("###ERROR_OPEN_DATABASE###");
}

void DB_OP::File_Match_Insert(const FileNode& file)
{
	sqlite3* db;
	int rc;
	char *zErrMsg = nullptr;

	rc = sqlite3_open(INFO_DB, &db);
	if (! rc)
	{
		string sql = "INSERT INTO FILE_MATCH VALUES ('" + file.file_name_+ "','" + file.hash_value_ + "','" + file.pre_file_ + "')";
		rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else
		{
			fprintf(stdout, "Insert Successfully\n");
		}
		sqlite3_close(db);
		return;
	}
	else
	{
		throw Error("###ERROR_OPEN_DATABASE###");
	}
}



void DB_OP::Branch_Match_Insert(const Branch& branch)
{
	sqlite3* db;
	int rc;
	char *zErrMsg = nullptr;

	rc = sqlite3_open(INFO_DB, &db);
	if (! rc)
	{
		string sql = "INSERT INTO BRANCH_MATCH VALUES ('" + branch.branch_name_ + "','" +branch.hash_value_+ "','" + branch.pre_branch_  + "',NULL)";
		rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else
		{
			fprintf(stdout, "Insert Successfully\n");
		}
		sqlite3_close(db);
		return;
	}
	else
	{
		throw Error("###ERROR_OPEN_DATABASE###");
	}
}




string DB_OP::get_File_Hash(const string& name)
{
	sqlite3* db;
	int rc;
	char *zErrMsg = nullptr;
	char *hash = nullptr;
	char** pResult;
	int nRow;
	int nCol;
	rc = sqlite3_open(INFO_DB, &db);
	if (! rc)
	{
		string sql = "SELECT HASH FROM FILE_MATCH WHERE NAME='"+name+"'";
		rc = sqlite3_get_table(db, sql.c_str(),&pResult,&nRow,&nCol,&zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			return NONE_FILE_HASH;
		}

		else
		{
			if (nCol==0)
			{
				fprintf(stdout, "No such File.\n");
				return NONE_FILE_HASH;
			}
			else
			{
				fprintf(stdout, "Find Successfully\n");
				return std::string(pResult[1]);
			}
		}
		sqlite3_free_table(pResult);
		sqlite3_close(db);
	}
	else
	{
		sqlite3_free_table(pResult);
		throw Error("###ERROR_OPEN_DATABASE###");
		return NONE_FILE_HASH;
	}
}



string DB_OP::get_File_Pre_Hash(const string& hash)
{
	sqlite3* db;
	int rc;
	char *zErrMsg = nullptr;
	char *prehash = nullptr;
	char** pResult;
	int nRow;
	int nCol;
	rc = sqlite3_open(INFO_DB, &db);
	if (! rc)
	{
		string sql = "SELECT PRE_HASH FROM FILE_MATCH WHERE HASH='" + hash + "'";
		rc = sqlite3_get_table(db, sql.c_str(), &pResult, &nRow, &nCol, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			return NONE_FILE_HASH;
		}

		else
		{
			if (nCol==0)
			{
				fprintf(stdout, "No such File.\n");
				return NONE_FILE_HASH;
			}
			else
			{
				fprintf(stdout, "Find Successfully\n");
				return std::string(pResult[1]);
			}
		}
		sqlite3_free_table(pResult);
		sqlite3_close(db);
	}
	else
	{
		sqlite3_free_table(pResult);
		throw Error("###ERROR_OPEN_DATABASE###");
		return NONE_FILE_HASH;
	}
	
}

string DB_OP::get_Branch_Hash(const string& name)
{
	sqlite3* db;
	int rc;
	char *zErrMsg = nullptr;
	char *hash = nullptr;
	char** pResult=nullptr;
	int nRow;
	int nCol;

	rc = sqlite3_open(INFO_DB, &db);
	if (!rc)
	{
		string sql = "SELECT HASH FROM BRANCH_MATCH WHERE NAME='" + name + "'";
		rc = sqlite3_get_table(db, sql.c_str(), &pResult, &nRow, &nCol, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			return NONE_FILE_HASH;
		}

		else
		{
			if (nCol==0)
			{
				fprintf(stdout, "No such Branch.\n");
				return NONE_FILE_HASH;
			}
			else
			{
				cout << "FOUND:" << pResult[1] <<"end"<<endl;
				fprintf(stdout, "Find Successfully\n");
				return std::string(pResult[1]);
			}
				
		}
		sqlite3_free_table(pResult);
		sqlite3_close(db);
	}
	else
	{
		sqlite3_free_table(pResult);
		throw Error("###ERROR_OPEN_DATABASE###");
		return NONE_FILE_HASH;
	}
}


//---------------------------------------------------------------------

