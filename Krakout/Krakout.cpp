#define M_PI 3.14159265358979
#include <windows.h>   
#include <initguid.h>
#include <stdio.h>
#include <ddraw.h>
#include <dsound.h>
#include <math.h>
//--------------------------------------------------------------------------
#define FPS 60.0
//--------------------------------------------------------------------------
HINSTANCE hProjectInstance;
#include "sprites.h"
#include "basis.h"
#include "font.h"
#include "ds_class.h"
#include "sound.h"
#include "character_head.h"
#include "menu.h"
#include "paddle.h"
#include "block.h"
#include "missile.h"
#include "ball.h"
#include "character_body.h"
#include "game.h"
#include "wnd_main.h"
//------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevstance,LPSTR lpstrCmdLine,int nCmdShow)
{
 hProjectInstance=hInstance;
 MSG msg;
 WND_MAIN_Register();
 CreateWindow("Wnd_Main","Krakout",WS_POPUP|WS_VISIBLE,0,0,0,0,0,0,hProjectInstance,NULL);
 int step=0;
 LARGE_INTEGER start_time;
 LARGE_INTEGER current_time;
 LARGE_INTEGER CounterFrequency;
 QueryPerformanceFrequency(&CounterFrequency);
 double d_CounterFrequency=(double)CounterFrequency.QuadPart;
 QueryPerformanceCounter(&start_time);
 while(1)
 {
  Sound.MainLoop();//вызываем функцию удаления закончивших воспроизведение звуков
  while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
  {
   if (msg.message==WM_QUIT) break;
   TranslateMessage(&msg);
   DispatchMessage(&msg);
  }
  if (msg.message==WM_QUIT) break;
  //делаем синхронизацию по таймеру
  while(1)
  {
   QueryPerformanceCounter(&current_time);
   double delta_time=(double)(current_time.QuadPart-start_time.QuadPart);
   if (delta_time<0) 
   {
    start_time=current_time;
    continue;
   }
   if (delta_time<d_CounterFrequency/FPS) continue;
   break;
  }
  QueryPerformanceCounter(&start_time);
  Wnd_Main.Processing(step);//основной процесс игры step-значение шага в текущий момент
  step++;//step нужно т.к. некоторые процессы должны идти медленнее чем частота таймера
  if (step==2) step=0;
 }
 return(msg.wParam);
}


/*
 double d_start_time=(double)start_time.QuadPart;
 while(1)
 {
  Sound.MainLoop();//вызываем функцию удаления закончивших воспроизведение звуков
  while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
  {
   if (msg.message==WM_QUIT) break;
   TranslateMessage(&msg);
   DispatchMessage(&msg);
  }
  if (msg.message==WM_QUIT) break;
  //делаем синхронизацию по таймеру
  while(1)
  {
   QueryPerformanceCounter(&current_time);
   double d_current_time=(double)current_time.QuadPart;
   double delta_time=d_current_time-d_start_time;
   if (delta_time<0) 
   {
    d_start_time=d_current_time;
    continue;
   }
   if (delta_time<d_CounterFrequency/FPS) continue;
   break;
  }
  QueryPerformanceCounter(&start_time);
  d_start_time=(double)start_time.QuadPart;
  Wnd_Main.Processing(step);//основной процесс игры step-значение шага в текущий момент
  step++;//step нужно т.к. некоторые процессы должны идти медленнее чем частота таймера
  if (step==2) step=0;
 }
 return(msg.wParam);
}

  */