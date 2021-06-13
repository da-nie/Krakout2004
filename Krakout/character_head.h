struct CHARACTER_1
{
 float X;
 float Y;
 int CurrentImage;
 int ChangeImage;
 //параметры перемещения персонажа
 int ModeOfMove;//режим перемещения
 int TimeOfMove;//время перемещения
 int TimeOfLife;//время жизни персонажа
 int LifeMode;//режим (1-рождение;2-жизнь;3-гибель)
};
struct CHARACTER_2
{
 float X;
 float Y;
 int CurrentImage;
 int ChangeImage;
 //параметры перемещения персонажа
 int ModeOfMove;//режим перемещения
 int TimeOfMove;//время перемещения
 int TimeOfLife;//время жизни персонажа
 int LifeMode;//режим (1-рождение;2-жизнь;3-гибель,4-взрыв)
};
struct CHARACTER_3
{
 float X;
 float Y;
 int CurrentImage;
 int ChangeImage;
 //параметры перемещения персонажа
 int ModeOfMove;//режим перемещения
 int TimeOfMove;//время перемещения
 int TimeOfLife;//время жизни персонажа
 int LifeMode;//режим (1-рождение;2-жизнь;3-гибель)
};
struct CHARACTER_4
{
 float X;
 float Y;
 int CurrentImage;
 int ChangeImage;
 //параметры перемещения персонажа
 int ModeOfMove;//режим перемещения
 int TimeOfLife;//время жизни персонажа
 int LifeMode;//режим (1-рождение;2-жизнь;3-гибель)
};
struct CHARACTER_5
{
 float X;
 float Y;
 int CurrentImage;
 int ChangeImage;
 //параметры перемещения персонажа
 int ModeOfMove;//режим перемещения
 int TimeOfMove;//время перемещения
 int TimeOfLife;//время жизни персонажа
 int LifeMode;//режим (1-рождение;2-жизнь;3-гибель)
};
struct CHARACTER_6
{
 float X;
 float Y;
 int CurrentImage;
 int ChangeImage;
 //параметры перемещения персонажа
 int ModeOfMove;//режим перемещения
 int TimeOfMove;//время перемещения
 int TimeOfLife;//время жизни персонажа
 int LifeMode;//режим (1-рождение;2-жизнь;3-гибель)
};
struct CHARACTER_7
{
 float X[6];
 float Y[6];
 int CurrentImage[6];
 int ChangeImage[6];
 //параметры перемещения персонажа
 int ModeOfMove[6];//режим перемещения
 int TimeOfMove[6];//время перемещения
 int TimeOfLife;//время жизни персонажа
 int LifeMode[6];//режим (1-рождение;2-жизнь;3-гибель)
};
struct CHARACTER_8
{
 float X;
 float Y;
 int CurrentImage;
 int ChangeImage;
 //параметры перемещения персонажа
 int ModeOfMove;//режим перемещения
 int TimeOfMove;//время перемещения
 int TimeOfLife;//время жизни персонажа
 int LifeMode;//режим (1-рождение;2-жизнь;3-гибель)
};
struct CHARACTER_9
{
 float X;
 float Y;
 int CurrentImage;
 int ChangeImage;
 //параметры перемещения персонажа
 int ModeOfMove;//режим перемещения
 int TimeOfMove;//время перемещения
 int TimeOfLife;//время жизни персонажа
 int LifeMode;//режим (1-рождение;2-жизнь;3-гибель)
};
//--------------------------------------------------------------------------
class CHARACTERMAP
{
 protected:
  //-----------------------------------------------------------
  SPRITE Character1Sprite;//спрайты персонажей	
  int Character1_Birth_Frame_Start;
  int Character1_Birth_Frame_End;
  int Character1_Life_Frame_Start;
  int Character1_Life_Frame_End;
  int Character1_Destruction_Frame_Start;
  int Character1_Destruction_Frame_End;
  CHARACTER_1 Character1[5];
  int CurrentCharacter1;
  float Character1Radius;
  int TimerDoStartCharacter1;//время до появления персонажа 1-го типа (если это возможно)
  //-----------------------------------------------------------
  SPRITE Character2Sprite;//спрайты персонажей	
  int Character2_Birth_Frame_Start;
  int Character2_Birth_Frame_End;
  int Character2_Life_Frame_Start;
  int Character2_Life_Frame_End;
  int Character2_Destruction_Frame_Start;
  int Character2_Destruction_Frame_End;
  int Character2_Explosion_Frame_Start;
  int Character2_Explosion_Frame_End;
  CHARACTER_2 Character2[5];
  int CurrentCharacter2;
  float Character2Radius;
  int TimerDoStartCharacter2;//время до появления персонажа 2-го типа (если это возможно)
  //-----------------------------------------------------------
  SPRITE Character3Sprite;//спрайты персонажей	
  int Character3_Birth_Frame_Start;
  int Character3_Birth_Frame_End;
  int Character3_Life_Frame_Start;
  int Character3_Life_Frame_End;
  int Character3_Destruction_Frame_Start;
  int Character3_Destruction_Frame_End;
  CHARACTER_3 Character3[5];
  int CurrentCharacter3;
  float Character3Radius;
  int TimerDoStartCharacter3;//время до появления персонажа 3-го типа (если это возможно)
  //-----------------------------------------------------------
  SPRITE Character4Sprite;//спрайты персонажей	
  int Character4_Birth_Frame_Start;
  int Character4_Birth_Frame_End;
  int Character4_Life_Frame_Start;
  int Character4_Life_Frame_End;
  int Character4_Destruction_Frame_Start;
  int Character4_Destruction_Frame_End;
  CHARACTER_4 Character4[5];
  int CurrentCharacter4;
  float Character4Radius;
  int TimerDoStartCharacter4;//время до появления персонажа 4-го типа (если это возможно)
  //-----------------------------------------------------------
  SPRITE Character5Sprite;//спрайты персонажей	
  int Character5_Birth_Frame_Start;
  int Character5_Birth_Frame_End;
  int Character5_Life_Frame_Start;
  int Character5_Life_Frame_End;
  int Character5_Destruction_Frame_Start;
  int Character5_Destruction_Frame_End;
  CHARACTER_5 Character5[5];
  int CurrentCharacter5;
  float Character5Radius;
  int TimerDoStartCharacter5;//время до появления персонажа 5-го типа (если это возможно)
  //-----------------------------------------------------------
  SPRITE Character6Sprite;//спрайты персонажей	
  int Character6_Birth_Frame_Start;
  int Character6_Birth_Frame_End;
  int Character6_Life_Frame_Start;
  int Character6_Life_Frame_End;
  int Character6_Destruction_Frame_Start;
  int Character6_Destruction_Frame_End;
  CHARACTER_6 Character6[5];
  int CurrentCharacter6;
  float Character6Radius;
  int TimerDoStartCharacter6;//время до появления персонажа 6-го типа (если это возможно)
  //-----------------------------------------------------------
  SPRITE Character7Sprite;//спрайты персонажей	
  int Character7_Birth_Frame_Start;
  int Character7_Birth_Frame_End;
  int Character7_Life_Frame_Start;
  int Character7_Life_Frame_End;
  int Character7_Destruction_Frame_Start;
  int Character7_Destruction_Frame_End;
  CHARACTER_7 Character7[5];
  int CurrentCharacter7;
  float Character7Radius;
  int TimerDoStartCharacter7;//время до появления персонажа 7-го типа (если это возможно)
  //-----------------------------------------------------------
  SPRITE Character8Sprite;//спрайты персонажей	
  int Character8_Birth_Frame_Start;
  int Character8_Birth_Frame_End;
  int Character8_Life_Frame_Start;
  int Character8_Life_Frame_End;
  int Character8_Destruction_Frame_Start;
  int Character8_Destruction_Frame_End;
  CHARACTER_8 Character8[5];
  int CurrentCharacter8;
  float Character8Radius;
  int TimerDoStartCharacter8;//время до появления персонажа 8-го типа (если это возможно)
  //-----------------------------------------------------------
  SPRITE Character9Sprite;//спрайты персонажей	
  int Character9_Birth_Frame_Start;
  int Character9_Birth_Frame_End;
  int Character9_Life_Frame_Start;
  int Character9_Life_Frame_End;
  int Character9_Destruction_Frame_Start;
  int Character9_Destruction_Frame_End;
  CHARACTER_9 Character9[5];
  int CurrentCharacter9;
  float Character9Radius;
  int TimerDoStartCharacter9;//время до появления персонажа 9-го типа (если это возможно)
  //-----------------------------------------------------------
  int Step;
  //-----------------------------------------------------------
 public:
  //-----------------------------------------------------------
  void Create(void);
  void Release(void);
  void CreateSpriteSurface(LPDIRECTDRAW7 lpdd);
  void ReleaseSpriteSurface(void);
  //-----------------------------------------------------------
  void InitializeToStartLevel(void);
  //-----------------------------------------------------------
  void LoadCharacter1Sprite(void);
  void CreateNewCharacter1(int x,int y);
  void DestroyCharacter1(int character);
  void DeleteCharacter1(int character);
  void AnimateCharacter1(void);
  void MoveCharacter1(void);
  void PutCharacter1(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void DestroyAllCharacter1(void);
  //-----------------------------------------------------------
  void LoadCharacter2Sprite(void);
  void CreateNewCharacter2(int x,int y);
  void DestroyCharacter2(int character);
  void ExplosionCharacter2(int character);
  void DeleteCharacter2(int character);
  void AnimateCharacter2(void);
  void MoveCharacter2(void);
  void PutCharacter2(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void DestroyAllCharacter2(void);
  //-----------------------------------------------------------
  void LoadCharacter3Sprite(void);
  void CreateNewCharacter3(int x,int y);
  void DestroyCharacter3(int character);
  void DeleteCharacter3(int character);
  void AnimateCharacter3(void);
  void MoveCharacter3(void);
  void PutCharacter3(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void DestroyAllCharacter3(void);
  //-----------------------------------------------------------
  void LoadCharacter4Sprite(void);
  void CreateNewCharacter4(int x,int y);
  void DestroyCharacter4(int character);
  void DeleteCharacter4(int character);
  void AnimateCharacter4(void);
  void MoveCharacter4(void);
  void PutCharacter4(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void DestroyAllCharacter4(void);
  //-----------------------------------------------------------
  void LoadCharacter5Sprite(void);
  void CreateNewCharacter5(int x,int y);
  void DestroyCharacter5(int character);
  void DeleteCharacter5(int character);
  void AnimateCharacter5(void);
  void MoveCharacter5(void);
  void PutCharacter5(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void DestroyAllCharacter5(void);
  //-----------------------------------------------------------
  void LoadCharacter6Sprite(void);
  void CreateNewCharacter6(int x,int y);
  void DestroyCharacter6(int character);
  void DeleteCharacter6(int character);
  void AnimateCharacter6(void);
  void MoveCharacter6(void);
  void PutCharacter6(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void DestroyAllCharacter6(void);
  //-----------------------------------------------------------
  void LoadCharacter7Sprite(void);
  void CreateNewCharacter7(int x,int y);
  void DestroyCharacter7(int character,int segment);
  void DeleteCharacter7(int character);
  void AnimateCharacter7(void);
  void MoveCharacter7(void);
  void PutCharacter7(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void DestroyAllCharacter7(void);
  //-----------------------------------------------------------
  void LoadCharacter8Sprite(void);
  void CreateNewCharacter8(int x,int y);
  void DestroyCharacter8(int character);
  void DeleteCharacter8(int character);
  void AnimateCharacter8(void);
  void MoveCharacter8(void);
  void PutCharacter8(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void DestroyAllCharacter8(void);
  //-----------------------------------------------------------
  void LoadCharacter9Sprite(void);
  void CreateNewCharacter9(int x,int y);
  void DestroyCharacter9(int character);
  void DeleteCharacter9(int character);
  void AnimateCharacter9(void);
  void MoveCharacter9(void);
  void PutCharacter9(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void DestroyAllCharacter9(void);
  //-----------------------------------------------------------
  void PutAllCharacter(LPDIRECTDRAWSURFACE7 lpddssurface,DDSURFACEDESC2 ddsd);
  void DestroyAllCharacter(void);
  void ChangeImageFrame(void);
  void Processing(void);
  float ImpactCharacterToBall(int ball_x,int ball_y,int ball_radius,float ball_angle);
  int ImpactCharacterToMissile(int xleft,int xright,int yup,int ydown);
} CharacterMap; 
//--------------------------------------------------------------------------