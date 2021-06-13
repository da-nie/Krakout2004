class GAME
{
 protected:
  //-----------------------------------------------------------
  int Mode;//режим работы(0-меню,1-игра,2-ждём перезапуска уровня,3-конец игры,4-пауза,5-подтверждение выхода)
  int Timer;//переменная для хранения любого требуемого времени
  int MissileTimer;//время до срабатывания специального режима
  int SoundTrackPlay;//1-звук запущен
  //-----------------------------------------------------------
 public:
  //-----------------------------------------------------------
  void Create(void);
  void Release(void);
  void ReleaseSpriteSurface(LPDIRECTDRAW7 lpdd);
  void CreateSpriteSurface(LPDIRECTDRAW7 lpdd);
  //-----------------------------------------------------------
  void InitializeToStartGame(void);
  void InitializeToStartPracticsGame(void);
  void InitializeToStartNextLevel(void);
  void InitializeToReStartLevel(void);
  //-----------------------------------------------------------
  int Processing(int step);
  void TransferChar(int code);
  void Draw(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  //-----------------------------------------------------------
};
//--------------------------------------------------------------------------
void GAME::Create(void)
{
 Font.Load();
 Paddle.Create();
 BlockMap.Create();
 BallMap.Create();
 MissileMap.Create();
 CharacterMap.Create();
 //найдём число доступных уровней
 GameParameters.MaxLevel=0;
 GameParameters.MusicVolume=100;
 GameParameters.SoundVolume=100;
 FILE *file=fopen("level_list.txt","r+b");
 if (file!=NULL)
 {
  fscanf(file,"%i",&GameParameters.MaxLevel);
  fclose(file);
 }
 //загрузим настройки звука
 file=fopen("sound_setting.txt","r+b");
 if (file!=NULL)
 {
  fscanf(file,"%i",&GameParameters.MusicVolume);
  fscanf(file,"%i",&GameParameters.SoundVolume);
  fclose(file);
 }
 Mode=0;//режим меню
 Timer=0;
 GameParameters.StartLevel=1;
 GameParameters.SpecialMode=0;
 SoundTrackPlay=0;//музыки нет
 MenuMap.Create(GameParameters.MaxLevel);
}
void GAME::Release(void)
{
 BlockMap.Release();
 MissileMap.Release();
 BallMap.Release();
 Paddle.Release();
 MenuMap.Release();
 CharacterMap.Release();
 Font.Release();
}
void GAME::ReleaseSpriteSurface(LPDIRECTDRAW7 lpdd)
{
 Font.ReleaseSpriteSurface();
 Paddle.ReleaseSpriteSurface();
 BlockMap.ReleaseSpriteSurface();
 BallMap.ReleaseSpriteSurface();
 MissileMap.ReleaseSpriteSurface();
 CharacterMap.ReleaseSpriteSurface();
 MenuMap.ReleaseSpriteSurface();
}
void GAME::CreateSpriteSurface(LPDIRECTDRAW7 lpdd)
{
 Font.CreateSpriteSurface(lpdd);
 Paddle.CreateSpriteSurface(lpdd);
 BlockMap.CreateSpriteSurface(lpdd);
 BallMap.CreateSpriteSurface(lpdd);
 MissileMap.CreateSpriteSurface(lpdd);
 CharacterMap.CreateSpriteSurface(lpdd);
 MenuMap.CreateSpriteSurface(lpdd);
}
//--------------------------------------------------------------------------
void GAME::InitializeToStartGame(void)
{
 BallMap.InitializeToStartLevel();
 MissileMap.InitializeToStartLevel();
 Paddle.InitializeToStartLevel();
 BallMap.SetAllBallToPaddle();
 CharacterMap.InitializeToStartLevel();

 GameParameters.Level=1;
 GameParameters.Life=10;
 GameParameters.Practics=0;
 GameParameters.Score=0;
 GameParameters.BallSpeed=2;
 GameParameters.RightWall=0;
 GameParameters.RightWallTime=0;
 GameParameters.SelectBlock_X=-1;
 GameParameters.SelectBlock_Y=-1;
 BlockMap.LoadMap();
}
void GAME::InitializeToStartPracticsGame(void)
{
 BallMap.InitializeToStartLevel();
 Paddle.InitializeToStartLevel();
 MissileMap.InitializeToStartLevel();
 BallMap.SetAllBallToPaddle();
 CharacterMap.InitializeToStartLevel();

 GameParameters.Level=GameParameters.StartLevel;
 GameParameters.Life=0;
 GameParameters.Practics=1;
 GameParameters.Score=0;
 GameParameters.BallSpeed=2;
 GameParameters.RightWall=0;
 GameParameters.RightWallTime=0;
 GameParameters.SelectBlock_X=-1;
 GameParameters.SelectBlock_Y=-1;
 BlockMap.LoadMap();
}
void GAME::InitializeToStartNextLevel(void)
{
 GameParameters.Level++;
 if (GameParameters.Level>GameParameters.MaxLevel)
 {
  //мы прошли всю игру !!!
  //запустим её заново
  GameParameters.Level=1;
 }
 GameParameters.BallSpeed=2;
 GameParameters.RightWall=0;
 GameParameters.RightWallTime=0;
 BallMap.InitializeToStartLevel();
 Paddle.InitializeToStartLevel();
 MissileMap.InitializeToStartLevel();
 BallMap.SetAllBallToPaddle();
 CharacterMap.InitializeToStartLevel();
 BlockMap.LoadMap();
}
void GAME::InitializeToReStartLevel(void)
{
 BallMap.InitializeToStartLevel();
 Paddle.InitializeToStartLevel();
 MissileMap.InitializeToStartLevel();
 BallMap.SetAllBallToPaddle();
 CharacterMap.InitializeToStartLevel();

 GameParameters.BallSpeed=2;
 GameParameters.RightWall=0;
 GameParameters.RightWallTime=0;
 GameParameters.SelectBlock_X=-1;
 GameParameters.SelectBlock_Y=-1;
}
//--------------------------------------------------------------------------
int GAME::Processing(int step)
{
 if (Timer>0) Timer--;
 if (MissileTimer>0) MissileTimer--;
 if (Timer==0 && Mode==2) 
 {
  Mode=1;
  Timer=50;
  MissileTimer=100;
  SoundTrackPlay=0;
  Sound.StopAllSound();
  InitializeToReStartLevel();
 }
 if (Mode==0)
 {
  if (SoundTrackPlay==0)
  {
   Sound.PlayMusic(SOUND__MUSIC_1,1);
   SoundTrackPlay=1;
  }
  if (step==0) MenuMap.ChangeImageFrame(); 
  int res=MenuMap.Processing();
  if (res==1)//выход из игры
  {
   //сохраним настройки звука
   FILE *file=fopen("sound_setting.txt","w+b");
   if (file!=NULL)
   {
    fprintf(file,"%i\n%i\n",GameParameters.MusicVolume,GameParameters.SoundVolume);
    fclose(file);
   }
   return(1);
  }
  if (res==2)//старт игры
  {
   Mode=1;
   Timer=50;
   MissileTimer=100;
   SoundTrackPlay=0;
   Sound.StopAllSound();
   Sound.StopAllMusic();
   InitializeToStartGame();
   GameParameters.DemoMode=0;
   Sound.PlayMusic(SOUND__MUSIC_2,1);
   Sound.SetMusicVolume(GameParameters.MusicVolume);
   return(0);
  }
  if (res==3)//старт практики
  {
   Mode=1;
   Timer=50;
   MissileTimer=100;
   SoundTrackPlay=0;
   Sound.StopAllSound();
   Sound.StopAllMusic();
   InitializeToStartPracticsGame();
   GameParameters.DemoMode=0;
   Sound.PlayMusic(SOUND__MUSIC_2,1);
   Sound.SetMusicVolume(GameParameters.MusicVolume);
   return(0);
  }
  if (res==4)//старт демонстрации
  {
   Mode=1;
   Timer=50;
   MissileTimer=100;
   SoundTrackPlay=0;
   Sound.StopAllSound();
   Sound.StopAllMusic();
   GameParameters.StartLevel=(GameParameters.MaxLevel-1)*rand()/RAND_MAX+1;
   InitializeToStartPracticsGame();
   GameParameters.DemoMode=1;
   Sound.PlayMusic(SOUND__MUSIC_2,1);
   Sound.SetMusicVolume(GameParameters.MusicVolume);
   return(0);
  }
 }
 if (Mode!=0)
 {
  if (GetAsyncKeyState(VK_PRIOR)&32768)
  {
   GameParameters.MusicVolume++;
   if (GameParameters.MusicVolume>100) GameParameters.MusicVolume=100;
   Sound.SetMusicVolume(GameParameters.MusicVolume);
  }
  if (GetAsyncKeyState(VK_NEXT)&32768)
  {
   GameParameters.MusicVolume--;
   if (GameParameters.MusicVolume<0) GameParameters.MusicVolume=0;
   Sound.SetMusicVolume(GameParameters.MusicVolume);
  }
  if (GetAsyncKeyState(VK_HOME)&32768)
  {
   GameParameters.SoundVolume++;
   if (GameParameters.SoundVolume>100) GameParameters.SoundVolume=100;
  }
  if (GetAsyncKeyState(VK_END)&32768)
  {
   GameParameters.SoundVolume--;
   if (GameParameters.SoundVolume<0) GameParameters.SoundVolume=0;
  }
  if (Mode==3 && GetAsyncKeyState(VK_SPACE)&32768 && Timer==0)
  {
   Mode=0;
   Sound.StopAllMusic();
   MenuMap.AddNewNameInHiScore();
   return(0); 
  }
  if (Mode==1 && step==0)
  {
   BallMap.ChangeImageFrame(); 
   BlockMap.ChangeImageFrame();
   MissileMap.ChangeImageFrame();
   CharacterMap.ChangeImageFrame();
  }
  if (Mode==2 && step==0) 
  {
   BlockMap.ChangeImageFrame();
   CharacterMap.ChangeImageFrame();
  }
  //опрашиваем клавиши
  if (GetAsyncKeyState(VK_ESCAPE)&32768 && Mode==5 && Timer==0)//отмена выхода из игры
  {
   Mode=1;
   Timer=30;
   return(0); 
  }
  if (GetAsyncKeyState(VK_RETURN)&32768 && Mode==5 && Timer==0)//подтверждение выхода из игры
  {
   if (GameParameters.Practics==0) MenuMap.AddNewNameInHiScore();
   Sound.StopAllMusic();
   Mode=0;
   return(0); 
  }
  if (GetAsyncKeyState(VK_RETURN)&32768 && (Mode==1 || Mode==4) && Timer==0)//пауза
  {
   if (Mode==4) Mode=1;
           else Mode=4;
   Timer=30;
   return(0);
  }
  if (Mode==1 && GetAsyncKeyState(VK_ESCAPE)&32768 && Timer==0)//выход из игры
  {
   Timer=30;
   Mode=5;
   return(0);
  }
  if (Mode==1 && Timer==0)
  {
   if (GameParameters.SpecialMode==1)//если у нас специальный режим
   {
    if (GetAsyncKeyState(VK_TAB)&32768 && GameParameters.DemoMode==0) 
	{
     Paddle.MissileModeOn();
	 GameParameters.RightWall=1;
	 GameParameters.RightWallTime=500000000;
	}
   }
   if (GameParameters.DemoMode==0)
   {
    if (GetAsyncKeyState(VK_UP)&32768) Paddle.MoveUp();
    if (GetAsyncKeyState(VK_DOWN)&32768) Paddle.MoveDown();
   }
   //Автоматическое управление биткой
   if (GameParameters.DemoMode==1)
   {
    //int selectball=BallMap.GetNearestBallNumber(Paddle.GetX(),Paddle.GetY());
	int selectball=BallMap.GetNearestToVerticalLineBallNumber((float)(Paddle.GetX()-Paddle.GetWidth()/2));
    if (selectball>=0)
	{
     float bx,by;
	 BallMap.GetBallCoord(selectball,&bx,&by);
	 float ballangle=BallMap.GetBallAngle(selectball);
	 ballangle=NormalizeAngle(ballangle);
	 if (bx>=400 && (ballangle<90 || ballangle>270))
	 {
	  if (by>Paddle.GetY()+Paddle.GetHeight()/2) Paddle.MoveDown();
	  if (by<Paddle.GetY()-Paddle.GetHeight()/2) Paddle.MoveUp();
      if (by<=Paddle.GetY()+Paddle.GetHeight()/2 && by>=Paddle.GetY()-Paddle.GetHeight()/2)//скорректируем положение битки
	  {
       //если мы ещё не выбрали блок, то сделаем это теперь
	   int onselectblock=0;
	   int x,y;
       BLOCK Block;
	   if (GameParameters.SelectBlock_X!=-1 && GameParameters.SelectBlock_Y!=-1)
	   {
        Block=BlockMap.GetBlock(GameParameters.SelectBlock_X,GameParameters.SelectBlock_Y);
		if (Block.Obstacle==0 || Block.Space==1) onselectblock=1;
	   }
	   else onselectblock=1;
	   //поищем, не появились ли призовые блоки на поле
        //поищем призовые (по приоритету M-B-S-+-E-X-G--);
       int SelectLevel=0;//нет выбранного приза
       for(x=0;x<26;x++)
	   {
        for(y=0;y<13;y++)
		{
         Block=BlockMap.GetBlock(x,y);
         if (Block.Space==1) continue;//тут нет блока
	     if (Block.Obstacle==0) continue;//блок есть, но он растворяется
         if (Block.Prize==-1) continue;//блок без приза
		 if (Block.PrizeActive==0) continue;//приз не активирован (жульничать не стоит)
         int level=-1;
		 if (Block.Prize==0) level=7;//B
		 if (Block.Prize==1) level=6;//S
		 if (Block.Prize==2) level=8;//M
		 if (Block.Prize==3) level=3;//X
		 if (Block.Prize==4) level=1;//G
		 if (Block.Prize==5) level=5;//E
		 if (Block.Prize==6) level=4;//+
		 if (Block.Prize==7) level=2;//-
		 if (SelectLevel<=level)//приз с более высоким приоритетом
		 {
          GameParameters.SelectBlock_X=x;
	      GameParameters.SelectBlock_Y=y;
          SelectLevel=level;
		 }
		}
	   }	
       if (SelectLevel!=0) onselectblock=0;
	   if (onselectblock==1)
	   {
        //нужно выбрать блок, на который мы отразим мяч
	    GameParameters.SelectBlock_X=-1;
        GameParameters.SelectBlock_Y=-1;
        int maxblock=0;
        for(x=0;x<26;x++)
         for(y=0;y<13;y++)
		 {
          Block=BlockMap.GetBlock(x,y);
          if (Block.Space==1) continue;
	      if (Block.Obstacle==0) continue;
          maxblock++;     
		 }
        //теперь мы знаем сколько у нас всего неразбитых блоков 
        int search=(int)(maxblock*rand()/RAND_MAX)+1;
        for(x=0;x<26;x++)
		{
         for(y=0;y<13;y++)
		 {
          Block=BlockMap.GetBlock(x,y);
          if (Block.Space==1) continue;
	      if (Block.Obstacle==0) continue;
          GameParameters.SelectBlock_X=x;
	      GameParameters.SelectBlock_Y=y;
	      search--;
	      if (search==0) break;
		 }
         if (search==0) break;
		}
	   }
       //изменяем положение битки
       if (GameParameters.SelectBlock_X!=-1 && GameParameters.SelectBlock_Y!=-1)	  
	   { 
        //координаты центра блока 
        float bc_x=(float)(GameParameters.SelectBlock_X*20+23+10);
        float bc_y=(float)(GameParameters.SelectBlock_Y*30+82+15);
        float dx=bc_x-bx;
        float dy=-(bc_y-by);
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
        //теперь на известен угол, под которым нам нужно отразить мяч
        float dangle=angle-NormalizeAngle(180-ballangle);
        float ball_dy=(float)(dangle/30.0);
		float paddle_y=(float)(by-ball_dy*(Paddle.GetHeight()/2.0));
	    if (paddle_y>Paddle.GetY()) Paddle.MoveDown();
	    if (paddle_y<Paddle.GetY()) Paddle.MoveUp();
	   }
	  }
	 }
	 else
	 {
      if (Paddle.GetMissile()==1)//если есть ракета
	  {
       int block_y=0;
	   int maxblock_in_line=0;
       for(int y=9;y>=1;y--)
	   {
        int block_in_line=0;
        for(int x=0;x<=24;x++)
		{
         BLOCK Block=BlockMap.GetBlock(x,y);
         if (Block.Obstacle==0 || Block.Space==1) continue;
         block_in_line++;
		}
		if (maxblock_in_line<block_in_line) 
		{
		 maxblock_in_line=block_in_line;
		 block_y=y;
		}
	   }
       float up_by=(float)(block_y*30+82+5);
       float down_by=(float)(block_y*30+82+25);
       if (up_by>Paddle.GetY()) Paddle.MoveDown();
	   if (down_by<Paddle.GetY()) Paddle.MoveUp();
	   if (Paddle.GetY()<=down_by && Paddle.GetY()>=up_by)
	   {
        MissileTimer=100;
        Sound.PlaySound(SOUND__MISSILE,0,GameParameters.SoundVolume);
        Paddle.MissileModeOff();
        MissileMap.CreateNewMissile((float)Paddle.GetX(),(float)Paddle.GetY());
	   }
	  }
	 }
	}
    BallMap.StartAllBall();
   }
   if (GetAsyncKeyState(VK_SPACE)&32768 && GameParameters.DemoMode==0)
   {
    BallMap.StartAllBall();
    if (Paddle.GetMissile()==1 && MissileTimer==0)
    {
     MissileTimer=100;
     Sound.PlaySound(SOUND__MISSILE,0,GameParameters.SoundVolume);
     Paddle.MissileModeOff();
     MissileMap.CreateNewMissile((float)Paddle.GetX(),(float)Paddle.GetY());
    }
   }
   //проверим, не выиграли ли мы уже 
   if (BlockMap.LevelOver()==1)//победа !
   {
    Timer=750;
	Mode=2;
    Sound.StopAllSound();
    SoundTrackPlay=0;
	Sound.PlaySound(SOUND__LEVEL_UP,0,GameParameters.SoundVolume);
	InitializeToStartNextLevel();
    return(0);
   }
   //выполняем физику сцены
   int res=0;
   for(int s=0;s<GameParameters.BallSpeed;s++)
   {
    res=BallMap.Processing(); 
    if (res==1) break;//мячи кончились
   }
   if (res==1)
   {
    if (GameParameters.Practics==0)
	{
     GameParameters.Life--;
     if (GameParameters.Life==0) //конец игры
	 {
      Mode=3;
      Sound.StopAllSound();
	  Sound.PlaySound(SOUND__GAME_OVER,0,GameParameters.SoundVolume);
	  Timer=100;
      return(0);
	 }
	}
    Sound.StopAllSound();
    Sound.PlaySound(SOUND__LOSE,0,GameParameters.SoundVolume);
	CharacterMap.DestroyAllCharacter();
	Mode=2;
	Timer=350;
   }
   MissileMap.Processing();
   Paddle.Processing();
   CharacterMap.Processing();
  }
 }
 return(0);
}
void GAME::TransferChar(int code)
{
 if (Mode==0) MenuMap.TransferChar(code);
}
void GAME::Draw(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd)
{
 if (Mode==0) MenuMap.PutMenu(lpddssurface,ddsd);
 if (Mode!=0)
 {
  BallMap.PutAllBall(lpddssurface,ddsd); 
  BlockMap.PutMap(lpddssurface,ddsd); 
  CharacterMap.PutAllCharacter(lpddssurface,ddsd);
  MissileMap.PutAllMissile(lpddssurface,ddsd);
  Paddle.PutPaddle(lpddssurface,ddsd);
  if (Mode==4) Font.PrintAtCenter(200,"Pause.Press Enter to cancel.",4,lpddssurface,ddsd);
  if (Mode==3) 
  { 
   Font.PrintAtCenter(200,"Game Over",4,lpddssurface,ddsd);
   Font.PrintAtCenter(230,"Press Space to continue",1,lpddssurface,ddsd);
  }
  if (Mode==5)
  {
   Font.PrintAtCenter(200,"Are you sure want to quit ?",2,lpddssurface,ddsd);
   Font.PrintAtCenter(230,"Press Escape to continue game, Enter to quit",3,lpddssurface,ddsd);
  }
 }
}
