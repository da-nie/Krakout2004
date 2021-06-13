struct BLOCK
{
 int ImageX;//координаты картинки
 int ImageY;
 int Break;//число попаданий для разрушения блока
 int Obstacle;//1-блок является препятствием
 int Prize;//тип приза для призового блока
 int PrizeActive;//1-приз активен
 int PrizeTime;//время существования приза
 int Space;//1-блок-пустое пространство
 //-----------------------------------------------------------
 int Dust;//стадии растворения блока
};
class BLOCKMAP
{
 protected:
  //-----------------------------------------------------------
  BLOCK Block[13][26];
  SPRITE BlockSprite;
  SPRITE BlockPrizeSprite;
  SPRITE UpWall;
  SPRITE DownWall;
  SPRITE LeftWall;
  unsigned char Dust[10][600];//маски для растворения блоков
  //-----------------------------------------------------------
 public:
  //-----------------------------------------------------------
  void Create(void);
  void Release(void);
  void CreateSpriteSurface(LPDIRECTDRAW7 lpdd);
  void ReleaseSpriteSurface(void);
  //-----------------------------------------------------------
  BLOCK GetBlock(int x,int y);
  //-----------------------------------------------------------
  void LoadMap(void);
  void PutMap(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void ActivateBlock(int x,int y);
  void ChangeImageFrame(void);
  void ExplosionBlock(int x,int y);
  void DestroyBlock(int x,int y);
  int LevelOver(void);
 //-----------------------------------------------------------
} BlockMap;
//--------------------------------------------------------------------------
void BLOCKMAP::Create(void)
{
 BlockSprite.Load("bitmap\\block.bmp");
 BlockSprite.SetSpriteSize(20,30);
 BlockSprite.SetBlendColor(0,0,0);
 BlockPrizeSprite.Load("bitmap\\block_prize.bmp");
 BlockPrizeSprite.SetSpriteSize(20,30);
 BlockPrizeSprite.SetBlendColor(0,0,0);
 UpWall.Load("bitmap\\upframe.bmp");
 UpWall.SetBlendColor(0,0,0);
 DownWall.Load("bitmap\\downframe.bmp");
 DownWall.SetBlendColor(0,0,0);
 LeftWall.Load("bitmap\\leftframe.bmp");
 LeftWall.SetBlendColor(0,0,0);
 int n,m;
 //создадим маски для растворения блоков
 for(n=0;n<600;n++) Dust[0][n]=1;
 for(n=1;n<10;n++)
  for(m=0;m<600;m++) Dust[n][m]=(int)(Dust[n-1][m]*2*rand()/RAND_MAX);
}
void BLOCKMAP::Release(void)
{
 BlockSprite.Delete();
 BlockPrizeSprite.Delete();
 UpWall.Delete();
 DownWall.Delete();
 LeftWall.Delete();
}
void BLOCKMAP::CreateSpriteSurface(LPDIRECTDRAW7 lpdd)
{
 BlockSprite.CreateSpriteSurface(lpdd);
 BlockPrizeSprite.CreateSpriteSurface(lpdd);
 UpWall.CreateSpriteSurface(lpdd);
 DownWall.CreateSpriteSurface(lpdd);
 LeftWall.CreateSpriteSurface(lpdd);
}
void BLOCKMAP::ReleaseSpriteSurface(void)
{
 BlockSprite.ReleaseSpriteSurface();
 BlockPrizeSprite.ReleaseSpriteSurface();
 UpWall.ReleaseSpriteSurface();
 DownWall.ReleaseSpriteSurface();
 LeftWall.ReleaseSpriteSurface();
}
//--------------------------------------------------------------------------
BLOCK BLOCKMAP::GetBlock(int x,int y)
{
 return(Block[y][x]);
}
//--------------------------------------------------------------------------
void BLOCKMAP::LoadMap(void)
{
 int n;
 int x,y;
 //найдём требуемый уровень
 FILE *file=fopen("level_list.txt","r+b");
 if (file==NULL)//список уровней не найден, сделаем уровень из случайных блоков
 {
  for(x=0;x<25;x++)
   for(y=0;y<12;y++)
   {
    if (100.0*rand()/RAND_MAX>80)
    {
     Block[y][x].Space=1;
     continue;
    }
    else Block[y][x].Space=0;
    Block[y][x].Break=(int)(1+3.0*rand()/RAND_MAX);
    Block[y][x].Obstacle=1;
    Block[y][x].Dust=0;
    Block[y][x].ImageX=(int)72.0*rand()/RAND_MAX;
    Block[y][x].ImageY=0;
    if (100.0*rand()/RAND_MAX>80)
    {
     Block[y][x].Prize=(int)(8.0*rand()/RAND_MAX);
     Block[y][x].PrizeActive=0;
    }
    else Block[y][x].Prize=-1;
   } 
  for(n=1;n<8;n++) GameParameters.EnableCharacter[n]=1;
  return;
 }
 char LevelName[65535];
 for(n=0;n<GameParameters.Level;n++) fscanf(file,"%s",&LevelName);
 fscanf(file,"%s",&LevelName);
 fclose(file);
 //загружаем сам уровень
 file=fopen(LevelName,"r+b");
 if (file==NULL)
 {
  for(x=0;x<25;x++)
   for(y=0;y<12;y++)
   {
    if (100.0*rand()/RAND_MAX>80)
    {
     Block[y][x].Space=1;
     continue;
    }
    else Block[y][x].Space=0;
    Block[y][x].Break=(int)(1+3.0*rand()/RAND_MAX);
    Block[y][x].Obstacle=1;
    Block[y][x].Dust=0;
    Block[y][x].ImageX=(int)72.0*rand()/RAND_MAX;
    Block[y][x].ImageY=0;
    if (100.0*rand()/RAND_MAX>80)
    {
     Block[y][x].Prize=(int)(8.0*rand()/RAND_MAX);
     Block[y][x].PrizeActive=0;
    }
    else Block[y][x].Prize=-1;
   } 
  for(n=1;n<10;n++) GameParameters.EnableCharacter[n]=1;
  return;
 }
 for(y=0;y<12;y++) 
  for(x=0;x<25;x++) 
  {
   int Space,Prize,Image,Break;
   fread(&Space,1,sizeof(Space),file);
   if (Space!=1)
   {
    fread(&Image,1,sizeof(Image),file);
    fread(&Break,1,sizeof(Break),file);
    fread(&Prize,1,sizeof(Prize),file);
    Block[y][x].ImageX=Image;
    Block[y][x].ImageY=0;
    Block[y][x].Prize=Prize;
    Block[y][x].Break=Break;
    Block[y][x].Obstacle=1;
    Block[y][x].Dust=0;
	Block[y][x].PrizeActive=0;
   }
   Block[y][x].Space=Space;
  }
 for(n=1;n<10;n++)
 {
  unsigned char state;
  fread(&state,1,sizeof(state),file);
  if (state==0) GameParameters.EnableCharacter[n]=0;
  if (state==1) GameParameters.EnableCharacter[n]=1;
 }
 fclose(file);
}
void BLOCKMAP::PutMap(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 int n;
 DownWall.Put(0,442,lpddssurface,ddsd);
 UpWall.Put(0,45,lpddssurface,ddsd);
 if (GameParameters.RightWall==1) for(n=0;n<8;n++) LeftWall.Put(629,n*45+37+45,lpddssurface,ddsd);
 for(n=0;n<8;n++) LeftWall.Put(0,n*45+37+45,lpddssurface,ddsd);
 for(int x=0;x<25;x++)
  for(int y=0;y<12;y++)
  {
   if (Block[y][x].Space==1) continue;
   if (Block[y][x].Prize==-1)
   {
    BlockSprite.SetSpriteCoord(Block[y][x].ImageY,Block[y][x].ImageX);
    if (Block[y][x].Dust==0) BlockSprite.Put(23+x*20,82+y*30,lpddssurface,ddsd);
                        else BlockSprite.Put(23+x*20,82+y*30,Dust[Block[y][x].Dust],lpddssurface,ddsd);
   }
   if (Block[y][x].Prize!=-1 && Block[y][x].PrizeActive==0)
   {
    BlockSprite.SetSpriteCoord(Block[y][x].ImageY,Block[y][x].ImageX);
    if (Block[y][x].Dust==0) BlockSprite.Put(23+x*20,82+y*30,lpddssurface,ddsd);
                        else BlockSprite.Put(23+x*20,82+y*30,Dust[Block[y][x].Dust],lpddssurface,ddsd);
   }
   if (Block[y][x].Prize!=-1 && Block[y][x].PrizeActive==1)
   {
    BlockPrizeSprite.SetSpriteCoord(Block[y][x].ImageY,Block[y][x].ImageX);
    if (Block[y][x].Dust==0) BlockPrizeSprite.Put(23+x*20,82+y*30,lpddssurface,ddsd);
                        else BlockPrizeSprite.Put(23+x*20,82+y*30,Dust[Block[y][x].Dust],lpddssurface,ddsd);
   }
  }
 //рисуем статистику
 char slevel[255];
 char slife[255];
 char sscore[255];
 itoa(GameParameters.Level,slevel,10);
 itoa(GameParameters.Life,slife,10);
 itoa(GameParameters.Score,sscore,10);
 Font.Print(35,0,"Level",2,lpddssurface,ddsd);
 Font.Print(205,0,"Lifes",2,lpddssurface,ddsd);
 Font.Print(430,0,"Scores",2,lpddssurface,ddsd);
 int x1=(170-strlen(slevel)*Font.GetFontWidth(2))/2;
 int x2=170+(170-strlen(slife)*Font.GetFontWidth(2))/2;
 int x3=340+(300-strlen(sscore)*Font.GetFontWidth(2))/2;
 Font.Print(x1,18,slevel,4,lpddssurface,ddsd);
 Font.Print(x2,18,slife,4,lpddssurface,ddsd);
 Font.Print(x3,18,sscore,4,lpddssurface,ddsd);
}
void BLOCKMAP::ActivateBlock(int x,int y)
{
 Block[y][x].Break--;
 if (Block[y][x].Break==0)
 {
  if (Block[y][x].Prize==-1) 
  {
   Sound.PlaySound(SOUND__BREAK_1,0,GameParameters.SoundVolume);
   Block[y][x].Obstacle=0;//если блок не призовой
   GameParameters.Score+=100;//начислим очки
  }
  else //если блок приз - откроем его
  {
   if (Block[y][x].PrizeActive==0)//открытие приза
   {
    Sound.PlaySound(SOUND__PRIZE_OPEN,0,GameParameters.SoundVolume);
    Block[y][x].Break=1;
    Block[y][x].ImageX=4;
    Block[y][x].ImageY=Block[y][x].Prize;
    Block[y][x].PrizeActive=1;
	Block[y][x].PrizeTime=1000;
	GameParameters.Score+=10;
   }
   else//задействуем приз
   {
    GameParameters.Score+=1000;//начислим очки
    Block[y][x].Obstacle=0;//приз задействован
    if (Block[y][x].Prize==0) ExplosionBlock(x,y);//приз B-бомба
    if (Block[y][x].Prize==1)//приз S-стенка
	{
     Sound.PlaySound(SOUND__PRIZE_S,0,GameParameters.SoundVolume);
     GameParameters.RightWall=1;
	 GameParameters.RightWallTime=500;
     Paddle.MagnetModeOff();
	 Paddle.MissileModeOff();
	}
	if (Block[y][x].Prize==2)//приз M-ракета
	{
     Sound.PlaySound(SOUND__MISSILE_ON,0,GameParameters.SoundVolume);
	 Paddle.MissileModeOn();
	 Paddle.MagnetModeOff();
	}
    if (Block[y][x].Prize==3)//приз X-жизнь
	{
     Sound.PlaySound(SOUND__PRIZE_X,0,GameParameters.SoundVolume);
     if (GameParameters.Practics==0) GameParameters.Life++;
	}
	if (Block[y][x].Prize==4)//приз G-прилипание мяча
	{
     Sound.PlaySound(SOUND__PRIZE_G,0,GameParameters.SoundVolume);
	 Paddle.MagnetModeOn();
     Paddle.MissileModeOff();
	 Paddle.NormalMode();
	}
	if (Block[y][x].Prize==5)//приз E-удвоенная битка
	{
     Sound.PlaySound(SOUND__PRIZE_E,0,GameParameters.SoundVolume);
	 Paddle.DoubleMode();
     Paddle.MissileModeOff();
     Paddle.MagnetModeOff();
	}
	if (Block[y][x].Prize==6)//приз +-ускорение мячей
	{
	 GameParameters.BallSpeedPrizeTime=300;
	 GameParameters.BallSpeed++;
	 if (GameParameters.BallSpeed>3) GameParameters.BallSpeed=3;
	 Sound.PlaySound(SOUND__PRIZE_PLUS,0,GameParameters.SoundVolume);
	}
	if (Block[y][x].Prize==7)//приз --замедление мячей
	{
	 GameParameters.BallSpeedPrizeTime=300;
   	 GameParameters.BallSpeed--;
	 if (GameParameters.BallSpeed<1) GameParameters.BallSpeed=1;
	 Sound.PlaySound(SOUND__PRIZE_MINUS,0,GameParameters.SoundVolume);
	}
   }
  }
 }
 else
 {
  GameParameters.Score+=10;
  int sound=(6*rand())/RAND_MAX;
  if (sound==0) Sound.PlaySound(SOUND__IMPACT_1,0,GameParameters.SoundVolume);
  if (sound==1) Sound.PlaySound(SOUND__IMPACT_2,0,GameParameters.SoundVolume);
  if (sound==2) Sound.PlaySound(SOUND__IMPACT_3,0,GameParameters.SoundVolume);
  if (sound==3) Sound.PlaySound(SOUND__IMPACT_4,0,GameParameters.SoundVolume);
  if (sound==4) Sound.PlaySound(SOUND__IMPACT_5,0,GameParameters.SoundVolume);
  if (sound==5) Sound.PlaySound(SOUND__IMPACT_6,0,GameParameters.SoundVolume);
 }
}
void BLOCKMAP::ChangeImageFrame(void)
{
 if (GameParameters.BallSpeedPrizeTime>0)
 {
  GameParameters.BallSpeedPrizeTime--;
  if (GameParameters.BallSpeedPrizeTime==0) GameParameters.BallSpeed=2;
 }
 if (GameParameters.RightWall==1)
 {
  if (GameParameters.RightWallTime>0) GameParameters.RightWallTime--;
  if (GameParameters.RightWallTime==0)
  {
   Sound.PlaySound(SOUND__PRIZE_S_END,0,GameParameters.SoundVolume);
   GameParameters.RightWall=0;
  }
 }
 for(int x=0;x<25;x++)
  for(int y=0;y<12;y++)
  {
   if (Block[y][x].Space==1) continue;
   if (Block[y][x].Obstacle==0)//растворение блока
   {
    Block[y][x].Dust++;
	if (Block[y][x].Dust==10) Block[y][x].Space=1;
   }
   if (Block[y][x].Prize!=-1)//блок призовой
   {
    if (Block[y][x].PrizeActive==1)
	{
     if (Block[y][x].ImageX>0)
	 {
      Block[y][x].ImageX--;
	 }
	 Block[y][x].PrizeTime--;
	 if (Block[y][x].PrizeTime==0) Block[y][x].Obstacle=0;//уничтожим приз
	}
   }
  }
}
void BLOCKMAP::ExplosionBlock(int x,int y)
{
 Sound.PlaySound(SOUND__PRIZE_B,0,GameParameters.SoundVolume);
 int x1=x-1;
 int x2=x+1;
 int y1=y-1;
 int y2=y+1;
 if (x1<0) x1=0;
 if (y1<0) y1=0;
 if (x2>24) x2=24;
 if (y2>11) y2=11;
 for(int xc=x1;xc<=x2;xc++)
  for(int yc=y1;yc<=y2;yc++) DestroyBlock(xc,yc);
}
void BLOCKMAP::DestroyBlock(int x,int y)
{
 if (Block[y][x].Space==1) return;
 Block[y][x].Obstacle=0;
 GameParameters.Score+=10;
}
int BLOCKMAP::LevelOver(void)
{
 for(int x=0;x<25;x++)
  for(int y=0;y<12;y++)
  {
   if (Block[y][x].Space==0) return(0);
  }
 return(1);
}

