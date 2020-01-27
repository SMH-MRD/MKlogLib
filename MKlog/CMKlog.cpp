

#include <stdexcept>

#include "stdafx.h"
#include "CMKlog.h"


using namespace std;

namespace MKlog
{

	WCHAR CMKlog::szInipath[_MAX_PATH], CMKlog::szDrive[_MAX_DRIVE], CMKlog::szPath[_MAX_PATH], CMKlog::szFName[_MAX_FNAME], CMKlog::szExt[_MAX_EXT];
	WCHAR CMKlog::szLogfolder1[_MAX_PATH];
	ST_MKLOG_SET CMKlog::mklogset[LOG_RECORD_MAX];
	int CMKlog::nlogs;
	wstring CMKlog::log_path;

	//########################################################################
	int CMKlog::init_logfunc() {
	
	//iniファイルPATH取得
	GetModuleFileName(NULL, szInipath, (sizeof(TCHAR) * _MAX_PATH));// exe fileのパス取り込み
	_wsplitpath_s(szInipath, szDrive, sizeof(szDrive), szPath, sizeof(szPath), szFName, sizeof(szFName), szExt, sizeof(szExt)); // exe fileのパス分割
	log_path.clear(); log_path += szPath;
	_wmakepath_s(szInipath, sizeof(szInipath), szDrive, szPath, NAME_OF_INIFILE, EXT_OF_INIFILE); // ini fileのパスセット

	for (int i = 0; i < LOG_RECORD_MAX; i++)mklogset[i].fp = nullptr;

	//iniファイル設定値読み込み
	TCHAR buf_t[128];
	DWORD	str_num = GetPrivateProfileString(PATH_SECT_OF_INIFILE, PATH1_LOG1_KEY_OF_INIFILE, L"FAILED", szLogfolder1, sizeof(szLogfolder1), szInipath);
			log_path += szLogfolder1;
			str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_NUM_OF_LOGS_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 2) nlogs = stoi(buf_t);

			//LOG01
			if (nlogs > 0) {
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_LOGNAME1_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath);
				_wsplitpath_s(szInipath, szDrive, sizeof(szDrive), szPath, sizeof(szPath), szFName, sizeof(szFName), szExt, sizeof(szExt)); // exe fileのパス分割
				_wmakepath_s(mklogset[MK_LOGSET_1].fname, sizeof(mklogset[MK_LOGSET_1].fname), szDrive, szPath, buf_t, EXT_OF_CSVFILE);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_LOGTYPE1_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_1].szType, sizeof(mklogset[MK_LOGSET_1].szType), szInipath);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_SAMPLE_TIME1_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_1].ms_period = stoi(buf_t);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_ITME_NUM1_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); mklogset[MK_LOGSET_1].n_item = stoi(buf_t);
				str_num = GetPrivateProfileString(DATA_TYPE1_SECT_OF_INIFILE, TYPE1_01_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_1].data_type[0] = stoi(buf_t);
				str_num = GetPrivateProfileString(DATA_TYPE1_SECT_OF_INIFILE, TYPE1_02_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_1].data_type[1] = stoi(buf_t);
				str_num = GetPrivateProfileString(DATA_TYPE1_SECT_OF_INIFILE, TYPE1_03_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_1].data_type[2] = stoi(buf_t);
			}
			//LOG02
			if (nlogs > 1) {
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_LOGNAME2_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath);
				_wsplitpath_s(szInipath, szDrive, sizeof(szDrive), szPath, sizeof(szPath), szFName, sizeof(szFName), szExt, sizeof(szExt)); // exe fileのパス分割
				_wmakepath_s(mklogset[MK_LOGSET_2].fname, sizeof(mklogset[MK_LOGSET_2].fname), szDrive, szPath, buf_t, EXT_OF_CSVFILE);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_LOGTYPE2_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_2].szType, sizeof(mklogset[MK_LOGSET_2].szType), szInipath);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_SAMPLE_TIME2_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_2].ms_period = stoi(buf_t);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_ITME_NUM2_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); mklogset[MK_LOGSET_2].n_item = stoi(buf_t);
				str_num = GetPrivateProfileString(DATA_TYPE2_SECT_OF_INIFILE, TYPE2_01_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_2].data_type[0] = stoi(buf_t);
				str_num = GetPrivateProfileString(DATA_TYPE2_SECT_OF_INIFILE, TYPE2_02_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_2].data_type[1] = stoi(buf_t);
				str_num = GetPrivateProfileString(DATA_TYPE2_SECT_OF_INIFILE, TYPE2_03_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_2].data_type[2] = stoi(buf_t);
			}
			//LOG03
			if (nlogs > 2) {
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_LOGNAME3_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath);
				_wsplitpath_s(szInipath, szDrive, sizeof(szDrive), szPath, sizeof(szPath), szFName, sizeof(szFName), szExt, sizeof(szExt)); // exe fileのパス分割
				_wmakepath_s(mklogset[MK_LOGSET_3].fname, sizeof(mklogset[MK_LOGSET_3].fname), szDrive, szPath, buf_t, EXT_OF_CSVFILE);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_LOGTYPE3_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_3].szType, sizeof(mklogset[MK_LOGSET_3].szType), szInipath);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_SAMPLE_TIME3_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_3].ms_period = stoi(buf_t);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_ITME_NUM3_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); mklogset[MK_LOGSET_3].n_item = stoi(buf_t);
				str_num = GetPrivateProfileString(DATA_TYPE3_SECT_OF_INIFILE, TYPE3_01_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_3].data_type[0] = stoi(buf_t);
				str_num = GetPrivateProfileString(DATA_TYPE3_SECT_OF_INIFILE, TYPE3_02_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_3].data_type[1] = stoi(buf_t);
				str_num = GetPrivateProfileString(DATA_TYPE3_SECT_OF_INIFILE, TYPE3_03_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_3].data_type[2] = stoi(buf_t);
			}
			//LOG04
			if (nlogs > 3) {}
			//LOG05
			if (nlogs > 4) {}			
			//LOG06
			if (nlogs > 5) {}
			//LOG07
			if (nlogs > 6) {}
			//LOG08
			if (nlogs > 7) {}

			wstring ws_now = getDatetimeStr();

		return 0;
	};
	//########################################################################
	VOID CALLBACK CMKlog::MKlogTimerProc(HWND hWnd, UINT msg, UINT idEvent, DWORD dwTime)
	{
		int logID = 0;

		for (; logID < nlogs; logID++) if (mklogset[logID].timerID == idEvent)break;
		if (logID >= nlogs) return;

		wcout << "LOG ID :" << logID << endl;

		if (mklogset[logID].status == LOG_STATUS_ACTIVE) add_record(logID);
		else if ((mklogset[logID].status == LOG_STATUS_STOP) || (mklogset[logID].status == LOG_STATUS_ERROR)) {
			KillTimer(nullptr, idEvent); mklogset[logID].timerID = 0;
		}
		else;
		return;
	};

	//########################################################################
	int CMKlog::start_record(int logID, HWND hWnd) {
		if ((logID > nlogs)||(logID < 0))return -1;
		
		mklogset[logID].status = LOG_STATUS_ACTIVE;

		if (mklogset[logID].ms_period > 9) {
			if (hWnd != NULL) mklogset[logID].timerID = SetTimer(hWnd, TIMER_ID_BASE+logID, mklogset[logID].ms_period, NULL);
			else              mklogset[logID].timerID = SetTimer(NULL, NULL, mklogset[logID].ms_period, MKlogTimerProc);
		}

		return 0;
	};

	//########################################################################
	int CMKlog::end_record(int logID) {
		if ((logID > nlogs) || (logID < 0))return -1;
		mklogset[logID].status = LOG_STATUS_STOP;
		if (mklogset[logID].fp != nullptr) {
			fclose(mklogset[logID].fp); mklogset[logID].fp = nullptr;
		}
		return 0;
	};

	//########################################################################
	int CMKlog::pause_record(int logID) {
		if ((logID > nlogs) || (logID < 0))return -1;
		mklogset[logID].status = LOG_STATUS_PAUSE;
		return 0;
	};

	//########################################################################
	int CMKlog::add_record(int logID) {
		
		return 0;
	};

	//########################################################################
	wstring CMKlog::getDatetimeStr() {
	
		time_t t = time(nullptr);
		struct tm t_now;
		errno_t error = localtime_s(&t_now, &t);

		std::wstringstream ws;
		ws << L"20" << t_now.tm_year - 100;
		// setw(),setfill()で0詰め
		ws << setw(2) << setfill(L'0') << t_now.tm_mon + 1;
		ws << setw(2) << setfill(L'0') << t_now.tm_mday;
		ws << setw(2) << setfill(L'0') << t_now.tm_hour;
		ws << setw(2) << setfill(L'0') << t_now.tm_min;
		ws << setw(2) << setfill(L'0') << t_now.tm_sec;
		// std::stringにして値を返す
		return ws.str();
	}

}

