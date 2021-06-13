struct STAR
{
 float X;
 float Y;
 float Speed;
 unsigned char R[4];
 unsigned char G[4];
 unsigned char B[4];
};
struct HISCORE
{
 char Name[21];
 int Score;
};
struct GAME_PARAMETERS
{
 int Life;//жизни
 int Score;//очки
 int Level;//уровень
 int Practics;//1-режим практики
 int BallSpeed;//скорость мячей
 int BallSpeedPrizeTime;//время работы призов ускорения и замедления
 int RightWall;//1-существует правая стенка
 int RightWallTime;//время существования правой стенки
 int StartLevel;//начальный уровень для практики
 int MaxLevel;//всего уровней доступно
 int EnableCharacter[10];//1-персонаж доступен на уровне

 int SpecialMode;//специальный режим
 int MusicVolume;//громкость музыки в игре
 int SoundVolume;//громкость звуков в игре

 int DemoMode;//1-включен режим демонстрации
 int SelectBlock_X;//выбранный блок для автоматического управления биткой
 int SelectBlock_Y;

} GameParameters;
//--------------------------------------------------------------------------
float NormalizeAngle(float Angle)
{
 //приведение угла в диапазон 0-360
 while(Angle>=360) Angle-=360;
 while(Angle<0) Angle+=360;
 return(Angle);
}
int CircleIntercectionToLine(float x1,float y1,float x2,float y2,float xc,float yc,float r)
{
 //проверка пересечения окружности с отрезком.
 float xl1=x1-xc;
 float yl1=y1-yc;
 float xl2=x2-xc;
 float yl2=y2-yc;
 float a=xl2-xl1;
 float b=yl2-yl1;
 float kd=a*a+b*b;
 float ld=2*a*xl1+2*b*yl1;
 float md=xl1*xl1+yl1*yl1-r*r;
 float d=ld*ld-4*kd*md;
 if (d<0) return(0);
 float sd=(float)sqrt(d);
 float l1=(-ld+sd)/(2*kd);
 float l2=(-ld-sd)/(2*kd);
 float xp1=xl1+l1*a;
 float yp1=yl1+l1*b;
 float xp2=xl1+l2*a;
 float yp2=yl1+l2*b;
 //проверим, находится ли точка пересечения с прямой в отрезке
 if (((xp1>=xl1 && xp1<=xl2) || (xp1>=xl2 && xp1<=xl1)) &&
    ((yp1>=yl1 && yp1<=yl2) || (yp1>=yl2 && yp1<=yl1))) return(1);
 if (((xp2>=xl1 && xp2<=xl2) || (xp2>=xl2 && xp2<=xl1)) &&
    ((yp2>=yl1 && yp2<=yl2) || (yp2>=yl2 && yp2<=yl1))) return(1);
 return(0);
}
int FindStringInFile(FILE *File,char *SearchString)
{
 //функция ищет строку в файле  
 unsigned char byte;
 int pos=0;
 while(1)
  {
   if (fread(&byte,1,1,File)==0) break;
   if (byte==SearchString[pos]) pos++;
                           else pos=0;
   if (pos==(int)(strlen(SearchString))) return(1);
  }
 return(0);
}
int GetParameters(char *FileName,char *ParametersName,int *parameters)
{
 //функция читает значение пареметра из файла
 FILE *file=fopen(FileName,"r+b");
 if (file==NULL) return(0);
 if (FindStringInFile(file,ParametersName))
 {
  fscanf(file,"%i",parameters);
  fclose(file);
  return(1);
 }
 fclose(file);
 return(0);
}