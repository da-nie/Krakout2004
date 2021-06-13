#define IDI_ICON1 1

#include "stdafx.h"
//------------------------------------------------------------------------------
#include "sprites.h"
#include "cwnd_main.h"
//------------------------------------------------------------------------------
class CMainApp:public CWinApp
{
 public:
  //-Базовые переменные класса--------------------------------------------------
  //-Переменные класса----------------------------------------------------------
  //-Базовые методы класса------------------------------------------------------
  CMainApp(void);
  ~CMainApp();
  //-Методы класса--------------------------------------------------------------
  BOOL InitInstance(void);
};
CMainApp::CMainApp(void)
{
}
CMainApp::~CMainApp()
{
}
BOOL CMainApp::InitInstance(void)
{
 CMainWnd *cMainWnd=new CMainWnd;
 HCURSOR hCursor=LoadStandardCursor(IDC_ARROW);
 HICON hIcon=(HICON)LoadIcon("IDI_ICON1");
 HBRUSH hBrush=(HBRUSH)COLOR_WINDOW;
 LPCSTR ClassName=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,hCursor,hBrush,hIcon);
 cMainWnd->CreateEx(0,ClassName,"Редактор карт Krakout",WS_MINIMIZEBOX|WS_SYSMENU|WS_VISIBLE,0,0,850,500,NULL,NULL);
 cMainWnd->ShowWindow(m_nCmdShow);
 m_pMainWnd=cMainWnd;
 return TRUE;
}

CMainApp MainApp;


