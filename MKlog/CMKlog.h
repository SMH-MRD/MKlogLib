#pragma once

#include <Windows.h>

namespace MKlog
{
#define LOG_ITEM_MAX 128

	class CMKlog
	{
	public:
		CMKlog() {};
		~CMKlog(){};

		static	WCHAR szInipath[_MAX_PATH], szDrive[_MAX_DRIVE], szPath[_MAX_PATH], szFName[_MAX_FNAME], szExt[_MAX_EXT];//iniファイルパス取得用
		static	WCHAR szLogfile1[_MAX_PATH];
		static void* pData[LOG_ITEM_MAX];

		int sample_t;
		int n_item;
		int data_type[LOG_ITEM_MAX];


		int init_logfunc();//初期化　設定フィル読み込み
		FILE *start_record(int mode, FILE *fp);
		int end_record(FILE *fp);
		int pause_record(FILE *fp);
		int add_record(FILE *fp);

	};


#define NAME_OF_INIFILE L"mklog"	//iniファイル名
#define EXT_OF_INIFILE L"ini"		//iniファイル拡張子
#define EXT_OF_CSVFILE L"csv"		//csvファイル拡張子

#define PATH_SECT_OF_INIFILE			L"PATH"			//ファルダパスセクション
#define SET_SECT_OF_INIFILE				L"SET"			//機能パラメータセクション
#define DATAL_TYPE_SECT_OF_INIFILE		L"DATA_TYPE"	//記録データのタイプ　0:double 1:int 2:bool
#define LABEL_NAME_SECT_OF_INIFILE		L"LABEL"		//ログデータラベルセクション


#define PATH_LOG1_KEY_OF_INIFILE		L"LOG_PATH1"

#define SET_SAMPLE_TIME_KEY_OF_INIFILE	L"SAMPLING_ms"
#define SET_ITME_NUM_KEY_OF_INIFILE		L"N_ITEM"

#define LABEL01_KEY_OF_INIFILE			L"LABEL01"
#define LABEL02_KEY_OF_INIFILE			L"LABEL02"
#define LABEL03_KEY_OF_INIFILE			L"LABEL03"

#define TYPE01_KEY_OF_INIFILE			L"TYPE01"
#define TYPE02_KEY_OF_INIFILE			L"TYPE02"
#define TYPE03_KEY_OF_INIFILE			L"TYPE03"

}

