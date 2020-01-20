

#include <stdexcept>

#include "stdafx.h"
#include "CMKlog.h"


using namespace std;

namespace MKlog
{

	WCHAR CMKlog::szInipath[_MAX_PATH], CMKlog::szDrive[_MAX_DRIVE], CMKlog::szPath[_MAX_PATH], CMKlog::szFName[_MAX_FNAME], CMKlog::szExt[_MAX_EXT];
	WCHAR CMKlog::szLogfile1[_MAX_PATH];
	ST_MKLOG_SET CMKlog::mklogset[LOG_RECORD_MAX];

	int CMKlog::init_logfunc() {
	
	//iniファイルPATH取得
	GetModuleFileName(NULL, szInipath, (sizeof(TCHAR) * _MAX_PATH));// exe fileのパス取り込み
	_wsplitpath_s(szInipath, szDrive, sizeof(szDrive), szPath, sizeof(szPath), szFName, sizeof(szFName), szExt, sizeof(szExt)); // exe fileのパス分割
	_wmakepath_s(szInipath, sizeof(szInipath), szDrive, szPath, NAME_OF_INIFILE, EXT_OF_INIFILE); // ini fileのパスセット

	//iniファイル設定値読み込み
	TCHAR buf_t[128];
	DWORD	str_num = GetPrivateProfileString(PATH_SECT_OF_INIFILE, PATH1_LOG1_KEY_OF_INIFILE, L"FAILED", szLogfile1, sizeof(szLogfile1), szInipath);
			str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_LOGTYPE1_KEY_OF_INIFILE, L"FAILED", mklogset[0].szType, sizeof(mklogset[0].szType), szInipath);
			str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_SAMPLE_TIME1_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); mklogset[0].ms_period = stoi(buf_t);
			str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_ITME_NUM1_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); mklogset[0].n_item = stoi(buf_t);
			

		return 0;
	};

}

