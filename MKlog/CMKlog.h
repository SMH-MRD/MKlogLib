#pragma once

#include <Windows.h>
#include "MKlog_ini.h"

namespace MKlog
{
#define LOG_RECORD_MAX		8	//LOG記録数最大値
#define LOG_ITEM_MAX		128 //LOGに記録するITEM数最大値
#define TIMER_ID_BASE		300 //LOGに記録するITEM数最大値

#define LOG_STATUS_STANDBY	0 //LOG記録の状態
#define LOG_STATUS_ACTIVE	1 //LOG記録の状態
#define LOG_STATUS_PAUSE	2 //LOG記録の状態
#define LOG_STATUS_STOP		3 //LOG記録の状態
#define LOG_STATUS_ERROR	-1 //LOG記録の状態


	typedef struct stMKlogSet {
		FILE*	fp;
		WCHAR	fname[256];
		WCHAR	szType[128];				//BASIC:定周期で記録し続ける　TRAP:定周期で指定数サンプリング　EVENT：イベントトリガで記録
		int		ms_period;					//サンプリング周期　msec NEGATIVE VALUE:イベント型
		int		n_item;						//サンプリングデータ項目数
		int		data_type[LOG_ITEM_MAX];	//0:double 1:int 2:bool
		double*	p_double[LOG_ITEM_MAX];		//記録データのアドレスマップ
		int*	p_int[LOG_ITEM_MAX];		//記録データのアドレスマップ
		bool*	p_bool[LOG_ITEM_MAX];		//記録データのアドレスマップ
		UINT	timerID;
		int		status;						//0:STANDBY 1:ACTIVE 2:PAUSE 3:STOP NEGATIVE VALUE:ERROR
		int		max_sample;					//サンプリング最大数
	}ST_MKLOG_SET, *PST_MKLOG_SET;

	class CMKlog
	{
	public:
		CMKlog() {};
		~CMKlog(){};

		static	WCHAR szInipath[_MAX_PATH], szDrive[_MAX_DRIVE], szPath[_MAX_PATH], szFName[_MAX_FNAME], szExt[_MAX_EXT];//iniファイルパス取得用
		static	WCHAR szLogfolder1[_MAX_PATH];
		static	ST_MKLOG_SET mklogset[LOG_RECORD_MAX];
		static	int nlogs;
		static  std::wstring log_path;
		static  HWND hwnd_client;


		
		int init_logfunc();//初期化　設定フィル読み込み

		static int start_record(int logID, HWND hWnd);//int logID, HWND hWnd:クライアント側でタイマー処理をする場合のイベント受信Window
		static int end_record(int logID);
		static int pause_record(int logID);
		static int add_record(int logID);

		static VOID CALLBACK MKlogTimerProc(HWND hwnd, UINT msg, UINT idEvent, DWORD dwTime);


		std::wstring getDatetimeStr();
	};


#define MK_LOGSET_1				0 //LOG SET配列Index
#define MK_LOGSET_2				1 //LOG SET配列Index
#define MK_LOGSET_3				2 //LOG SET配列Index

#define MK_DATA_TYPE_DOUBLE		0 //記録データの型　double
#define MK_DATA_TYPE_INT		1 //記録データの型　int
#define MK_DATA_TYPE_BOOL		2 //記録データの型　bool
}





