#include <SimpleTimer.h>
SimpleTimer timer;
int timer_ayar;
//int frekans = 10;  //Hz
//int duty    = 5 ;    //%
int frekans;  //Hz
int duty;    //%
int cikis=13;
int duty_saniye;
int periyot;
int sayac;
String gelen;
int pot_frekans=A0;
int pot_duty=A1;
String data1;
String data2;
int virgul_loc=0;
int secim=1;
int b_num=0;
void setup()
{
  Serial.begin(9600);
  pinMode(cikis,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(pot_frekans,INPUT);
  pinMode(pot_duty,INPUT);
  timer_ayar=timer.setInterval(1,pwm_signal_generator);
  digitalWrite(10,LOW);
}
void loop()
{   
  timer.run();
  timer.enable(timer_ayar);
  gelen=Serial.readString();
  if(secim==1)
  {
      Serial.print("123456");
  }
  if(gelen.indexOf('a')==0)
  {
    frekans=map(analogRead(pot_frekans),0,1023,1,1000);
    duty=map(analogRead(pot_duty),0,1023,1,100);
    periyot=1000/frekans;
    duty_saniye=periyot/(100/duty);
    Serial.print("123456");
    Serial.print(",");
    Serial.print(frekans);
    Serial.print(",");
    Serial.println(duty);
    digitalWrite(10,LOW);
    secim=2;
    gelen="";
  }
  else 
  {
      for(int i=0;i<=gelen.count();i++)
      {
        if(gelen.indexOf('b')==i)
          {
           b_num=i;
           break; 
          }
      }
      gelen.substring(b_num);
      gelen.trim();
      gelen=gelen.substring(1);
      for(int i=0;i<=gelen.length();i++)
      {
        virgul_loc=i;
        if(gelen.indexOf(',')==i)
          break;  
      }
      for(int a=0;a<=virgul_loc-1;a++)
      {
        data1+=gelen[a];
      }
      data2=gelen.substring(virgul_loc+1);
      frekans=data1.toInt();
      duty=data2.toInt();
      /*if(frekans>=0 && frekans<=1000)
        digitalWrite(10,HIGH); 
      if(duty>=0 && duty<=100)
        digitalWrite(10,HIGH);*/
      if(frekans==500)
        digitalWrite(10,HIGH); 
      if(duty==20)
        digitalWrite(10,HIGH);
      periyot=1000/frekans;
      duty_saniye=periyot/(100/duty);
      gelen="";
      secim=3;
  }
  delay(10);
}
void pwm_signal_generator()
{
   sayac++;
   if(sayac<=duty_saniye)
     digitalWrite(cikis,HIGH);
   else if((sayac>duty_saniye) && (sayac<=periyot))
     digitalWrite(cikis,LOW);
   else if( sayac> periyot)
   {
     sayac=0;
     timer.disable(timer_ayar);
   }
}



