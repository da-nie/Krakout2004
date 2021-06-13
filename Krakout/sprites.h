class SPRITE
{
 public:
  //-----------------------------------------------------------
  unsigned char *Image;
  int OffsetImage;//смещение с начала картинки для некого кусочка
  int HeightImage;//размеры спрайта (кусочка картинки)
  int WidthImage;
  int Height;//размеры всей картинки
  int Width;
  int ImageXPos;//координаты кусочка
  int ImageYPos;
  unsigned char blend_r;//прозрачные цвета
  unsigned char blend_g;
  unsigned char blend_b;
  //-----------------------------------------------------------
  LPDIRECTDRAWSURFACE7 Surface;//поверхность спрайта (всей картинки)
  DDSURFACEDESC2 Surfaceddsd;
  //-----------------------------------------------------------
  SPRITE(void);
  ~SPRITE(void);
  int Load(char *FileName);
  void Delete(void);
  void Put(int x,int y,LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void Put(int x,int y,unsigned char *Mask,LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void SetSpriteSize(int width,int height);
  void SetSpriteCoord(int y,int x);
  void SetBlendColor(unsigned char r,unsigned char g,unsigned char b);
  void ReleaseSpriteSurface(void);
  void CreateSpriteSurface(LPDIRECTDRAW7 lpdd);
  //-----------------------------------------------------------
};
//------------------------------------------------------------------------------
SPRITE::SPRITE(void)
{
 Image=NULL;
 Surface=NULL;
 blend_r=0;
 blend_g=0;
 blend_b=0;
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
  for(int x=0;x<Width*3;x++,upptr++,downptr++)
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
 if (Surface!=NULL) Surface->Release();
 Surface=NULL;
 Image=NULL;
}
void SPRITE::Put(int x,int y,LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 if (Image==NULL) return;
 if (Surface==NULL) return;

 DDCOLORKEY color_key;
 color_key.dwColorSpaceHighValue=blend_b+(blend_g<<8)+(blend_r<<16);
 color_key.dwColorSpaceLowValue=blend_b+(blend_g<<8)+(blend_r<<16);
 Surface->SetColorKey(DDCKEY_SRCBLT,&color_key);

 int x1=x;
 int y1=y;
 int x2=x+WidthImage;
 int y2=y+HeightImage;
 if (x1<0) x1=0;
 if (x1>=640) return;
 if (x2<0) return;
 if (x2>640) x2=640;
 if (y1<0) y1=0;
 if (y1>480) return;
 if (y2<0) return;
 if (y2>480) y2=480;


 RECT dest_rect;
 dest_rect.left=x1;
 dest_rect.top=y1;
 dest_rect.right=x2;
 dest_rect.bottom=y2;
 RECT surf_rect;
 surf_rect.left=ImageXPos*WidthImage;
 surf_rect.top=ImageYPos*HeightImage;
 surf_rect.right=ImageXPos*WidthImage+(x2-x1);
 surf_rect.bottom=ImageYPos*HeightImage+(y2-y1);

 lpddssurface->Blt(&dest_rect,Surface,&surf_rect,DDBLT_WAIT|DDBLT_KEYSRC,NULL);
}
void SPRITE::Put(int x,int y,unsigned char *Mask,LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 if (Image==NULL) return;
 if (Surface==NULL) return;

 int x1=x;
 int y1=y;
 int x2=x+WidthImage;
 int y2=y+HeightImage;
 if (x1<0) x1=0;
 if (x1>=640) return;
 if (x2<0) return;
 if (x2>=640) x2=639;
 if (y1<0) y1=0;
 if (y1>=480) return;
 if (y2<0) return;
 if (y2>=480) y2=479;
 lpddssurface->Lock(NULL,&ddsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
 UINT *Video_Buffer=(UINT *)ddsd.lpSurface;
 int lPitch32=ddsd.lPitch>>2;

 int offsety=OffsetImage+((y1-y)*Width+(x1-x))*3;
 int vptry=y1*lPitch32+x1;
 int offsetdy=(y1-y)*WidthImage+(x1-x);
 for(int n=y1;n<y2;n++,offsety+=Width*3,offsetdy+=WidthImage,vptry+=lPitch32)
 {
  int offsetx=offsety;
  int offsetdx=offsetdy;
  int vptrx=vptry;
  for(int m=x1;m<x2;m++,offsetx+=3,offsetdx++,vptrx++)
  {
   if (Mask[offsetdx]==0) continue;
   unsigned char r=Image[offsetx];
   unsigned char g=Image[offsetx+1];
   unsigned char b=Image[offsetx+2];
   if (b==blend_b && g==blend_g && r==blend_r) continue;
   Video_Buffer[vptrx]=b+(g<<8)+(r<<16);
  }
 }
 lpddssurface->Unlock(NULL);
}
void SPRITE::SetSpriteSize(int width,int height)
{
 HeightImage=height;
 WidthImage=width;
}
void SPRITE::SetSpriteCoord(int y,int x)
{
 OffsetImage=y*Width*HeightImage*3+x*WidthImage*3;
 ImageXPos=x;
 ImageYPos=y;
}
void SPRITE::SetBlendColor(unsigned char r,unsigned char g,unsigned char b)
{
 blend_r=r;
 blend_g=g;
 blend_b=b;
}
void SPRITE::ReleaseSpriteSurface(void)
{
 if (Surface!=NULL) Surface->Release();
 Surface=NULL;
}
void SPRITE::CreateSpriteSurface(LPDIRECTDRAW7 lpdd)
{
 if (Image==NULL) return;

 ReleaseSpriteSurface();
 //создадим поверхность спрайта
 memset(&Surfaceddsd,0,sizeof(Surfaceddsd)); 
 Surfaceddsd.dwSize=sizeof(Surfaceddsd);
 Surfaceddsd.dwFlags=DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT;
 Surfaceddsd.dwWidth=Width;
 Surfaceddsd.dwHeight=Height;
 Surfaceddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN|DDSCAPS_VIDEOMEMORY;
 lpdd->CreateSurface(&Surfaceddsd,&Surface,NULL);
 DDCOLORKEY color_key;
 color_key.dwColorSpaceHighValue=0;
 color_key.dwColorSpaceLowValue=0;
 Surface->SetColorKey(DDCKEY_SRCBLT,&color_key);
 //запишем в неё данные спрайта
 Surface->Lock(NULL,&Surfaceddsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
 UINT *Sprite_Buffer=(UINT *)Surfaceddsd.lpSurface;
 int lPitch32=Surfaceddsd.lPitch>>2;
 for(int y=0;y<Height;y++)
 {
  for(int x=0;x<Width;x++)
  {
   int offsetx=(y*Width+x)*3;
   unsigned char r=Image[offsetx];
   unsigned char g=Image[offsetx+1];
   unsigned char b=Image[offsetx+2];
   *(Sprite_Buffer+y*lPitch32+x)=b+(g<<8)+(r<<16);
  }
 }
 Surface->Unlock(NULL);
}


