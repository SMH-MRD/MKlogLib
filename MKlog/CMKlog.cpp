

#include <stdexcept>

#include "stdafx.h"
#include "CMKlog.h"


using namespace std;

namespace MKlog
{

	WCHAR CMKlog::szInipath[_MAX_PATH], CMKlog::szDrive[_MAX_DRIVE], CMKlog::szPath[_MAX_PATH], CMKlog::szFName[_MAX_FNAME], CMKlog::szExt[_MAX_EXT];
	WCHAR CMKlog::szLogfile1[_MAX_PATH];

	int CMKlog::init_logfunc() {
	
	//ini�t�@�C��PATH�擾
	GetModuleFileName(NULL, szInipath, (sizeof(TCHAR) * _MAX_PATH));// exe file�̃p�X��荞��
	_wsplitpath_s(szInipath, szDrive, sizeof(szDrive), szPath, sizeof(szPath), szFName, sizeof(szFName), szExt, sizeof(szExt)); // exe file�̃p�X����
	_wmakepath_s(szInipath, sizeof(szInipath), szDrive, szPath, NAME_OF_INIFILE, EXT_OF_INIFILE); // ini file�̃p�X�Z�b�g

	//ini�t�@�C���ݒ�l�ǂݍ���








		return 0;
	};

}

