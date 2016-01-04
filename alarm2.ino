#include <Wire.h>
#include<EEPROM.h>
#include <RTClib.h>
//#include <LiquidCrystal.h>

//LiquidCrystal lcd(3, 2, 4, 5, 6, 7); 
RTC_DS1307 RTC;
int temp,inc,hours1,minut,add=11;

int next=10;    
int INC=11;
int set_mad=12;

#define buzzer 13

int HOUR,MINUT,SECOND;

 
void setup()
{
 Wire.begin();
 RTC.begin();
 pinMode(INC, INPUT);
 pinMode(next, INPUT);
 pinMode(set_mad, INPUT);
 pinMode(buzzer, OUTPUT);
 digitalWrite(next, HIGH);
 digitalWrite(set_mad, HIGH);
 digitalWrite(INC, HIGH);
 Serial.begin(9600);
      Serial.print("Real Time Clock");
  // lcd.setCursor(0,1);
   Serial.print("Circuit Digest ");
    delay(2000);
    
 if(!RTC.isrunning())
 {
 RTC.adjust(DateTime(__DATE__,__TIME__));
 }
}
 
void loop()
{
   int temp=0,val=1,temp4;
   DateTime now = RTC.now();
   if(digitalRead(set_mad) == 0)      //set Alarm time
   { 
     //lcd.setCursor(0,0);
     Serial.print("  Set Alarm  ");
    delay(2000);
    defualt();
    time();
    delay(1000);
    Serial.print("\n");
    //lcd.clear();
    //lcd.setCursor(0,0);
    Serial.print("  Alarm time ");
    //lcd.setCursor(0,1);
    Serial.print(" has been set  ");
    delay(2000);
 }
 Serial.print("\n");
 //lcd.clear();
 //lcd.setCursor(0,0);
 Serial.print("Time:");
 //lcd.setCursor(6,0);
 Serial.print(HOUR=now.hour(),DEC); 
 Serial.print(":");
 Serial.print(MINUT=now.minute(),DEC);
 Serial.print(":");
 Serial.print(SECOND=now.second(),DEC);
 //lcd.setCursor(0,1);
 Serial.print("Date: ");
 Serial.print(now.day(),DEC);
 Serial.print("/");
 Serial.print(now.month(),DEC);
 Serial.print("/");
 Serial.print(now.year(),DEC);
 match();
 delay(200);
}

void defualt()
{
  //lcd.setCursor(0,1);
  Serial.print(HOUR);
  Serial.print(":");
  Serial.print(MINUT);
  Serial.print(":");
  Serial.print(SECOND);
Serial.print("\n");
}

/*Function to set alarm time and feed time into Internal eeprom*/

void time()                             
{
  int temp=1,minuts=0,hours=0,seconds=0;
    while(temp==1)
    {
     if(digitalRead(INC)==0)
     {
      HOUR++;
      if(HOUR==24)
      {
       HOUR=0;
      }
      while(digitalRead(INC)==0);
     }
     //lcd.clear();
     Serial.print("\n");
      //lcd.setCursor(0,0);
    Serial.print("Set Alarm Time ");
   //Serial.print(x); 
    //lcd.setCursor(0,1);
    Serial.print(HOUR);
    Serial.print(":");
    Serial.print(MINUT);
    Serial.print(":");
    Serial.print(SECOND);

    Serial.print("\n");
    delay(100);
    if(digitalRead(next)==0)
    {
      hours1=HOUR;
      EEPROM.write(add++,hours1);
     temp=2;
     while(digitalRead(next)==0);
    }
    }
    
    while(temp==2)
    {
     if(digitalRead(INC)==0)
     {
      MINUT++;
      if(MINUT==60)
      {MINUT=0;}
      while(digitalRead(INC)==0);
     }
     // lcd.clear();
     Serial.print("\n");
    //lcd.setCursor(0,1);
    Serial.print(HOUR);
    Serial.print(":");
    Serial.print(MINUT);
    Serial.print(":");
    Serial.print(SECOND);

    Serial.print("\n");
    delay(100);
      if(digitalRead(next)==0)
      {
       minut=MINUT;
       EEPROM.write(add++, minut);
       temp=0;
       while(digitalRead(next)==0);
      }
    }
    delay(1000);
}

/* Function to chack medication time */

void match()
{
  int tem[17];
  for(int i=11;i<17;i++)
  {
    tem[i]=EEPROM.read(i);
  }
  if(HOUR == tem[11] && MINUT == tem[12]) 
  {
   beep();
   beep();
   beep();
   beep();
   //lcd.clear();
   Serial.print("\n");
   Serial.print("Wake Up........");
   //lcd.setCursor(0,1);
   Serial.print("Wake Up.......");
   beep();
   beep();
   beep();
   beep();
  }
}

/* function to buzzer indication */

void beep()
{
   digitalWrite(buzzer,HIGH);
   delay(500);
   digitalWrite(buzzer, LOW);
   delay(500);
}

