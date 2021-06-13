struct MISSILE
{
 float X;
 float Y;
 int Image;
 int Height;
 int Width;
};
class MISSILEMAP
{
 protected:
  //-----------------------------------------------------------
  SPRITE MissileSprite;
  //-----------------------------------------------------------
  MISSILE Missile[100];
  int CurrentMissile;
  int Frame;
  //-----------------------------------------------------------
 public: 
  //-----------------------------------------------------------
  void Create(void);
  void Release(void);
  void CreateSpriteSurface(LPDIRECTDRAW7 lpdd);
  void ReleaseSpriteSurface(void);
  //-----------------------------------------------------------
  void InitializeToStartLevel(void);
  void CreateNewMissile(float x,float y);
  void DeleteMissile(int missile);
  void PutAllMissile(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void Processing(void);
  void ChangeImageFrame(void);
 //-----------------------------------------------------------
} MissileMap;
//--------------------------------------------------------------------------
void MISSILEMAP::Create(void)
{
 int frame_size_x;
 int frame_size_y;
 int blend_color_r;
 int blend_color_g;
 int blend_color_b;
 if (!GetParameters("bitmap\\missile.txt","FRAME_SIZE_X:",&frame_size_x)) return;
 if (!GetParameters("bitmap\\missile.txt","FRAME_SIZE_Y:",&frame_size_y)) return;
 if (!GetParameters("bitmap\\missile.txt","BLEND_COLOR_R:",&blend_color_r)) return;
 if (!GetParameters("bitmap\\missile.txt","BLEND_COLOR_G:",&blend_color_g)) return;
 if (!GetParameters("bitmap\\missile.txt","BLEND_COLOR_B:",&blend_color_b)) return;
 if (!GetParameters("bitmap\\missile.txt","FRAME:",&Frame)) return;
 MissileSprite.Load("bitmap\\missile.bmp");
 MissileSprite.SetSpriteSize(frame_size_x,frame_size_y);
 MissileSprite.SetBlendColor(blend_color_r,blend_color_g,blend_color_b);
}
void MISSILEMAP::Release(void)
{
 MissileSprite.Delete();
}
void MISSILEMAP::CreateSpriteSurface(LPDIRECTDRAW7 lpdd)
{
 MissileSprite.CreateSpriteSurface(lpdd);
}
void MISSILEMAP::ReleaseSpriteSurface(void)
{
 MissileSprite.ReleaseSpriteSurface();
}
//--------------------------------------------------------------------------
void MISSILEMAP::InitializeToStartLevel(void)
{
 CurrentMissile=0;
}
void MISSILEMAP::CreateNewMissile(float x,float y)
{
 Missile[CurrentMissile].X=x;
 Missile[CurrentMissile].Y=y;
 Missile[CurrentMissile].Image=0;
 Missile[CurrentMissile].Height=MissileSprite.HeightImage;
 Missile[CurrentMissile].Width=MissileSprite.WidthImage;
 CurrentMissile++;
 if (CurrentMissile>=100) CurrentMissile=99;
}
void MISSILEMAP::DeleteMissile(int missile)
{
 if (CurrentMissile==0) return;
 for(int n=missile+1;n<CurrentMissile;n++) Missile[n-1]=Missile[n];
 CurrentMissile--;
}
void MISSILEMAP::PutAllMissile(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 for(int n=0;n<CurrentMissile;n++)
 {
  MissileSprite.SetSpriteCoord(Missile[n].Image,0);
  MissileSprite.Put((int)(Missile[n].X-Missile[n].Width/2),(int)(Missile[n].Y-Missile[n].Height/2),lpddssurface,ddsd);
 }
}
void MISSILEMAP::Processing(void)
{
 for(int n=0;n<CurrentMissile;n++)
 {
  float xleft=Missile[n].X-Missile[n].Width/2;
  float xright=Missile[n].X+Missile[n].Width/2;
  float yup=Missile[n].Y-Missile[n].Height/2;
  float ydown=Missile[n].Y+Missile[n].Height/2;
  int x1=(int)(xleft-23)/20-2;
  int x2=(int)(xright-23)/20+2;
  int y1=(int)(yup-82)/30-2;
  int y2=(int)(ydown-82)/30+2;
  if (x1<0) x1=0;
  if (y1<0) y1=0;
  if (x2>24) x2=24;
  if (y2>11) y2=11;
  for(int x=x1;x<=x2;x++)
   for(int y=y1;y<=y2;y++)
   {
    int xb1=x*20+23;
    int xb2=(x+1)*20+23;
    int yb1=y*30+82;
    int yb2=(y+1)*30+82;
    if (xleft>xb2) continue;
    if (xright<xb1) continue;
    if (yup>yb2) continue;
    if (ydown<yb1) continue;
    BlockMap.DestroyBlock(x,y);
   }
  Missile[n].X-=2;
  int res=CharacterMap.ImpactCharacterToMissile((int)xleft,(int)xright,(int)yup,(int)ydown);
  if (Missile[n].X-Missile[n].Width/2<23 || res!=0) 
  {
   DeleteMissile(n);
   n--;
   continue;
  }
 }
}
void MISSILEMAP::ChangeImageFrame(void)
{
 for(int n=0;n<CurrentMissile;n++)
 {
  Missile[n].Image++;
  if (Missile[n].Image==Frame) Missile[n].Image=0;
 }
}
