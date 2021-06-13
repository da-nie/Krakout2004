void CHARACTERMAP::Create(void)
{
 LoadCharacter1Sprite();
 LoadCharacter2Sprite();
 LoadCharacter3Sprite();
 LoadCharacter4Sprite();
 LoadCharacter5Sprite();
 LoadCharacter6Sprite();
 LoadCharacter7Sprite();
 LoadCharacter8Sprite();
 LoadCharacter9Sprite();
}
void CHARACTERMAP::Release(void)
{ 	 
 Character1Sprite.Delete();
 Character2Sprite.Delete();
 Character3Sprite.Delete();
 Character4Sprite.Delete();
 Character5Sprite.Delete();
 Character6Sprite.Delete();
 Character7Sprite.Delete();
 Character8Sprite.Delete();
 Character9Sprite.Delete();
}
void CHARACTERMAP::InitializeToStartLevel(void)
{
 //--------------------------------------------------------------------------
 CurrentCharacter1=0;
 TimerDoStartCharacter1=(int)(5000.0*rand()/RAND_MAX+100);
 //--------------------------------------------------------------------------
 CurrentCharacter2=0;
 TimerDoStartCharacter2=(int)(5000.0*rand()/RAND_MAX+100);
 //--------------------------------------------------------------------------
 CurrentCharacter3=0;
 TimerDoStartCharacter3=(int)(5000.0*rand()/RAND_MAX+100);
 //--------------------------------------------------------------------------
 CurrentCharacter4=0;
 TimerDoStartCharacter4=(int)(5000.0*rand()/RAND_MAX+100);
 //--------------------------------------------------------------------------
 CurrentCharacter5=0;
 TimerDoStartCharacter5=(int)(5000.0*rand()/RAND_MAX+100);
 //--------------------------------------------------------------------------
 CurrentCharacter6=0;
 TimerDoStartCharacter6=(int)(5000.0*rand()/RAND_MAX+200);
 //--------------------------------------------------------------------------
 CurrentCharacter7=0;
 TimerDoStartCharacter7=(int)(5000.0*rand()/RAND_MAX+200);
 //--------------------------------------------------------------------------
 CurrentCharacter8=0;
 TimerDoStartCharacter8=(int)(5000.0*rand()/RAND_MAX+100);
 //--------------------------------------------------------------------------
 CurrentCharacter9=0;
 TimerDoStartCharacter9=(int)(5000.0*rand()/RAND_MAX+100);
 //--------------------------------------------------------------------------
 Step=0;
}
void CHARACTERMAP::CreateSpriteSurface(LPDIRECTDRAW7 lpdd)
{
 Character1Sprite.CreateSpriteSurface(lpdd);
 Character2Sprite.CreateSpriteSurface(lpdd);
 Character3Sprite.CreateSpriteSurface(lpdd);
 Character4Sprite.CreateSpriteSurface(lpdd);
 Character5Sprite.CreateSpriteSurface(lpdd);
 Character6Sprite.CreateSpriteSurface(lpdd);
 Character7Sprite.CreateSpriteSurface(lpdd);
 Character8Sprite.CreateSpriteSurface(lpdd);
 Character9Sprite.CreateSpriteSurface(lpdd);
}
void CHARACTERMAP::ReleaseSpriteSurface(void)
{
 Character1Sprite.ReleaseSpriteSurface();
 Character2Sprite.ReleaseSpriteSurface();
 Character3Sprite.ReleaseSpriteSurface();
 Character4Sprite.ReleaseSpriteSurface();
 Character5Sprite.ReleaseSpriteSurface();
 Character6Sprite.ReleaseSpriteSurface();
 Character7Sprite.ReleaseSpriteSurface();
 Character8Sprite.ReleaseSpriteSurface();
 Character9Sprite.ReleaseSpriteSurface();
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void CHARACTERMAP::LoadCharacter1Sprite(void)
{
 int frame_size_x;
 int frame_size_y;
 int blend_color_r;
 int blend_color_g;
 int blend_color_b;
 if (!GetParameters("bitmap\\t1.txt","FRAME_SIZE_X:",&frame_size_x)) return;
 if (!GetParameters("bitmap\\t1.txt","FRAME_SIZE_Y:",&frame_size_y)) return;
 if (!GetParameters("bitmap\\t1.txt","BLEND_COLOR_R:",&blend_color_r)) return;
 if (!GetParameters("bitmap\\t1.txt","BLEND_COLOR_G:",&blend_color_g)) return;
 if (!GetParameters("bitmap\\t1.txt","BLEND_COLOR_B:",&blend_color_b)) return;
 if (!GetParameters("bitmap\\t1.txt","BIRTH_FRAME_START:",&Character1_Birth_Frame_Start)) return;
 if (!GetParameters("bitmap\\t1.txt","BIRTH_FRAME_END:",&Character1_Birth_Frame_End)) return;
 if (!GetParameters("bitmap\\t1.txt","LIFE_FRAME_START:",&Character1_Life_Frame_Start)) return;
 if (!GetParameters("bitmap\\t1.txt","LIFE_FRAME_END:",&Character1_Life_Frame_End)) return;
 if (!GetParameters("bitmap\\t1.txt","DESTRUCTION_FRAME_START:",&Character1_Destruction_Frame_Start)) return;
 if (!GetParameters("bitmap\\t1.txt","DESTRUCTION_FRAME_END:",&Character1_Destruction_Frame_End)) return;
 Character1Sprite.Load("bitmap\\t1.bmp");
 Character1Sprite.SetSpriteSize(frame_size_x,frame_size_y);
 Character1Sprite.SetBlendColor(blend_color_r,blend_color_g,blend_color_b);
 Character1Radius=(float)frame_size_x/2;
 if (Character1Radius<frame_size_y/2) Character1Radius=(float)frame_size_y/2;
}
void CHARACTERMAP::CreateNewCharacter1(int x,int y)
{
 if (CurrentCharacter1>=3 || GameParameters.EnableCharacter[1]==0) return;
 Sound.PlaySound(SOUND__BIRTH,0,GameParameters.SoundVolume);
 Character1[CurrentCharacter1].X=(float)x;
 Character1[CurrentCharacter1].Y=(float)y;
 Character1[CurrentCharacter1].CurrentImage=Character1_Birth_Frame_Start-1;
 Character1[CurrentCharacter1].ChangeImage=1;
 Character1[CurrentCharacter1].LifeMode=1;

 Character1[CurrentCharacter1].TimeOfLife=(int)(5000.0*rand()/RAND_MAX+500);
 Character1[CurrentCharacter1].TimeOfMove=0;
 Character1[CurrentCharacter1].ModeOfMove=0;
 CurrentCharacter1++;
}
void CHARACTERMAP::DestroyCharacter1(int character)
{
 Character1[character].CurrentImage=Character1_Destruction_Frame_Start-1;
 Character1[character].ChangeImage=1;
 Character1[character].LifeMode=3;
}
void CHARACTERMAP::DeleteCharacter1(int character)
{
 for(int n=character+1;n<CurrentCharacter1;n++) Character1[n-1]=Character1[n];
 CurrentCharacter1--;
}
void CHARACTERMAP::AnimateCharacter1(void)
{
 if (Step!=0) return;
 for(int n=0;n<CurrentCharacter1;n++)
 {
  if (Character1[n].LifeMode==0)
  {
   DeleteCharacter1(n);
   n--;
   continue;
  }
  Character1[n].CurrentImage+=Character1[n].ChangeImage;
  if (Character1[n].LifeMode==1)
  {
   if (Character1[n].CurrentImage==Character1_Birth_Frame_End-1)
   {
    Character1[n].LifeMode=2;
    Character1[n].CurrentImage=Character1_Life_Frame_Start-1;
	continue;
   }
  }
  if (Character1[n].LifeMode==2)
  {
   if (Character1[n].CurrentImage==Character1_Life_Frame_End-1) Character1[n].CurrentImage=Character1_Life_Frame_Start-1;
   continue;
  }
  if (Character1[n].LifeMode==3)
  {
   if (Character1[n].CurrentImage==Character1_Destruction_Frame_End-1) Character1[n].LifeMode=0;
   continue;
  }
 }
}
void CHARACTERMAP::PutCharacter1(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 for(int n=0;n<CurrentCharacter1;n++)
 {
  Character1Sprite.SetSpriteCoord(0,Character1[n].CurrentImage);
  Character1Sprite.Put((int)Character1[n].X-(int)Character1Radius,(int)Character1[n].Y-(int)Character1Radius,lpddssurface,ddsd);
 }
}
void CHARACTERMAP::MoveCharacter1(void)
{
 int pd_x_left=(int)(Paddle.GetX()-Paddle.GetWidth()/2+9);
 int pd_x_right=(int)(Paddle.GetX()+Paddle.GetWidth()/2-9);
 int pd_y_up=(int)(Paddle.GetY()-Paddle.GetHeight()/2);
 int pd_y_down=(int)(Paddle.GetY()+Paddle.GetHeight()/2);
 for(int n=0;n<CurrentCharacter1;n++)
 {
  if (Character1[n].LifeMode!=2) continue;
  Character1[n].TimeOfLife--;
  if (Character1[n].TimeOfLife==0)//время жизни персонажа закончилось
  {
   DestroyCharacter1(n); 
   continue;
  }
  float new_x=Character1[n].X;
  float new_y=Character1[n].Y;
  if (Character1[n].ModeOfMove==1) new_x--;
  if (Character1[n].ModeOfMove==2) new_x++;
  if (Character1[n].ModeOfMove==3) new_y--;
  if (Character1[n].ModeOfMove==4) new_y++;
  //Проверка столкновения со стенками
  int face1=CircleIntercectionToLine(0,72,640,72,new_x,new_y,(float)Character1Radius);//верхняя
  int face2=CircleIntercectionToLine(0,452,640,452,new_x,new_y,(float)Character1Radius);//нижняя
  int face3=CircleIntercectionToLine(23,0,23,480,new_x,new_y,(float)Character1Radius);//левая
  int face4=CircleIntercectionToLine(630,0,630,480,new_x,new_y,(float)Character1Radius);//правая
  if (face1+face2+face3+face4!=0) Character1[n].TimeOfMove=0;
  else 
  {
   Character1[n].X=new_x;
   Character1[n].Y=new_y;
  }
  //проверка столкновения с биткой
  int pd_face1=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_right,(float)pd_y_up,Character1[n].X,Character1[n].Y,(float)Character1Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_down,(float)pd_x_right,(float)pd_y_down,Character1[n].X,Character1[n].Y,(float)Character1Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_left,(float)pd_y_down,Character1[n].X,Character1[n].Y,(float)Character1Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)pd_x_right,(float)pd_y_up,(float)pd_x_right,(float)pd_y_down,Character1[n].X,Character1[n].Y,(float)Character1Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0) DestroyCharacter1(n);
  if (Character1[n].TimeOfMove>0) Character1[n].TimeOfMove--;
  if (Character1[n].TimeOfMove==0)
  {
   Character1[n].TimeOfMove=(int)(200.0*rand()/RAND_MAX+10);
   Character1[n].ModeOfMove=(int)(5.0*rand()/RAND_MAX);
  }
 }
}
void CHARACTERMAP::DestroyAllCharacter1(void)
{
 for(int n=0;n<CurrentCharacter1;n++)
 {
  if (Character1[n].LifeMode!=2 && Character1[n].LifeMode!=1) continue;
  DestroyCharacter1(n);
 }
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void CHARACTERMAP::LoadCharacter2Sprite(void)
{
 int frame_size_x;
 int frame_size_y;
 int blend_color_r;
 int blend_color_g;
 int blend_color_b;
 if (!GetParameters("bitmap\\t2.txt","FRAME_SIZE_X:",&frame_size_x)) return;
 if (!GetParameters("bitmap\\t2.txt","FRAME_SIZE_Y:",&frame_size_y)) return;
 if (!GetParameters("bitmap\\t2.txt","BLEND_COLOR_R:",&blend_color_r)) return;
 if (!GetParameters("bitmap\\t2.txt","BLEND_COLOR_G:",&blend_color_g)) return;
 if (!GetParameters("bitmap\\t2.txt","BLEND_COLOR_B:",&blend_color_b)) return;
 if (!GetParameters("bitmap\\t2.txt","BIRTH_FRAME_START:",&Character2_Birth_Frame_Start)) return;
 if (!GetParameters("bitmap\\t2.txt","BIRTH_FRAME_END:",&Character2_Birth_Frame_End)) return;
 if (!GetParameters("bitmap\\t2.txt","LIFE_FRAME_START:",&Character2_Life_Frame_Start)) return;
 if (!GetParameters("bitmap\\t2.txt","LIFE_FRAME_END:",&Character2_Life_Frame_End)) return;
 if (!GetParameters("bitmap\\t2.txt","DESTRUCTION_FRAME_START:",&Character2_Destruction_Frame_Start)) return;
 if (!GetParameters("bitmap\\t2.txt","DESTRUCTION_FRAME_END:",&Character2_Destruction_Frame_End)) return;
 if (!GetParameters("bitmap\\t2.txt","EXPLOSION_FRAME_START:",&Character2_Explosion_Frame_Start)) return;
 if (!GetParameters("bitmap\\t2.txt","EXPLOSION_FRAME_END:",&Character2_Explosion_Frame_End)) return;
 Character2Sprite.Load("bitmap\\t2.bmp");
 Character2Sprite.SetSpriteSize(frame_size_x,frame_size_y);
 Character2Sprite.SetBlendColor(blend_color_r,blend_color_g,blend_color_b);
 Character2Radius=(float)frame_size_x/2;
 if (Character2Radius<frame_size_y/2) Character2Radius=(float)frame_size_y/2;
}
void CHARACTERMAP::CreateNewCharacter2(int x,int y)
{
 if (CurrentCharacter2>=3 || GameParameters.EnableCharacter[2]==0) return;
 Sound.PlaySound(SOUND__BIRTH,0,GameParameters.SoundVolume);
 Character2[CurrentCharacter2].X=(float)x;
 Character2[CurrentCharacter2].Y=(float)y;
 Character2[CurrentCharacter2].CurrentImage=Character2_Birth_Frame_Start-1;
 Character2[CurrentCharacter2].ChangeImage=1;
 Character2[CurrentCharacter2].LifeMode=1;

 Character2[CurrentCharacter2].TimeOfLife=(int)(5000.0*rand()/RAND_MAX+500);
 Character2[CurrentCharacter2].TimeOfMove=0;
 Character2[CurrentCharacter2].ModeOfMove=0;
 CurrentCharacter2++;
}
void CHARACTERMAP::DestroyCharacter2(int character)
{
 Character2[character].CurrentImage=Character2_Destruction_Frame_Start-1;
 Character2[character].ChangeImage=1;
 Character2[character].LifeMode=3;
}
void CHARACTERMAP::ExplosionCharacter2(int character)
{
 Character2[character].CurrentImage=Character2_Explosion_Frame_Start-1;
 Character2[character].ChangeImage=1;
 Character2[character].LifeMode=4;
}
void CHARACTERMAP::DeleteCharacter2(int character)
{
 for(int n=character+1;n<CurrentCharacter2;n++) Character2[n-1]=Character2[n];
 CurrentCharacter2--;
}
void CHARACTERMAP::AnimateCharacter2(void)
{
 if (Step!=0) return;
 for(int n=0;n<CurrentCharacter2;n++)
 {
  if (Character2[n].LifeMode==0)
  {
   DeleteCharacter2(n);
   n--;
   continue;
  }
  Character2[n].CurrentImage+=Character2[n].ChangeImage;
  if (Character2[n].LifeMode==1)
  {
   if (Character2[n].CurrentImage==Character2_Birth_Frame_End-1)
   {
    Character2[n].LifeMode=2;
    Character2[n].CurrentImage=Character2_Life_Frame_Start-1;
	continue;
   }
  }
  if (Character2[n].LifeMode==2)
  {
   if (Character2[n].CurrentImage==Character2_Life_Frame_End-1) Character2[n].CurrentImage=Character2_Life_Frame_Start-1;
   continue;
  }
  if (Character2[n].LifeMode==3)
  {
   if (Character2[n].CurrentImage==Character2_Destruction_Frame_End-1) Character2[n].LifeMode=0;
   continue;
  }
  if (Character2[n].LifeMode==4)
  {
   if (Character2[n].CurrentImage==Character2_Explosion_Frame_End-1) Character2[n].LifeMode=0;
   continue;
  }
 }
}
void CHARACTERMAP::PutCharacter2(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 for(int n=0;n<CurrentCharacter2;n++)
 {
  Character2Sprite.SetSpriteCoord(0,Character2[n].CurrentImage);
  Character2Sprite.Put((int)Character2[n].X-(int)Character2Radius,(int)Character2[n].Y-(int)Character2Radius,lpddssurface,ddsd);
 }
}
void CHARACTERMAP::MoveCharacter2(void)
{
 int pd_x_left=(int)(Paddle.GetX()-Paddle.GetWidth()/2+9);
 int pd_x_right=(int)(Paddle.GetX()+Paddle.GetWidth()/2-9);
 int pd_y_up=(int)(Paddle.GetY()-Paddle.GetHeight()/2);
 int pd_y_down=(int)(Paddle.GetY()+Paddle.GetHeight()/2);
 for(int n=0;n<CurrentCharacter2;n++)
 {
  if (Character2[n].LifeMode!=2) continue;
  Character2[n].TimeOfLife--;
  if (Character2[n].TimeOfLife==0)//время жизни персонажа закончилось
  {
   DestroyCharacter2(n); 
   continue;
  }
  float new_x=Character2[n].X;
  float new_y=Character2[n].Y;
  if (Character2[n].ModeOfMove==1) new_x-=0.5;
  if (Character2[n].ModeOfMove==2) new_x+=0.5;
  if (Character2[n].ModeOfMove==3) new_y-=0.5;
  if (Character2[n].ModeOfMove==4) new_y+=0.5;
  if (Character2[n].ModeOfMove>=5 && Character2[n].ModeOfMove<=7)//погоня за мячом (ближайшим)
  {
   int selectball=BallMap.GetNearestBallNumber(new_x,new_y);
   if (selectball>=0)
   {
    float bx,by;
    BallMap.GetBallCoord(selectball,&bx,&by);
    if (new_x>bx) new_x-=0.5;
    if (new_x<bx) new_x+=0.5;
    if (new_y>by) new_y-=0.5;
    if (new_y<by) new_y+=0.5;
   }
  }
  if (Character2[n].ModeOfMove>=8 && Character2[n].ModeOfMove<=10)//убегаем от мяча(от ближайшего)
  {
   int selectball=BallMap.GetNearestBallNumber(new_x,new_y);
   if (selectball>=0)
   {
    float bx,by;
    BallMap.GetBallCoord(selectball,&bx,&by);
    if (new_x>bx) new_x+=0.5;
    if (new_x<bx) new_x-=0.5;
    if (new_y>by) new_y+=0.5;
    if (new_y<by) new_y-=0.5;
   }
  }
  //Проверка столкновения со стенками
  int face1=CircleIntercectionToLine(0,72,640,72,new_x,new_y,(float)Character2Radius);//верхняя
  int face2=CircleIntercectionToLine(0,452,640,452,new_x,new_y,(float)Character2Radius);//нижняя
  int face3=CircleIntercectionToLine(23,0,23,480,new_x,new_y,(float)Character2Radius);//левая
  int face4=CircleIntercectionToLine(630,0,630,480,new_x,new_y,(float)Character2Radius);//правая
  if (face1+face2+face3+face4!=0) Character2[n].TimeOfMove=0;
  else 
  {
   Character2[n].X=new_x;
   Character2[n].Y=new_y;
  }
  //проверка столкновения с биткой
  int pd_face1=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_right,(float)pd_y_up,Character2[n].X,Character2[n].Y,(float)Character2Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_down,(float)pd_x_right,(float)pd_y_down,Character2[n].X,Character2[n].Y,(float)Character2Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_left,(float)pd_y_down,Character2[n].X,Character2[n].Y,(float)Character2Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)pd_x_right,(float)pd_y_up,(float)pd_x_right,(float)pd_y_down,Character2[n].X,Character2[n].Y,(float)Character2Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0) DestroyCharacter2(n);
  if (Character2[n].TimeOfMove>0) Character2[n].TimeOfMove--;
  if (Character2[n].TimeOfMove==0)
  {
   Character2[n].TimeOfMove=(int)(200.0*rand()/RAND_MAX+10);
   Character2[n].ModeOfMove=(int)(11.0*rand()/RAND_MAX);
  }
 }
}
void CHARACTERMAP::DestroyAllCharacter2(void)
{
 for(int n=0;n<CurrentCharacter2;n++)
 {
  if (Character2[n].LifeMode!=2 && Character2[n].LifeMode!=1) continue;
  DestroyCharacter2(n);
 }
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void CHARACTERMAP::LoadCharacter3Sprite(void)
{
 int frame_size_x;
 int frame_size_y;
 int blend_color_r;
 int blend_color_g;
 int blend_color_b;
 if (!GetParameters("bitmap\\t3.txt","FRAME_SIZE_X:",&frame_size_x)) return;
 if (!GetParameters("bitmap\\t3.txt","FRAME_SIZE_Y:",&frame_size_y)) return;
 if (!GetParameters("bitmap\\t3.txt","BLEND_COLOR_R:",&blend_color_r)) return;
 if (!GetParameters("bitmap\\t3.txt","BLEND_COLOR_G:",&blend_color_g)) return;
 if (!GetParameters("bitmap\\t3.txt","BLEND_COLOR_B:",&blend_color_b)) return;
 if (!GetParameters("bitmap\\t3.txt","BIRTH_FRAME_START:",&Character3_Birth_Frame_Start)) return;
 if (!GetParameters("bitmap\\t3.txt","BIRTH_FRAME_END:",&Character3_Birth_Frame_End)) return;
 if (!GetParameters("bitmap\\t3.txt","LIFE_FRAME_START:",&Character3_Life_Frame_Start)) return;
 if (!GetParameters("bitmap\\t3.txt","LIFE_FRAME_END:",&Character3_Life_Frame_End)) return;
 if (!GetParameters("bitmap\\t3.txt","DESTRUCTION_FRAME_START:",&Character3_Destruction_Frame_Start)) return;
 if (!GetParameters("bitmap\\t3.txt","DESTRUCTION_FRAME_END:",&Character3_Destruction_Frame_End)) return;
 Character3Sprite.Load("bitmap\\t3.bmp");
 Character3Sprite.SetSpriteSize(frame_size_x,frame_size_y);
 Character3Sprite.SetBlendColor(blend_color_r,blend_color_g,blend_color_b);
 Character3Radius=(float)frame_size_x/2;
 if (Character3Radius<frame_size_y/2) Character3Radius=(float)frame_size_y/2;
}
void CHARACTERMAP::CreateNewCharacter3(int x,int y)
{
 if (CurrentCharacter3>=3 || GameParameters.EnableCharacter[3]==0) return;
 Sound.PlaySound(SOUND__BIRTH,0,GameParameters.SoundVolume);
 Character3[CurrentCharacter3].X=(float)x;
 Character3[CurrentCharacter3].Y=(float)y;
 Character3[CurrentCharacter3].CurrentImage=Character3_Birth_Frame_Start-1;
 Character3[CurrentCharacter3].ChangeImage=1;
 Character3[CurrentCharacter3].LifeMode=1;

 Character3[CurrentCharacter3].TimeOfLife=(int)(5000.0*rand()/RAND_MAX+500);
 Character3[CurrentCharacter3].TimeOfMove=0;
 Character3[CurrentCharacter3].ModeOfMove=0;
 CurrentCharacter3++;
}
void CHARACTERMAP::DestroyCharacter3(int character)
{
 Character3[character].CurrentImage=Character3_Destruction_Frame_Start-1;
 Character3[character].ChangeImage=1;
 Character3[character].LifeMode=3;
}
void CHARACTERMAP::DeleteCharacter3(int character)
{
 for(int n=character+1;n<CurrentCharacter3;n++) Character3[n-1]=Character3[n];
 CurrentCharacter3--;
}
void CHARACTERMAP::AnimateCharacter3(void)
{
 if (Step!=0) return;
 for(int n=0;n<CurrentCharacter3;n++)
 {
  if (Character3[n].LifeMode==0)
  {
   DeleteCharacter3(n);
   n--;
   continue;
  }
  Character3[n].CurrentImage+=Character3[n].ChangeImage;
  if (Character3[n].LifeMode==1)
  {
   if (Character3[n].CurrentImage==Character3_Birth_Frame_End-1)
   {
    Character3[n].LifeMode=2;
    Character3[n].CurrentImage=Character3_Life_Frame_Start-1;
	continue;
   }
  }
  if (Character3[n].LifeMode==2)
  {
   if (Character3[n].CurrentImage==Character3_Life_Frame_End-1) Character3[n].CurrentImage=Character3_Life_Frame_Start-1;
   continue;
  }
  if (Character3[n].LifeMode==3)
  {
   if (Character3[n].CurrentImage==Character3_Destruction_Frame_End-1) Character3[n].LifeMode=0;
   continue;
  }
 }
}
void CHARACTERMAP::PutCharacter3(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 for(int n=0;n<CurrentCharacter3;n++)
 {
  Character3Sprite.SetSpriteCoord(0,Character3[n].CurrentImage);
  Character3Sprite.Put((int)Character3[n].X-(int)Character3Radius,(int)Character3[n].Y-(int)Character3Radius,lpddssurface,ddsd);
 }
}
void CHARACTERMAP::MoveCharacter3(void)
{
 int pd_x_left=(int)(Paddle.GetX()-Paddle.GetWidth()/2+9);
 int pd_x_right=(int)(Paddle.GetX()+Paddle.GetWidth()/2-9);
 int pd_y_up=(int)(Paddle.GetY()-Paddle.GetHeight()/2);
 int pd_y_down=(int)(Paddle.GetY()+Paddle.GetHeight()/2);
 for(int n=0;n<CurrentCharacter3;n++)
 {
  if (Character3[n].LifeMode!=2) continue;
  Character3[n].TimeOfLife--;
  if (Character3[n].TimeOfLife==0)//время жизни персонажа закончилось
  {
   DestroyCharacter3(n); 
   continue;
  }
  float new_x=Character3[n].X;
  float new_y=Character3[n].Y;
  if (Character3[n].ModeOfMove>=1 && Character3[n].ModeOfMove<=5)//держимся от мячей на некотором расстоянии
  {
   int selectball=BallMap.GetNearestBallNumber(new_x,new_y);
   if (selectball>=0)
   {
    float bx,by;
    BallMap.GetBallCoord(selectball,&bx,&by);
	float dist=(float)sqrt((bx-new_x)*(bx-new_x)+(by-new_y)*(by-new_y));
	if (dist<300)
	{
	 if (new_x>bx) new_x+=(float)0.3;
     if (new_x<bx) new_x-=(float)0.3;
     if (new_y>by) new_y+=(float)0.3;
     if (new_y<by) new_y-=(float)0.3;
	}
	else
	{
	 if (new_x>bx) new_x-=(float)0.3;
     if (new_x<bx) new_x+=(float)0.3;
     if (new_y>by) new_y-=(float)0.3;
     if (new_y<by) new_y+=(float)0.3;
	}
   }
  }
  //Проверка столкновения со стенками
  int face1=CircleIntercectionToLine(0,72,640,72,new_x,new_y,(float)Character3Radius);//верхняя
  int face2=CircleIntercectionToLine(0,452,640,452,new_x,new_y,(float)Character3Radius);//нижняя
  int face3=CircleIntercectionToLine(23,0,23,480,new_x,new_y,(float)Character3Radius);//левая
  int face4=CircleIntercectionToLine(630,0,630,480,new_x,new_y,(float)Character3Radius);//правая
  if (face1+face2+face3+face4!=0) Character3[n].TimeOfMove=0;
  else 
  {
   Character3[n].X=new_x;
   Character3[n].Y=new_y;
  }
  //проверка столкновения с биткой
  int pd_face1=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_right,(float)pd_y_up,Character3[n].X,Character3[n].Y,(float)Character3Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_down,(float)pd_x_right,(float)pd_y_down,Character3[n].X,Character3[n].Y,(float)Character3Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_left,(float)pd_y_down,Character3[n].X,Character3[n].Y,(float)Character3Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)pd_x_right,(float)pd_y_up,(float)pd_x_right,(float)pd_y_down,Character3[n].X,Character3[n].Y,(float)Character3Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0) DestroyCharacter3(n);
  if (Character3[n].TimeOfMove>0) Character3[n].TimeOfMove--;
  if (Character3[n].TimeOfMove==0)
  {
   Character3[n].TimeOfMove=(int)(200.0*rand()/RAND_MAX+10);
   Character3[n].ModeOfMove=(int)(6.0*rand()/RAND_MAX);
  }
 }
}
void CHARACTERMAP::DestroyAllCharacter3(void)
{
 for(int n=0;n<CurrentCharacter3;n++)
 {
  if (Character3[n].LifeMode!=2 && Character3[n].LifeMode!=1) continue;
  DestroyCharacter3(n);
 }
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void CHARACTERMAP::LoadCharacter4Sprite(void)
{
 int frame_size_x;
 int frame_size_y;
 int blend_color_r;
 int blend_color_g;
 int blend_color_b;
 if (!GetParameters("bitmap\\t4.txt","FRAME_SIZE_X:",&frame_size_x)) return;
 if (!GetParameters("bitmap\\t4.txt","FRAME_SIZE_Y:",&frame_size_y)) return;
 if (!GetParameters("bitmap\\t4.txt","BLEND_COLOR_R:",&blend_color_r)) return;
 if (!GetParameters("bitmap\\t4.txt","BLEND_COLOR_G:",&blend_color_g)) return;
 if (!GetParameters("bitmap\\t4.txt","BLEND_COLOR_B:",&blend_color_b)) return;
 if (!GetParameters("bitmap\\t4.txt","BIRTH_FRAME_START:",&Character4_Birth_Frame_Start)) return;
 if (!GetParameters("bitmap\\t4.txt","BIRTH_FRAME_END:",&Character4_Birth_Frame_End)) return;
 if (!GetParameters("bitmap\\t4.txt","LIFE_FRAME_START:",&Character4_Life_Frame_Start)) return;
 if (!GetParameters("bitmap\\t4.txt","LIFE_FRAME_END:",&Character4_Life_Frame_End)) return;
 if (!GetParameters("bitmap\\t4.txt","DESTRUCTION_FRAME_START:",&Character4_Destruction_Frame_Start)) return;
 if (!GetParameters("bitmap\\t4.txt","DESTRUCTION_FRAME_END:",&Character4_Destruction_Frame_End)) return;
 Character4Sprite.Load("bitmap\\t4.bmp");
 Character4Sprite.SetSpriteSize(frame_size_x,frame_size_y);
 Character4Sprite.SetBlendColor(blend_color_r,blend_color_g,blend_color_b);
 Character4Radius=(float)frame_size_x/2;
 if (Character4Radius<frame_size_y/2) Character4Radius=(float)frame_size_y/2;
}
void CHARACTERMAP::CreateNewCharacter4(int x,int y)
{
 if (CurrentCharacter4>=3 || GameParameters.EnableCharacter[4]==0) return;
 Sound.PlaySound(SOUND__BIRTH,0,GameParameters.SoundVolume);
 Character4[CurrentCharacter4].X=(float)x;
 Character4[CurrentCharacter4].Y=(float)y;
 Character4[CurrentCharacter4].CurrentImage=Character4_Birth_Frame_Start-1;
 Character4[CurrentCharacter4].ChangeImage=1;
 Character4[CurrentCharacter4].LifeMode=1;

 Character4[CurrentCharacter4].TimeOfLife=(int)(5000.0*rand()/RAND_MAX+500);
 Character4[CurrentCharacter4].ModeOfMove=0;
 CurrentCharacter4++;
}
void CHARACTERMAP::DestroyCharacter4(int character)
{
 Character4[character].CurrentImage=Character4_Destruction_Frame_Start-1;
 Character4[character].ChangeImage=1;
 Character4[character].LifeMode=3;
}
void CHARACTERMAP::DeleteCharacter4(int character)
{
 for(int n=character+1;n<CurrentCharacter4;n++) Character4[n-1]=Character4[n];
 CurrentCharacter4--;
}
void CHARACTERMAP::AnimateCharacter4(void)
{
 if (Step!=0) return;
 for(int n=0;n<CurrentCharacter4;n++)
 {
  if (Character4[n].LifeMode==0)
  {
   DeleteCharacter4(n);
   n--;
   continue;
  }
  Character4[n].CurrentImage+=Character4[n].ChangeImage;
  if (Character4[n].LifeMode==1)
  {
   if (Character4[n].CurrentImage==Character4_Birth_Frame_End-1)
   {
    Character4[n].LifeMode=2;
    Character4[n].CurrentImage=Character4_Life_Frame_Start-1;
	continue;
   }
  }
  if (Character4[n].LifeMode==2)
  {
   if (Character4[n].CurrentImage==Character4_Life_Frame_End-1) Character4[n].ChangeImage=-1;
   if (Character4[n].CurrentImage==Character4_Life_Frame_Start-1) Character4[n].ChangeImage=1;
   continue;
  }
  if (Character4[n].LifeMode==3)
  {
   if (Character4[n].CurrentImage==Character4_Destruction_Frame_End-1) Character4[n].LifeMode=0;
   continue;
  }
 }
}
void CHARACTERMAP::PutCharacter4(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 for(int n=0;n<CurrentCharacter4;n++)
 {
  Character4Sprite.SetSpriteCoord(0,Character4[n].CurrentImage);
  Character4Sprite.Put((int)Character4[n].X-(int)Character4Radius,(int)Character4[n].Y-(int)Character4Radius,lpddssurface,ddsd);
 }
}
void CHARACTERMAP::MoveCharacter4(void)
{
 int pd_x_left=(int)(Paddle.GetX()-Paddle.GetWidth()/2+9);
 int pd_x_right=(int)(Paddle.GetX()+Paddle.GetWidth()/2-9);
 int pd_y_up=(int)(Paddle.GetY()-Paddle.GetHeight()/2);
 int pd_y_down=(int)(Paddle.GetY()+Paddle.GetHeight()/2);
 for(int n=0;n<CurrentCharacter4;n++)
 {
  if (Character4[n].LifeMode!=2) continue;
  Character4[n].TimeOfLife--;
  if (Character4[n].TimeOfLife==0)//время жизни персонажа закончилось
  {
   DestroyCharacter4(n); 
   continue;
  }
  float new_x=Character4[n].X;
  float new_y=Character4[n].Y;
  if (Character4[n].ModeOfMove==0)//ждём, пока мяч подлетит к нам на некоторое расстояние
  {
   int selectball=BallMap.GetNearestBallNumber(new_x,new_y);
   if (selectball>=0)
   {
    float bx,by;
    BallMap.GetBallCoord(selectball,&bx,&by);
	float dist2=(bx-new_x)*(bx-new_x)+(by-new_y)*(by-new_y);
	if (dist2<150*150) Character4[n].ModeOfMove=1;
    continue;
   }
  }
  if (Character4[n].ModeOfMove==1)//атакуем мяч
  {
   int selectball=BallMap.GetNearestBallNumber(new_x,new_y);
   if (selectball>=0)
   {
    float bx,by;
    BallMap.GetBallCoord(selectball,&bx,&by);
    if (new_x>bx) new_x-=(float)1.5;
    if (new_x<bx) new_x+=(float)1.5;
    if (new_y>by) new_y-=(float)1.5;
    if (new_y<by) new_y+=(float)1.5;
   }
  }
  //Проверка столкновения со стенками
  int face1=CircleIntercectionToLine(0,72,640,72,new_x,new_y,(float)Character4Radius);//верхняя
  int face2=CircleIntercectionToLine(0,452,640,452,new_x,new_y,(float)Character4Radius);//нижняя
  int face3=CircleIntercectionToLine(23,0,23,480,new_x,new_y,(float)Character4Radius);//левая
  int face4=CircleIntercectionToLine(630,0,630,480,new_x,new_y,(float)Character4Radius);//правая
  if (face1+face2+face3+face4==0)
  {
   Character4[n].X=new_x;
   Character4[n].Y=new_y;
  }
  //проверка столкновения с биткой
  int pd_face1=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_right,(float)pd_y_up,Character4[n].X,Character4[n].Y,(float)Character4Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_down,(float)pd_x_right,(float)pd_y_down,Character4[n].X,Character4[n].Y,(float)Character4Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_left,(float)pd_y_down,Character4[n].X,Character4[n].Y,(float)Character4Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)pd_x_right,(float)pd_y_up,(float)pd_x_right,(float)pd_y_down,Character4[n].X,Character4[n].Y,(float)Character4Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0) DestroyCharacter4(n);
 }
}
void CHARACTERMAP::DestroyAllCharacter4(void)
{
 for(int n=0;n<CurrentCharacter4;n++)
 {
  if (Character4[n].LifeMode!=2 && Character4[n].LifeMode!=1) continue;
  DestroyCharacter4(n);
 }
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void CHARACTERMAP::LoadCharacter5Sprite(void)
{
 int frame_size_x;
 int frame_size_y;
 int blend_color_r;
 int blend_color_g;
 int blend_color_b;
 if (!GetParameters("bitmap\\t5.txt","FRAME_SIZE_X:",&frame_size_x)) return;
 if (!GetParameters("bitmap\\t5.txt","FRAME_SIZE_Y:",&frame_size_y)) return;
 if (!GetParameters("bitmap\\t5.txt","BLEND_COLOR_R:",&blend_color_r)) return;
 if (!GetParameters("bitmap\\t5.txt","BLEND_COLOR_G:",&blend_color_g)) return;
 if (!GetParameters("bitmap\\t5.txt","BLEND_COLOR_B:",&blend_color_b)) return;
 if (!GetParameters("bitmap\\t5.txt","BIRTH_FRAME_START:",&Character5_Birth_Frame_Start)) return;
 if (!GetParameters("bitmap\\t5.txt","BIRTH_FRAME_END:",&Character5_Birth_Frame_End)) return;
 if (!GetParameters("bitmap\\t5.txt","LIFE_FRAME_START:",&Character5_Life_Frame_Start)) return;
 if (!GetParameters("bitmap\\t5.txt","LIFE_FRAME_END:",&Character5_Life_Frame_End)) return;
 if (!GetParameters("bitmap\\t5.txt","DESTRUCTION_FRAME_START:",&Character5_Destruction_Frame_Start)) return;
 if (!GetParameters("bitmap\\t5.txt","DESTRUCTION_FRAME_END:",&Character5_Destruction_Frame_End)) return;
 Character5Sprite.Load("bitmap\\t5.bmp");
 Character5Sprite.SetSpriteSize(frame_size_x,frame_size_y);
 Character5Sprite.SetBlendColor(blend_color_r,blend_color_g,blend_color_b);
 Character5Radius=(float)frame_size_x/2;
 if (Character5Radius<frame_size_y/2) Character5Radius=(float)frame_size_y/2;
}
void CHARACTERMAP::CreateNewCharacter5(int x,int y)
{
 if (CurrentCharacter5>=3 || GameParameters.EnableCharacter[5]==0) return;
 Sound.PlaySound(SOUND__BIRTH,0,GameParameters.SoundVolume);
 Character5[CurrentCharacter5].X=(float)x;
 Character5[CurrentCharacter5].Y=(float)y;
 Character5[CurrentCharacter5].CurrentImage=Character5_Birth_Frame_Start-1;
 Character5[CurrentCharacter5].ChangeImage=1;
 Character5[CurrentCharacter5].LifeMode=1;

 Character5[CurrentCharacter5].TimeOfLife=(int)(5000.0*rand()/RAND_MAX+500);
 Character5[CurrentCharacter5].TimeOfMove=0;
 Character5[CurrentCharacter5].ModeOfMove=0;
 CurrentCharacter5++;
}
void CHARACTERMAP::DestroyCharacter5(int character)
{
 Character5[character].CurrentImage=Character5_Destruction_Frame_Start-1;
 Character5[character].ChangeImage=1;
 Character5[character].LifeMode=3;
}
void CHARACTERMAP::DeleteCharacter5(int character)
{
 for(int n=character+1;n<CurrentCharacter5;n++) Character5[n-1]=Character5[n];
 CurrentCharacter5--;
}
void CHARACTERMAP::AnimateCharacter5(void)
{
 if (Step!=0) return;
 for(int n=0;n<CurrentCharacter5;n++)
 {
  if (Character5[n].LifeMode==0)
  {
   DeleteCharacter5(n);
   n--;
   continue;
  }
  Character5[n].CurrentImage+=Character5[n].ChangeImage;
  if (Character5[n].LifeMode==1)
  {
   if (Character5[n].CurrentImage==Character5_Birth_Frame_End-1)
   {
    Character5[n].LifeMode=2;
    Character5[n].CurrentImage=Character5_Life_Frame_Start-1;
	continue;
   }
  }
  if (Character5[n].LifeMode==2)
  {
   if (Character5[n].CurrentImage==Character5_Life_Frame_End-1) Character5[n].ChangeImage=-1;
   if (Character5[n].CurrentImage==Character5_Life_Frame_Start-1) Character5[n].ChangeImage=1;
   continue;
  }
  if (Character5[n].LifeMode==3)
  {
   if (Character5[n].CurrentImage==Character5_Destruction_Frame_End-1) Character5[n].LifeMode=0;
   continue;
  }
 }
}
void CHARACTERMAP::PutCharacter5(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 for(int n=0;n<CurrentCharacter5;n++)
 {
  Character5Sprite.SetSpriteCoord(0,Character5[n].CurrentImage);
  Character5Sprite.Put((int)Character5[n].X-(int)Character5Radius,(int)Character5[n].Y-(int)Character5Radius,lpddssurface,ddsd);
 }
}
void CHARACTERMAP::MoveCharacter5(void)
{
 int pd_x_left=(int)(Paddle.GetX()-Paddle.GetWidth()/2+9);
 int pd_x_right=(int)(Paddle.GetX()+Paddle.GetWidth()/2-9);
 int pd_y_up=(int)(Paddle.GetY()-Paddle.GetHeight()/2);
 int pd_y_down=(int)(Paddle.GetY()+Paddle.GetHeight()/2);
 for(int n=0;n<CurrentCharacter5;n++)
 {
  if (Character5[n].LifeMode!=2) continue;
  Character5[n].TimeOfLife--;
  if (Character5[n].TimeOfLife==0)//время жизни персонажа закончилось
  {
   DestroyCharacter5(n); 
   continue;
  }
  float new_x=Character5[n].X;
  float new_y=Character5[n].Y;
  if (Character5[n].ModeOfMove==1) new_x--;
  if (Character5[n].ModeOfMove==2) new_x++;
  if (Character5[n].ModeOfMove==3) new_y--;
  if (Character5[n].ModeOfMove==4) new_y++;
  //Проверка столкновения со стенками
  int face1=CircleIntercectionToLine(0,72,640,72,new_x,new_y,(float)Character5Radius);//верхняя
  int face2=CircleIntercectionToLine(0,452,640,452,new_x,new_y,(float)Character5Radius);//нижняя
  int face3=CircleIntercectionToLine(23,0,23,480,new_x,new_y,(float)Character5Radius);//левая
  int face4=CircleIntercectionToLine(630,0,630,480,new_x,new_y,(float)Character5Radius);//правая
  if (face1+face2+face3+face4!=0) Character5[n].TimeOfMove=0;
  else 
  {
   Character5[n].X=new_x;
   Character5[n].Y=new_y;
  }
  //проверка столкновения с биткой
  int pd_face1=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_right,(float)pd_y_up,Character5[n].X,Character5[n].Y,(float)Character5Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_down,(float)pd_x_right,(float)pd_y_down,Character5[n].X,Character5[n].Y,(float)Character5Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_left,(float)pd_y_down,Character5[n].X,Character5[n].Y,(float)Character5Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)pd_x_right,(float)pd_y_up,(float)pd_x_right,(float)pd_y_down,Character5[n].X,Character5[n].Y,(float)Character5Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0) DestroyCharacter5(n);
  if (Character5[n].TimeOfMove>0) Character5[n].TimeOfMove--;
  if (Character5[n].TimeOfMove==0)
  {
   Character5[n].TimeOfMove=(int)(200.0*rand()/RAND_MAX+10);
   Character5[n].ModeOfMove=(int)(5.0*rand()/RAND_MAX);
  }
 }
}
void CHARACTERMAP::DestroyAllCharacter5(void)
{
 for(int n=0;n<CurrentCharacter5;n++)
 {
  if (Character5[n].LifeMode!=2 && Character5[n].LifeMode!=1) continue;
  DestroyCharacter5(n);
 }
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void CHARACTERMAP::LoadCharacter6Sprite(void)
{
 int frame_size_x;
 int frame_size_y;
 int blend_color_r;
 int blend_color_g;
 int blend_color_b;
 if (!GetParameters("bitmap\\t6.txt","FRAME_SIZE_X:",&frame_size_x)) return;
 if (!GetParameters("bitmap\\t6.txt","FRAME_SIZE_Y:",&frame_size_y)) return;
 if (!GetParameters("bitmap\\t6.txt","BLEND_COLOR_R:",&blend_color_r)) return;
 if (!GetParameters("bitmap\\t6.txt","BLEND_COLOR_G:",&blend_color_g)) return;
 if (!GetParameters("bitmap\\t6.txt","BLEND_COLOR_B:",&blend_color_b)) return;
 if (!GetParameters("bitmap\\t6.txt","BIRTH_FRAME_START:",&Character6_Birth_Frame_Start)) return;
 if (!GetParameters("bitmap\\t6.txt","BIRTH_FRAME_END:",&Character6_Birth_Frame_End)) return;
 if (!GetParameters("bitmap\\t6.txt","LIFE_FRAME_START:",&Character6_Life_Frame_Start)) return;
 if (!GetParameters("bitmap\\t6.txt","LIFE_FRAME_END:",&Character6_Life_Frame_End)) return;
 if (!GetParameters("bitmap\\t6.txt","DESTRUCTION_FRAME_START:",&Character6_Destruction_Frame_Start)) return;
 if (!GetParameters("bitmap\\t6.txt","DESTRUCTION_FRAME_END:",&Character6_Destruction_Frame_End)) return;
 Character6Sprite.Load("bitmap\\t6.bmp");
 Character6Sprite.SetSpriteSize(frame_size_x,frame_size_y);
 Character6Sprite.SetBlendColor(blend_color_r,blend_color_g,blend_color_b);
 Character6Radius=(float)frame_size_x/2;
 if (Character6Radius<frame_size_y/2) Character6Radius=(float)frame_size_y/2;
}
void CHARACTERMAP::CreateNewCharacter6(int x,int y)
{
 if (CurrentCharacter6>=3 || GameParameters.EnableCharacter[6]==0) return;
 Sound.PlaySound(SOUND__BIRTH,0,GameParameters.SoundVolume);
 Character6[CurrentCharacter6].X=(float)x;
 Character6[CurrentCharacter6].Y=(float)y;
 Character6[CurrentCharacter6].CurrentImage=Character6_Birth_Frame_Start-1;
 Character6[CurrentCharacter6].ChangeImage=1;
 Character6[CurrentCharacter6].LifeMode=1;

 Character6[CurrentCharacter6].TimeOfLife=(int)(5000.0*rand()/RAND_MAX+500);
 Character5[CurrentCharacter5].TimeOfMove=0;
 Character6[CurrentCharacter6].ModeOfMove=0;
 CurrentCharacter6++;
}
void CHARACTERMAP::DestroyCharacter6(int character)
{
 Character6[character].CurrentImage=Character6_Destruction_Frame_Start-1;
 Character6[character].ChangeImage=1;
 Character6[character].LifeMode=3;
}
void CHARACTERMAP::DeleteCharacter6(int character)
{
 for(int n=character+1;n<CurrentCharacter6;n++) Character6[n-1]=Character6[n];
 CurrentCharacter6--;
}
void CHARACTERMAP::AnimateCharacter6(void)
{
 if (Step!=0) return;
 for(int n=0;n<CurrentCharacter6;n++)
 {
  if (Character6[n].LifeMode==0)
  {
   DeleteCharacter6(n);
   n--;
   continue;
  }
  Character6[n].CurrentImage+=Character6[n].ChangeImage;
  if (Character6[n].LifeMode==1)
  {
   if (Character6[n].CurrentImage==Character6_Birth_Frame_End-1)
   {
    Character6[n].LifeMode=2;
    Character6[n].CurrentImage=Character6_Life_Frame_Start-1;
	continue;
   }
  }
  if (Character6[n].LifeMode==2)
  {
   if (Character6[n].CurrentImage==Character6_Life_Frame_End-1) Character6[n].ChangeImage=-1;
   if (Character6[n].CurrentImage==Character6_Life_Frame_Start-1) Character6[n].ChangeImage=1;
   continue;
  }
  if (Character6[n].LifeMode==3)
  {
   if (Character6[n].CurrentImage==Character6_Destruction_Frame_End-1) Character6[n].LifeMode=0;
   continue;
  }
 }
}
void CHARACTERMAP::PutCharacter6(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 for(int n=0;n<CurrentCharacter6;n++)
 {
  Character6Sprite.SetSpriteCoord(0,Character6[n].CurrentImage);
  Character6Sprite.Put((int)Character6[n].X-(int)Character6Radius,(int)Character6[n].Y-(int)Character6Radius,lpddssurface,ddsd);
 }
}
void CHARACTERMAP::MoveCharacter6(void)
{
 int pd_x_left=(int)(Paddle.GetX()-Paddle.GetWidth()/2+9);
 int pd_x_right=(int)(Paddle.GetX()+Paddle.GetWidth()/2-9);
 int pd_y_up=(int)(Paddle.GetY()-Paddle.GetHeight()/2);
 int pd_y_down=(int)(Paddle.GetY()+Paddle.GetHeight()/2);
 for(int n=0;n<CurrentCharacter6;n++)
 {
  if (Character6[n].LifeMode!=2) continue;
  Character6[n].TimeOfLife--;
  if (Character6[n].TimeOfLife==0)//время жизни персонажа закончилось
  {
   DestroyCharacter6(n); 
   continue;
  }
  float new_x=Character6[n].X;
  float new_y=Character6[n].Y;
  if (Character6[n].ModeOfMove==0)//идём к битке
  {
   if (new_x<560) new_x++;
   else 
   {
    Character6[n].TimeOfMove=(int)(50.0*rand()/RAND_MAX+10);
    Character6[n].ModeOfMove=1;//стоим
   }
  }
  if (Character6[n].ModeOfMove==2) new_y--;
  if (Character6[n].ModeOfMove==3) new_y++;
  if (Character6[n].ModeOfMove==4) new_x--;
  if (Character6[n].ModeOfMove==5) new_x++;
  if (Character6[n].ModeOfMove>=6 && Character6[n].ModeOfMove<=8) //бегаем за мячом
  {
   int selectball=BallMap.GetNearestBallNumber(new_x,new_y);
   if (selectball>=0)
   {
    float bx,by;
    BallMap.GetBallCoord(selectball,&bx,&by);
	if (by>new_y) new_y++;
	if (by<new_y) new_y--;
   }
  }
  //Проверка столкновения со стенками
  int face1=CircleIntercectionToLine(0,72,640,72,new_x,new_y,(float)Character6Radius);//верхняя
  int face2=CircleIntercectionToLine(0,452,640,452,new_x,new_y,(float)Character6Radius);//нижняя
  int face3=CircleIntercectionToLine(23,0,23,480,new_x,new_y,(float)Character6Radius);//левая
  int face4=CircleIntercectionToLine(630,0,630,480,new_x,new_y,(float)Character6Radius);//правая
  if (face1+face2+face3+face4!=0) Character6[n].TimeOfMove=0;
  else 
  {
   Character6[n].X=new_x;
   Character6[n].Y=new_y;
  }
  //проверка столкновения с биткой
  int pd_face1=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_right,(float)pd_y_up,Character6[n].X,Character6[n].Y,(float)Character6Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_down,(float)pd_x_right,(float)pd_y_down,Character6[n].X,Character6[n].Y,(float)Character6Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_left,(float)pd_y_down,Character6[n].X,Character6[n].Y,(float)Character6Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)pd_x_right,(float)pd_y_up,(float)pd_x_right,(float)pd_y_down,Character6[n].X,Character6[n].Y,(float)Character6Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0) DestroyCharacter6(n);
  if (Character6[n].TimeOfMove>0 && Character6[n].ModeOfMove!=0) Character6[n].TimeOfMove--;
  if (Character6[n].TimeOfMove==0 && Character6[n].ModeOfMove!=0)
  {
   Character6[n].ModeOfMove=(int)(8.0*rand()/RAND_MAX);
   if (Character6[n].ModeOfMove==4 || Character6[n].ModeOfMove==5) Character6[n].TimeOfMove=(int)(20.0*rand()/RAND_MAX+10);
                                                              else Character6[n].TimeOfMove=(int)(200.0*rand()/RAND_MAX+10);
  }
 }
}
void CHARACTERMAP::DestroyAllCharacter6(void)
{
 for(int n=0;n<CurrentCharacter6;n++)
 {
  if (Character6[n].LifeMode!=2 && Character6[n].LifeMode!=1) continue;
  DestroyCharacter6(n);
 }
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void CHARACTERMAP::LoadCharacter7Sprite(void)
{
 int frame_size_x;
 int frame_size_y;
 int blend_color_r;
 int blend_color_g;
 int blend_color_b;
 if (!GetParameters("bitmap\\t7.txt","FRAME_SIZE_X:",&frame_size_x)) return;
 if (!GetParameters("bitmap\\t7.txt","FRAME_SIZE_Y:",&frame_size_y)) return;
 if (!GetParameters("bitmap\\t7.txt","BLEND_COLOR_R:",&blend_color_r)) return;
 if (!GetParameters("bitmap\\t7.txt","BLEND_COLOR_G:",&blend_color_g)) return;
 if (!GetParameters("bitmap\\t7.txt","BLEND_COLOR_B:",&blend_color_b)) return;
 if (!GetParameters("bitmap\\t7.txt","BIRTH_FRAME_START:",&Character7_Birth_Frame_Start)) return;
 if (!GetParameters("bitmap\\t7.txt","BIRTH_FRAME_END:",&Character7_Birth_Frame_End)) return;
 if (!GetParameters("bitmap\\t7.txt","LIFE_FRAME_START:",&Character7_Life_Frame_Start)) return;
 if (!GetParameters("bitmap\\t7.txt","LIFE_FRAME_END:",&Character7_Life_Frame_End)) return;
 if (!GetParameters("bitmap\\t7.txt","DESTRUCTION_FRAME_START:",&Character7_Destruction_Frame_Start)) return;
 if (!GetParameters("bitmap\\t7.txt","DESTRUCTION_FRAME_END:",&Character7_Destruction_Frame_End)) return;
 Character7Sprite.Load("bitmap\\t7.bmp");
 Character7Sprite.SetSpriteSize(frame_size_x,frame_size_y);
 Character7Sprite.SetBlendColor(blend_color_r,blend_color_g,blend_color_b);
 Character7Radius=(float)frame_size_x/2;
 if (Character7Radius<frame_size_y/2) Character7Radius=(float)frame_size_y/2;
}
void CHARACTERMAP::CreateNewCharacter7(int x,int y)
{
 int n;
 if (CurrentCharacter7>=2 || GameParameters.EnableCharacter[7]==0) return;
 Sound.PlaySound(SOUND__BIRTH,0,GameParameters.SoundVolume);
 for(n=0;n<6;n++)
 {
  Character7[CurrentCharacter7].X[n]=(float)x;
  Character7[CurrentCharacter7].Y[n]=(float)y+Character7Radius*2*n;
  Character7[CurrentCharacter7].LifeMode[n]=1;
  Character7[CurrentCharacter7].CurrentImage[n]=(Character7_Birth_Frame_Start-1);
  Character7[CurrentCharacter7].ChangeImage[n]=1;
  Character7[CurrentCharacter7].ModeOfMove[n]=0;
  Character7[CurrentCharacter7].TimeOfMove[n]=0;
 }
 Character7[CurrentCharacter7].TimeOfLife=(int)(10000.0*rand()/RAND_MAX+1000);
 CurrentCharacter7++;
}
void CHARACTERMAP::DestroyCharacter7(int character,int segment)
{
 Character7[character].CurrentImage[segment]=Character7_Destruction_Frame_Start-1;
 Character7[character].ChangeImage[segment]=1;
 Character7[character].LifeMode[segment]=3;
}
void CHARACTERMAP::DeleteCharacter7(int character)
{
 for(int n=character+1;n<CurrentCharacter7;n++) Character7[n-1]=Character7[n];
 CurrentCharacter7--;
}
void CHARACTERMAP::AnimateCharacter7(void)
{
 int n,m;
 if (Step!=0) return;
 for(n=0;n<CurrentCharacter7;n++)
 {
  int segment=6;
  for(m=0;m<6;m++)
  {
   if (Character7[n].LifeMode[m]==0) segment--;
  }
  if (segment==0)//Все сегменты змейки разрушены
  {
   DeleteCharacter7(n);
   n--;
   continue;
  }
  for(m=0;m<6;m++)
  {
   if (Character7[n].LifeMode[m]==0) continue;
   Character7[n].CurrentImage[m]+=Character7[n].ChangeImage[m];
   if (Character7[n].LifeMode[m]==1)
   {
    if (Character7[n].CurrentImage[m]==Character7_Birth_Frame_End-1)
    {
     Character7[n].LifeMode[m]=2;
     Character7[n].CurrentImage[m]=Character7_Life_Frame_Start-1+(int)((Character7_Life_Frame_End-Character7_Life_Frame_Start)*rand())/RAND_MAX;;
     continue;
    }
   }
   if (Character7[n].LifeMode[m]==2)
   {
    if (Character7[n].CurrentImage[m]==Character7_Life_Frame_End-1) Character7[n].CurrentImage[m]=Character7_Life_Frame_Start-1;
    continue;
   }
   if (Character7[n].LifeMode[m]==3)
   {
    if (Character7[n].CurrentImage[m]==Character7_Destruction_Frame_End-1) Character7[n].LifeMode[m]=0;
    continue;
   }
  }
 }
}
void CHARACTERMAP::PutCharacter7(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 for(int n=0;n<CurrentCharacter7;n++)
 {
  for(int m=0;m<6;m++)
  {
   if (Character7[n].LifeMode[m]==0) continue;
   Character7Sprite.SetSpriteCoord(0,Character7[n].CurrentImage[m]);
   Character7Sprite.Put((int)Character7[n].X[m]-(int)Character7Radius,(int)Character7[n].Y[m]-(int)Character7Radius,lpddssurface,ddsd);
  }
 }
}
void CHARACTERMAP::MoveCharacter7(void)
{
 int n,m;
 int pd_x_left=(int)(Paddle.GetX()-Paddle.GetWidth()/2+9);
 int pd_x_right=(int)(Paddle.GetX()+Paddle.GetWidth()/2-9);
 int pd_y_up=(int)(Paddle.GetY()-Paddle.GetHeight()/2);
 int pd_y_down=(int)(Paddle.GetY()+Paddle.GetHeight()/2);
 for(n=0;n<CurrentCharacter7;n++)
 {
  int segment=6;
  for(m=0;m<6;m++)
  {
   if (Character7[n].LifeMode[m]!=2) segment--;
  }
  if (segment==0) continue;
  Character7[n].TimeOfLife--;
  if (Character7[n].TimeOfLife==0)//время жизни персонажа закончилось
  {
   for(m=0;m<6;m++)
   {
    if (Character7[n].LifeMode[m]!=2) continue;
    DestroyCharacter7(n,m); 
   }
   continue;
  }
  for(m=0;m<6;m++)
  {
   float new_x=Character7[n].X[m];
   float new_y=Character7[n].Y[m];
   //прямое направление
   if (Character7[n].ModeOfMove[m]==0) new_y--;//движемся вверх
   if (Character7[n].ModeOfMove[m]==1) new_x++;//движемся вправо
   if (Character7[n].ModeOfMove[m]==2) new_y++;//движемся вниз
   if (Character7[n].ModeOfMove[m]==3) new_x++;//движемся вправо
   //обратное направление
   if (Character7[n].ModeOfMove[m]==5) new_y--;//движемся вверх
   if (Character7[n].ModeOfMove[m]==6) new_x--;//движемся вправо
   if (Character7[n].ModeOfMove[m]==7) new_y++;//движемся вниз
   if (Character7[n].ModeOfMove[m]==8) new_x--;//движемся вправо 

   //Проверка столкновения со стенками
   int face1=CircleIntercectionToLine(0,72,640,72,new_x,new_y,(float)Character7Radius);//верхняя
   int face2=CircleIntercectionToLine(0,452,640,452,new_x,new_y,(float)Character7Radius);//нижняя
   int face3=CircleIntercectionToLine(23,0,23,480,new_x,new_y,(float)Character7Radius);//левая
   int face4=CircleIntercectionToLine(550,0,550,480,new_x,new_y,(float)Character7Radius);//правая
   if (face1+face2+face3+face4!=0)//столкнулись со стенками и нужно менять режим движения
   {
    Character7[n].ModeOfMove[m]++;
    if (Character7[n].ModeOfMove[m]==4) Character7[n].ModeOfMove[m]=0;
    if (Character7[n].ModeOfMove[m]==9) Character7[n].ModeOfMove[m]=5;
    if (Character7[n].ModeOfMove[m]==1) Character7[n].TimeOfMove[m]=80;
    if (Character7[n].ModeOfMove[m]==3) Character7[n].TimeOfMove[m]=80;
    if (Character7[n].ModeOfMove[m]==6) Character7[n].TimeOfMove[m]=80;
    if (Character7[n].ModeOfMove[m]==8) Character7[n].TimeOfMove[m]=80;
    if (face4!=0) Character7[n].ModeOfMove[m]=5;//меняем направление на обратное
    if (face3!=0) Character7[n].ModeOfMove[m]=0;
   }
   if (Character7[n].TimeOfMove[m]>0) Character7[n].TimeOfMove[m]--;
   if (Character7[n].TimeOfMove[m]==0)
   {
    if (Character7[n].ModeOfMove[m]==1) Character7[n].ModeOfMove[m]++;
    if (Character7[n].ModeOfMove[m]==3) Character7[n].ModeOfMove[m]++;
    if (Character7[n].ModeOfMove[m]==6) Character7[n].ModeOfMove[m]++;
    if (Character7[n].ModeOfMove[m]==8) Character7[n].ModeOfMove[m]++;
    if (Character7[n].ModeOfMove[m]==4) Character7[n].ModeOfMove[m]=0;
    if (Character7[n].ModeOfMove[m]==9) Character7[n].ModeOfMove[m]=5;
   }
   if (face1+face2+face3+face4==0)
   {
    Character7[n].X[m]=new_x;
    Character7[n].Y[m]=new_y;
   }
   //проверка столкновения с биткой
   if (Character7[n].LifeMode[m]!=2) continue;
   int pd_face1=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_right,(float)pd_y_up,Character7[n].X[m],Character7[n].Y[m],(float)Character7Radius);//верхняя
   int pd_face2=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_down,(float)pd_x_right,(float)pd_y_down,Character7[n].X[m],Character7[n].Y[m],(float)Character7Radius);//нижняя
   int pd_face3=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_left,(float)pd_y_down,Character7[n].X[m],Character7[n].Y[m],(float)Character7Radius);//левая
   int pd_face4=CircleIntercectionToLine((float)pd_x_right,(float)pd_y_up,(float)pd_x_right,(float)pd_y_down,Character7[n].X[m],Character7[n].Y[m],(float)Character7Radius);//правая
   if (pd_face1+pd_face2+pd_face3+pd_face4!=0) DestroyCharacter7(n,m);
  }
 }
}
void CHARACTERMAP::DestroyAllCharacter7(void)
{
 for(int n=0;n<CurrentCharacter7;n++)
 {
  for(int m=0;m<6;m++)
  {
   if (Character7[n].LifeMode[m]!=2 && Character7[n].LifeMode[m]!=1) continue;
   DestroyCharacter7(n,m);
  }
 }
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void CHARACTERMAP::LoadCharacter8Sprite(void)
{
 int frame_size_x;
 int frame_size_y;
 int blend_color_r;
 int blend_color_g;
 int blend_color_b;
 if (!GetParameters("bitmap\\t8.txt","FRAME_SIZE_X:",&frame_size_x)) return;
 if (!GetParameters("bitmap\\t8.txt","FRAME_SIZE_Y:",&frame_size_y)) return;
 if (!GetParameters("bitmap\\t8.txt","BLEND_COLOR_R:",&blend_color_r)) return;
 if (!GetParameters("bitmap\\t8.txt","BLEND_COLOR_G:",&blend_color_g)) return;
 if (!GetParameters("bitmap\\t8.txt","BLEND_COLOR_B:",&blend_color_b)) return;
 if (!GetParameters("bitmap\\t8.txt","BIRTH_FRAME_START:",&Character8_Birth_Frame_Start)) return;
 if (!GetParameters("bitmap\\t8.txt","BIRTH_FRAME_END:",&Character8_Birth_Frame_End)) return;
 if (!GetParameters("bitmap\\t8.txt","LIFE_FRAME_START:",&Character8_Life_Frame_Start)) return;
 if (!GetParameters("bitmap\\t8.txt","LIFE_FRAME_END:",&Character8_Life_Frame_End)) return;
 if (!GetParameters("bitmap\\t8.txt","DESTRUCTION_FRAME_START:",&Character8_Destruction_Frame_Start)) return;
 if (!GetParameters("bitmap\\t8.txt","DESTRUCTION_FRAME_END:",&Character8_Destruction_Frame_End)) return;
 Character8Sprite.Load("bitmap\\t8.bmp");
 Character8Sprite.SetSpriteSize(frame_size_x,frame_size_y);
 Character8Sprite.SetBlendColor(blend_color_r,blend_color_g,blend_color_b);
 Character8Radius=(float)frame_size_x/2;
 if (Character8Radius<frame_size_y/2) Character8Radius=(float)frame_size_y/2;
}
void CHARACTERMAP::CreateNewCharacter8(int x,int y)
{
 if (CurrentCharacter8>=3 || GameParameters.EnableCharacter[8]==0) return;
 Sound.PlaySound(SOUND__BIRTH,0,GameParameters.SoundVolume);
 Character8[CurrentCharacter8].X=(float)x;
 Character8[CurrentCharacter8].Y=(float)y;
 Character8[CurrentCharacter8].CurrentImage=Character8_Birth_Frame_Start-1;
 Character8[CurrentCharacter8].ChangeImage=1;
 Character8[CurrentCharacter8].LifeMode=1;

 Character8[CurrentCharacter8].TimeOfLife=(int)(5000.0*rand()/RAND_MAX+500);
 Character8[CurrentCharacter8].TimeOfMove=0;
 Character8[CurrentCharacter8].ModeOfMove=0;
 CurrentCharacter8++;
}
void CHARACTERMAP::DestroyCharacter8(int character)
{
 Character8[character].CurrentImage=Character8_Destruction_Frame_Start-1;
 Character8[character].ChangeImage=1;
 Character8[character].LifeMode=3;
}
void CHARACTERMAP::DeleteCharacter8(int character)
{
 for(int n=character+1;n<CurrentCharacter8;n++) Character8[n-1]=Character8[n];
 CurrentCharacter8--;
}
void CHARACTERMAP::AnimateCharacter8(void)
{
 if (Step!=0) return;
 for(int n=0;n<CurrentCharacter8;n++)
 {
  if (Character8[n].LifeMode==0)
  {
   DeleteCharacter8(n);
   n--;
   continue;
  }
  Character8[n].CurrentImage+=Character8[n].ChangeImage;
  if (Character8[n].LifeMode==1)
  {
   if (Character8[n].CurrentImage==Character8_Birth_Frame_End-1)
   {
    Character8[n].LifeMode=2;
    Character8[n].CurrentImage=Character8_Life_Frame_Start-1;
	continue;
   }
  }
  if (Character8[n].LifeMode==2)
  {
   if (Character8[n].CurrentImage==Character8_Life_Frame_End-1) Character8[n].CurrentImage=Character8_Life_Frame_Start-1;
   continue;
  }
  if (Character8[n].LifeMode==3)
  {
   if (Character8[n].CurrentImage==Character8_Destruction_Frame_End-1) Character8[n].LifeMode=0;
   continue;
  }
 }
}
void CHARACTERMAP::PutCharacter8(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 for(int n=0;n<CurrentCharacter8;n++)
 {
  Character8Sprite.SetSpriteCoord(0,Character8[n].CurrentImage);
  Character8Sprite.Put((int)Character8[n].X-(int)Character8Radius,(int)Character8[n].Y-(int)Character8Radius,lpddssurface,ddsd);
 }
}
void CHARACTERMAP::MoveCharacter8(void)
{
 int pd_x_left=(int)(Paddle.GetX()-Paddle.GetWidth()/2+9);
 int pd_x_right=(int)(Paddle.GetX()+Paddle.GetWidth()/2-9);
 int pd_y_up=(int)(Paddle.GetY()-Paddle.GetHeight()/2);
 int pd_y_down=(int)(Paddle.GetY()+Paddle.GetHeight()/2);
 for(int n=0;n<CurrentCharacter8;n++)
 {
  if (Character8[n].LifeMode!=2) continue;
  Character8[n].TimeOfLife--;
  if (Character8[n].TimeOfLife==0)//время жизни персонажа закончилось
  {
   DestroyCharacter8(n); 
   continue;
  }
  float new_x=Character8[n].X;
  float new_y=Character8[n].Y;
  if (Character8[n].ModeOfMove==1) new_x--;
  if (Character8[n].ModeOfMove==2) new_x++;
  if (Character8[n].ModeOfMove==3) new_y--;
  if (Character8[n].ModeOfMove==4) new_y++;
  //Проверка столкновения со стенками
  int face1=CircleIntercectionToLine(0,72,640,72,new_x,new_y,(float)Character8Radius);//верхняя
  int face2=CircleIntercectionToLine(0,452,640,452,new_x,new_y,(float)Character8Radius);//нижняя
  int face3=CircleIntercectionToLine(23,0,23,480,new_x,new_y,(float)Character8Radius);//левая
  int face4=CircleIntercectionToLine(630,0,630,480,new_x,new_y,(float)Character8Radius);//правая
  if (face1+face2+face3+face4!=0) Character8[n].TimeOfMove=0;
  else 
  {
   Character8[n].X=new_x;
   Character8[n].Y=new_y;
  }
  //проверка столкновения с биткой
  int pd_face1=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_right,(float)pd_y_up,Character8[n].X,Character8[n].Y,(float)Character8Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_down,(float)pd_x_right,(float)pd_y_down,Character8[n].X,Character8[n].Y,(float)Character8Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_left,(float)pd_y_down,Character8[n].X,Character8[n].Y,(float)Character8Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)pd_x_right,(float)pd_y_up,(float)pd_x_right,(float)pd_y_down,Character8[n].X,Character8[n].Y,(float)Character8Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0) DestroyCharacter8(n);
  if (Character8[n].TimeOfMove>0) Character8[n].TimeOfMove--;
  if (Character8[n].TimeOfMove==0)
  {
   Character8[n].TimeOfMove=(int)(200.0*rand()/RAND_MAX+10);
   Character8[n].ModeOfMove=(int)(5.0*rand()/RAND_MAX);
  }
 }
}
void CHARACTERMAP::DestroyAllCharacter8(void)
{
 for(int n=0;n<CurrentCharacter8;n++)
 {
  if (Character8[n].LifeMode!=2 && Character8[n].LifeMode!=1) continue;
  DestroyCharacter8(n);
 }
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void CHARACTERMAP::LoadCharacter9Sprite(void)
{
 int frame_size_x;
 int frame_size_y;
 int blend_color_r;
 int blend_color_g;
 int blend_color_b;
 if (!GetParameters("bitmap\\t9.txt","FRAME_SIZE_X:",&frame_size_x)) return;
 if (!GetParameters("bitmap\\t9.txt","FRAME_SIZE_Y:",&frame_size_y)) return;
 if (!GetParameters("bitmap\\t9.txt","BLEND_COLOR_R:",&blend_color_r)) return;
 if (!GetParameters("bitmap\\t9.txt","BLEND_COLOR_G:",&blend_color_g)) return;
 if (!GetParameters("bitmap\\t9.txt","BLEND_COLOR_B:",&blend_color_b)) return;
 if (!GetParameters("bitmap\\t9.txt","BIRTH_FRAME_START:",&Character9_Birth_Frame_Start)) return;
 if (!GetParameters("bitmap\\t9.txt","BIRTH_FRAME_END:",&Character9_Birth_Frame_End)) return;
 if (!GetParameters("bitmap\\t9.txt","LIFE_FRAME_START:",&Character9_Life_Frame_Start)) return;
 if (!GetParameters("bitmap\\t9.txt","LIFE_FRAME_END:",&Character9_Life_Frame_End)) return;
 if (!GetParameters("bitmap\\t9.txt","DESTRUCTION_FRAME_START:",&Character9_Destruction_Frame_Start)) return;
 if (!GetParameters("bitmap\\t9.txt","DESTRUCTION_FRAME_END:",&Character9_Destruction_Frame_End)) return;
 Character9Sprite.Load("bitmap\\t9.bmp");
 Character9Sprite.SetSpriteSize(frame_size_x,frame_size_y);
 Character9Sprite.SetBlendColor(blend_color_r,blend_color_g,blend_color_b);
 Character9Radius=(float)frame_size_x/2;
 if (Character9Radius<frame_size_y/2) Character9Radius=(float)frame_size_y/2;
}
void CHARACTERMAP::CreateNewCharacter9(int x,int y)
{
 if (CurrentCharacter9>=3 || GameParameters.EnableCharacter[9]==0) return;
 Sound.PlaySound(SOUND__BIRTH,0,GameParameters.SoundVolume);
 Character9[CurrentCharacter9].X=(float)x;
 Character9[CurrentCharacter9].Y=(float)y;
 Character9[CurrentCharacter9].CurrentImage=Character9_Birth_Frame_Start-1;
 Character9[CurrentCharacter9].ChangeImage=1;
 Character9[CurrentCharacter9].LifeMode=1;

 Character9[CurrentCharacter9].TimeOfLife=(int)(5000.0*rand()/RAND_MAX+500);
 Character9[CurrentCharacter9].TimeOfMove=0;
 Character9[CurrentCharacter9].ModeOfMove=0;
 CurrentCharacter9++;
}
void CHARACTERMAP::DestroyCharacter9(int character)
{
 Character9[character].CurrentImage=Character9_Destruction_Frame_Start-1;
 Character9[character].ChangeImage=1;
 Character9[character].LifeMode=3;
}
void CHARACTERMAP::DeleteCharacter9(int character)
{
 for(int n=character+1;n<CurrentCharacter9;n++) Character9[n-1]=Character9[n];
 CurrentCharacter9--;
}
void CHARACTERMAP::AnimateCharacter9(void)
{
 if (Step!=0) return;
 for(int n=0;n<CurrentCharacter9;n++)
 {
  if (Character9[n].LifeMode==0)
  {
   DeleteCharacter9(n);
   n--;
   continue;
  }
  Character9[n].CurrentImage+=Character9[n].ChangeImage;
  if (Character9[n].LifeMode==1)
  {
   if (Character9[n].CurrentImage==Character9_Birth_Frame_End-1)
   {
    Character9[n].LifeMode=2;
    Character9[n].CurrentImage=Character9_Life_Frame_Start-1;
	continue;
   }
  }
  if (Character9[n].LifeMode==2)
  {
   if (Character9[n].CurrentImage==Character9_Life_Frame_End-1) Character9[n].CurrentImage=Character9_Life_Frame_Start-1;
   continue;
  }
  if (Character9[n].LifeMode==3)
  {
   if (Character9[n].CurrentImage==Character9_Destruction_Frame_End-1) Character9[n].LifeMode=0;
   continue;
  }
 }
}
void CHARACTERMAP::PutCharacter9(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 for(int n=0;n<CurrentCharacter9;n++)
 {
  Character9Sprite.SetSpriteCoord(0,Character9[n].CurrentImage);
  Character9Sprite.Put((int)Character9[n].X-(int)Character9Radius,(int)Character9[n].Y-(int)Character9Radius,lpddssurface,ddsd);
 }
}
void CHARACTERMAP::MoveCharacter9(void)
{
 int pd_x_left=(int)(Paddle.GetX()-Paddle.GetWidth()/2+9);
 int pd_x_right=(int)(Paddle.GetX()+Paddle.GetWidth()/2-9);
 int pd_y_up=(int)(Paddle.GetY()-Paddle.GetHeight()/2);
 int pd_y_down=(int)(Paddle.GetY()+Paddle.GetHeight()/2);
 for(int n=0;n<CurrentCharacter9;n++)
 {
  if (Character9[n].LifeMode!=2) continue;
  Character9[n].TimeOfLife--;
  if (Character9[n].TimeOfLife==0)//время жизни персонажа закончилось
  {
   DestroyCharacter9(n); 
   continue;
  }
  float new_x=Character9[n].X;
  float new_y=Character9[n].Y;
  if (Character9[n].ModeOfMove==1)
  {
   new_x--;
   new_y--;
  }
  if (Character9[n].ModeOfMove==2)
  {
   new_x--;
   new_y++;
  }
  if (Character9[n].ModeOfMove==3)
  {
   new_x++;
   new_y--;
  }
  if (Character9[n].ModeOfMove==4)
  {
   new_x++;
   new_y++;
  }
  //Проверка столкновения со стенками
  int face1=CircleIntercectionToLine(0,72,640,72,new_x,new_y,(float)Character9Radius);//верхняя
  int face2=CircleIntercectionToLine(0,452,640,452,new_x,new_y,(float)Character9Radius);//нижняя
  int face3=CircleIntercectionToLine(23,0,23,480,new_x,new_y,(float)Character9Radius);//левая
  int face4=CircleIntercectionToLine(630,0,630,480,new_x,new_y,(float)Character9Radius);//правая
  if (face1+face2+face3+face4!=0) Character9[n].TimeOfMove=0;
  else 
  {
   Character9[n].X=new_x;
   Character9[n].Y=new_y;
  }
  //проверка столкновения с биткой
  int pd_face1=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_right,(float)pd_y_up,Character9[n].X,Character9[n].Y,(float)Character9Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_down,(float)pd_x_right,(float)pd_y_down,Character9[n].X,Character9[n].Y,(float)Character9Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)pd_x_left,(float)pd_y_up,(float)pd_x_left,(float)pd_y_down,Character9[n].X,Character9[n].Y,(float)Character9Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)pd_x_right,(float)pd_y_up,(float)pd_x_right,(float)pd_y_down,Character9[n].X,Character9[n].Y,(float)Character9Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0) DestroyCharacter9(n);
  if (Character9[n].TimeOfMove>0) Character9[n].TimeOfMove--;
  if (Character9[n].TimeOfMove==0)
  {
   Character9[n].TimeOfMove=(int)(200.0*rand()/RAND_MAX+10);
   Character9[n].ModeOfMove=(int)(5.0*rand()/RAND_MAX);
  }
 }
}
void CHARACTERMAP::DestroyAllCharacter9(void)
{
 for(int n=0;n<CurrentCharacter9;n++)
 {
  if (Character9[n].LifeMode!=2 && Character9[n].LifeMode!=1) continue;
  DestroyCharacter9(n);
 }
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void CHARACTERMAP::PutAllCharacter(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 PutCharacter1(lpddssurface,ddsd);
 PutCharacter2(lpddssurface,ddsd);
 PutCharacter3(lpddssurface,ddsd);
 PutCharacter4(lpddssurface,ddsd);
 PutCharacter5(lpddssurface,ddsd);
 PutCharacter6(lpddssurface,ddsd);
 PutCharacter7(lpddssurface,ddsd);
 PutCharacter8(lpddssurface,ddsd);
 PutCharacter9(lpddssurface,ddsd);
}
void CHARACTERMAP::Processing(void)
{
 if (TimerDoStartCharacter1>0)
 {
  TimerDoStartCharacter1--;
  if (TimerDoStartCharacter1==0)
  {
   CreateNewCharacter1(500*rand()/RAND_MAX+50,300*rand()/RAND_MAX+100);
   TimerDoStartCharacter1=(int)(5000.0*rand()/RAND_MAX+500);
  }
 }
 MoveCharacter1();
 //--------------------------------------------------------------------------
 if (TimerDoStartCharacter2>0)
 {
  TimerDoStartCharacter2--;
  if (TimerDoStartCharacter2==0)
  {
   CreateNewCharacter2(500*rand()/RAND_MAX+50,300*rand()/RAND_MAX+100);
   TimerDoStartCharacter2=(int)(5000.0*rand()/RAND_MAX+500);
  }
 }
 MoveCharacter2();
 //--------------------------------------------------------------------------
 if (TimerDoStartCharacter3>0)
 {
  TimerDoStartCharacter3--;
  if (TimerDoStartCharacter3==0)
  {
   CreateNewCharacter3(500*rand()/RAND_MAX+50,300*rand()/RAND_MAX+100);
   TimerDoStartCharacter3=(int)(5000.0*rand()/RAND_MAX+500);
  }
 }
 MoveCharacter3();
 //--------------------------------------------------------------------------
 if (TimerDoStartCharacter4>0)
 {
  TimerDoStartCharacter4--;
  if (TimerDoStartCharacter4==0)
  {
   CreateNewCharacter4(500*rand()/RAND_MAX+50,300*rand()/RAND_MAX+100);
   TimerDoStartCharacter4=(int)(5000.0*rand()/RAND_MAX+500);
  }
 }
 MoveCharacter4();
 //--------------------------------------------------------------------------
 if (TimerDoStartCharacter5>0)
 {
  TimerDoStartCharacter5--;
  if (TimerDoStartCharacter5==0)
  {
   if (BallMap.GetCurrentBall()<=3) CreateNewCharacter5(500*rand()/RAND_MAX+50,300*rand()/RAND_MAX+100);
   TimerDoStartCharacter5=(int)(5000.0*rand()/RAND_MAX+500);
  }
 }
 MoveCharacter5();
 //--------------------------------------------------------------------------
 if (TimerDoStartCharacter6>0)
 {
  TimerDoStartCharacter6--;
  if (TimerDoStartCharacter6==0)
  {
   CreateNewCharacter6(500*rand()/RAND_MAX+50,300*rand()/RAND_MAX+100);
   TimerDoStartCharacter6=(int)(5000.0*rand()/RAND_MAX+500);
  }
 }
 MoveCharacter6();
 //--------------------------------------------------------------------------
 if (TimerDoStartCharacter7>0)
 {
  TimerDoStartCharacter7--;
  if (TimerDoStartCharacter7==0)
  {
   CreateNewCharacter7(50+100*rand()/RAND_MAX,450-(int)(6*Character7Radius*2));
   TimerDoStartCharacter7=(int)(5000.0*rand()/RAND_MAX+500);
  }
 }
 MoveCharacter7();
 //--------------------------------------------------------------------------
 if (TimerDoStartCharacter8>0)
 {
  TimerDoStartCharacter8--;
  if (TimerDoStartCharacter8==0)
  {
   CreateNewCharacter8(500*rand()/RAND_MAX+50,300*rand()/RAND_MAX+100);
   TimerDoStartCharacter8=(int)(5000.0*rand()/RAND_MAX+500);
  }
 }
 MoveCharacter8();
 //--------------------------------------------------------------------------
 if (TimerDoStartCharacter9>0)
 {
  TimerDoStartCharacter9--;
  if (TimerDoStartCharacter9==0)
  {
   CreateNewCharacter9(500*rand()/RAND_MAX+50,300*rand()/RAND_MAX+100);
   TimerDoStartCharacter9=(int)(5000.0*rand()/RAND_MAX+500);
  }
 }
 MoveCharacter9();
 //--------------------------------------------------------------------------
}
void CHARACTERMAP::ChangeImageFrame(void)
{
 Step++;
 Step=Step%2;
 AnimateCharacter1();
 AnimateCharacter2();
 AnimateCharacter3();
 AnimateCharacter4();
 AnimateCharacter5();
 AnimateCharacter6();
 AnimateCharacter7();
 AnimateCharacter8();
 AnimateCharacter9();
}
void CHARACTERMAP::DestroyAllCharacter(void)
{
 DestroyAllCharacter1();
 DestroyAllCharacter2();
 DestroyAllCharacter3();
 DestroyAllCharacter4();
 DestroyAllCharacter5();
 DestroyAllCharacter6();
 DestroyAllCharacter7();
 DestroyAllCharacter8();
 DestroyAllCharacter9();
}
float CHARACTERMAP::ImpactCharacterToBall(int ball_x,int ball_y,int ball_radius,float ball_angle)
{
 int n,m;
 int x,y;
 float dangle=0;
 //проверим столкновение с персонажами 1-го типа (отклоняет мяч)
 for(n=0;n<CurrentCharacter1;n++)
 {
  if (Character1[n].LifeMode!=2) continue;
  float r2=(ball_x-Character1[n].X)*(ball_x-Character1[n].X)+(ball_y-Character1[n].Y)*(ball_y-Character1[n].Y);
  if (r2<=(Character1Radius+ball_radius)*(Character1Radius+ball_radius))//есть столкновение
  {
   Sound.PlaySound(SOUND__DESTROY,0,GameParameters.SoundVolume);
   DestroyCharacter1(n);
   dangle+=(float)180.0*rand()/RAND_MAX;
  }
 }
 //проверим столкновение с персонажами 2-го типа(взрывает блоки рядом с собой)
 for(n=0;n<CurrentCharacter2;n++)
 {
  if (Character2[n].LifeMode!=2) continue;
  float r2=(ball_x-Character2[n].X)*(ball_x-Character2[n].X)+(ball_y-Character2[n].Y)*(ball_y-Character2[n].Y);
  if (r2<=(Character2Radius+ball_radius)*(Character2Radius+ball_radius))//есть столкновение
  {
   ExplosionCharacter2(n);
   int x=(int)(Character2[n].X-23)/20;
   int y=(int)(Character2[n].Y-82)/30;
   BlockMap.ExplosionBlock(x,y);
  }
 }
 //проверим столкновение с персонажами 3-го типа (отклоняет мяч в сторону битки и даёт очки)
 for(n=0;n<CurrentCharacter3;n++)
 {
  if (Character3[n].LifeMode!=2) continue;
  float r2=(ball_x-Character3[n].X)*(ball_x-Character3[n].X)+(ball_y-Character3[n].Y)*(ball_y-Character3[n].Y);
  if (r2<=(Character3Radius+ball_radius)*(Character3Radius+ball_radius))//есть столкновение
  {
   Sound.PlaySound(SOUND__DOLLAR,0,GameParameters.SoundVolume);
   DestroyCharacter3(n);
   dangle=-ball_angle+(float)((float)120.0*rand()/RAND_MAX-60.0);
   GameParameters.Score+=200;
  }
 }
 //проверим столкновение с персонажами 4-го типа (отклоняет мяч в сторону битки)
 for(n=0;n<CurrentCharacter4;n++)
 {
  if (Character4[n].LifeMode!=2) continue;
  float r2=(ball_x-Character4[n].X)*(ball_x-Character4[n].X)+(ball_y-Character4[n].Y)*(ball_y-Character4[n].Y);
  if (r2<=(Character4Radius+ball_radius)*(Character4Radius+ball_radius))//есть столкновение
  {
   Sound.PlaySound(SOUND__DESTROY,0,GameParameters.SoundVolume);
   DestroyCharacter4(n);
   dangle=-ball_angle+(float)((float)80.0*rand()/RAND_MAX-40.0);
  }
 }
 //проверим столкновение с персонажами 5-го типа (создаёт новый мяч)
 for(n=0;n<CurrentCharacter5;n++)
 {
  if (Character5[n].LifeMode!=2) continue;
  float r2=(ball_x-Character5[n].X)*(ball_x-Character5[n].X)+(ball_y-Character5[n].Y)*(ball_y-Character5[n].Y);
  if (r2<=(Character5Radius+ball_radius)*(Character5Radius+ball_radius))//есть столкновение
  {
   Sound.PlaySound(SOUND__DOUBLE_BALL,0,GameParameters.SoundVolume);
   DestroyCharacter5(n);
   dangle+=(float)180.0*rand()/RAND_MAX;
   BallMap.CreateNewBall((float)Character5[n].X,(float)Character5[n].Y,-(ball_angle+dangle),1);
  }
 }
 //проверим столкновение с персонажами 6-го типа (отклоняет мяч от битки)
 for(n=0;n<CurrentCharacter6;n++)
 {
  if (Character6[n].LifeMode!=2) continue;
  float r2=(ball_x-Character6[n].X)*(ball_x-Character6[n].X)+(ball_y-Character6[n].Y)*(ball_y-Character6[n].Y);
  if (r2<=(Character6Radius+ball_radius)*(Character6Radius+ball_radius))//есть столкновение
  {
   Sound.PlaySound(SOUND__DESTROY,0,GameParameters.SoundVolume);
   DestroyCharacter6(n);
   dangle+=-ball_angle+100+(float)160.0*rand()/RAND_MAX;
  }
 }
 //проверим столкновение с персонажами 7-го типа (отклоняет мяч)
 for(n=0;n<CurrentCharacter7;n++)
 {
  for(m=0;m<6;m++)
  {
   if (Character7[n].LifeMode[m]!=2) continue;
   float r2=(ball_x-Character7[n].X[m])*(ball_x-Character7[n].X[m])+(ball_y-Character7[n].Y[m])*(ball_y-Character7[n].Y[m]);
   if (r2<=(Character7Radius+ball_radius)*(Character7Radius+ball_radius))//есть столкновение
   {
    Sound.PlaySound(SOUND__DESTROY,0,GameParameters.SoundVolume);
    DestroyCharacter7(n,m);
    dangle+=(float)180.0*rand()/RAND_MAX;
   }
  }
 }
 //проверим столкновение с персонажами 8-го типа (отклоняет мяч на некоторый блок)
 for(n=0;n<CurrentCharacter8;n++)
 {
  if (Character8[n].LifeMode!=2) continue;
  float r2=(ball_x-Character8[n].X)*(ball_x-Character8[n].X)+(ball_y-Character8[n].Y)*(ball_y-Character8[n].Y);
  if (r2<=(Character8Radius+ball_radius)*(Character8Radius+ball_radius))//есть столкновение
  {
   Sound.PlaySound(SOUND__DESTROY,0,GameParameters.SoundVolume);
   DestroyCharacter8(n);
   dangle=-ball_angle;
   //ищем блок
   int b_x=0;
   int b_y=0;
   BLOCK Block;
   int maxblock=0;
   for(x=0;x<26;x++)
    for(y=0;y<13;y++)
	{
     Block=BlockMap.GetBlock(x,y);
     if (Block.Space==1) continue;
	 if (Block.Obstacle==0) continue;
     maxblock++;     
	}
   int search=(int)(maxblock*rand()/RAND_MAX)+1;
   for(x=0;x<26;x++)
   {
    for(y=0;y<13;y++)
	{
     Block=BlockMap.GetBlock(x,y);
     if (Block.Space==1) continue;
	 if (Block.Obstacle==0) continue;
     b_x=x;
	 b_y=y;
	 search--;
	 if (search==0) break;
	}
    if (search==0) break;
   }
   //координаты центра блока 
   float n_x=(float)(b_x*20+23+10);
   float n_y=(float)(b_y*30+82+15);
   float dx=n_x-ball_x;
   float dy=-(n_y-ball_y);
   float angle=0;
   if (dx!=0)
   {
    angle=(float)(180.0/M_PI*atan(fabs(dy/dx)));
    if (dy==0 && dx<0) angle=180; 
	if (dy==0 && dx>0) angle=0; 
	if (dx<0 && dy>0) angle=180-angle;
	if (dx<0 && dy<0) angle=180+angle;
	if (dx>0 && dy<0) angle=360-angle;
   }
   else
   {
    if (dy==0) angle=180;
    if (dy<0) angle=270;
    if (dy>0) angle=90;
   }
   dangle+=angle;
  }
 }
 //проверим столкновение с персонажами 9-го типа (отклоняет мяч)
 for(n=0;n<CurrentCharacter9;n++)
 {
  if (Character9[n].LifeMode!=2) continue;
  float r2=(ball_x-Character9[n].X)*(ball_x-Character9[n].X)+(ball_y-Character9[n].Y)*(ball_y-Character9[n].Y);
  if (r2<=(Character9Radius+ball_radius)*(Character9Radius+ball_radius))//есть столкновение
  {
   Sound.PlaySound(SOUND__DESTROY,0,GameParameters.SoundVolume);
   DestroyCharacter9(n);
   dangle+=(float)180.0*rand()/RAND_MAX;
  }
 }
 return(dangle);
}
int CHARACTERMAP::ImpactCharacterToMissile(int xleft,int xright,int yup,int ydown)
{
 int ret=0;
 int n,m;
 for(n=0;n<CurrentCharacter1;n++)
 {
  if (Character1[n].LifeMode!=2) continue;
  int pd_face1=CircleIntercectionToLine((float)xleft,(float)yup,(float)xright,(float)yup,Character1[n].X,Character1[n].Y,(float)Character1Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)xleft,(float)ydown,(float)xright,(float)ydown,Character1[n].X,Character1[n].Y,(float)Character1Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)xleft,(float)yup,(float)xleft,(float)ydown,Character1[n].X,Character1[n].Y,(float)Character1Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)xright,(float)yup,(float)xright,(float)ydown,Character1[n].X,Character1[n].Y,(float)Character1Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0)
  {
   Sound.PlaySound(SOUND__DESTROY,0,GameParameters.SoundVolume);
   DestroyCharacter1(n);
  }
 }
 for(n=0;n<CurrentCharacter2;n++)
 {
  if (Character2[n].LifeMode!=2) continue;
  int pd_face1=CircleIntercectionToLine((float)xleft,(float)yup,(float)xright,(float)yup,Character2[n].X,Character2[n].Y,(float)Character2Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)xleft,(float)ydown,(float)xright,(float)ydown,Character2[n].X,Character2[n].Y,(float)Character2Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)xleft,(float)yup,(float)xleft,(float)ydown,Character2[n].X,Character2[n].Y,(float)Character2Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)xright,(float)yup,(float)xright,(float)ydown,Character2[n].X,Character2[n].Y,(float)Character2Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0)
  {
   ExplosionCharacter2(n);
   int x=(int)(Character2[n].X-23)/20;
   int y=(int)(Character2[n].Y-82)/30;
   BlockMap.ExplosionBlock(x,y);
   ret=1;//и взорвём ещё и ракету !
  }
 }
 for(n=0;n<CurrentCharacter3;n++)
 {
  if (Character3[n].LifeMode!=2) continue;
  int pd_face1=CircleIntercectionToLine((float)xleft,(float)yup,(float)xright,(float)yup,Character3[n].X,Character3[n].Y,(float)Character3Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)xleft,(float)ydown,(float)xright,(float)ydown,Character3[n].X,Character3[n].Y,(float)Character3Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)xleft,(float)yup,(float)xleft,(float)ydown,Character3[n].X,Character3[n].Y,(float)Character3Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)xright,(float)yup,(float)xright,(float)ydown,Character3[n].X,Character3[n].Y,(float)Character3Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0)
  {
   Sound.PlaySound(SOUND__DESTROY,0,GameParameters.SoundVolume);
   DestroyCharacter3(n);
  }
 }
 for(n=0;n<CurrentCharacter4;n++)
 {
  if (Character4[n].LifeMode!=2) continue;
  int pd_face1=CircleIntercectionToLine((float)xleft,(float)yup,(float)xright,(float)yup,Character4[n].X,Character4[n].Y,(float)Character4Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)xleft,(float)ydown,(float)xright,(float)ydown,Character4[n].X,Character4[n].Y,(float)Character4Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)xleft,(float)yup,(float)xleft,(float)ydown,Character4[n].X,Character4[n].Y,(float)Character4Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)xright,(float)yup,(float)xright,(float)ydown,Character4[n].X,Character4[n].Y,(float)Character4Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0)
  {
   Sound.PlaySound(SOUND__DESTROY,0,GameParameters.SoundVolume);
   DestroyCharacter4(n);
  }
 }
 for(n=0;n<CurrentCharacter5;n++)
 {
  if (Character5[n].LifeMode!=2) continue;
  int pd_face1=CircleIntercectionToLine((float)xleft,(float)yup,(float)xright,(float)yup,Character5[n].X,Character5[n].Y,(float)Character5Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)xleft,(float)ydown,(float)xright,(float)ydown,Character5[n].X,Character5[n].Y,(float)Character5Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)xleft,(float)yup,(float)xleft,(float)ydown,Character5[n].X,Character5[n].Y,(float)Character5Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)xright,(float)yup,(float)xright,(float)ydown,Character5[n].X,Character5[n].Y,(float)Character5Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0)
  {
   Sound.PlaySound(SOUND__DESTROY,0,GameParameters.SoundVolume);
   DestroyCharacter5(n);
  }
 }
 for(n=0;n<CurrentCharacter6;n++)
 {
  if (Character6[n].LifeMode!=2) continue;
  int pd_face1=CircleIntercectionToLine((float)xleft,(float)yup,(float)xright,(float)yup,Character6[n].X,Character6[n].Y,(float)Character6Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)xleft,(float)ydown,(float)xright,(float)ydown,Character6[n].X,Character6[n].Y,(float)Character6Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)xleft,(float)yup,(float)xleft,(float)ydown,Character6[n].X,Character6[n].Y,(float)Character6Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)xright,(float)yup,(float)xright,(float)ydown,Character6[n].X,Character6[n].Y,(float)Character6Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0)
  {
   Sound.PlaySound(SOUND__DESTROY,0,GameParameters.SoundVolume);
   DestroyCharacter6(n);
  }
 }
 for(n=0;n<CurrentCharacter7;n++)
 {
  for(m=0;m<6;m++)
  {
   if (Character7[n].LifeMode[m]!=2) continue;
   int pd_face1=CircleIntercectionToLine((float)xleft,(float)yup,(float)xright,(float)yup,Character7[n].X[m],Character7[n].Y[m],(float)Character7Radius);//верхняя
   int pd_face2=CircleIntercectionToLine((float)xleft,(float)ydown,(float)xright,(float)ydown,Character7[n].X[m],Character7[n].Y[m],(float)Character7Radius);//нижняя
   int pd_face3=CircleIntercectionToLine((float)xleft,(float)yup,(float)xleft,(float)ydown,Character7[n].X[m],Character7[n].Y[m],(float)Character7Radius);//левая
   int pd_face4=CircleIntercectionToLine((float)xright,(float)yup,(float)xright,(float)ydown,Character7[n].X[m],Character7[n].Y[m],(float)Character7Radius);//правая
   if (pd_face1+pd_face2+pd_face3+pd_face4!=0)
   {
    Sound.PlaySound(SOUND__DESTROY,0,GameParameters.SoundVolume);
	DestroyCharacter7(n,m);
   }
  }
 }
 for(n=0;n<CurrentCharacter8;n++)
 {
  if (Character8[n].LifeMode!=2) continue;
  int pd_face1=CircleIntercectionToLine((float)xleft,(float)yup,(float)xright,(float)yup,Character8[n].X,Character8[n].Y,(float)Character8Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)xleft,(float)ydown,(float)xright,(float)ydown,Character8[n].X,Character8[n].Y,(float)Character8Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)xleft,(float)yup,(float)xleft,(float)ydown,Character8[n].X,Character8[n].Y,(float)Character8Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)xright,(float)yup,(float)xright,(float)ydown,Character8[n].X,Character8[n].Y,(float)Character8Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0)
  {
   Sound.PlaySound(SOUND__DESTROY,0,GameParameters.SoundVolume);
   DestroyCharacter8(n);
  }
 }
 for(n=0;n<CurrentCharacter9;n++)
 {
  if (Character9[n].LifeMode!=2) continue;
  int pd_face1=CircleIntercectionToLine((float)xleft,(float)yup,(float)xright,(float)yup,Character9[n].X,Character9[n].Y,(float)Character9Radius);//верхняя
  int pd_face2=CircleIntercectionToLine((float)xleft,(float)ydown,(float)xright,(float)ydown,Character9[n].X,Character9[n].Y,(float)Character9Radius);//нижняя
  int pd_face3=CircleIntercectionToLine((float)xleft,(float)yup,(float)xleft,(float)ydown,Character9[n].X,Character9[n].Y,(float)Character9Radius);//левая
  int pd_face4=CircleIntercectionToLine((float)xright,(float)yup,(float)xright,(float)ydown,Character9[n].X,Character9[n].Y,(float)Character9Radius);//правая
  if (pd_face1+pd_face2+pd_face3+pd_face4!=0)
  {
   Sound.PlaySound(SOUND__DESTROY,0,GameParameters.SoundVolume);
   DestroyCharacter9(n);
  }
 }
 return(ret);
}