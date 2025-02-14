// MKlogTestApp.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include "CMKlog.h"
#include "math.h"

using namespace std;
using namespace MKlog;

static double	double_data[8];
static int		int_data[8];
static bool		bool_data[8];
static UINT IDtimer;

VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime) {


	double_data[0] += 0.1111; if (double_data[0]>6.28)double_data[0] = 0.0;
	double_data[1] = sin(double_data[0]); 
	double_data[2] -= 0.00014; if (double_data[2]<-1.0)double_data[0] = 0.0;
	
	int_data[0] += 1; if (int_data[0] > 100)int_data[0] = 0;
	if (int_data[0] % 10<5)bool_data[0] = true; else bool_data[0] = false;

	if((idEvent == IDtimer)&&(int_data[0]%100 ==1)) {
    	wcout << int_data[0] << double_data[0] << bool_data[0] << endl;
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_TIMER:
		wcout << "TIMER EVENT TRIGGERRED!" << endl;
		return 0;
	case WM_CREATE:

		return 0;
	}
	return DefWindowProc(hwnd, msg, wp, lp);
}

void set_address(CMKlog* plogobj) {
	for (int i = 0; i < 8; i++) {
		plogobj->set_double_data(double_data + i, MK_LOGSET_1, i);
	}
	return;
}


int main()
{
	HWND hwnd;
	MSG msg;
	WNDCLASS winc;
	HINSTANCE hInstance = GetModuleHandle(0);
	
	CMKlog *plogobj = new CMKlog ;

	
	plogobj->init_logfunc();
	set_address(plogobj);

	wcout << plogobj->szInipath<<endl;

	//Timerイベント受信用Window	作成
	{
		winc.style = CS_HREDRAW | CS_VREDRAW;
		winc.lpfnWndProc = WndProc;
		winc.cbClsExtra = winc.cbWndExtra = 0;
		winc.hInstance = hInstance;
		winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		winc.hCursor = LoadCursor(NULL, IDC_ARROW);
		winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		winc.lpszMenuName = NULL;
		winc.lpszClassName = TEXT("KITTY");

		if (!RegisterClass(&winc)) return -1;

		hwnd = CreateWindow(TEXT("KITTY"), TEXT("CLOSE THIS WINDOW FOR QUIT APPLI!!"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 400, 300, 400, 40, NULL, NULL, hInstance, NULL);

		if (hwnd == NULL) return -1;
	}


	plogobj->start_record(MK_LOGSET_1, NULL);
//	plogobj->start_record(MK_LOGSET_2, NULL);
//	plogobj->start_record(MK_LOGSET_3, NULL);

	IDtimer = SetTimer(NULL, NULL, 10, TimerProc);
	//IDtimer = SetTimer(hwnd, 1, 1000, NULL);

	while (GetMessage(&msg, NULL, 0, 0)) DispatchMessage(&msg);
	
	plogobj->end_record(MK_LOGSET_1);
//	plogobj->end_record(MK_LOGSET_2);
//	plogobj->end_record(MK_LOGSET_3);

	char inputc='0';
	while (inputc != 'q') cin >> inputc;

	KillTimer(NULL,IDtimer);
	delete plogobj;

	return 0;
}

