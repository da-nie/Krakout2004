class WND_MAIN
{
 public:
  //-----------------------------------------------------------
  HWND hWnd;
  //-----------------------------------------------------------
  LPDIRECTDRAW lpdd_old;
  LPDIRECTDRAW7 lpdd;
  DDSURFACEDESC2 ddsd;
  LPDIRECTDRAWSURFACE7 lpddsprimary;
  LPDIRECTDRAWSURFACE7 lpddssecondary;
  int lPitch32;
  UINT *Video_Buffer;
  int Active;
  //-----------------------------------------------------------
  GAME Game;
  SPRITE Back;//задний фон
  //-----------------------------------------------------------
  void Create(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void Destroy(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void Activate(HWND hWnds,WPARAM wParam,LPARAM lParam);
  void Char(HWND hWnds,WPARAM wParam,LPARAM lParam);
  //-----------------------------------------------------------
  void Processing(int step);
 //-----------------------------------------------------------
} Wnd_Main;
//------------------------------------------------------------------------------
void WND_MAIN::Create(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 hWnd=hWnds;
 Active=0;
 lpdd=NULL;
 lpddsprimary=NULL;
 lpddssecondary=NULL;
 if (FAILED(DirectDrawCreate(NULL,&lpdd_old,NULL)))
 {
  MessageBox(hWnd,"Ошибка инициализации DirectDraw7","ERROR",MB_OK);
  DestroyWindow(hWnd);
  return;
 }
 lpdd_old->QueryInterface(IID_IDirectDraw7,(void **)&lpdd);
 lpdd_old->Release();
 Game.Create();
 Back.Load("bitmap\\back.bmp");
 Sound.Create(hWnd);
}
void WND_MAIN::Destroy(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 Game.Release();
 Game.ReleaseSpriteSurface(lpdd);
 if (lpdd!=NULL) lpdd->Release();
 if (Active==1)
 {
  if (lpddsprimary!=NULL) lpddsprimary->Release();
 }
}
//------------------------------------------------------------------------------
void WND_MAIN_Register(void);
LONG WINAPI WND_MAIN_wndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
//------------------------------------------------------------------------------
void WND_MAIN_Register(void)
{
 WNDCLASS wc;
 wc.style=CS_HREDRAW|CS_VREDRAW;
 wc.cbClsExtra=0;
 wc.cbWndExtra=0;
 wc.hInstance=hProjectInstance;
 wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
 wc.hCursor=LoadCursor(NULL,IDC_ARROW);
 wc.hbrBackground=(HBRUSH)(COLOR_WINDOW);
 wc.lpszMenuName=NULL;
 wc.lpszClassName="Wnd_Main";
 wc.lpfnWndProc=(WNDPROC)WND_MAIN_wndProc;
 RegisterClass(&wc);
}
LONG WINAPI WND_MAIN_wndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
  {
   case WM_CREATE:
    {
     Wnd_Main.Create(hWnd,wParam,lParam);
     return(0);
    }
   case WM_DESTROY:
    {
     Wnd_Main.Destroy(hWnd,wParam,lParam);
     PostQuitMessage(0);
     return(0);
    }
   case WM_ACTIVATE:
    {
     Wnd_Main.Activate(hWnd,wParam,lParam);
     return(0);
    }
   case WM_CHAR:
   {
    Wnd_Main.Char(hWnd,wParam,lParam);
    return(0);
   }
  }
 return(DefWindowProc(hWnd,msg,wParam,lParam));
}
//------------------------------------------------------------------------------
void WND_MAIN::Activate(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 if ((LOWORD(wParam)==WA_ACTIVE || LOWORD(wParam)==WA_CLICKACTIVE) && Active==0) 
 {
  lpdd->SetCooperativeLevel(hWnd,DDSCL_FULLSCREEN|DDSCL_ALLOWMODEX|DDSCL_EXCLUSIVE|DDSCL_ALLOWREBOOT);
  lpdd->SetDisplayMode(640,480,32,0,0);
  memset(&ddsd,0,sizeof(ddsd));
  ddsd.dwSize=sizeof(DDSURFACEDESC2);
  ddsd.dwFlags=DDSD_CAPS|DDSD_BACKBUFFERCOUNT;
  ddsd.dwBackBufferCount=1;
  ddsd.ddsCaps.dwCaps=DDSCAPS_COMPLEX|DDSCAPS_FLIP|DDSCAPS_PRIMARYSURFACE;
  lpdd->CreateSurface(&ddsd,&lpddsprimary,NULL);
  ddsd.ddsCaps.dwCaps=DDSCAPS_BACKBUFFER;
  lpddsprimary->GetAttachedSurface(&ddsd.ddsCaps,&lpddssecondary);
  Active=1;
  ShowCursor(FALSE);
  Game.CreateSpriteSurface(lpdd);
  Back.CreateSpriteSurface(lpdd);
 }
 if (LOWORD(wParam)==WA_INACTIVE && Active==1) 
 {
  Game.ReleaseSpriteSurface(lpdd);
  Back.ReleaseSpriteSurface();
  if (lpddsprimary!=NULL) lpddsprimary->Release();
  Active=0;
  ShowCursor(TRUE);
 }
}
void WND_MAIN::Char(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 int press=(lParam&2147483648)<<31;
 if (press!=0) return;
 Game.TransferChar(LOWORD(wParam));
}
//------------------------------------------------------------------------------
void WND_MAIN::Processing(int step)
{
 if (Active==0) return;
 for(int n=0;n<3;n++)
 {
  int res=Game.Processing(n+3*step);
  if (res==1)
  {
   DestroyWindow(hWnd);
   return;
  }
 }
 if (step==0)
 {
  Back.Put(0,0,lpddssecondary,ddsd);
  //очистим вторичную поверхность
  /*RECT dest_rect;
  dest_rect.left=0;
  dest_rect.top=0;
  dest_rect.right=640;
  dest_rect.bottom=480;
  DDBLTFX ddbltfx;
  memset(&ddbltfx,0,sizeof(ddbltfx)); 
  ddbltfx.dwSize=sizeof(ddbltfx);
  ddbltfx.dwFillColor=0;
  lpddssecondary->Blt(&dest_rect,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&ddbltfx);*/
  //выведем графику
  Game.Draw(lpddssecondary,ddsd);
  lpddsprimary->Flip(NULL,DDFLIP_WAIT);
 }
}
