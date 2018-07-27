#include "callback.h"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	if (argv[0] != nullptr)
	{
		char* tm = (char*)NotUsed;
		tm = argv[0];//如果结果集不为空，则将传入的指针指向结果集第一个元素（SELECT时用）；
	}
	
	return 0;
}
