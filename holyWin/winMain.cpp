// 데스크톱 애플리케이션.
#include <windows.h>
#include <stdio.h>

#define ID_OK_BTN	2000

HINSTANCE g_hInst; // 핸들
LPCTSTR lpszClass = L"HelloAPI";
LPCTSTR ChildClassName = L"ChildWin";
LPCTSTR ChildClassName2 = L"ChildWin2";


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void main(int argc, char** argv)
{
	printf("HELLO CONSOLE WINDOW!!!");
}

// 메인 진입
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow)
{
	HWND hWnd, hWnd2;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance; //

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//배경색 브러시
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);// 커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);// 아이콘
	WndClass.hInstance = hInstance;// 핸들
	WndClass.lpfnWndProc = (WNDPROC)WndProc; // 프로시져
	WndClass.lpszClassName = lpszClass; // 윈도우 타이틀 이름
	WndClass.lpszMenuName = NULL; // 메뉴 지정
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);     //메인윈도우 클래스 등록

	WndClass.lpfnWndProc = ChildWndProc;      //차일드 윈도우 프로시저
	WndClass.lpszClassName = ChildClassName; //차일드 윈도우 클래스이름
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = ChildWndProc;      //차일드 윈도우 프로시저
	WndClass.lpszClassName = ChildClassName2; //차일드 윈도우 클래스이름
	RegisterClass(&WndClass);

	// 윈도우 생성
	hWnd = CreateWindow(lpszClass,			//윈도우클래스 이름
		L"윈도우 프로그래밍",			    //윈도우타이틀
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //윈도우스타일
		200, 200,							//윈도우가 보일때 X Y좌표
		600, 600,							//윈도우의 폭과 높이				
		(HWND)NULL,							//부모윈도우 핸들
		(HMENU)NULL,						//윈도우가 가지는 메뉴핸들
		hInstance,							//인스턴스핸들
		NULL);								//여분의 데이터

	//WS_OVERLAPPEDWINDOW
	//WS_CAPTION	타이틀 바를 가진다.
	//WS_HSCROLL	수평 스크롤 바를 가진다.
	//WS_VSCROLL	수직 스크롤 바를 가진다.
	//WS_MAXIMIZEBOX	최대화 버튼을 가진다.
	//WS_MINIMIZEBOX	최소화 버튼을 가진다.
	//WS_SYSMENU	시스템 메뉴를 가진다.
	//WS_THICKFRAME	크기를 조절할 수 있는 경계선을 가진다.


	hWnd2 = CreateWindow(lpszClass,			//윈도우클래스 이름
		L"윈도우 프로그래밍",			    //윈도우타이틀
		WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL,   //윈도우스타일
		100, 100,							//윈도우가 보일때 X Y좌표
		600, 600,							//윈도우의 폭과 높이				
		(HWND)NULL,							//부모윈도우 핸들
		(HMENU)NULL,						//윈도우가 가지는 메뉴핸들
		hInstance,							//인스턴스핸들
		NULL);								//여분의 데이터

	ShowWindow(hWnd, nCmdShow);		//보여줌
	ShowWindow(hWnd2, nCmdShow);		//보여줌

	// 콘솔 띄우기, 로그 찍기위해 사용함
	AllocConsole();
	FILE* fpstdin = stdin, * fpstdout = stdout, * fpstderr = stderr;
	//freopen("CONOUT$", "w+", stdout);
	freopen_s(&fpstdin, "CONIN$", "r", stdin);
	freopen_s(&fpstdout, "CONOUT$", "w", stdout);
	freopen_s(&fpstderr, "CONOUT$", "w", stderr);

	// 반복적으로 윈도우 표시
	// WM_QUIT 인 경우 false
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
		printf("%d , %d\n", Message.pt.x, Message.pt.y);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,	WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"메인윈도우 생성";
	switch (iMessage) {
	case WM_LBUTTONDOWN://마우스 좌측버튼
	{
	}
	case WM_CHAR:// 문자 입력 받을때
	{

	}
	case WM_PAINT://다시 화면 그릴때
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, text, lstrlen(text));
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_CREATE://처음 만들대
	{
		HWND hChildWnd = CreateWindow(
			ChildClassName,     		// 차일드 윈도우 클래스 이름 
			L"차일드 윈도우",            	// 윈도우 타이틀 
			WS_OVERLAPPEDWINDOW | WS_CHILD,  // 윈도우  스타일 
			150,       		// 윈도우 보일 때 x 좌표 
			150,       		// 윈도우 보일 때 y 좌표 
			260,       		// 윈도우 폭
			200,       		// 윈도우 높이
			hWnd,         		// 부모 윈도우
			(HMENU)1000,        	// 차일드 윈도우ID 
			g_hInst,           		// 인스턴스 핸들 
			(LPVOID)NULL);      	// 여분의 데이터					
		
		HWND hChildWnd2 = CreateWindow(
			ChildClassName2,     		// 차일드 윈도우 클래스 이름 
			L"차일드 윈도우2",            	// 윈도우 타이틀 
			WS_OVERLAPPEDWINDOW | WS_CHILD,  // 윈도우  스타일 
			100,       		// 윈도우 보일 때 x 좌표 
			100,       		// 윈도우 보일 때 y 좌표 
			260,       		// 윈도우 폭
			200,       		// 윈도우 높이
			hWnd,         		// 부모 윈도우
			(HMENU)1001,        	// 차일드 윈도우ID 
			g_hInst,           		// 인스턴스 핸들 
			(LPVOID)NULL);      	// 여분의 데이터			

		ShowWindow(hChildWnd, SW_SHOW);
		ShowWindow(hChildWnd2, SW_SHOW);

		hChildWnd = CreateWindow(
			L"button",        		// 윈도우 클래스 이름 
			L"지역대학",			// 윈도우 타이틀 
			WS_CHILD | WS_VISIBLE, 	// 윈도우 스타일 
			20,       		// 윈도우 보일 때 x 좌표 
			400,       		// 윈도우 보일 때 y 좌표 
			100,       		// 윈도우 폭
			30,       		// 윈도우 높이
			hWnd,         		// 부모 윈도우
			(HMENU)ID_OK_BTN,   	// 컨트롤 ID
			g_hInst,           		// 인스턴스 핸들 
			(LPVOID)NULL);      	// 여분의 데이터

		if (!hChildWnd) 	return -1;
		return 0;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == ID_OK_BTN)
		{
			MessageBox(hWnd, L"[지역대학] 버튼이 클릭되었다", L"지역대학", MB_OK);
		}

		return 0;
	}
	case WM_DESTROY://메모리에서 파괴될때
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"차일드 윈도우생성";
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, text, lstrlen(text));
		EndPaint(hWnd, &ps);
		return 0;
	}

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}