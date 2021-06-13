#define ID_MENU__FILE__OPEN  100
#define ID_MENU__FILE__SAVE  101
#define ID_MENU__FILE__CLEAR 102
#define ID_MENU__FILE__EXIT  103
//------------------------------------------------------------------------------
struct BLOCK
{
 int Space;//1-блок-пустое пространство
 int Image;//картинка блока
 int Prize;//номер приза (-1-нет приза)
 int Break;//с какого раза разбивается блок
};
struct BLOCK_MAP
{
 BLOCK Map[26][13];
 unsigned char VideoBuffer[500*360*3];
 SPRITE BlockSprite;
 int AccessBlock;//всего доступно блоков
 //-----------------------------------------------------------------------------
 unsigned char VideoBuffer_1[500*30*3];
 int LeftBlockPos;//позиция левого блока панели выбора
 BLOCK WorkingBlock;//параметры рабочего блока
};
//------------------------------------------------------------------------------
class CMainWnd:public CWnd
{
 public:
  //-Базовые переменные класса--------------------------------------------------
  CMenu cMenu__Main;
  CMenu cMenu__File;
  CScrollBar cScrollBar__Block;
  CComboBox cComboBox__Prize;
  CComboBox cComboBox__Break;
  CButton cButton_Character[9];
  CStatic cStatic_PrizeInfo;
  CStatic cStatic_BreakInfo;
  //-Переменные класса----------------------------------------------------------
  BLOCK_MAP BlockMap;
  TCHAR FileName[16384];
  //-Базовые методы класса------------------------------------------------------
  CMainWnd(void);
  ~CMainWnd();
  //-Обработка сообщений--------------------------------------------------------
  DECLARE_MESSAGE_MAP()
  int OnCreate(LPCREATESTRUCT lpCreateStruct);
  int OnDestroy(void);
  void Menu__File__Open(void);
  void Menu__File__Save(void);
  void Menu__File__Clear(void);
  void Menu__File__Exit(void);
  void OnPaint(void);
  void OnHScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar);
  void OnLButtonDown(UINT nFlags,CPoint point);
  void OnRButtonDown(UINT nFlags,CPoint point);
  void OnMouseMove(UINT nFlags,CPoint point);
  //-Методы класса--------------------------------------------------------------
};
//------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CMainWnd,CWnd)
 ON_WM_CREATE()
 ON_WM_DESTROY()
 ON_WM_PAINT()
 ON_WM_HSCROLL()
 ON_WM_LBUTTONDOWN()
 ON_WM_RBUTTONDOWN()
 ON_WM_MOUSEMOVE()
 ON_COMMAND(ID_MENU__FILE__OPEN,Menu__File__Open)
 ON_COMMAND(ID_MENU__FILE__SAVE,Menu__File__Save)
 ON_COMMAND(ID_MENU__FILE__CLEAR,Menu__File__Clear)
 ON_COMMAND(ID_MENU__FILE__EXIT,Menu__File__Exit)
END_MESSAGE_MAP()
//------------------------------------------------------------------------------
CMainWnd::CMainWnd(void)
{
}
CMainWnd::~CMainWnd()
{
}
//------------------------------------------------------------------------------
int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
 //-----------------------------------------------------------------------------
 //Создадим меню
 //-----------------------------------------------------------------------------
 cMenu__File.CreatePopupMenu();
 cMenu__Main.CreateMenu();
 cMenu__File.InsertMenu(1,MF_STRING,ID_MENU__FILE__OPEN,"Открыть карту");
 cMenu__File.InsertMenu(2,MF_STRING,ID_MENU__FILE__SAVE,"Сохранить карту");
 cMenu__File.InsertMenu(3,MF_SEPARATOR,0,"");
 cMenu__File.InsertMenu(4,MF_STRING,ID_MENU__FILE__CLEAR,"Очистить поле");
 cMenu__File.InsertMenu(5,MF_SEPARATOR,0,"");
 cMenu__File.InsertMenu(6,MF_STRING,ID_MENU__FILE__EXIT,"Выход");
 cMenu__Main.InsertMenu(1,MF_POPUP,(UINT)cMenu__File.m_hMenu,"Файл");
 SetMenu(&cMenu__Main);	
 DrawMenuBar();
 //-----------------------------------------------------------------------------
 //Загрузим блоки
 //-----------------------------------------------------------------------------
 BlockMap.BlockSprite.Load("bitmap\\block.bmp");
 BlockMap.BlockSprite.SetSpriteSize(20,30);
 BlockMap.AccessBlock=BlockMap.BlockSprite.Width/20;
 //-----------------------------------------------------------------------------
 //Настроим переменные
 //-----------------------------------------------------------------------------
 for(int x=0;x<25;x++)
  for(int y=0;y<12;y++) BlockMap.Map[x][y].Space=1;
 BlockMap.LeftBlockPos=0;
 BlockMap.WorkingBlock.Space=0;
 BlockMap.WorkingBlock.Break=1;
 BlockMap.WorkingBlock.Image=0;
 BlockMap.WorkingBlock.Prize=-1;
 FileName[0]=0;
 //-----------------------------------------------------------------------------
 //Создадим элементы управления
 //-----------------------------------------------------------------------------
 cScrollBar__Block.Create(SBS_HORZ|WS_CHILD|WS_VISIBLE,CRect(10,434,530,450),this,0);
 if (BlockMap.AccessBlock-25<=0) cScrollBar__Block.EnableWindow(FALSE);
                            else cScrollBar__Block.SetScrollRange(0,BlockMap.AccessBlock-25,TRUE);
 cScrollBar__Block.SetScrollPos(BlockMap.LeftBlockPos,TRUE);
 cComboBox__Break.Create(WS_VSCROLL|CBS_DROPDOWNLIST|CBS_DISABLENOSCROLL|WS_CHILD|WS_VISIBLE,CRect(540,10,840,150),this,0);
 cComboBox__Break.AddString("Блок пробивается с первого удара");
 cComboBox__Break.AddString("Блок пробивается со второго удара");
 cComboBox__Break.AddString("Блок пробивается с третьего удара");
 cComboBox__Break.AddString("Блок пробивается с четвёртого удара");
 cComboBox__Break.AddString("Блок пробивается с пятого удара");
 cComboBox__Break.SetCurSel(0);
 cComboBox__Prize.Create(WS_VSCROLL|CBS_DROPDOWNLIST|CBS_DISABLENOSCROLL|WS_CHILD|WS_VISIBLE,CRect(540,50,840,200),this,0);
 cComboBox__Prize.AddString("Нет приза");
 cComboBox__Prize.AddString("Приз B (бомба)");
 cComboBox__Prize.AddString("Приз S (стенка)");
 cComboBox__Prize.AddString("Приз M (ракета)");
 cComboBox__Prize.AddString("Приз X (жизнь)");
 cComboBox__Prize.AddString("Приз G (прилипание мяча к битке)");
 cComboBox__Prize.AddString("Приз E (удвоение битки)");
 cComboBox__Prize.AddString("Приз + (скорость мяча)");
 cComboBox__Prize.AddString("Приз - (скорость мяча)");
 cComboBox__Prize.SetCurSel(0);
 char CharacterName[9][255];
 strcpy(CharacterName[0],"Разрешить кольцо");
 strcpy(CharacterName[1],"Разрешить мину(взрывает блоки)");
 strcpy(CharacterName[2],"Разрешить монету");
 strcpy(CharacterName[3],"Разрешить шлем");
 strcpy(CharacterName[4],"Разрешить щит (даёт мяч)");
 strcpy(CharacterName[5],"Разрешить череп");
 strcpy(CharacterName[6],"Разрешить змейку из кубиков");
 strcpy(CharacterName[7],"Разрешить глаз");
 strcpy(CharacterName[8],"Разрешить вертолёт");
 for(int n=0;n<9;n++)
 {
  cButton_Character[n].Create(CharacterName[n],BS_AUTOCHECKBOX|WS_CHILD|WS_VISIBLE,CRect(540,90+n*24,840,114+n*24),this,0);
  cButton_Character[n].SetCheck(0);
 }
 cStatic_BreakInfo.Create("11",WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(10,370,350,390),this,0);
 cStatic_PrizeInfo.Create("11",WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(360,370,510,390),this,0);
 return(0);
}
int CMainWnd::OnDestroy(void)
{
 return(0);
}
void CMainWnd::Menu__File__Open(void)
{
 CFileDialog cFileDialog_Main(TRUE);
 TCHAR title[]="Открытие уровня игры Krakout";
 CString str("*.klv");
 str+=(TCHAR)NULL;
 str+="*.klv";
 str+=(TCHAR)NULL;
 str+="*.*";
 str+=(TCHAR)NULL;
 str+="*.*";
 str+=(TCHAR)NULL;
 cFileDialog_Main.m_ofn.lpstrFilter=str;
 cFileDialog_Main.m_ofn.nFilterIndex=1;
 cFileDialog_Main.m_ofn.lpstrFile=FileName;
 cFileDialog_Main.m_ofn.lpstrTitle=title;
 int res=cFileDialog_Main.DoModal();
 if (res==IDOK)
 {
  FILE *File=fopen(cFileDialog_Main.m_ofn.lpstrFile,"r+b");
  if (File==NULL)
  {
   MessageBox("Не могу открыть файл","Ошибка",MB_OK);
   return;
  }
  for(int y=0;y<12;y++) 
   for(int x=0;x<25;x++) 
   {
    fread(&BlockMap.Map[x][y].Space,1,sizeof(BlockMap.Map[x][y].Space),File);
	if (BlockMap.Map[x][y].Space==1) continue;
    fread(&BlockMap.Map[x][y].Image,1,sizeof(BlockMap.Map[x][y].Image),File);
    fread(&BlockMap.Map[x][y].Break,1,sizeof(BlockMap.Map[x][y].Break),File);
    fread(&BlockMap.Map[x][y].Prize,1,sizeof(BlockMap.Map[x][y].Prize),File);
   }
  for(int n=0;n<9;n++)
  {
   unsigned char state;
   fread(&state,1,sizeof(state),File);
   if (state==0) cButton_Character[n].SetCheck(0);
   if (state==1) cButton_Character[n].SetCheck(1);
  }
  fclose(File);
  InvalidateRect(NULL,FALSE);
 }
}
void CMainWnd::Menu__File__Save(void)
{
 CFileDialog cFileDialog_Main(FALSE);
 TCHAR title[]="Сохранение уровня игры Krakout";
 CString str("*.klv");
 str+=(TCHAR)NULL;
 str+="*.klv";
 str+=(TCHAR)NULL;
 cFileDialog_Main.m_ofn.lpstrFilter=str;
 cFileDialog_Main.m_ofn.nFilterIndex=1;
 cFileDialog_Main.m_ofn.lpstrFile=FileName;
 cFileDialog_Main.m_ofn.lpstrTitle=title;
 cFileDialog_Main.m_ofn.lpstrDefExt="klv";
 int res=cFileDialog_Main.DoModal();
 if (res==IDOK)
 {
  FILE *File=fopen(cFileDialog_Main.m_ofn.lpstrFile,"w+b");
  if (File==NULL)
  {
   MessageBox("Не могу записать файл","Ошибка",MB_OK);
   return;
  }
  for(int y=0;y<12;y++) 
   for(int x=0;x<25;x++) 
   {
    fwrite(&BlockMap.Map[x][y].Space,1,sizeof(BlockMap.Map[x][y].Space),File);
	if (BlockMap.Map[x][y].Space==1) continue;
    fwrite(&BlockMap.Map[x][y].Image,1,sizeof(BlockMap.Map[x][y].Image),File);
    fwrite(&BlockMap.Map[x][y].Break,1,sizeof(BlockMap.Map[x][y].Break),File);
    fwrite(&BlockMap.Map[x][y].Prize,1,sizeof(BlockMap.Map[x][y].Prize),File);
   }
  for(int n=0;n<9;n++)
  {
   unsigned char state=(cButton_Character[n].GetCheck())&0x0003;
   fwrite(&state,1,sizeof(state),File);
  }
  fclose(File);
 }
}
void CMainWnd::Menu__File__Clear(void)
{
 int res=MessageBox("Вы уверены, что Вы хотите очистить поле ?","Подтвержение",MB_YESNO|MB_DEFBUTTON2);
 if (res!=IDYES) return;
 for(int x=0;x<25;x++)
  for(int y=0;y<12;y++) BlockMap.Map[x][y].Space=1;
 InvalidateRect(NULL,FALSE);
}
void CMainWnd::Menu__File__Exit(void)
{ 
 int res=MessageBox("Вы уверены, что Вы хотите выйти ?","Подтвержение",MB_YESNO|MB_DEFBUTTON2);
 if (res!=IDYES) return;
 DestroyWindow(); 
}
void CMainWnd::OnPaint(void)
{
 int x,y;
 memset(BlockMap.VideoBuffer,0,500*360*3);
 memset(BlockMap.VideoBuffer_1,0,500*30*3);
 //рисуем линии сетки
 for(x=0;x<25;x++)
 {
  unsigned char *vptr=BlockMap.VideoBuffer+x*3*20;
  for(y=0;y<360;y++,vptr+=500*3)
  {
   *(vptr)=255;
   *(vptr+1)=255;
   *(vptr+2)=255;
  }
 }
 for(y=0;y<12;y++)
 {
  unsigned char *vptr=BlockMap.VideoBuffer+y*3*30*500;
  for(x=0;x<500;x++,vptr+=3)
  {
   *(vptr)=255;
   *(vptr+1)=255;
   *(vptr+2)=255;
  }
 }
 //рисуем сами блоки
 BlockMap.BlockSprite.SetScreenSize(500,360);
 for(x=0;x<25;x++)
  for(y=0;y<12;y++)
  {
   if (BlockMap.Map[x][y].Space==1) continue;
   BlockMap.BlockSprite.SetSpriteCoord(BlockMap.Map[x][y].Image,0);
   BlockMap.BlockSprite.Put(x*20,y*30,BlockMap.VideoBuffer);
  }
 //рисуем поле выбора
 BlockMap.BlockSprite.SetScreenSize(500,30);
 for(x=0;x<25;x++)
 {
  int pos=BlockMap.LeftBlockPos+x;
  if (pos>=BlockMap.AccessBlock) continue;
  BlockMap.BlockSprite.SetSpriteCoord(pos,0);
  if (pos==BlockMap.WorkingBlock.Image) BlockMap.BlockSprite.PutSelect(x*20,0,BlockMap.VideoBuffer_1);
                                   else BlockMap.BlockSprite.Put(x*20,0,BlockMap.VideoBuffer_1); 
 }
 CPaintDC dc(this);
 BITMAPINFOHEADER bmih;
 bmih.biSize=sizeof(BITMAPINFOHEADER);
 bmih.biWidth=500;
 bmih.biHeight=360;
 bmih.biPlanes=1;
 bmih.biBitCount=24;
 bmih.biCompression=BI_RGB;
 bmih.biSizeImage=0;
 bmih.biXPelsPerMeter=300;
 bmih.biYPelsPerMeter=300;
 bmih.biClrUsed=0;
 bmih.biClrImportant=0;
 RGBQUAD rgbq;
 BITMAPINFO info;
 rgbq.rgbBlue=1;
 rgbq.rgbGreen=0;
 rgbq.rgbRed=0;
 rgbq.rgbReserved=0;
 info.bmiHeader=bmih;
 info.bmiColors[0]=rgbq;
 StretchDIBits(dc.m_hDC,10,0,500,360,0,0,500,360,BlockMap.VideoBuffer,&info,DIB_RGB_COLORS,SRCCOPY);

 bmih.biWidth=500;
 bmih.biHeight=30;
 info.bmiHeader=bmih;
 StretchDIBits(dc.m_hDC,10,400,500,30,0,0,500,30,BlockMap.VideoBuffer_1,&info,DIB_RGB_COLORS,SRCCOPY);
}
void CMainWnd::OnHScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar)
{
 if (pScrollBar!=&cScrollBar__Block) return;
 if (nSBCode==SB_LINERIGHT) BlockMap.LeftBlockPos++;
 if (nSBCode==SB_LINELEFT) BlockMap.LeftBlockPos--;
 if (nSBCode==SB_PAGERIGHT) BlockMap.LeftBlockPos+=25;
 if (nSBCode==SB_PAGELEFT) BlockMap.LeftBlockPos-=25;
 if (nSBCode==SB_RIGHT) BlockMap.LeftBlockPos=BlockMap.AccessBlock-25;
 if (nSBCode==SB_LEFT) BlockMap.LeftBlockPos=0;
 if (nSBCode==SB_THUMBPOSITION || nSBCode==SB_THUMBTRACK) BlockMap.LeftBlockPos=nPos;
 if (BlockMap.LeftBlockPos<0) BlockMap.LeftBlockPos=0;
 if (BlockMap.LeftBlockPos>=BlockMap.AccessBlock-25) BlockMap.LeftBlockPos=BlockMap.AccessBlock-25;
 pScrollBar->SetScrollPos(BlockMap.LeftBlockPos,TRUE);
 InvalidateRect(NULL,FALSE);
}
void CMainWnd::OnLButtonDown(UINT nFlags,CPoint point)
{
 int m_x_1=point.x-10;
 int m_y_1=point.y;
 int m_x_2=point.x-10;
 int m_y_2=point.y-400;
 if (m_x_1>=0 && m_x_1<500 && m_y_1>=0 && m_y_1<360)
 {
  int bx=m_x_1/20;
  int by=m_y_1/30;
  //получим параметры блока
  BlockMap.WorkingBlock.Break=cComboBox__Break.GetCurSel()+1;
  BlockMap.WorkingBlock.Prize=cComboBox__Prize.GetCurSel()-1;
  if (nFlags&MK_LBUTTON) BlockMap.Map[bx][by]=BlockMap.WorkingBlock;
  InvalidateRect(NULL,FALSE);
 }
 if (m_x_2>=0 && m_x_2<500 && m_y_2>=0 && m_y_2<30 && nFlags&MK_LBUTTON)
 {
  int bx=m_x_2/20;
  if (BlockMap.LeftBlockPos+bx<BlockMap.AccessBlock) BlockMap.WorkingBlock.Image=bx+BlockMap.LeftBlockPos;
  InvalidateRect(NULL,FALSE);
 }
}
void CMainWnd::OnRButtonDown(UINT nFlags,CPoint point)
{
 if (!(nFlags&MK_RBUTTON)) return;
 int m_x=point.x-10;
 int m_y=point.y;
 if (m_x>=0 && m_x<500 && m_y>=0 && m_y<360)
 {
  int bx=m_x/20;
  int by=m_y/30;
  BlockMap.Map[bx][by].Space=1;
  InvalidateRect(NULL,FALSE);
 }
}
void CMainWnd::OnMouseMove(UINT nFlags,CPoint point)
{
 int m_x_1=point.x-10;
 int m_y_1=point.y;
 int m_x_2=point.x-10;
 int m_y_2=point.y-400;
 if (m_x_1>=0 && m_x_1<500 && m_y_1>=0 && m_y_1<360)
 {
  int bx=m_x_1/20;
  int by=m_y_1/30;
  //получим параметры блока
  BlockMap.WorkingBlock.Break=cComboBox__Break.GetCurSel()+1;
  BlockMap.WorkingBlock.Prize=cComboBox__Prize.GetCurSel()-1;
  if (nFlags&MK_LBUTTON) BlockMap.Map[bx][by]=BlockMap.WorkingBlock;
  if (nFlags&MK_RBUTTON) BlockMap.Map[bx][by].Space=1;
  int b_break=BlockMap.Map[bx][by].Break;  
  int b_prize=BlockMap.Map[bx][by].Prize;
  int b_space=BlockMap.Map[bx][by].Space;
  if (b_space==1)
  {
   cStatic_PrizeInfo.SetWindowText("-");
   cStatic_BreakInfo.SetWindowText("Пустое пространство");
  }
  else
  {
   if (b_prize==-1) cStatic_PrizeInfo.SetWindowText("Приза нет");
   if (b_prize==0) cStatic_PrizeInfo.SetWindowText("Приз B");
   if (b_prize==1) cStatic_PrizeInfo.SetWindowText("Приз S");
   if (b_prize==2) cStatic_PrizeInfo.SetWindowText("Приз M");
   if (b_prize==3) cStatic_PrizeInfo.SetWindowText("Приз X");
   if (b_prize==4) cStatic_PrizeInfo.SetWindowText("Приз G");
   if (b_prize==5) cStatic_PrizeInfo.SetWindowText("Приз E");
   if (b_prize==6) cStatic_PrizeInfo.SetWindowText("Приз +");
   if (b_prize==7) cStatic_PrizeInfo.SetWindowText("Приз -");
   if (b_break==1) cStatic_BreakInfo.SetWindowText("Блок пробивается с первого удара");
   if (b_break==2) cStatic_BreakInfo.SetWindowText("Блок пробивается со второго удара");
   if (b_break==3) cStatic_BreakInfo.SetWindowText("Блок пробивается с третьего удара");
   if (b_break==4) cStatic_BreakInfo.SetWindowText("Блок пробивается с четвёртого удара");
   if (b_break==5) cStatic_BreakInfo.SetWindowText("Блок пробивается с пятого удара");
  }
  InvalidateRect(NULL,FALSE);
 }
 else
 {
  cStatic_PrizeInfo.SetWindowText("-");
  cStatic_BreakInfo.SetWindowText("-");
 }
 if (m_x_2>=0 && m_x_2<500 && m_y_2>=0 && m_y_2<30 && nFlags&MK_LBUTTON)
 {
  int bx=m_x_2/20;
  if (BlockMap.LeftBlockPos+bx<BlockMap.AccessBlock) BlockMap.WorkingBlock.Image=bx+BlockMap.LeftBlockPos;
  InvalidateRect(NULL,FALSE);
 }
}
