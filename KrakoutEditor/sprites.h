class SPRITE
{
 public:
  //-----------------------------------------------------------
  unsigned char *Image;
  unsigned int OffsetImage;//смещение с начала картинки для некого кусочка
  int HeightImage;//размеры спрайта (кусочка картинки)
  int WidthImage;
  int Height;//размеры всей картинки
  int Width;
  int ImageXPos;//координаты кусочка
  int ImageYPos;
  int ScreenWidth;//размеры экранного буфера
  int ScreenHeight;
  //-----------------------------------------------------------
  SPRITE(void);
  ~SPRITE(void);
  int Load(char *FileName);
  void Delete(void);
  void Put(int x,int y,unsigned char *screen);
  void PutSelect(int x,int y,unsigned char *screen);
  void SetSpriteSize(int width,int height);
  void SetSpriteCoord(int x,int y);
  void SetScreenSize(int width,int height);
  //-----------------------------------------------------------
};
//------------------------------------------------------------------------------
SPRITE::SPRITE(void)
{
 Image=NULL;
}
SPRITE::~SPRITE(void)
{
 Delete();
}
int SPRITE::Load(char *FileName)
{
 int x,y;
 HANDLE hfbm=CreateFile(FileName,GENERIC_READ,FILE_SHARE_READ,(LPSECURITY_ATTRIBUTES)NULL,
                        OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,(HANDLE)NULL);
 if (hfbm==INVALID_HANDLE_VALUE) return(1);
 DWORD dwRead;
 BITMAPFILEHEADER bmfh;
 ReadFile(hfbm, &bmfh,sizeof(BITMAPFILEHEADER),&dwRead,(LPOVERLAPPED)NULL);
 BITMAPINFOHEADER bmih;
 ReadFile(hfbm,&bmih,sizeof(BITMAPINFOHEADER),&dwRead,(LPOVERLAPPED)NULL);
 LPBITMAPINFO lpbmi=(LPBITMAPINFO)new char[sizeof(BITMAPINFOHEADER)+((1<<bmih.biBitCount)*sizeof(RGBQUAD))];
 lpbmi->bmiHeader.biSize=bmih.biSize;
 lpbmi->bmiHeader.biWidth=bmih.biWidth;
 lpbmi->bmiHeader.biHeight=bmih.biHeight;
 lpbmi->bmiHeader.biPlanes=bmih.biPlanes;
 lpbmi->bmiHeader.biBitCount=bmih.biBitCount;
 lpbmi->bmiHeader.biCompression=bmih.biCompression;
 lpbmi->bmiHeader.biSizeImage=bmih.biSizeImage;
 lpbmi->bmiHeader.biXPelsPerMeter=bmih.biXPelsPerMeter;
 lpbmi->bmiHeader.biYPelsPerMeter=bmih.biYPelsPerMeter;
 lpbmi->bmiHeader.biClrUsed=bmih.biClrUsed;
 lpbmi->bmiHeader.biClrImportant=bmih.biClrImportant;
 if (lpbmi->bmiHeader.biPlanes!=1 || bmih.biCompression!=0 || (lpbmi->bmiHeader.biBitCount!=24 && lpbmi->bmiHeader.biBitCount!=8) )
 {
  Image=NULL;
  Height=0;
  Width=0;
  HeightImage=0;
  WidthImage=0;
  OffsetImage=0;
  delete(lpbmi);
  return(1);
 }
 if (lpbmi->bmiHeader.biBitCount<24)//существует палитра цветов, нужно загрузить палитру
 {
  ReadFile(hfbm,lpbmi->bmiColors,((1<<bmih.biBitCount)*sizeof(RGBQUAD)),&dwRead,(LPOVERLAPPED)NULL);
 }
 unsigned char *lpvBits=new unsigned char[bmfh.bfSize-bmfh.bfOffBits];
 ReadFile(hfbm,lpvBits,(bmfh.bfSize-bmfh.bfOffBits),&dwRead,(LPOVERLAPPED)NULL);
 CloseHandle(hfbm);
 if (lpbmi->bmiHeader.biBitCount==8)//256 цветов, нужно перекодировать цвета
 {
  Image=new unsigned char[lpbmi->bmiHeader.biWidth*lpbmi->bmiHeader.biHeight*3];
  int len=lpbmi->bmiHeader.biWidth;
  if (len%4!=0)len=len+4-lpbmi->bmiHeader.biWidth%4;
  for(y=0;y<lpbmi->bmiHeader.biHeight;y++)
   for(x=0;x<lpbmi->bmiHeader.biWidth;x++)
   {
    int offset=(x+y*lpbmi->bmiHeader.biWidth)*3;
    int offset1=(x+y*len);
    Image[offset]=(lpbmi->bmiColors[lpvBits[offset1]].rgbRed);
    Image[offset+1]=(lpbmi->bmiColors[lpvBits[offset1]].rgbGreen);
    Image[offset+2]=(lpbmi->bmiColors[lpvBits[offset1]].rgbBlue);
   }
  delete(lpvBits);
 }
 else
 {
  Image=new unsigned char[lpbmi->bmiHeader.biWidth*lpbmi->bmiHeader.biHeight*3];
  int len=lpbmi->bmiHeader.biWidth*3;
  if (len%4!=0) len=len+4-len%4;
  for(y=0;y<lpbmi->bmiHeader.biHeight;y++)
   for(x=0;x<lpbmi->bmiHeader.biWidth;x++)
   {
    int offset=(x+y*lpbmi->bmiHeader.biWidth)*3;
    int offset1=x*3+len*y;
    Image[offset]=(lpvBits[offset1+2]);
    Image[offset+1]=(lpvBits[offset1+1]);
    Image[offset+2]=(lpvBits[offset1]);
   }
  delete(lpvBits);
 }
 Width=lpbmi->bmiHeader.biWidth;
 Height=lpbmi->bmiHeader.biHeight;
 WidthImage=Width;
 HeightImage=Height;
 OffsetImage=0;
 ImageXPos=0;
 ImageYPos=0;
 delete(lpbmi);
 //перевернём изображение
 for(y=0;y<Height/2;y++)
 {
  unsigned char *upptr=Image+y*Width*3;
  unsigned char *downptr=Image+(Height-y-1)*Width*3;
  for(x=0;x<Width*3;x++,upptr++,downptr++)
  {
   unsigned char byte=*(upptr);
   *(upptr)=*(downptr);
   *(downptr)=byte;
  }
 }
 return(0);
}
void SPRITE::Delete(void)
{
 if (Image!=NULL) delete(Image);
 Image=NULL;
}
void SPRITE::Put(int x,int y,unsigned char *screen)
{
 if (Image==NULL) return;

 int x1=x;
 int y1=y;
 int x2=x+WidthImage;
 int y2=y+HeightImage;
 if (x1<0) x1=0;
 if (x1>=ScreenWidth) return;
 if (x2<0) return;
 if (x2>=ScreenWidth) x2=ScreenWidth-1;
 if (y1<0) y1=0;
 if (y1>=ScreenHeight) return;
 if (y2<0) return;
 if (y2>=ScreenHeight) y2=ScreenHeight-1;

 unsigned char *sptr=Image+OffsetImage;
 unsigned char *vptr=screen+3*(x1+(ScreenHeight-y1-1)*ScreenWidth);
 for(int cy=y1;cy<y2;cy++,sptr+=Width*3,vptr-=ScreenWidth*3)
 {
  unsigned char *csptr=sptr;
  unsigned char *cvptr=vptr;
  for(int cx=x1;cx<x2;cx++)
  {
   unsigned char r=*(csptr);
   csptr++;
   unsigned char g=*(csptr);
   csptr++;
   unsigned char b=*(csptr);
   csptr++;
   *(cvptr)=b;
   cvptr++;
   *(cvptr)=g;
   cvptr++;
   *(cvptr)=r;
   cvptr++;
  }
 }
}
void SPRITE::PutSelect(int x,int y,unsigned char *screen)
{
 if (Image==NULL) return;

 int x1=x;
 int y1=y;
 int x2=x+WidthImage;
 int y2=y+HeightImage;
 if (x1<0) x1=0;
 if (x1>=ScreenWidth) return;
 if (x2<0) return;
 if (x2>=ScreenWidth) x2=ScreenWidth-1;
 if (y1<0) y1=0;
 if (y1>=ScreenHeight) return;
 if (y2<0) return;
 if (y2>=ScreenHeight) y2=ScreenHeight-1;

 unsigned char *sptr=Image+OffsetImage;
 unsigned char *vptr=screen+3*(x1+(ScreenHeight-y1-1)*ScreenWidth);
 for(int cy=y1;cy<y2;cy++,sptr+=Width*3,vptr-=ScreenWidth*3)
 {
  unsigned char *csptr=sptr;
  unsigned char *cvptr=vptr;
  for(int cx=x1;cx<x2;cx++)
  {
   unsigned char r=*(csptr);
   csptr++;
   unsigned char g=*(csptr);
   csptr++;
   unsigned char b=*(csptr);
   if (cx-x1>=WidthImage-2 || cx-x1<=1 || cy-y1<=1 || cy-y1>=HeightImage-2) 
   {
    r=255;
	g=32;
	b=32;
   }

   csptr++;
   *(cvptr)=b;
   cvptr++;
   *(cvptr)=g;
   cvptr++;
   *(cvptr)=r;
   cvptr++;
  }
 }
}
void SPRITE::SetSpriteSize(int width,int height)
{
 HeightImage=height;
 WidthImage=width;
}
void SPRITE::SetSpriteCoord(int x,int y)
{
 OffsetImage=y*Width*HeightImage*3+x*WidthImage*3;
 ImageXPos=x;
 ImageYPos=y;
}
void SPRITE::SetScreenSize(int width,int height)
{
 ScreenWidth=width;
 ScreenHeight=height;
}



