class MENUMAP
{
 protected:
  //-----------------------------------------------------------
  SPRITE Krakout_NameSprite[7];//спрайты букв названия игры
  int Krakout_Name_Offset[7];
  int Krakout_Name_Change;

  SPRITE BallSprite;//спрайт мяча (курсор)
  int Frame;//число кадров для мяча
  STAR Star[500];//массив звёзд 
  int CurrentStar;//всего сейчас звёзд
  int Pos;//позиция тучи
  int DPos;//перемещение тучи
  int Screen;//номер показываемого экрана
  HISCORE HiScore[10];//таблица рекордов
  int CursorY[10];//координаты курсора в экранах
  int CursorYMax[10];//максимальные координаты курсора в экранах
  int CursorImage;//картинка курсора
  int KeyPause;//задержка до реакции на следующее нажатие клавиши
  int NewNamePosX;//позиция записи в таблицу рекордов имени
  int NewNamePosY;//позиция записи в таблицу рекордов имени
  //-----------------------------------------------------------
 public:
  //-----------------------------------------------------------
  void Create(int maxlevel);
  void Release(void);
  //-----------------------------------------------------------
  void CreateSpriteSurface(LPDIRECTDRAW7 lpdd);
  void ReleaseSpriteSurface(void);
  void ChangeImageFrame(void);
  int Processing(void);
  void TransferChar(int code);
  void PutMenu(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void AddNewNameInHiScore(void);//добавить в таблицу рекордов имя (если это возможно)
  void SaveHiScore(void);//сохранить таблицу рекордов
  void LoadHiScore(void);//загрузить таблицу рекордов
  void InitHiScore(void);//инициализировать таблицу рекордов
  //-----------------------------------------------------------
  void PutPixel(int x,int y,unsigned char r,unsigned char g,unsigned char b,int lPitch32,UINT *Video_Buffer);
  //-----------------------------------------------------------
} MenuMap;
//--------------------------------------------------------------------------
void MENUMAP::Create(int maxlevel)
{
 int n;
 Krakout_NameSprite[0].Load("bitmap\\k_name_1.bmp");
 Krakout_NameSprite[0].SetBlendColor(0,0,0);
 Krakout_NameSprite[1].Load("bitmap\\k_name_2.bmp");
 Krakout_NameSprite[1].SetBlendColor(0,0,0);
 Krakout_NameSprite[2].Load("bitmap\\k_name_3.bmp");
 Krakout_NameSprite[2].SetBlendColor(0,0,0);
 Krakout_NameSprite[3].Load("bitmap\\k_name_4.bmp");
 Krakout_NameSprite[3].SetBlendColor(0,0,0);
 Krakout_NameSprite[4].Load("bitmap\\k_name_5.bmp");
 Krakout_NameSprite[4].SetBlendColor(0,0,0);
 Krakout_NameSprite[5].Load("bitmap\\k_name_6.bmp");
 Krakout_NameSprite[5].SetBlendColor(0,0,0);
 Krakout_NameSprite[6].Load("bitmap\\k_name_7.bmp");
 Krakout_NameSprite[6].SetBlendColor(0,0,0);
 
 int frame_size_x;
 int frame_size_y;
 int blend_color_r;
 int blend_color_g;
 int blend_color_b;
 if (!GetParameters("bitmap\\ball.txt","FRAME_SIZE_X:",&frame_size_x)) return;
 if (!GetParameters("bitmap\\ball.txt","FRAME_SIZE_Y:",&frame_size_y)) return;
 if (!GetParameters("bitmap\\ball.txt","BLEND_COLOR_R:",&blend_color_r)) return;
 if (!GetParameters("bitmap\\ball.txt","BLEND_COLOR_G:",&blend_color_g)) return;
 if (!GetParameters("bitmap\\ball.txt","BLEND_COLOR_B:",&blend_color_b)) return;
 if (!GetParameters("bitmap\\ball.txt","FRAME:",&Frame)) return;
 BallSprite.Load("bitmap\\ball.bmp");
 BallSprite.SetSpriteSize(frame_size_x,frame_size_y);
 BallSprite.SetBlendColor(blend_color_r,blend_color_g,blend_color_b);

 LoadHiScore();

 Krakout_Name_Change=1;
 for(n=0;n<7;n++) Krakout_Name_Offset[n]=n-3;

 CurrentStar=0;
 Pos=0;
 DPos=5;
 Screen=0;
 CursorY[0]=0;
 CursorYMax[0]=5;
 CursorY[1]=0;
 CursorYMax[1]=0;
 CursorY[2]=0;
 CursorYMax[2]=0;
 CursorImage=0;
 CursorYMax[3]=0;
 CursorImage=0;
 KeyPause=0;
}
void MENUMAP::Release(void)
{
 for(int n=0;n<7;n++) Krakout_NameSprite[n].Delete();
 BallSprite.Delete();
 SaveHiScore();
}
//--------------------------------------------------------------------------
void MENUMAP::CreateSpriteSurface(LPDIRECTDRAW7 lpdd)
{
 for(int n=0;n<7;n++) Krakout_NameSprite[n].CreateSpriteSurface(lpdd);
 BallSprite.CreateSpriteSurface(lpdd);
}
void MENUMAP::ReleaseSpriteSurface(void)
{
 for(int n=0;n<7;n++) Krakout_NameSprite[n].ReleaseSpriteSurface();
 BallSprite.ReleaseSpriteSurface();
}
void MENUMAP::ChangeImageFrame(void)
{
 CursorImage++;
 if (CursorImage>=Frame) CursorImage=0;
 for(int n=6;n>=1;n--) Krakout_Name_Offset[n]=Krakout_Name_Offset[n-1];
 Krakout_Name_Offset[0]+=Krakout_Name_Change;
 if (Krakout_Name_Offset[0]>=4) Krakout_Name_Change=-1;
 if (Krakout_Name_Offset[0]<=-4) Krakout_Name_Change=1;
}
int MENUMAP::Processing(void)
{
 int n,m;
 for(n=0;n<CurrentStar;n++)
 {
  Star[n].Y+=Star[n].Speed;
  if (Star[n].Y>=479)
  {
   for(m=n+1;m<CurrentStar;m++) Star[m-1]=Star[m];
   CurrentStar--;
   n--;
   continue;
  }
 }
 int newstar=(int)5.0*rand()/RAND_MAX;
 if (CurrentStar+newstar>=500) newstar=499-CurrentStar;
 float maxx=30;
 if (maxx+Pos>=638) maxx=(float)(638-Pos);
 for(n=0;n<newstar;n++,CurrentStar++)
 {
  Star[CurrentStar].Y=0;
  Star[CurrentStar].X=maxx*rand()/(float)(RAND_MAX)+Pos;
  Star[CurrentStar].Speed=(float)5.0*rand()/RAND_MAX+1;
  for(m=0;m<4;m++)
  {
   int r=(int)255.0*rand()/RAND_MAX;
   int g=(int)255*rand()/RAND_MAX;
   int b=(int)255.0*rand()/RAND_MAX;

   Star[CurrentStar].R[m]=r;
   Star[CurrentStar].G[m]=g;
   Star[CurrentStar].B[m]=b;
  }
 }
 Pos+=DPos;
 if (Pos>=630) DPos=-DPos;
 if (Pos<0) DPos=-DPos;
 //обработка клавиш
 if (KeyPause>0) KeyPause--;
 if (Screen==0)
 {
  if (GetAsyncKeyState(VK_UP)&32768 && KeyPause==0)
  {
   CursorY[Screen]--;
   if (CursorY[Screen]<0) CursorY[Screen]=CursorYMax[Screen];
   Sound.PlaySound(SOUND__MENU,0,100);
   KeyPause=20;
   return(0);
  }
  if (GetAsyncKeyState(VK_DOWN)&32768 && KeyPause==0)
  {
   CursorY[Screen]++;
   if (CursorY[Screen]>CursorYMax[Screen]) CursorY[Screen]=0;
   Sound.PlaySound(SOUND__MENU,0,100);
   KeyPause=20;
   return(0);
  }
 }
 if (GetAsyncKeyState(VK_SPACE)&32768 && KeyPause==0)
 {
  if (Screen==0 && CursorY[Screen]==2)//переход к таблице рекордов
  {
   Screen=1;
   KeyPause=20;
   return(0);
  }
  if (Screen==0 && CursorY[Screen]==0)//старт игры
  {
   KeyPause=20;
   return(2);
  }
  if (Screen==0 && CursorY[Screen]==1)//практика
  {
   Screen=3;
   KeyPause=20;
   return(0);
  }
  if (Screen==0 && CursorY[Screen]==3)//помощь
  {
   Screen=4;
   KeyPause=20;
   return(0);
  }
  if (Screen==0 && CursorY[Screen]==4)//демонстрация
  {
   KeyPause=20;
   return(4);
  }
  if (Screen==0 && CursorY[Screen]==5)//выход из игры
  {
   KeyPause=20;
   return(1);
  }
  if (Screen==3)//старт практики
  {
   Screen=0;
   KeyPause=20;
   return(3);
  }
  if (Screen==1)//возврат в меню
  {
   Screen=0;
   KeyPause=20;
   return(0);
  }
 }
 if (Screen==4)
 {
  if (GetAsyncKeyState(VK_SPACE)&32768 && KeyPause==0)
  {
   Screen=0;
   KeyPause=20;
   return(0);
  }
 }
 if (Screen==3)
 {
  if (GetAsyncKeyState(VK_ESCAPE)&32768 && KeyPause==0)
  {
   Screen=0;
   KeyPause=20;
   return(0);
  }
  if (GetAsyncKeyState(VK_DOWN)&32768 && KeyPause==0)
  {
   GameParameters.StartLevel--;
   if (GameParameters.StartLevel<=0) GameParameters.StartLevel=GameParameters.MaxLevel;
   Sound.PlaySound(SOUND__CHANGE_LEVEL,0,100);
   KeyPause=20;
   return(0);
  }
  if (GetAsyncKeyState(VK_UP)&32768 && KeyPause==0)
  {
   GameParameters.StartLevel++;
   if (GameParameters.StartLevel>GameParameters.MaxLevel) GameParameters.StartLevel=1;
   Sound.PlaySound(SOUND__CHANGE_LEVEL,0,100);
   KeyPause=20;
   return(0);
  }
 }
 return(0);
}
void MENUMAP::TransferChar(int code)
{
 if (Screen==2)//запись таблицы рекордов
 {
  if (GetAsyncKeyState(VK_RETURN)&32768 && KeyPause==0)
  {
   SaveHiScore();
   Screen=0;
   //проверим на совпадение с паролем
   char Password[]="GREMLIN GRAPHICS    ";
   for(int n=0;n<20;n++) 
   {
    if (Password[n]!=HiScore[NewNamePosY].Name[n]) return;
   }
   GameParameters.SpecialMode=1;
   return;
  }
  if (GetAsyncKeyState(VK_BACK)&32768 && KeyPause==0)
  {
   HiScore[NewNamePosY].Name[NewNamePosX]=32;
   NewNamePosX--;
   if (NewNamePosX<0) NewNamePosX=0;
   HiScore[NewNamePosY].Name[NewNamePosX]=32;
   return;
  }
  if (code<32 || code>32+96) return;
  HiScore[NewNamePosY].Name[NewNamePosX]=code;
  NewNamePosX++;
  if (NewNamePosX==21) NewNamePosX=20;
 }
}
void MENUMAP::PutMenu(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 lpddssurface->Lock(NULL,&ddsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
 UINT *Video_Buffer=(UINT *)ddsd.lpSurface;
 int lPitch32=ddsd.lPitch>>2;
 for(int n=0;n<CurrentStar;n++)
 {
  PutPixel((int)Star[n].X,(int)Star[n].Y,Star[n].R[0],Star[n].G[0],Star[n].B[0],lPitch32,Video_Buffer);
  PutPixel((int)Star[n].X+1,(int)Star[n].Y,Star[n].R[1],Star[n].G[1],Star[n].B[1],lPitch32,Video_Buffer);
  PutPixel((int)Star[n].X+1,(int)Star[n].Y+1,Star[n].R[2],Star[n].G[2],Star[n].B[2],lPitch32,Video_Buffer);
  PutPixel((int)Star[n].X,(int)Star[n].Y+1,Star[n].R[3],Star[n].G[3],Star[n].B[3],lPitch32,Video_Buffer);
 }
 lpddssurface->Unlock(NULL);
 int lengthname=0;
 for(n=0;n<7;n++) lengthname+=Krakout_NameSprite[n].Width;
 int pos=(640-lengthname)/2;
 for(n=0;n<7;n++)
 {
  Krakout_NameSprite[n].Put(pos,24+Krakout_Name_Offset[n],lpddssurface,ddsd);
  pos+=Krakout_NameSprite[n].Width;
 }

 if (Screen==0)//главное меню
 {
  int MenuX[6];
  MenuX[0]=(640-strlen("Start Game")*Font.GetFontWidth(1))/2;
  MenuX[1]=(640-strlen("Practics")*Font.GetFontWidth(3))/2;
  MenuX[2]=(640-strlen("Hight Score")*Font.GetFontWidth(1))/2;
  MenuX[3]=(640-strlen("Help")*Font.GetFontWidth(3))/2;
  MenuX[4]=(640-strlen("Demonstration")*Font.GetFontWidth(1))/2;
  MenuX[5]=(640-strlen("Exit")*Font.GetFontWidth(3))/2;
  Font.Print(MenuX[0],200,"Start Game",1,lpddssurface,ddsd);
  Font.Print(MenuX[1],230,"Practics",3,lpddssurface,ddsd);
  Font.Print(MenuX[2],260,"Hight Score",1,lpddssurface,ddsd);
  Font.Print(MenuX[3],290,"Help",3,lpddssurface,ddsd);
  Font.Print(MenuX[4],320,"Demonstration",1,lpddssurface,ddsd);
  Font.Print(MenuX[5],350,"Exit",3,lpddssurface,ddsd);
  Font.PrintAtCenter(400,"Press Up, Down and Space to select",3,lpddssurface,ddsd);
  Font.PrintAtCenter(430,"Written by: Dmitriy Trunow. Texno-Ars Software 27.07.2004",1,lpddssurface,ddsd);
  BallSprite.SetSpriteCoord(0,CursorImage);
  BallSprite.Put(MenuX[CursorY[Screen]]-BallSprite.WidthImage-5,200+CursorY[Screen]*30+5-BallSprite.HeightImage/2,lpddssurface,ddsd);
  if (GameParameters.SpecialMode==1) Font.Print(32,455,"Special mode on",1,lpddssurface,ddsd);
 }
 if (Screen==1)//таблица рекордов
 {
  Font.PrintAtCenter(150,"Hight Score",2,lpddssurface,ddsd);
  for(n=0;n<10;n++)
  {
   Font.Print(160,190+(int)(1.5*Font.GetFontHeight(3)*n),HiScore[n].Name,3,lpddssurface,ddsd);
   char string[255];
   itoa(HiScore[n].Score,string,10);
   Font.Print(380,190+(int)(1.5*Font.GetFontHeight(1)*n),string,1,lpddssurface,ddsd);
  }
  Font.PrintAtCenter(430,"Press Space to return",1,lpddssurface,ddsd);
 }
 if (Screen==2)//ввод таблицы рекордов
 {
  Font.PrintAtCenter(150,"Hight Score",4,lpddssurface,ddsd);
  for(n=0;n<10;n++)
  {
   Font.Print(160,190+(int)(1.5*Font.GetFontHeight(1)*n),HiScore[n].Name,1,lpddssurface,ddsd);
   char string[255];
   itoa(HiScore[n].Score,string,10);
   Font.Print(380,190+(int)(1.5*Font.GetFontHeight(3)*n),string,3,lpddssurface,ddsd);
  }
  Font.Print(160+NewNamePosX*Font.GetFontWidth(1),190+(int)(1.5*Font.GetFontHeight(1)*NewNamePosY),"_",3,lpddssurface,ddsd); 
  Font.PrintAtCenter(450,"Press Enter to continue",1,lpddssurface,ddsd);
 }
 if (Screen==3)//настройка практики
 {
  Font.PrintAtCenter(150,"Practics setting",4,lpddssurface,ddsd);
  char string[255];
  itoa(GameParameters.StartLevel,string,10);
  Font.PrintAtCenter(200,"Start level",1,lpddssurface,ddsd);
  Font.PrintAtCenter(220,string,3,lpddssurface,ddsd);
  Font.PrintAtCenter(430,"Press Up,Down-change start level",3,lpddssurface,ddsd);
  Font.PrintAtCenter(450,"Press Escape to return, Space to start game",1,lpddssurface,ddsd);
 }
 if (Screen==4)//помошь
 {
  Font.PrintAtCenter(150,"Help in Game",4,lpddssurface,ddsd);
  Font.PrintAtCenter(200,"Enter-pause",1,lpddssurface,ddsd);
  Font.PrintAtCenter(230,"Escape-exit to main menu",1,lpddssurface,ddsd);
  Font.PrintAtCenter(260,"Space-start ball/missile",1,lpddssurface,ddsd);
  Font.PrintAtCenter(290,"PageUp-music volume +",1,lpddssurface,ddsd);
  Font.PrintAtCenter(320,"PageDown-music volume -",1,lpddssurface,ddsd);
  Font.PrintAtCenter(350,"Home-sound volume +",1,lpddssurface,ddsd);
  Font.PrintAtCenter(380,"End-sound volume -",1,lpddssurface,ddsd);
  Font.PrintAtCenter(450,"Press Space to return",1,lpddssurface,ddsd);
 }
}
void MENUMAP::AddNewNameInHiScore(void)
{
 int n;
 //ищем куда бы записать новое имя
 NewNamePosY=-1;
 for(n=0;n<10;n++)
 {
  if (HiScore[n].Score<GameParameters.Score)
  {
   NewNamePosY=n;
   break;
  }
 }
 if (NewNamePosY<0)//не хватило очков
 {
  Screen=0;
  return;
 }
 //переместим имена вниз
 for(n=9;n>NewNamePosY;n--)
 {
  HiScore[n]=HiScore[n-1];
 }
 HiScore[NewNamePosY].Score=GameParameters.Score;
 strcpy(HiScore[NewNamePosY].Name,"                    ");
 NewNamePosX=0;
 Screen=2;
}
void MENUMAP::SaveHiScore(void)
{
 int n,m;
 unsigned char byte;
 char codeword[256];
 strcpy(codeword,"This is BASIS codename for Hight Score saving");
 int codewordlength=strlen(codeword);
 FILE *File=fopen("hiscore.txt","w+b");
 if (File==NULL) return;
 int codepos=0;
 int control=0;
 for(n=0;n<10;n++)
 {
  //запишем имя
  for(m=0;m<20;m++)  
  {
   byte=HiScore[n].Name[m];
   control+=byte;
   byte=byte^codeword[codepos];
   control+=byte;
   codepos+=m-n;
   codepos++;
   while(codepos<0) codepos+=codewordlength;
   while(codepos>=codewordlength) codepos-=codewordlength;
   byte=byte^codeword[codepos];
   control+=byte;
   fwrite(&byte,1,1,File);
  }
  //запишем результат
  unsigned char *ptr=(unsigned char *)&HiScore[n].Score;
  for(m=0;m<sizeof(int);m++,ptr++)
  {
   byte=*(ptr);
   control+=byte;
   byte=byte^codeword[codepos];
   control+=byte;
   codepos+=n-m;
   codepos++;   while(codepos<0) codepos+=codewordlength;
   while(codepos>=codewordlength) codepos-=codewordlength;
   byte=byte^codeword[codepos];
   control+=byte;
   fwrite(&byte,1,1,File);
  }
 }
 //запишем контрольную сумму
 unsigned char *ptrs=(unsigned char *)&control;
 for(m=0;m<sizeof(int);m++,ptrs++)
 {
  byte=*(ptrs);
  byte=byte^codeword[codepos];
  codepos+=n-m;
  codepos++;   while(codepos<0) codepos+=codewordlength;
  while(codepos>=codewordlength) codepos-=codewordlength;
  byte=byte^codeword[codepos];
  fwrite(&byte,1,1,File);
 }
 fclose(File);
}
void MENUMAP::LoadHiScore(void)
{
 int n,m;
 unsigned char byte;
 char codeword[256];
 strcpy(codeword,"This is BASIS codename for Hight Score saving");
 int codewordlength=strlen(codeword);
 FILE *File=fopen("hiscore.txt","r+b");
 if (File==NULL)
 {
  InitHiScore();
  SaveHiScore();
  return;
 }
 int codepos=0;
 int control=0;
 for(n=0;n<10;n++)
 {
  //считаем имя
  for(m=0;m<20;m++)  
  {
   char code1=codeword[codepos];
   codepos+=m-n;
   codepos++;
   while(codepos<0) codepos+=codewordlength;
   while(codepos>=codewordlength) codepos-=codewordlength;
   char code2=codeword[codepos];
   fread(&byte,1,1,File);
   control+=byte;
   byte=byte^code2;
   control+=byte;
   byte=byte^code1;
   control+=byte;
   HiScore[n].Name[m]=byte;
  }
  //считаем результат
  unsigned char *ptr=(unsigned char *)&HiScore[n].Score;
  for(m=0;m<sizeof(int);m++,ptr++)
  {
   char code1=codeword[codepos];
   codepos+=n-m;
   codepos++;
   while(codepos<0) codepos+=codewordlength;
   while(codepos>=codewordlength) codepos-=codewordlength;
   char code2=codeword[codepos];
   fread(&byte,1,1,File);
   control+=byte;
   byte=byte^code2;
   control+=byte;
   byte=byte^code1;
   control+=byte;
   *(ptr)=byte;
  }
 }
 //считаем контрольную сумму
 int controlsumma;
 unsigned char *ptrs=(unsigned char *)&controlsumma;
 for(m=0;m<sizeof(int);m++,ptrs++)
 {
  char code1=codeword[codepos];
  codepos+=n-m;
  codepos++;
  while(codepos<0) codepos+=codewordlength;
  while(codepos>=codewordlength) codepos-=codewordlength;
  char code2=codeword[codepos];
  fread(&byte,1,1,File);
  byte=byte^code2;
  byte=byte^code1;
  *(ptrs)=byte;
 }
 if (controlsumma!=control) InitHiScore();
 fclose(File);
}
void MENUMAP::InitHiScore(void)
{
 for(int n=0;n<10;n++)
 {
  if (n<5) HiScore[n].Score=(int)pow(10,(9-n));
      else HiScore[n].Score=100000-n*10000;
 }
 strcpy(HiScore[0].Name,"Dmitriy Trunow      ");
 strcpy(HiScore[1].Name,"Texno-Ars Software  ");
 strcpy(HiScore[2].Name,"27.07.2004          ");
 strcpy(HiScore[3].Name,"Pavel Ivanow        ");
 strcpy(HiScore[4].Name,"Oleg Lipin          ");
 strcpy(HiScore[5].Name,"Alexander Below     ");
 strcpy(HiScore[6].Name,"Mishail Rubanjak    ");
 strcpy(HiScore[7].Name,"Gleb Pinskiy        ");
 strcpy(HiScore[8].Name,"And KOZEL wseja Rusi");
 strcpy(HiScore[9].Name,"  Makaew Ewgeniy    ");
}

//--------------------------------------------------------------------------
void MENUMAP::PutPixel(int x,int y,unsigned char r,unsigned char g,unsigned char b,int lPitch32,UINT *Video_Buffer)
{
 Video_Buffer[x+y*lPitch32]=b+(g<<8)+(r<<16);
}
