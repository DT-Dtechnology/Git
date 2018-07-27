// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include <stdio.h>
#include <tchar.h>
#include <string>
#include <io.h>
#include <fstream>
#include <iostream>

using std::string;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::cout;

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "db/sqlite3.h"
#include "struct/FileNode.h"
#include "struct/Branch.h"
#include "command/CommandSwitcher.h"
#include "DefineSetting.h"
#include "Error.h"
#include "hash/md5_wrapper.h"
#include "db/db_operate.h"
#include "file/file_operate.h"





