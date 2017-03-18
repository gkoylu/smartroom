#include <virtuabotixRTC.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>  
LiquidCrystal_I2C lcd(0x27,16,2); 
#include <dht11.h> 
#define DHT11PIN 11   
#include <SoftwareSerial.h>
virtuabotixRTC myRTC(6, 5, 4);
SoftwareSerial btserial(2,3);// rx,tx bt
dht11 DHT11;

int relay1=8;
int led1d;
int led2d;
int led3d;
int relay1d;
char unChar;
String data;
int led1=12;
int led2;
int led3;
int ISINEMgonder;
int say;

void setup()
{
 lcd.init();                      

pinMode(relay1,OUTPUT);
pinMode(led1,OUTPUT);
 lcd.backlight();                
    
     Serial.begin(9600);
 //myRTC.setDS1302Time(50, 00, 00,4, 15,03, 2017);
btserial.begin(9600);
 
  relay1d=0;
}
void loop()
{
  while(btserial.available())
{

unChar = btserial.read();
data +=unChar;

delay(1);
if(data=="S")  // servo motoru S komutu ile çalıştırır.
{
  motor1();
  }
  if(data=="ab")  // led 1 i ab komutu ile açar
  {if(led1d==0)
  {
    digitalWrite(led1,1);
  led1d=1;
  }
    
    }
    if(data=="ba"){  // led 1 i ba komutu ile kapatır
      if(led1d==1)
      {
      digitalWrite(led1,0);
      led1d=0;
      }}
      if(data=="ca")  // led 2 yi ca komutu ile açar
      {
        if(led2d==0)
        {digitalWrite(led2,1);
        led2d=1;
        }}
        if(data=="ac") // led 2 yi ac komutu ile kapatır
        {if(led2d==1)
          {digitalWrite(led2,0);
          led2d=0;
          }}
          if(data=="ea") // led 3 ü ea komutu ile açar
          {if(led3d==0)
          {
            digitalWrite(led3,1);
          led3d=1;
          }}
            if(data=="ae") // led 3 ü ae komutu ile kapatır
            {
              if(led3d==1)
              {digitalWrite(led3,0);
              led3d=0;
              }}
              if(data=="fa") // röle 1 i fa komutu ile açar
              {if(relay1d==0)
              {digitalWrite(relay1,1);
              relay1d=1;
                }
                }
                if(data=="af") // röle 1 i af komutu ile kapatır
                {if(relay1d==1)
                {digitalWrite(relay1,0);
                relay1d=0;
                  }
                  }
                  if(data=="ga")
                  {
                    ISINEM();
                    }
                    if(data=="ag")
                    {
                        delay(50);                  
                        btserial.print("Mesafe : ");
                        //btserial.print(sonar.ping_cm()); 
                        btserial.println(" cm\n");
                      }
                       if(data=="ha")
                  {
                    lcd.backlight();
                    }
                     if(data=="ah")
                  {
                    lcd.noBacklight();
                    }
                     
  //Serial.println(data);                    
                  

}
data="";
  myRTC.updateTime();

 


if(say % 2000==0 ){
LcdIsinem();}
   
if(say %4000==0){LcdTarih();}
  say++;


 
}



void motor1() // Servo motoru gelen değer ile açısal hareket ettirir.
{
//   delay(100);
//  while(btserial.available())
//  {
//   
//    char c =btserial.read();
//    poz=poz+c;
//    }
//   if(poz.length()>0)
//   {
//      btserial.println(poz.toInt());
//      servom.write(poz.toInt());
//      Serial.println(poz);
//    
//     poz="";
//     }
  }

void ISINEM() 
{
  ISINEMgonder=2000;
   int chk = DHT11.read(DHT11PIN);

  
  btserial.print("Nem(%): ");
  btserial.print((float)DHT11.humidity, 0);

  btserial.print("  Sicaklik : ");
  btserial.print((float)DHT11.temperature, 0);
  btserial.println();


  delay(1);
   
  }

void LcdIsinem()
{
  lcd.setCursor(1,0); 
   int chk = DHT11.read(DHT11PIN);
 lcd.clear(); 
 lcd.setCursor(0,0); 
 lcd.print("Sicaklik:");
 lcd.setCursor(10,0); 
 lcd.print((float)DHT11.temperature,0); 
 lcd.setCursor(12,0);
 lcd.print("'C");
 lcd.setCursor(0,1);
 lcd.print("Nem %:");
 lcd.setCursor(7,1);
 lcd.print((float)DHT11.humidity,0);
}
 //delay(2000);
 void LcdTarih()
 {
  lcd.clear(); 
 lcd.setCursor(0,0); 

 lcd.print(myRTC.dayofmonth); 
 lcd.setCursor(2,0);
 lcd.print(".");
 lcd.setCursor(3,0);
 lcd.print(myRTC.month);
 lcd.setCursor(5,0);
 lcd.print(".");
 lcd.setCursor(6,0);
 lcd.print(myRTC.year);
 lcd.setCursor(0,1);
  lcd.print(myRTC.hours); 
 lcd.setCursor(2,1);
 lcd.print(":");
 lcd.setCursor(3,1);
 lcd.print(myRTC.minutes);
 lcd.setCursor(5,1);
 lcd.print(":");
 lcd.setCursor(6,1);
 lcd.print(myRTC.seconds);
 //delay(2000);
  }





