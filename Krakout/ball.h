struct BALL
{
 int Radius;//радиус м€ча
 float X;//координаты центра м€ча
 float Y;
 float Angle;//угол полЄта м€ча (с горизонталью OX)
 int Mode;//состо€ние м€ча (0-следует за биткой, 1-летит)
 int Image;//номер картинки м€ча
 int WaitTime;//врем€ ожидани€ м€ча битки 
 int NoWaitTime;//1-м€ч прилип из-за приза G
 int MagnetDy;//смещение дл€ прилипшего с€ча относительно центра битки
};
class BALLMAP
{
 protected:
  //-----------------------------------------------------------
  SPRITE BallSprite;//спрайт м€ча 
  BALL Ball[100];//м€чи
  int CurrentBall;//текущее число м€чей
  int Frame;//число кадров м€ча
  //-----------------------------------------------------------
 public:
  //-----------------------------------------------------------
  void Create(void);//создать объект BALLMAP
  void Release(void);//освободить объект BALLMAP
  void CreateSpriteSurface(LPDIRECTDRAW7 lpdd);//создать поверхность спрайта (нужна дл€ Direct Draw)
  void ReleaseSpriteSurface(void);//освободить поверхность спрайта
  //-----------------------------------------------------------
  int GetCurrentBall(void);//получить текущее число м€чей
  void GetBallCoord(int ball,float *x,float *y);//получить координаты м€ча
  float GetBallAngle(int ball);//получить угол полЄта м€ча
  //-----------------------------------------------------------
  void InitializeToStartLevel(void);//инициализировать поле на начало уровн€
  //-----------------------------------------------------------
  void CreateNewBall(float x,float y,float angle,int mode);//создать новый м€ч
  void DeleteBall(int ball);//удалить м€ч
  //-----------------------------------------------------------
  void PutAllBall(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);//вывести все м€чи
  //-----------------------------------------------------------
  void ChangeImageFrame(void);//сменить кадр спрайта м€ча
  //-----------------------------------------------------------
  int Processing(void);//процесс управлени€ м€чами
  int MoveBall(int ball);//двинуть м€ч
  void StartAllBall(void);//запустить все м€чи в полЄт
  void SetAllBallToPaddle(void);//присоединить м€ч к битке (по координатам)
  int GetNearestBallNumber(float x,float y);//получить ближайший к координатам м€ч
  int GetNearestToVerticalLineBallNumber(float x);//получить ближайший к вертикально линии м€ч (нужно дл€ демонстрации)
  //-----------------------------------------------------------
} BallMap;
//--------------------------------------------------------------------------
void BALLMAP::Create(void)
{
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
}
void BALLMAP::Release(void)
{
 BallSprite.Delete();
}
void BALLMAP::CreateSpriteSurface(LPDIRECTDRAW7 lpdd)
{
 BallSprite.CreateSpriteSurface(lpdd);
}
void BALLMAP::ReleaseSpriteSurface(void)
{
 BallSprite.ReleaseSpriteSurface();
}
//--------------------------------------------------------------------------
int BALLMAP::GetCurrentBall(void)
{
 return(CurrentBall);
}
void BALLMAP::GetBallCoord(int ball,float *x,float *y)
{
 *x=Ball[ball].X;
 *y=Ball[ball].Y;
}
float BALLMAP::GetBallAngle(int ball)
{
 return(Ball[ball].Angle);
}
//--------------------------------------------------------------------------
void BALLMAP::InitializeToStartLevel(void)
{
 CurrentBall=0;
 CreateNewBall(620,300,190,0);
}
//--------------------------------------------------------------------------
void BALLMAP::CreateNewBall(float x,float y,float angle,int mode)
{
 Ball[CurrentBall].X=x;
 Ball[CurrentBall].Y=y;
 Ball[CurrentBall].Radius=12;
 Ball[CurrentBall].Angle=angle;
 Ball[CurrentBall].Mode=mode;
 Ball[CurrentBall].Image=0;
 Ball[CurrentBall].WaitTime=0;
 Ball[CurrentBall].NoWaitTime=0;
 Ball[CurrentBall].MagnetDy=0;
 if (mode==0)
 {
  Ball[CurrentBall].WaitTime=100;
  Ball[CurrentBall].NoWaitTime=0;
 }
 CurrentBall++;
}
void BALLMAP::DeleteBall(int ball)
{
 if (CurrentBall==0) return;
 for(int n=ball+1;n<CurrentBall;n++) Ball[n-1]=Ball[n];
 CurrentBall--;
}
//--------------------------------------------------------------------------
void BALLMAP::PutAllBall(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 for(int n=0;n<CurrentBall;n++)
 {
  BallSprite.SetSpriteCoord(0,Ball[n].Image);
  BallSprite.Put((int)Ball[n].X-Ball[n].Radius,(int)Ball[n].Y-Ball[n].Radius,lpddssurface,ddsd);
 }
}
//--------------------------------------------------------------------------
void BALLMAP::ChangeImageFrame(void)
{
 for(int n=0;n<CurrentBall;n++)
 {
  Ball[n].Image++;
  if (Ball[n].Image==Frame) Ball[n].Image-=Frame;
  if (Ball[n].Mode==0 && Ball[n].NoWaitTime==0 && Ball[n].WaitTime>0)
  {
   Ball[n].WaitTime--;
   if (Ball[n].WaitTime==0) Ball[n].Mode=1;
  }
 }
}
//--------------------------------------------------------------------------
int BALLMAP::Processing(void)
{
 for(int n=0;n<CurrentBall;n++) 
 {
  int res=MoveBall(n);
  if (res==1) 
  {
   DeleteBall(n);
   n--;
   continue;
  }
 }
 if (CurrentBall==0) return(1);
 return(0);
}
int BALLMAP::MoveBall(int ball)
{
 if (Ball[ball].Mode==0)
 {
  Ball[ball].X=(float)Paddle.GetX()-(float)Paddle.GetWidth()/2-Ball[ball].Radius+6;
  Ball[ball].Y=(float)Paddle.GetY()+Ball[ball].MagnetDy;
  if (Ball[ball].MagnetDy>0)//м€ч ниже центра битки
  {
   int dy=Ball[ball].MagnetDy+Ball[ball].Radius-Paddle.GetHeight()/2;
   if (dy>0) Paddle.CorrectDownYPos(dy);
  }
  if (Ball[ball].MagnetDy<0)//м€ч выше центра битки
  {
   int dy=(int)(fabs(Ball[ball].MagnetDy)+Ball[ball].Radius-Paddle.GetHeight()/2);
   if (dy>0) Paddle.CorrectUpYPos(dy);
  }
  //проверим столкновение с персонажами 
  CharacterMap.ImpactCharacterToBall((int)Ball[ball].X,(int)Ball[ball].Y,Ball[ball].Radius,Ball[ball].Angle);
  return(0);//м€ч следует за биткой и летать не может
 }
 float dx=(float)cos(M_PI/180.0*Ball[ball].Angle);
 float dy=(float)-sin(M_PI/180.0*Ball[ball].Angle);
 float new_x=Ball[ball].X+dx;
 float new_y=Ball[ball].Y+dy;
 //проверим столкновение с персонажами
 Ball[ball].Angle+=CharacterMap.ImpactCharacterToBall((int)Ball[ball].X,(int)Ball[ball].Y,Ball[ball].Radius,Ball[ball].Angle);
 Ball[ball].Angle=NormalizeAngle(Ball[ball].Angle);
 //проверим столкновение с другими м€чами
 for(int n=0;n<CurrentBall;n++)
 {
  if (n==ball) continue;
  float dist2=(Ball[n].X-new_x)*(Ball[n].X-new_x)+(Ball[n].Y-new_y)*(Ball[n].Y-new_y);
  if (dist2<=(Ball[n].Radius+Ball[ball].Radius)*(Ball[n].Radius+Ball[ball].Radius))//есть столкновение
  {
   float dx2=(Ball[n].X-new_x)*(Ball[n].X-new_x);
   float dy2=(Ball[n].Y-new_y)*(Ball[n].Y-new_y);
   if (dx2>dy2) Ball[ball].Angle=180-Ball[ball].Angle;
           else Ball[ball].Angle=-Ball[ball].Angle;
   Ball[ball].Angle+=10*rand()/RAND_MAX-5;
   //разлепим м€чи
   float d=Ball[n].Radius+Ball[ball].Radius-(float)sqrt(dist2)+2;
   dx=(float)cos(M_PI/180.0*Ball[ball].Angle)*d;
   dy=(float)-sin(M_PI/180.0*Ball[ball].Angle)*d;
   new_x=Ball[ball].X+dx;
   new_y=Ball[ball].Y+dy;
   break;
  }
 }
 //проверим столкновение со стенками
 int face1=CircleIntercectionToLine(0,72,640,72,new_x,new_y,(float)Ball[ball].Radius);//верхн€€
 int face2=CircleIntercectionToLine(0,452,640,452,new_x,new_y,(float)Ball[ball].Radius);//нижн€€
 int face3=CircleIntercectionToLine(23,0,23,480,new_x,new_y,(float)Ball[ball].Radius);//лева€
 int face4=CircleIntercectionToLine(630,0,630,480,new_x,new_y,(float)Ball[ball].Radius);//права€
 if (GameParameters.RightWall==0) face4=0;
 //проверим столкновение с биткой
 int pd_x_left=(int)(Paddle.GetX()-Paddle.GetWidth()/2+9);
 int pd_x_right=(int)(Paddle.GetX()+Paddle.GetWidth()/2-9);
 int pd_y_up=(int)(Paddle.GetY()-Paddle.GetHeight()/2);
 int pd_y_down=(int)(Paddle.GetY()+Paddle.GetHeight()/2);
 int pd_face1=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_right,(float)pd_y_up,new_x,new_y,(float)Ball[ball].Radius);//верхн€€
 int pd_face2=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_down,(float)pd_x_right,(float)pd_y_down,new_x,new_y,(float)Ball[ball].Radius);//нижн€€
 int pd_face3=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_left,(float)pd_y_down,new_x,new_y,(float)Ball[ball].Radius);//лева€
 int pd_face4=CircleIntercectionToLine((float)pd_x_right,(float)pd_y_up,(float)pd_x_right,(float)pd_y_down,new_x,new_y,(float)Ball[ball].Radius);//права€
 //проверим столкновение с блоками
 int x1=(int)((new_x-Ball[ball].Radius)-23)/20-2;
 int x2=(int)((new_x+Ball[ball].Radius)-23)/20+2;
 int y1=(int)((new_y-Ball[ball].Radius)-82)/30-2;
 int y2=(int)((new_y+Ball[ball].Radius)-82)/30+2;
 if (x1<0) x1=0;
 if (y1<0) y1=0;
 if (x2>24) x2=24;
 if (y2>11) y2=11;
 for(int x=x1;x<=x2;x++)
  for(int y=y1;y<=y2;y++)
  {
   BLOCK Block=BlockMap.GetBlock(x,y);
   int impact=0;
   if (Block.Obstacle==0 || Block.Space==1) continue; 
   int xleft=x*20+23;
   int xright=(x+1)*20+22;
   int yup=y*30+82;
   int ydown=(y+1)*30+81;
   if (CircleIntercectionToLine((float)xleft,(float)ydown,(float)xleft,(float)yup,new_x,new_y,(float)Ball[ball].Radius))
   {
	face3=1;
	impact=1;
   }
   if (CircleIntercectionToLine((float)xright,(float)ydown,(float)xright,(float)yup,new_x,new_y,(float)Ball[ball].Radius))
   {
	face4=1;
	impact=1;
   }
   if (CircleIntercectionToLine((float)xleft,(float)yup,(float)xright,(float)yup,new_x,new_y,(float)Ball[ball].Radius))
   {
	face1=1;
	impact=1;
   }
   if (CircleIntercectionToLine((float)xleft,(float)ydown,(float)xright,(float)ydown,new_x,new_y,(float)Ball[ball].Radius))
   {
    face2=1;
	impact=1;
   }
   if (impact==1) BlockMap.ActivateBlock(x,y);
  }
 if (face1!=0) Ball[ball].Angle=-Ball[ball].Angle;
 if (face2!=0) Ball[ball].Angle=-Ball[ball].Angle;
 if (face3!=0) Ball[ball].Angle=180-Ball[ball].Angle;
 if (face4!=0) Ball[ball].Angle=180-Ball[ball].Angle;
 //обработаем столкновение с биткой
 if (pd_face1!=0)
 {
  Ball[ball].Angle=-Ball[ball].Angle;
  Paddle.CorrectUpYPos(Ball[ball].Radius*2);
  Ball[ball].Y=(float)Paddle.GetY()-(float)Paddle.GetHeight()/2-Ball[ball].Radius-1;
  Ball[ball].X=(float)(pd_x_left-Ball[ball].Radius-1);
 }
 if (pd_face2!=0)
 {
  Ball[ball].Angle=-Ball[ball].Angle;
  Paddle.CorrectDownYPos(Ball[ball].Radius*2);
  Ball[ball].Y=(float)Paddle.GetY()+(float)Paddle.GetHeight()/2+Ball[ball].Radius+1;
  Ball[ball].X=(float)(pd_x_left-Ball[ball].Radius-1);
 }
 if (pd_face3!=0)
 {
  float dy=(float)(Ball[ball].Y-Paddle.GetY())/(float)(Paddle.GetHeight()/2.0);
  float dangle=30*dy;
  Ball[ball].Angle=180-Ball[ball].Angle+dangle;
  Ball[ball].Angle=NormalizeAngle(Ball[ball].Angle);
  Ball[ball].X=(float)(Paddle.GetX()-9-Paddle.GetWidth()/2);
 }
 if (pd_face4!=0) Ball[ball].Angle=180-Ball[ball].Angle;
 if (Paddle.GetMagnet()==1 && pd_face1+pd_face2+pd_face3+pd_face4!=0)
 {
  Ball[ball].Mode=0;
  Ball[ball].NoWaitTime=1;
  Ball[ball].MagnetDy=(int)(Ball[ball].Y-Paddle.GetY());
  //скорректируем угол
  Ball[ball].Angle=NormalizeAngle(Ball[ball].Angle);
  if (Ball[ball].Angle<100) Ball[ball].Angle+=100;
  if (Ball[ball].Angle>250) Ball[ball].Angle-=100;
 }
 if (pd_face1!=0)
 {
  //скорректируем угол
  Ball[ball].Angle=NormalizeAngle(Ball[ball].Angle);
  if (Ball[ball].Angle<100) Ball[ball].Angle+=100;
  if (Ball[ball].Angle>180) Ball[ball].Angle-=90;
 }
 if (pd_face2!=0)
 {
  //скорректируем угол
  Ball[ball].Angle=NormalizeAngle(Ball[ball].Angle);
  if (Ball[ball].Angle>260) Ball[ball].Angle-=260;
  if (Ball[ball].Angle<180) Ball[ball].Angle+=90;
 }
 if (pd_face1+pd_face2+pd_face3+pd_face4!=0) Sound.PlaySound(SOUND__IMPACT_5,0,GameParameters.SoundVolume);
 Ball[ball].Angle=NormalizeAngle(Ball[ball].Angle);
 //нельз€ допускать вертикальных углов полЄта м€ча
 float angle1=(float)fabs(fabs(Ball[ball].Angle)-90);
 float angle2=(float)fabs(fabs(Ball[ball].Angle)-270);
 if (angle1<5)
 {
  if (Ball[ball].Angle<=90) Ball[ball].Angle-=5;//корректируем угол
  if (Ball[ball].Angle>90) Ball[ball].Angle+=5;//корректируем угол
 }
 if (angle2<5)
 {
  if (Ball[ball].Angle<=270) Ball[ball].Angle-=5;//корректируем угол
  if (Ball[ball].Angle>270) Ball[ball].Angle+=5;//корректируем угол
 }
 if (face1+face2+face3+face4+pd_face1+pd_face2+pd_face3+pd_face4==0)
 {
  Ball[ball].X=new_x;
  Ball[ball].Y=new_y;
 }
 if (face1+face2+face3+face4!=0) Sound.PlaySound(SOUND__IMPACT_1,0,GameParameters.SoundVolume);
 if (Ball[ball].X>=640) return(1);//м€ч вылетел за пределы пол€
 return(0);
}
void BALLMAP::StartAllBall(void)
{
 for(int n=0;n<CurrentBall;n++) Ball[n].Mode=1;
}
void BALLMAP::SetAllBallToPaddle(void)
{
 for(int n=0;n<CurrentBall;n++)
 {
  if (Ball[n].Mode==0)
  {
   Ball[n].X=(float)Paddle.GetX()-(float)Paddle.GetWidth()/2-Ball[n].Radius+6;
   Ball[n].Y=(float)Paddle.GetY();
  }
 }
}
int BALLMAP::GetNearestBallNumber(float x,float y)
{
 int selectball=-1;
 float mindist2=10000000000;
 for(int m=0;m<CurrentBall;m++)
 {
  float bx,by;
  bx=Ball[m].X;
  by=Ball[m].Y;
  float dist2=(bx-x)*(bx-x)+(by-y)*(by-y);
  if (dist2<mindist2)
  {
   mindist2=dist2;
   selectball=m;
  }
 }
 return(selectball);
}
int BALLMAP::GetNearestToVerticalLineBallNumber(float x)
{
 int selectball=-1;
 float mindist2=10000000000;
 for(int m=0;m<CurrentBall;m++)
 {
  float bx,by;
  bx=Ball[m].X;
  by=Ball[m].Y;
  float dist2=(bx-x)*(bx-x);
  if (dist2<mindist2)
  {
   mindist2=dist2;
   selectball=m;
  }
 }
 return(selectball);
}


