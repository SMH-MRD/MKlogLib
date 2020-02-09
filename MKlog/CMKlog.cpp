

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
	double CMKlog::def_double=0.0;
	bool CMKlog::def_bool=false;

	//########################################################################
	int CMKlog::init_logfunc() {
	
		for (int i = 0; i < LOG_RECORD_MAX; i++) {
			for (int k = 0; k < LOG_ITEM_MAX; k++) {
				mklogset[i].p_double[k] = &def_double;
				mklogset[i].p_int[k] = &nlogs;
				mklogset[i].p_bool[k] = &def_bool;
			}
		}
		for (int i = 0; i < LOG_RECORD_MAX; i++)mklogset[i].fp = nullptr;

		//iniファイルPATH取得
		GetModuleFileName(NULL, szInipath, (sizeof(TCHAR) * _MAX_PATH));// exe fileのパス取り込み
		_wsplitpath_s(szInipath, szDrive, sizeof(szDrive), szPath, sizeof(szPath), szFName, sizeof(szFName), szExt, sizeof(szExt)); // exe fileのパス分割
		log_path.clear(); log_path += szPath;
		_wmakepath_s(szInipath, sizeof(szInipath), szDrive, szPath, NAME_OF_INIFILE, EXT_OF_INIFILE); // ini fileのパスセット


		//iniファイル設定値読み込み
		TCHAR buf_t[128];
		DWORD	str_num = GetPrivateProfileString(PATH_SECT_OF_INIFILE, PATH1_LOG1_KEY_OF_INIFILE, L"FAILED", szLogfolder1, sizeof(szLogfolder1), szInipath);
			log_path += szLogfolder1;
			str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_NUM_OF_LOGS_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 2) nlogs = stoi(buf_t);

			//LOG01
			if (nlogs > 0) {
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_LOGNAME1_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_1].fname, sizeof(mklogset[MK_LOGSET_1].fname), szInipath);
				_wsplitpath_s(szInipath, szDrive, sizeof(szDrive), szPath, sizeof(szPath), szFName, sizeof(szFName), szExt, sizeof(szExt)); // exe fileのパス分割
			//	_wmakepath_s(mklogset[MK_LOGSET_1].fname, sizeof(mklogset[MK_LOGSET_1].fname), szDrive, szPath, buf_t, EXT_OF_CSVFILE);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_LOGTYPE1_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_1].szType, sizeof(mklogset[MK_LOGSET_1].szType), szInipath);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_SAMPLE_TIME1_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_1].ms_period = stoi(buf_t);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_ITME_NUM1_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5) mklogset[MK_LOGSET_1].n_item = stoi(buf_t);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_ITME_TIMESET1_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5) mklogset[MK_LOGSET_1].timeset = stoi(buf_t);

				str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL01_KEY_OF_INIFILE, L"DATA01", mklogset[MK_LOGSET_1].labes[0], LABEL_LEN_MAX, szInipath); 
				str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL02_KEY_OF_INIFILE, L"DATA02", mklogset[MK_LOGSET_1].labes[1], LABEL_LEN_MAX, szInipath);
				str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL03_KEY_OF_INIFILE, L"DATA03", mklogset[MK_LOGSET_1].labes[2], LABEL_LEN_MAX, szInipath);
				str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL04_KEY_OF_INIFILE, L"DATA04", mklogset[MK_LOGSET_1].labes[3], LABEL_LEN_MAX, szInipath);
				str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL05_KEY_OF_INIFILE, L"DATA05", mklogset[MK_LOGSET_1].labes[4], LABEL_LEN_MAX, szInipath);
				str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL06_KEY_OF_INIFILE, L"DATA06", mklogset[MK_LOGSET_1].labes[5], LABEL_LEN_MAX, szInipath);
				str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL07_KEY_OF_INIFILE, L"DATA07", mklogset[MK_LOGSET_1].labes[6], LABEL_LEN_MAX, szInipath);
				str_num = GetPrivateProfileString(LABEL_NAME1_SECT_OF_INIFILE, LABEL08_KEY_OF_INIFILE, L"DATA08", mklogset[MK_LOGSET_1].labes[7], LABEL_LEN_MAX, szInipath);

			}
			//LOG02
			if (nlogs > 1) {
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_LOGNAME2_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_2].fname, sizeof(mklogset[MK_LOGSET_2].fname), szInipath);
				_wsplitpath_s(szInipath, szDrive, sizeof(szDrive), szPath, sizeof(szPath), szFName, sizeof(szFName), szExt, sizeof(szExt)); // exe fileのパス分割
			//	_wmakepath_s(mklogset[MK_LOGSET_2].fname, sizeof(mklogset[MK_LOGSET_2].fname), szDrive, szPath, buf_t, EXT_OF_CSVFILE);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_LOGTYPE2_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_2].szType, sizeof(mklogset[MK_LOGSET_2].szType), szInipath);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_SAMPLE_TIME2_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_2].ms_period = stoi(buf_t);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_ITME_NUM2_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5) mklogset[MK_LOGSET_2].n_item = stoi(buf_t);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_ITME_TIMESET2_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5) mklogset[MK_LOGSET_2].timeset = stoi(buf_t);

				str_num = GetPrivateProfileString(LABEL_NAME2_SECT_OF_INIFILE, LABEL01_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_2].labes[0], LABEL_LEN_MAX, szInipath);
				str_num = GetPrivateProfileString(LABEL_NAME2_SECT_OF_INIFILE, LABEL02_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_2].labes[1], LABEL_LEN_MAX, szInipath);
				str_num = GetPrivateProfileString(LABEL_NAME2_SECT_OF_INIFILE, LABEL03_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_2].labes[2], LABEL_LEN_MAX, szInipath);

			}
			//LOG03
			if (nlogs > 2) {
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_LOGNAME3_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_3].fname, sizeof(mklogset[MK_LOGSET_3].fname), szInipath);
				_wsplitpath_s(szInipath, szDrive, sizeof(szDrive), szPath, sizeof(szPath), szFName, sizeof(szFName), szExt, sizeof(szExt)); // exe fileのパス分割
			//	_wmakepath_s(mklogset[MK_LOGSET_3].fname, sizeof(mklogset[MK_LOGSET_3].fname), szDrive, szPath, buf_t, EXT_OF_CSVFILE);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_LOGTYPE3_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_3].szType, sizeof(mklogset[MK_LOGSET_3].szType), szInipath);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_SAMPLE_TIME3_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5)mklogset[MK_LOGSET_3].ms_period = stoi(buf_t);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_ITME_NUM3_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5) mklogset[MK_LOGSET_3].n_item = stoi(buf_t);
				str_num = GetPrivateProfileString(SET_SECT_OF_INIFILE, SET_ITME_TIMESET3_KEY_OF_INIFILE, L"FAILED", buf_t, sizeof(buf_t), szInipath); if (str_num < 5) mklogset[MK_LOGSET_3].timeset = stoi(buf_t);

				str_num = GetPrivateProfileString(LABEL_NAME3_SECT_OF_INIFILE, LABEL01_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_3].labes[0], LABEL_LEN_MAX, szInipath);
				str_num = GetPrivateProfileString(LABEL_NAME3_SECT_OF_INIFILE, LABEL02_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_3].labes[1], LABEL_LEN_MAX, szInipath);
				str_num = GetPrivateProfileString(LABEL_NAME3_SECT_OF_INIFILE, LABEL03_KEY_OF_INIFILE, L"FAILED", mklogset[MK_LOGSET_3].labes[2], LABEL_LEN_MAX, szInipath);

			}
			//LOG04
			if (nlogs > 3) { ; }
			//LOG05
			if (nlogs > 4) { ; }
			//LOG06
			if (nlogs > 5) { ; }
			//LOG07
			if (nlogs > 6) { ; }
			//LOG08
			if (nlogs > 7) { ; }

	
		return 0;
	};

	//########################################################################
	VOID CALLBACK CMKlog::MKlogTimerProc(HWND hWnd, UINT msg, UINT idEvent, DWORD dwTime)
	{
		int logID = 0;

		for (; logID < nlogs; logID++) if (mklogset[logID].timerID == idEvent)break;
		if (logID >= nlogs) return;

	//	wcout << "double[0] :" << *mklogset[logID].p_double[0] << endl;

		if (mklogset[logID].status == LOG_STATUS_ACTIVE) add_record(logID);
		else if ((mklogset[logID].status == LOG_STATUS_STOP) || (mklogset[logID].status == LOG_STATUS_ERROR)) {
			KillTimer(nullptr, idEvent); mklogset[logID].timerID = 0;
			end_record(logID);
		}
		else;
		return;
	};

	//########################################################################
	int CMKlog::set_label(int logID) {
		wstring wstr; wstr.clear();
		wstringstream ws;
		DWORD written;
		time_t t = time(0);
		ws << setw(10) << t;

		wstr += ws.str();
		for (int i = 0; i < mklogset[logID].n_item; i++) {
			wstr += L",";
			wstr += mklogset[logID].labes[i];
		}
		wstr += L"\r\n";
		WriteFile(mklogset[logID].hf, wstr.c_str(), wstr.length() * 2, &written, NULL);
		return 0;
	}

	//########################################################################
	int CMKlog::start_record(int logID, HWND hWnd) {
		if ((logID > nlogs)||(logID < 0))return -1;
		
		mklogset[logID].status = LOG_STATUS_ACTIVE;

		//ファイル名設定
		mklogset[logID].filename.clear();
		mklogset[logID].filename += log_path;
		mklogset[logID].filename += mklogset[logID].fname;
		mklogset[logID].filename += DELIMITER_OF_FILE;
		mklogset[logID].filename += getDatetimeStr();
		mklogset[logID].filename += EXT_OF_CSVFILE;
		//ログファイルオープン
		mklogset[logID].hf = CreateFile(mklogset[logID].filename.c_str(), GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
		//ラベル記録
		set_label(logID);
		//ログ記録タイマーセット
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
		KillTimer(nullptr, mklogset[logID].timerID); 
		mklogset[logID].timerID = 0;

		if(mklogset[logID].hf!=NULL) CloseHandle(mklogset[logID].hf);
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

		SYSTEMTIME stTime;
		static TCHAR strTime;

		wstring wstr; wstr.clear();
		wstringstream ws;
		DWORD written;

		GetLocalTime(&stTime);

		ws << stTime.wHour << L":"<< stTime.wMinute << L":" << stTime.wSecond << L"."<<setw(3)<<setfill(L'0') << stTime.wMilliseconds;

		int i_double=0, i_int=0, i_bool=0;
		for (int i = 0; i < mklogset[logID].n_item; i++) {
			ws << L",";
			switch (mklogset[logID].data_type[i]) {
			case MK_DATA_TYPE_DOUBLE:
				ws << *mklogset[logID].p_double[i];
				i_double++;
				break;
			case MK_DATA_TYPE_INT:
				ws << *mklogset[logID].p_int[i];
				i_int++;
				break;
			case MK_DATA_TYPE_BOOL:
				ws << *mklogset[logID].p_bool[i];
				i_bool++;
				break;

			}
		}
		wstr += ws.str();
		wstr += L"\r\n";
		WriteFile(mklogset[logID].hf, wstr.c_str(), wstr.length() * 2, &written, NULL);
		return 0;
	};

	//########################################################################
	wstring CMKlog::getDatetimeStr() {
		static std::wstringstream ws;
		time_t t = time(nullptr);
		struct tm t_now;
		errno_t error = localtime_s(&t_now, &t);

		ws.clear(); ws.str(L"");
	//	ws << L"20" << t_now.tm_year - 100;
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

