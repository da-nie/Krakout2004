#define SOUND__MUSIC_1      0
#define SOUND__MUSIC_2      1

#define SOUND__IMPACT_1     2
#define SOUND__IMPACT_2     3
#define SOUND__IMPACT_3     4
#define SOUND__IMPACT_4     5
#define SOUND__IMPACT_5     6
#define SOUND__IMPACT_6     7
#define SOUND__BREAK_1      8

#define SOUND__PRIZE_OPEN   9
#define SOUND__PRIZE_X      10
#define SOUND__PRIZE_B      11
#define SOUND__PRIZE_E      12
#define SOUND__PRIZE_G      13
#define SOUND__PRIZE_S      14
#define SOUND__PRIZE_S_END  15
#define SOUND__PRIZE_PLUS   16
#define SOUND__PRIZE_MINUS  17

#define SOUND__MENU         18
#define SOUND__GAME_OVER    19
#define SOUND__LOSE         20
#define SOUND__MISSILE      21
#define SOUND__DESTROY      22
#define SOUND__CHANGE_LEVEL 23
#define SOUND__DOLLAR       24
#define SOUND__DOUBLE_BALL  25
#define SOUND__BIRTH        26
#define SOUND__LEVEL_UP     27
#define SOUND__MISSILE_ON   28

class SOUND
{
 public:
 //-----------------------------------------------------------
 DIRECT_SOUND Ds;
 DIRECT_SOUND Ds_Music;
 //-----------------------------------------------------------
 SOUND_INFO Sound_Info[30];
 int music_audiobuffer;//номер буфера для музыки (он не меняется, т.к музыка может быть только одна)
 //-----------------------------------------------------------
 SOUND(void);
 ~SOUND(void);
 //-----------------------------------------------------------
 void Create(HWND hWnd);
 void Release(void);
 void PlaySound(int no,int loop,int volumeprocent);
 void PlayMusic(int no,int loop);
 void StopAllSound(void);
 void StopAllMusic(void);
 void MainLoop(void);
 void SetMusicVolume(int volumeprocent);
 //-----------------------------------------------------------
} Sound;
//--------------------------------------------------------------------------
SOUND::SOUND(void)
{
 for(int n=0;n<20;n++) Sound_Info[n].Image=NULL;
}
SOUND::~SOUND(void)
{
 Release();
}
//--------------------------------------------------------------------------
void SOUND::Create(HWND hWnd)
{
 Ds.Create(hWnd);
 Ds_Music.Create(hWnd);
 Sound_Info[SOUND__MUSIC_1]=Ds.LoadWavFile("sound\\k_music_1.wav");
 Sound_Info[SOUND__MUSIC_2]=Ds.LoadWavFile("sound\\k_music_2.wav");
 Sound_Info[SOUND__IMPACT_1]=Ds.LoadWavFile("sound\\k_impact_1.wav");
 Sound_Info[SOUND__IMPACT_2]=Ds.LoadWavFile("sound\\k_impact_2.wav");
 Sound_Info[SOUND__IMPACT_3]=Ds.LoadWavFile("sound\\k_impact_3.wav");
 Sound_Info[SOUND__IMPACT_4]=Ds.LoadWavFile("sound\\k_impact_4.wav");
 Sound_Info[SOUND__IMPACT_5]=Ds.LoadWavFile("sound\\k_impact_5.wav");
 Sound_Info[SOUND__IMPACT_6]=Ds.LoadWavFile("sound\\k_impact_6.wav");
 Sound_Info[SOUND__BREAK_1]=Ds.LoadWavFile("sound\\k_break_1.wav");
 
 Sound_Info[SOUND__PRIZE_OPEN]=Ds.LoadWavFile("sound\\k_prize_open.wav");
 Sound_Info[SOUND__PRIZE_X]=Ds.LoadWavFile("sound\\k_X.wav");
 Sound_Info[SOUND__PRIZE_B]=Ds.LoadWavFile("sound\\k_B.wav");
 Sound_Info[SOUND__PRIZE_E]=Ds.LoadWavFile("sound\\k_E.wav");
 Sound_Info[SOUND__PRIZE_G]=Ds.LoadWavFile("sound\\k_G.wav");
 Sound_Info[SOUND__PRIZE_S]=Ds.LoadWavFile("sound\\k_S.wav");
 Sound_Info[SOUND__PRIZE_S_END]=Ds.LoadWavFile("sound\\k_S_End.wav");
 Sound_Info[SOUND__PRIZE_PLUS]=Ds.LoadWavFile("sound\\k_speed_+.wav");
 Sound_Info[SOUND__PRIZE_MINUS]=Ds.LoadWavFile("sound\\k_Speed_-.wav");

 Sound_Info[SOUND__GAME_OVER]=Ds.LoadWavFile("sound\\k_GameOver.wav");
 Sound_Info[SOUND__LOSE]=Ds.LoadWavFile("sound\\k_lose.wav");
 Sound_Info[SOUND__MISSILE]=Ds.LoadWavFile("sound\\k_missile.wav");
 Sound_Info[SOUND__MENU]=Ds.LoadWavFile("sound\\k_menu.wav");
 Sound_Info[SOUND__DESTROY]=Ds.LoadWavFile("sound\\k_destroy.wav");
 Sound_Info[SOUND__CHANGE_LEVEL]=Ds.LoadWavFile("sound\\k_change_level.wav");
 Sound_Info[SOUND__DOLLAR]=Ds.LoadWavFile("sound\\k_dollar.wav");
 Sound_Info[SOUND__DOUBLE_BALL]=Ds.LoadWavFile("sound\\k_double_ball.wav");
 Sound_Info[SOUND__BIRTH]=Ds.LoadWavFile("sound\\k_birth.wav");
 Sound_Info[SOUND__LEVEL_UP]=Ds.LoadWavFile("sound\\k_level_up.wav");
 Sound_Info[SOUND__MISSILE_ON]=Ds.LoadWavFile("sound\\k_missile_on.wav");
}
void SOUND::Release(void)
{
 Ds.Release();
 Ds_Music.Release();
 for(int n=0;n<20;n++)
 {
  if (Sound_Info[n].Image!=NULL) delete(Sound_Info[n].Image);
 }
}
//--------------------------------------------------------------------------
void SOUND::PlaySound(int no,int loop,int volumeprocent)
{
 int buffer=Ds.CreateNewAudioBuffer(Sound_Info[no]);
 Ds.SetAudioBufferData(buffer,Sound_Info[no]);
 int volume=-20*(100-volumeprocent);
 Ds.SetVolumeAudioBuffer(buffer,volume);
 Ds.PlayAudioBuffer(buffer,loop);
}
void SOUND::PlayMusic(int no,int loop)
{
 music_audiobuffer=Ds_Music.CreateNewAudioBuffer(Sound_Info[no]);
 Ds_Music.SetAudioBufferData(music_audiobuffer,Sound_Info[no]);
 Ds_Music.PlayAudioBuffer(music_audiobuffer,loop);
}
void SOUND::StopAllSound(void)
{
 Ds.StopAllAudioBuffer();
 Ds.DeleteAllAudioBuffer();
}
void SOUND::StopAllMusic(void)
{
 Ds_Music.StopAllAudioBuffer();
 Ds_Music.DeleteAllAudioBuffer();
}
void SOUND::MainLoop(void)
{
 Ds.DeleteNotPlayingAudioBuffer();
}
void SOUND::SetMusicVolume(int volumeprocent)
{
 int volume=-20*(100-volumeprocent);
 Ds_Music.SetVolumeAudioBuffer(music_audiobuffer,volume);
} 