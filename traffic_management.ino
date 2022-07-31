#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
char auth[] = "B1AnlbprCRajHKIfhDcnYZISNtDnK3HD";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "traffic";
char pass[] = "12345678";



int red = D0;
int green = D4;
int traffic_sensor = D5;
int traffic_value = 0;
int traffic_sensor1 = D6;
int traffic_value1 = 0;
int traffic_sensor2 = D7;
int traffic_value2 = 0;
int normal;
int normal_flag;
int traffic;


BLYNK_WRITE(V1)
{
  int button =param.asInt();
  if(button==1)
  {
 
   if(traffic_value ==1)
  {
    Blynk.virtualWrite(V2,"Traffic Starts");
    Blynk.notify("Traffic Starts");
  }
   else if(traffic_value1==1)
  {
    Blynk.virtualWrite(V2,"Medium Traffic");
    Blynk.notify("Medium Traffic");
  }
  else if(traffic_value2==1)
  {
    Blynk.virtualWrite(V2,"Dense Traffic");
    Blynk.notify("Dense Traffic");
  }
  else
  {
    Blynk.virtualWrite(V2,"Normal Traffic");
  }
}
}

void setup()
{
  Serial.begin(9600);
  lcd.init();
 lcd.backlight();
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("connecting to");
      lcd.setCursor(0,1);
   lcd.print(ssid);
 Blynk.begin(auth, ssid, pass);
    lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("connecting to...");
      lcd.setCursor(0,1);
   lcd.print(ssid);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Connected:)");
   delay(1000);
   lcd.clear();
  lcd.print("DENSITY BASED");
  lcd.setCursor(0,1);
  lcd.print("TRAFFIC CONTROL");
  delay(2000);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(traffic_sensor, INPUT);
  pinMode(traffic_sensor1, INPUT);
  pinMode(traffic_sensor2, INPUT);
  timer.setInterval(1000L, main_fun);
}

void main_fun()
{
  if(traffic_value == 1)
  {
    normal_flag = 0;
    traffic = 0;
    traffic_value = 0;
    while(traffic <=19)
    {
      traffic_value1 = digitalRead(traffic_sensor1);
      traffic += 1;
      Serial.println("Ir 1 Count:" + String(traffic));
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Time:"+String(traffic));
      lcd.setCursor(0,1);
      lcd.print("TRAFFIC STARTS");
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);   
      delay(1000);   
    }
  }
  else if(traffic_value1 == 1)
  {
    normal_flag = 0;
    traffic = 0;
    traffic_value1 = 0;
    while(traffic <= 29)
    {
      traffic_value2 = digitalRead(traffic_sensor2);
      traffic += 1;
      Serial.println("Ir 2 Count:" + String(traffic));
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Time:"+String(traffic));
      lcd.setCursor(0,1);
      lcd.print("MEDIUM");
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);   
      delay(1000);   
    }
  }
  else if(traffic_value2 == 1)
  {
    normal_flag = 0;
    traffic = 0;
    traffic_value2 = 0;
    while(traffic <= 49)
    {
      traffic += 1;
      Serial.println("Ir 3 Count:" + String(traffic));
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Time:"+String(traffic));
      lcd.setCursor(0,1);
      lcd.print("DENSE");
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);   
      delay(1000);   
    }
  }
  else
  {
    normal += 1;
    Serial.println("Count:" + String(normal));
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Time:"+String(normal));
    lcd.setCursor(0,1);
      lcd.print("Normal");
    if(normal >= 15)
    {
      traffic_value = digitalRead(traffic_sensor);
      
      normal_flag = !normal_flag;
      normal = 0;
    }
    if(normal_flag == 0)
    {
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
    }
    else
    {
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);        
    }
  }
}

void loop()
{
  timer.run();
  Blynk.run();
}
