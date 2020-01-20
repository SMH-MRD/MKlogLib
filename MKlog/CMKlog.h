#pragma once

#include <Windows.h>
#include "MKlog_ini.h"

namespace MKlog
{
#define LOG_RECORD_MAX	8	//LOG�ɋL�^����ITEM���ő�l
#define LOG_ITEM_MAX	128 //LOG�ɋL�^����ITEM���ő�l

	typedef struct stMKlogSet {
		WCHAR szType[128];
		int ms_period;
		int n_item;
		int data_type[LOG_ITEM_MAX];
		void* pData[LOG_ITEM_MAX];	//�L�^�f�[�^�̃A�h���X�}�b�v
	}ST_MKLOG_SET, *PST_MKLOG_SET;

	class CMKlog
	{
	public:
		CMKlog() {};
		~CMKlog(){};

		static	WCHAR szInipath[_MAX_PATH], szDrive[_MAX_DRIVE], szPath[_MAX_PATH], szFName[_MAX_FNAME], szExt[_MAX_EXT];//ini�t�@�C���p�X�擾�p
		static	WCHAR szLogfile1[_MAX_PATH];
		static	ST_MKLOG_SET mklogset[LOG_RECORD_MAX];


		int init_logfunc();//�������@�ݒ�t�B���ǂݍ���
		FILE *start_record(int mode, FILE *fp);
		int end_record(FILE *fp);
		int pause_record(FILE *fp);
		int add_record(FILE *fp);

	};
}

