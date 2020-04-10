// ����ũ�� ���ø����̼�.
#include <windows.h>
#include <stdio.h>

#define ID_OK_BTN	2000

HINSTANCE g_hInst; // �ڵ�
LPCTSTR lpszClass = L"HelloAPI";
LPCTSTR ChildClassName = L"ChildWin";
LPCTSTR ChildClassName2 = L"ChildWin2";


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void main(int argc, char** argv)
{
	printf("HELLO CONSOLE WINDOW!!!");
}

// ���� ����
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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//���� �귯��
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);// Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);// ������
	WndClass.hInstance = hInstance;// �ڵ�
	WndClass.lpfnWndProc = (WNDPROC)WndProc; // ���ν���
	WndClass.lpszClassName = lpszClass; // ������ Ÿ��Ʋ �̸�
	WndClass.lpszMenuName = NULL; // �޴� ����
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);     //���������� Ŭ���� ���

	WndClass.lpfnWndProc = ChildWndProc;      //���ϵ� ������ ���ν���
	WndClass.lpszClassName = ChildClassName; //���ϵ� ������ Ŭ�����̸�
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = ChildWndProc;      //���ϵ� ������ ���ν���
	WndClass.lpszClassName = ChildClassName2; //���ϵ� ������ Ŭ�����̸�
	RegisterClass(&WndClass);

	// ������ ����
	hWnd = CreateWindow(lpszClass,			//������Ŭ���� �̸�
		L"������ ���α׷���",			    //������Ÿ��Ʋ
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //�����콺Ÿ��
		200, 200,							//�����찡 ���϶� X Y��ǥ
		600, 600,							//�������� ���� ����				
		(HWND)NULL,							//�θ������� �ڵ�
		(HMENU)NULL,						//�����찡 ������ �޴��ڵ�
		hInstance,							//�ν��Ͻ��ڵ�
		NULL);								//������ ������

	//WS_OVERLAPPEDWINDOW
	//WS_CAPTION	Ÿ��Ʋ �ٸ� ������.
	//WS_HSCROLL	���� ��ũ�� �ٸ� ������.
	//WS_VSCROLL	���� ��ũ�� �ٸ� ������.
	//WS_MAXIMIZEBOX	�ִ�ȭ ��ư�� ������.
	//WS_MINIMIZEBOX	�ּ�ȭ ��ư�� ������.
	//WS_SYSMENU	�ý��� �޴��� ������.
	//WS_THICKFRAME	ũ�⸦ ������ �� �ִ� ��輱�� ������.


	hWnd2 = CreateWindow(lpszClass,			//������Ŭ���� �̸�
		L"������ ���α׷���",			    //������Ÿ��Ʋ
		WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL,   //�����콺Ÿ��
		100, 100,							//�����찡 ���϶� X Y��ǥ
		600, 600,							//�������� ���� ����				
		(HWND)NULL,							//�θ������� �ڵ�
		(HMENU)NULL,						//�����찡 ������ �޴��ڵ�
		hInstance,							//�ν��Ͻ��ڵ�
		NULL);								//������ ������

	ShowWindow(hWnd, nCmdShow);		//������
	ShowWindow(hWnd2, nCmdShow);		//������

	// �ܼ� ����, �α� ������� �����
	AllocConsole();
	FILE* fpstdin = stdin, * fpstdout = stdout, * fpstderr = stderr;
	//freopen("CONOUT$", "w+", stdout);
	freopen_s(&fpstdin, "CONIN$", "r", stdin);
	freopen_s(&fpstdout, "CONOUT$", "w", stdout);
	freopen_s(&fpstderr, "CONOUT$", "w", stderr);

	// �ݺ������� ������ ǥ��
	// WM_QUIT �� ��� false
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
		printf("%d , %d\n", Message.pt.x, Message.pt.y);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,	WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"���������� ����";
	switch (iMessage) {
	case WM_LBUTTONDOWN://���콺 ������ư
	{
	}
	case WM_CHAR:// ���� �Է� ������
	{

	}
	case WM_PAINT://�ٽ� ȭ�� �׸���
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, text, lstrlen(text));
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_CREATE://ó�� �����
	{
		HWND hChildWnd = CreateWindow(
			ChildClassName,     		// ���ϵ� ������ Ŭ���� �̸� 
			L"���ϵ� ������",            	// ������ Ÿ��Ʋ 
			WS_OVERLAPPEDWINDOW | WS_CHILD,  // ������  ��Ÿ�� 
			150,       		// ������ ���� �� x ��ǥ 
			150,       		// ������ ���� �� y ��ǥ 
			260,       		// ������ ��
			200,       		// ������ ����
			hWnd,         		// �θ� ������
			(HMENU)1000,        	// ���ϵ� ������ID 
			g_hInst,           		// �ν��Ͻ� �ڵ� 
			(LPVOID)NULL);      	// ������ ������					
		
		HWND hChildWnd2 = CreateWindow(
			ChildClassName2,     		// ���ϵ� ������ Ŭ���� �̸� 
			L"���ϵ� ������2",            	// ������ Ÿ��Ʋ 
			WS_OVERLAPPEDWINDOW | WS_CHILD,  // ������  ��Ÿ�� 
			100,       		// ������ ���� �� x ��ǥ 
			100,       		// ������ ���� �� y ��ǥ 
			260,       		// ������ ��
			200,       		// ������ ����
			hWnd,         		// �θ� ������
			(HMENU)1001,        	// ���ϵ� ������ID 
			g_hInst,           		// �ν��Ͻ� �ڵ� 
			(LPVOID)NULL);      	// ������ ������			

		ShowWindow(hChildWnd, SW_SHOW);
		ShowWindow(hChildWnd2, SW_SHOW);

		hChildWnd = CreateWindow(
			L"button",        		// ������ Ŭ���� �̸� 
			L"��������",			// ������ Ÿ��Ʋ 
			WS_CHILD | WS_VISIBLE, 	// ������ ��Ÿ�� 
			20,       		// ������ ���� �� x ��ǥ 
			400,       		// ������ ���� �� y ��ǥ 
			100,       		// ������ ��
			30,       		// ������ ����
			hWnd,         		// �θ� ������
			(HMENU)ID_OK_BTN,   	// ��Ʈ�� ID
			g_hInst,           		// �ν��Ͻ� �ڵ� 
			(LPVOID)NULL);      	// ������ ������

		if (!hChildWnd) 	return -1;
		return 0;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == ID_OK_BTN)
		{
			MessageBox(hWnd, L"[��������] ��ư�� Ŭ���Ǿ���", L"��������", MB_OK);
		}

		return 0;
	}
	case WM_DESTROY://�޸𸮿��� �ı��ɶ�
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"���ϵ� ���������";
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