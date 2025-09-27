#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_LOGIN_INVITE[] = "������� ��� ������������";
//g_  - Global
//sz_ - String Zero (NULL-Terminated Line)

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*MessageBox
	(
		NULL,
		"������ WinAPI!\n��� ���� ����������?",
		"Hello",
		MB_YESNOCANCEL | MB_ICONQUESTION | MB_HELP | MB_DEFBUTTON3 | MB_SYSTEMMODAL
	);*/

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, NULL);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//1) hwnd - ����;
	//2) uMsg - ���������;
	//3) wParam - ������� ���������;
	//4) lParam - �������� ���������;
	switch (uMsg)
	{
	case WM_INITDIALOG:		//��� ������ ����������� ���� ���, ����� ��� ���������� ��������� � ���� �������.
	{
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		//SetFocus(hEditLogin);
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
		SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITE);
	}
	break;
	case WM_COMMAND:		//������������ ������� � ���������� � ����
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);	//�������� ��������� ���� Login
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				if (strcmp(sz_buffer, g_sz_LOGIN_INVITE) == 0)
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
			}
			if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				if (strcmp(sz_buffer, "") == 0)
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITE);
			}
		}
			break;
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			//HWND window_handler = GetDlgItem(parent_window_handler, ELEMENT_ID);
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK:		MessageBox(hwnd, "���� ������ ������ OK", "Info", MB_OK | MB_ICONINFORMATION);	break;
		case IDCANCEL:	EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:			//��������� ����
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}