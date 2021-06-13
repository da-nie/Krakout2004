class FONT
{
 public:
 //-----------------------------------------------------------
 SPRITE Font1;
 SPRITE Font2;
 SPRITE Font3;
 SPRITE Font4;
 //-----------------------------------------------------------
 void Load(void);
 void LoadFont1(void);
 void LoadFont2(void);
 void LoadFont3(void);
 void LoadFont4(void);
 void Release(void);
 void CreateSpriteSurface(LPDIRECTDRAW7 lpdd);
 void ReleaseSpriteSurface(void);
 //-----------------------------------------------------------
 void Print(int x,int y,char *string,int font,LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
 void PrintAtCenter(int y,char *string,int font,LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
 int GetFontWidth(int font);
 int GetFontHeight(int font);
 //-----------------------------------------------------------
} Font;
//--------------------------------------------------------------------------
void FONT::Load(void)
{
 LoadFont1();
 LoadFont2();
 LoadFont3();
 LoadFont4();
}
void FONT::LoadFont1(void)
{
 int frame_size_x;
 int frame_size_y;
 int blend_color_r;
 int blend_color_g;
 int blend_color_b;
 if (!GetParameters("bitmap\\font1.txt","FRAME_SIZE_X:",&frame_size_x)) return;
 if (!GetParameters("bitmap\\font1.txt","FRAME_SIZE_Y:",&frame_size_y)) return;
 if (!GetParameters("bitmap\\font1.txt","BLEND_COLOR_R:",&blend_color_r)) return;
 if (!GetParameters("bitmap\\font1.txt","BLEND_COLOR_G:",&blend_color_g)) return;
 if (!GetParameters("bitmap\\font1.txt","BLEND_COLOR_B:",&blend_color_b)) return;
 Font1.Load("bitmap\\font1.bmp");
 Font1.SetSpriteSize(frame_size_x,frame_size_y);
 Font1.SetBlendColor(blend_color_r,blend_color_g,blend_color_b);
}
void FONT::LoadFont2(void)
{
 int frame_size_x;
 int frame_size_y;
 int blend_color_r;
 int blend_color_g;
 int blend_color_b;
 if (!GetParameters("bitmap\\font2.txt","FRAME_SIZE_X:",&frame_size_x)) return;
 if (!GetParameters("bitmap\\font2.txt","FRAME_SIZE_Y:",&frame_size_y)) return;
 if (!GetParameters("bitmap\\font2.txt","BLEND_COLOR_R:",&blend_color_r)) return;
 if (!GetParameters("bitmap\\font2.txt","BLEND_COLOR_G:",&blend_color_g)) return;
 if (!GetParameters("bitmap\\font2.txt","BLEND_COLOR_B:",&blend_color_b)) return;
 Font2.Load("bitmap\\font2.bmp");
 Font2.SetSpriteSize(frame_size_x,frame_size_y);
 Font2.SetBlendColor(blend_color_r,blend_color_g,blend_color_b);
}
void FONT::LoadFont3(void)
{
 int frame_size_x;
 int frame_size_y;
 int blend_color_r;
 int blend_color_g;
 int blend_color_b;
 if (!GetParameters("bitmap\\font3.txt","FRAME_SIZE_X:",&frame_size_x)) return;
 if (!GetParameters("bitmap\\font3.txt","FRAME_SIZE_Y:",&frame_size_y)) return;
 if (!GetParameters("bitmap\\font3.txt","BLEND_COLOR_R:",&blend_color_r)) return;
 if (!GetParameters("bitmap\\font3.txt","BLEND_COLOR_G:",&blend_color_g)) return;
 if (!GetParameters("bitmap\\font3.txt","BLEND_COLOR_B:",&blend_color_b)) return;
 Font3.Load("bitmap\\font3.bmp");
 Font3.SetSpriteSize(frame_size_x,frame_size_y);
 Font3.SetBlendColor(blend_color_r,blend_color_g,blend_color_b);
}
void FONT::LoadFont4(void)
{
 int frame_size_x;
 int frame_size_y;
 int blend_color_r;
 int blend_color_g;
 int blend_color_b;
 if (!GetParameters("bitmap\\font4.txt","FRAME_SIZE_X:",&frame_size_x)) return;
 if (!GetParameters("bitmap\\font4.txt","FRAME_SIZE_Y:",&frame_size_y)) return;
 if (!GetParameters("bitmap\\font4.txt","BLEND_COLOR_R:",&blend_color_r)) return;
 if (!GetParameters("bitmap\\font4.txt","BLEND_COLOR_G:",&blend_color_g)) return;
 if (!GetParameters("bitmap\\font4.txt","BLEND_COLOR_B:",&blend_color_b)) return;
 Font4.Load("bitmap\\font4.bmp");
 Font4.SetSpriteSize(frame_size_x,frame_size_y);
 Font4.SetBlendColor(blend_color_r,blend_color_g,blend_color_b);
}
void FONT::Release(void)
{
 Font1.Delete();
 Font2.Delete();
 Font3.Delete();
 Font4.Delete();
}
void FONT::CreateSpriteSurface(LPDIRECTDRAW7 lpdd)
{
 Font1.CreateSpriteSurface(lpdd);
 Font2.CreateSpriteSurface(lpdd);
 Font3.CreateSpriteSurface(lpdd);
 Font4.CreateSpriteSurface(lpdd);
}
void FONT::ReleaseSpriteSurface(void)
{
 Font1.ReleaseSpriteSurface();
 Font2.ReleaseSpriteSurface();
 Font3.ReleaseSpriteSurface();
 Font4.ReleaseSpriteSurface();
}
void FONT::Print(int x,int y,char *string,int font,LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 for(unsigned int n=0;n<strlen(string);n++)
 {
  if (font==1)
  {
   Font1.SetSpriteCoord(0,string[n]-32);
   Font1.Put(x,y,lpddssurface,ddsd);
   x+=Font1.WidthImage;
  }
  if (font==2)
  {
   Font2.SetSpriteCoord(0,string[n]-32);
   Font2.Put(x,y,lpddssurface,ddsd);
   x+=Font2.WidthImage;
  }
  if (font==3)
  {
   Font3.SetSpriteCoord(0,string[n]-32);
   Font3.Put(x,y,lpddssurface,ddsd);
   x+=Font3.WidthImage;
  }
  if (font==4)
  {
   Font4.SetSpriteCoord(0,string[n]-32);
   Font4.Put(x,y,lpddssurface,ddsd);
   x+=Font4.WidthImage;
  }
 }
}
void FONT::PrintAtCenter(int y,char *string,int font,LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 int fwidth=0;
 if (font==1) fwidth=Font1.WidthImage;
 if (font==2) fwidth=Font2.WidthImage;
 if (font==3) fwidth=Font3.WidthImage;
 if (font==4) fwidth=Font4.WidthImage;
 Print((640-strlen(string)*fwidth)/2,y,string,font,lpddssurface,ddsd);
}
int FONT::GetFontWidth(int font)
{
 int fwidth=0;
 if (font==1) fwidth=Font1.WidthImage;
 if (font==2) fwidth=Font2.WidthImage;
 if (font==3) fwidth=Font3.WidthImage;
 if (font==4) fwidth=Font4.WidthImage;
 return(fwidth);
}
int FONT::GetFontHeight(int font)
{
 int fheight=0;
 if (font==1) fheight=Font1.HeightImage;
 if (font==2) fheight=Font2.HeightImage;
 if (font==3) fheight=Font3.HeightImage;
 if (font==4) fheight=Font4.HeightImage;
 return(fheight);
}
