

#include <stdexcept>

#include "stdafx.h"
#include "CMKlog.h"


using namespace std;

namespace MKlog
{

	WCHAR CMKlog::szInipath[_MAX_PATH], CMKlog::szDrive[_MAX_DRIVE], CMKlog::szPath[_MAX_PATH], CMKlog::szFName[_MAX_FNAME], CMKlog::szExt[_MAX_EXT];
	WCHAR CMKlog::szLogfile1[_MAX_PATH];

	int CMKlog::init_logfunc() {
	
	//iniファイルPATH取得
	GetModuleFileName(NULL, szInipath, (sizeof(TCHAR) * _MAX_PATH));// exe fileのパス取り込み
	_wsplitpath_s(szInipath, szDrive, sizeof(szDrive), szPath, sizeof(szPath), szFName, sizeof(szFName), szExt, sizeof(szExt)); // exe fileのパス分割
	_wmakepath_s(szInipath, sizeof(szInipath), szDrive, szPath, NAME_OF_INIFILE, EXT_OF_INIFILE); // ini fileのパスセット

	//iniファイル設定値読み込み








		return 0;
	};

}

