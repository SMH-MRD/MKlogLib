// MKlogTestApp.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include "CMKlog.h"

using namespace std;

int main()
{
	MKlog::CMKlog *plogobj = new MKlog::CMKlog ;

	plogobj->init_logfunc();
	wcout << plogobj->szInipath<<endl;

	char inputc='0';
	while (inputc != 'q') cin >> inputc;


	delete plogobj;

	return 0;
}

