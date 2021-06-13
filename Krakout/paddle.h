class PADDLE
{
 protected:
  //-----------------------------------------------------------
  float Y;//координаты центра битки
  float X;
  int Height;//высота битки
  int Width;//ширина битки
  int Double;//1-битка удвоена
  int Missile;//1-ракета есть
  float Speed;//скорость перемещения битки
  int Move;//1-производится движение битки
  int Magnet;//1-мяч прилипает к битке
  //-----------------------------------------------------------
  SPRITE PaddleNormalSprite;//спрайты нормальной и удвоенной битки
  SPRITE PaddleDoubleSprite;
  //-----------------------------------------------------------
 public:
  //-----------------------------------------------------------
  void Create(void);
  void Release(void);
  void CreateSpriteSurface(LPDIRECTDRAW7 lpdd);
  void ReleaseSpriteSurface(void);
  //-----------------------------------------------------------
  int GetHeight(void);
  int GetWidth(void);
  int GetX(void);
  int GetY(void);
  int GetMagnet(void);
  int GetMissile(void);
  //-----------------------------------------------------------
  void InitializeToStartLevel(void);
  void PutPaddle(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void MoveUp(void);
  void MoveDown(void);
  void Processing(void);
  void DoubleMode(void);
  void NormalMode(void);
  void MissileModeOn(void);
  void MissileModeOff(void);
  void MagnetModeOn(void);
  void MagnetModeOff(void);
  void CorrectUpYPos(int dy);
  void CorrectDownYPos(int dy);
  //-----------------------------------------------------------
} Paddle;
//--------------------------------------------------------------------------
void PADDLE::Create(void)
{
 PaddleNormalSprite.Load("bitmap\\paddle_normal.bmp");
 PaddleDoubleSprite.Load("bitmap\\paddle_double.bmp");
 PaddleNormalSprite.SetSpriteSize(36,73);
 PaddleDoubleSprite.SetSpriteSize(36,123);
 PaddleNormalSprite.SetBlendColor(0,0,0);
 PaddleDoubleSprite.SetBlendColor(0,0,0);
}
void PADDLE::Release(void)
{
 PaddleNormalSprite.Delete();
 PaddleDoubleSprite.Delete();
}
void PADDLE::CreateSpriteSurface(LPDIRECTDRAW7 lpdd)
{
 PaddleNormalSprite.CreateSpriteSurface(lpdd);
 PaddleDoubleSprite.CreateSpriteSurface(lpdd);
}
void PADDLE::ReleaseSpriteSurface(void)
{
 PaddleNormalSprite.ReleaseSpriteSurface();
 PaddleDoubleSprite.ReleaseSpriteSurface();
}
//--------------------------------------------------------------------------
int PADDLE::GetHeight(void)
{
 return(Height);
}
int PADDLE::GetWidth(void)
{ 
 return(Width);
}
int PADDLE::GetX(void)
{
 return((int)X);
}
int PADDLE::GetY(void)
{
 return((int)Y);
}
int PADDLE::GetMagnet(void)
{
 return(Magnet);
}
int PADDLE::GetMissile(void)
{
 return(Missile);
}
//--------------------------------------------------------------------------
void PADDLE::InitializeToStartLevel(void)
{
 X=625;
 Y=200;
 Height=PaddleNormalSprite.HeightImage;
 Width=PaddleNormalSprite.WidthImage;
 Double=0;
 Missile=0;
 Magnet=0;
}
void PADDLE::PutPaddle(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 if (Double==0)
 {
  if (Missile==0) PaddleNormalSprite.SetSpriteCoord(0,0);
             else PaddleNormalSprite.SetSpriteCoord(0,1);
  PaddleNormalSprite.Put((int)(X-Width/2),(int)(Y-Height/2),lpddssurface,ddsd);
 }
 else
 {
  if (Missile==0) PaddleDoubleSprite.SetSpriteCoord(0,0);
             else PaddleDoubleSprite.SetSpriteCoord(0,1);
  PaddleDoubleSprite.Put((int)(X-Width/2),(int)(Y-Height/2),lpddssurface,ddsd);
 }
}
void PADDLE::MoveUp(void)
{
 if (Speed>0) Speed=0;
 Speed-=0.5;
 Move=1;
 if (Speed<-5) Speed=-5;
}
void PADDLE::MoveDown(void)
{
 if (Speed<0) Speed=0;
 Speed+=0.5;
 Move=1;
 if (Speed>5) Speed=5;
}
void PADDLE::Processing(void)
{
 if (Speed==0) return;
 if (Move==0) Speed=0;
 Y+=Speed;
 if (Y-Height/2<72) Y=(float)(72+Height/2);
 if (Y+Height/2>451) Y=(float)(451-Height/2);
 Move=0;
}
void PADDLE::DoubleMode(void)
{
 Double=1;
 Height=PaddleDoubleSprite.HeightImage;
 Width=PaddleDoubleSprite.WidthImage;
 if (Y-Height/2<72) Y=(float)(72+Height/2);
 if (Y+Height/2>451) Y=(float)(451-Height/2);
}
void PADDLE::NormalMode(void)
{
 Double=0;
 Height=PaddleNormalSprite.HeightImage;
 Width=PaddleNormalSprite.WidthImage;
 if (Y-Height/2<72) Y=(float)(72+Height/2);
 if (Y+Height/2>451) Y=(float)(451-Height/2);
}
void PADDLE::MissileModeOn(void)
{
 Missile=1;
}
void PADDLE::MissileModeOff(void)
{
 Missile=0;
}
void PADDLE::MagnetModeOn(void)
{
 Magnet=1;
}
void PADDLE::MagnetModeOff(void)
{
 Magnet=0;
}
void PADDLE::CorrectUpYPos(int dy)
{
 if (Y-Height/2-dy-2<72) Y=(float)(72+Height/2+dy+2);
}
void PADDLE::CorrectDownYPos(int dy)
{
 if (Y+Height/2+dy+2>451) Y=(float)(451-Height/2-dy-2);
}
