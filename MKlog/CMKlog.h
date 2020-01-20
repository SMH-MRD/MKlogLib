#pragma once

#include <Windows.h>
#include "MKlog_ini.h"

namespace MKlog
{
#define LOG_RECORD_MAX	8	//LOGに記録するITEM数最大値
#define LOG_ITEM_MAX	128 //LOGに記録するITEM数最大値

	typedef struct stMKlogSet {
		WCHAR szType[128];
		int ms_period;
		int n_item;
		int data_type[LOG_ITEM_MAX];
		void* pData[LOG_ITEM_MAX];	//記録データのアドレスマップ
	}ST_MKLOG_SET, *PST_MKLOG_SET;

	class CMKlog
	{
	public:
		CMKlog() {};
		~CMKlog(){};

		static	WCHAR szInipath[_MAX_PATH], szDrive[_MAX_DRIVE], szPath[_MAX_PATH], szFName[_MAX_FNAME], szExt[_MAX_EXT];//iniファイルパス取得用
		static	WCHAR szLogfile1[_MAX_PATH];
		static	ST_MKLOG_SET mklogset[LOG_RECORD_MAX];


		int init_logfunc();//初期化　設定フィル読み込み
		FILE *start_record(int mode, FILE *fp);
		int end_record(FILE *fp);
		int pause_record(FILE *fp);
		int add_record(FILE *fp);

	};
}

