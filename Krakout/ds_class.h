#ifndef DSBCAPS_CTRLDEFAULT
#define DSBCAPS_CTRLDEFAULT (DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME )
#endif

struct SOUND_INFO
{
 int Frequency;//�������
 int BlockAlign;//�����������
 int Channels;//����� ������� (����=1, ������=2 � �.�.)
 unsigned char *Image;//������ �����
 unsigned long Size;//����� ������
};

class DIRECT_SOUND
{
 public:
 //-----------------------------------------------------------
 LPDIRECTSOUND lpDS;
 DSBUFFERDESC dsbd;
 WAVEFORMATEX pcmwf;
 //-----------------------------------------------------------
 int IsCreate;//1-�� ��������
 int AudioBuffers;//����� ��������� ����� �������� (����� ������)
 LPDIRECTSOUNDBUFFER *lpdsbuffer;//������ ���������� �� ����� �������

 //-----------------------------------------------------------
 DIRECT_SOUND(void);
 ~DIRECT_SOUND(void);
 //-----------------------------------------------------------
 void Create(HWND hWnd);
 void Release(void);
 int CreateNewAudioBuffer(SOUND_INFO sound_info);
 void SetAudioBufferData(int buffer,SOUND_INFO sound_info);
 void PlayAudioBuffer(int buffer,int loop);
 void DeleteAudioBuffer(int buffer);
 void StopAudioBuffer(int buffer);
 void StopAllAudioBuffer(void);
 void SetVolumeAudioBuffer(int buffer,long volume);
 void SetFrequencyAudioBuffer(int buffer,long frequency);
 void SetPanAudioBuffer(int buffer,long pan);
 int GetStateAudioBuffer(int buffer);
 void DeleteNotPlayingAudioBuffer(void);
 void DeleteAllAudioBuffer(void);
 //-----------------------------------------------------------
 SOUND_INFO LoadWavFile(char *FileName);//������� �������� wav �����
};
//------------------------------------------------------------------------------
DIRECT_SOUND::DIRECT_SOUND(void)
{
 IsCreate=0;
 AudioBuffers=0;
}
DIRECT_SOUND::~DIRECT_SOUND(void)
{
 Release();
}
//------------------------------------------------------------------------------
void DIRECT_SOUND::Create(HWND hWnd)
{
 lpDS=NULL;
 if (FAILED(DirectSoundCreate(NULL,&lpDS,NULL))) return;
  //����� ������� ��������������
 lpDS->SetCooperativeLevel(hWnd,DSSCL_NORMAL);
 IsCreate=1;
}
void DIRECT_SOUND::Release(void)
{
 if (IsCreate!=0)
 {
  if (AudioBuffers!=0)
  {
   for(int n=0;n<AudioBuffers;n++)
   {
	lpdsbuffer[n]->Stop();  
	lpdsbuffer[n]->Release();  
   }
   delete(lpdsbuffer);
   lpdsbuffer=NULL;
   AudioBuffers=0;
  }
  lpDS->Release();
  lpDS=NULL;
  IsCreate=0;
 }
}
int DIRECT_SOUND::CreateNewAudioBuffer(SOUND_INFO sound_info)
{
 if (IsCreate==0 || sound_info.Size<=0 || sound_info.Image==NULL) return(-1);
 //������� ����� ����� ������
 LPDIRECTSOUNDBUFFER *newlpdsbuffer;
 newlpdsbuffer=new LPDIRECTSOUNDBUFFER[AudioBuffers+1];
 for(int n=0;n<AudioBuffers;n++) newlpdsbuffer[n]=lpdsbuffer[n];
 if (AudioBuffers!=0) delete(lpdsbuffer);
 lpdsbuffer=newlpdsbuffer;
 //����� ������ ���������������� �����
 memset(&pcmwf,0,sizeof(WAVEFORMATEX));
 pcmwf.wFormatTag=WAVE_FORMAT_PCM;//������ �����
 pcmwf.nChannels=sound_info.Channels;//����� ������� (1-����,2-������)
 pcmwf.nSamplesPerSec=sound_info.Frequency;//������� ���������
 pcmwf.nBlockAlign=sound_info.BlockAlign;//���������� ������ � ����� (1-8 ���, 2-16 ��� � �.�.)
 pcmwf.nAvgBytesPerSec=pcmwf.nSamplesPerSec*pcmwf.nBlockAlign;//����� �������� ������
 pcmwf.wBitsPerSample=8*sound_info.BlockAlign/sound_info.Channels;//����������� �����
 pcmwf.cbSize=0;//������ 0
 //��������� ��������� ��� �������� ��������������� ����� �������
 memset(&dsbd,0,sizeof(DSBUFFERDESC));
 dsbd.dwSize=sizeof(DSBUFFERDESC);//������ ���� ���������
 dsbd.dwFlags=DSBCAPS_CTRLDEFAULT|DSBCAPS_STATIC|DSBCAPS_LOCSOFTWARE;//�����
 dsbd.dwBufferBytes=sound_info.Size;//������ �������
 dsbd.lpwfxFormat=&pcmwf;//������ �����
 //������ �������������� ����� ������
 if (FAILED(lpDS->CreateSoundBuffer(&dsbd,&(lpdsbuffer[AudioBuffers]),NULL))) return(-1);
 AudioBuffers++;
 return(AudioBuffers-1);
}
void DIRECT_SOUND::SetAudioBufferData(int buffer,SOUND_INFO sound_info)
{
 if (IsCreate==0 || buffer<0 || sound_info.Image==NULL || sound_info.Size<=0 || buffer>=AudioBuffers) return;
 //������� � ������ ������
 UCHAR *audio_ptr1,*audio_ptr2;
 unsigned long audio_length1,audio_length2;
 //��������� ������
 lpdsbuffer[buffer]->Lock(0,sound_info.Size,(void **)&audio_ptr1,&audio_length1,(void **)&audio_ptr2,&audio_length2,DSBLOCK_FROMWRITECURSOR);
 memcpy(audio_ptr1,sound_info.Image,audio_length1);
 memcpy(audio_ptr2,sound_info.Image+audio_length1,audio_length2);
 //������������ ������
 lpdsbuffer[buffer]->Unlock(audio_ptr1,audio_length1,audio_ptr2,audio_length2);
}
void DIRECT_SOUND::PlayAudioBuffer(int buffer,int loop)
{
 if (IsCreate==0 || buffer<0 || buffer>=AudioBuffers) return;
 if (loop!=0) lpdsbuffer[buffer]->Play(0,0,DSBPLAY_LOOPING);
         else lpdsbuffer[buffer]->Play(0,0,0);
}
void DIRECT_SOUND::DeleteAudioBuffer(int buffer)
{
 int n;
 if (IsCreate==0 || buffer<0 || buffer>=AudioBuffers) return;
 lpdsbuffer[buffer]->Stop();
 lpdsbuffer[buffer]->Release();
 LPDIRECTSOUNDBUFFER *newlpdsbuffer;
 newlpdsbuffer=new LPDIRECTSOUNDBUFFER[AudioBuffers-1];
 for(n=0;n<buffer;n++) newlpdsbuffer[n]=lpdsbuffer[n];
 for(n=buffer+1;n<AudioBuffers;n++) newlpdsbuffer[n-1]=lpdsbuffer[n];
 delete(lpdsbuffer);
 AudioBuffers--;
 lpdsbuffer=newlpdsbuffer;
}
void DIRECT_SOUND::StopAudioBuffer(int buffer)
{
 if (IsCreate==0 || buffer<0 || buffer>=AudioBuffers) return;
 lpdsbuffer[buffer]->Stop();
}
void DIRECT_SOUND::StopAllAudioBuffer(void)
{
 if (IsCreate==0) return;
 for(int n=0;n<AudioBuffers;n++) lpdsbuffer[n]->Stop();
}
void DIRECT_SOUND::SetVolumeAudioBuffer(int buffer,long volume)
{
 if (IsCreate==0 || buffer<0 || buffer>=AudioBuffers) return;
 lpdsbuffer[buffer]->SetVolume(volume);
}
void DIRECT_SOUND::SetFrequencyAudioBuffer(int buffer,long frequency)
{
 if (IsCreate==0 || buffer<0 || buffer>=AudioBuffers) return;
 lpdsbuffer[buffer]->SetFrequency(frequency);
}
void DIRECT_SOUND::SetPanAudioBuffer(int buffer,long pan)
{
 if (IsCreate==0 || buffer<0 || buffer>=AudioBuffers) return;
 lpdsbuffer[buffer]->SetPan(pan);
}
int DIRECT_SOUND::GetStateAudioBuffer(int buffer)
{
 if (IsCreate==0 || buffer<0 || buffer>=AudioBuffers) return(-1);
 DWORD status;
 if (FAILED(lpdsbuffer[buffer]->GetStatus(&status))) return(-1);
 if (status&DSBSTATUS_BUFFERLOST) return(-1);
 if (status&DSBSTATUS_LOOPING) return(1);
 if (status&DSBSTATUS_PLAYING) return(1);
 return(0);
}
void DIRECT_SOUND::DeleteNotPlayingAudioBuffer(void)
{
 if (IsCreate==0) return;
 LPDIRECTSOUNDBUFFER *newlpdsbuffer;
 newlpdsbuffer=new LPDIRECTSOUNDBUFFER[AudioBuffers];
 int pos=0;
 for(int n=0;n<AudioBuffers;n++)
 {
  if (GetStateAudioBuffer(n)!=1)//����� �� ������������� ����
  {
   //������ ���� �����
   lpdsbuffer[n]->Release();
   continue;
  }
  else
  {
   newlpdsbuffer[pos]=lpdsbuffer[n];
   pos++;
  }
 }
 delete(lpdsbuffer);
 AudioBuffers=pos;
 lpdsbuffer=new LPDIRECTSOUNDBUFFER[AudioBuffers];
 memcpy(lpdsbuffer,newlpdsbuffer,sizeof(LPDIRECTSOUNDBUFFER)*AudioBuffers);
 delete(newlpdsbuffer);
}
void DIRECT_SOUND::DeleteAllAudioBuffer(void)
{
 if (IsCreate==0) return;
 for(int n=0;n<AudioBuffers;n++) lpdsbuffer[n]->Release();
 if (lpdsbuffer!=NULL) delete(lpdsbuffer);
 lpdsbuffer=NULL;
 AudioBuffers=0;
}
//------------------------------------------------------------------------------
SOUND_INFO DIRECT_SOUND::LoadWavFile(char *FileName)
{
 SOUND_INFO sound_info;
 sound_info.BlockAlign=0;
 sound_info.Channels=0;
 sound_info.Frequency=0;
 sound_info.Image=NULL;
 sound_info.Size=0;

 HMMIO hwav;
 MMCKINFO parent,child;
 WAVEFORMATEX wfmtx;
 parent.ckid=(FOURCC)0;
 parent.cksize=0;
 parent.fccType=(FOURCC)0;
 parent.dwDataOffset=0;
 parent.dwFlags=0;
 child=parent;
 if ((hwav=mmioOpen(FileName,NULL,MMIO_READ|MMIO_ALLOCBUF))==NULL) return(sound_info);
 parent.fccType=mmioFOURCC('W','A','V','E');
 if (mmioDescend(hwav,&parent,NULL,MMIO_FINDRIFF))
  {
   mmioClose(hwav,0);
   return(sound_info);
  }
 child.ckid=mmioFOURCC('f','m','t',' ');
 if (mmioDescend(hwav,&child,&parent,0))
  {
   mmioClose(hwav,0);
   return(sound_info);
  }
 if (mmioRead(hwav,(char *)&wfmtx,sizeof(wfmtx))!=sizeof(wfmtx))
  {
   mmioClose(hwav,0);
   return(sound_info);
  }
 if (wfmtx.wFormatTag!=WAVE_FORMAT_PCM)
  {
   mmioClose(hwav,0);
   return(sound_info);
  }
 if (mmioAscend(hwav,&child,0))
  {
   mmioClose(hwav,0);
   return(sound_info);
  }
 child.ckid=mmioFOURCC('d','a','t','a');
 if (mmioDescend(hwav,&child,&parent,MMIO_FINDCHUNK))
  {
   mmioClose(hwav,0);
   return(sound_info);
  }
 sound_info.Frequency=wfmtx.nSamplesPerSec;
 sound_info.Channels=wfmtx.nChannels;
 sound_info.BlockAlign=wfmtx.nBlockAlign;
 sound_info.Size=child.cksize;
 sound_info.Image=new unsigned char[child.cksize];
 //� ������ ��������� ������ �����
 sound_info.Size=child.cksize;
 mmioRead(hwav,(char *)sound_info.Image,child.cksize);
 mmioClose(hwav,0);
 return(sound_info);
}
