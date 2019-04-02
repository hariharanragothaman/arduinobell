//C.O.D.E ~ Electric Bell

#include <LiquidCrystal.h>
#include "Wire.h"
#define DS1307_I2C_ADDRESS 0x68


LiquidCrystal lcd(4,7,8,9,12,13);

/* RELAY CIRCUIT DEFINITIONS */
// Circuitry:- red --ground ,orange-- supply 

int relay= 8; // black
int current_pin=9; //brown

/* Function for Type Conversions */ 
byte decToBcd(byte val)
  {
    return ( (val/10*16) + (val%10) );
  }

byte bcdToDec(byte val)
  {
   return ( (val/16*10) + (val%16) );
  }

 
void stopDs1307()
{
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.send(0);
  Wire.send(0x80);
  Wire.endTransmission();
}

// FUNCTION TO SET DATA ...
void setDateDs1307(byte second, // 0-59
 byte minute, // 0-59
 byte hour, // 1-23
 byte dayOfWeek, // 1-7
 byte dayOfMonth, // 1-28/29/30/31
 byte month, // 1-12
 byte year) // 0-99
  {
      Wire.beginTransmission(DS1307_I2C_ADDRESS);
      Wire.send(0); Wire.send(decToBcd(second)); // 0 to bit 7 starts the clock
      Wire.send(decToBcd(minute));
      Wire.send(decToBcd(hour)); // If you want 12 hour am/pm you need to set
        // bit 6 (also need to change readDateDs1307)
      Wire.send(decToBcd(dayOfWeek));
      Wire.send(decToBcd(dayOfMonth));
      Wire.send(decToBcd(month));
      Wire.send(decToBcd(year));
      Wire.endTransmission();
  }
// END OF SETTING FUNCTION ..................


// FUNCTION TO GET TIME AND DATE FROM DS1307
void getDateDs1307(byte *second,
 byte *minute,
 byte *hour,
 byte *dayOfWeek,
 byte *dayOfMonth,
 byte *month,
 byte *year)
  {
    // Reset the register pointer
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.send(0);
    Wire.endTransmission();
    Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
    // A few of these need masks because certain bits are control bits
    *second = bcdToDec(Wire.receive() & 0x7f);
    *minute = bcdToDec(Wire.receive());
    *hour = bcdToDec(Wire.receive() & 0x3f); // Need to change this if 12 hour am/pm
    *dayOfWeek = bcdToDec(Wire.receive());
    *dayOfMonth = bcdToDec(Wire.receive());
    *month = bcdToDec(Wire.receive());
    *year = bcdToDec(Wire.receive());
  }

// END OF FUNCTION ...


// SETUP FUNCTION ..
void setup()
{
  pinMode(14,OUTPUT); lcd.begin(16,2);
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  Wire.begin();
  Serial.begin(9600);
  second=0;
  minute=10;
  hour=8;
  dayOfWeek=1;
  dayOfMonth=19;
  month=10;
  year=11;
  setDateDs1307(second, minute, hour, dayOfWeek, dayOfMonth, month, year);
}

/* LOOP FUNCTION */ 

void loop()
  {
    byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
    getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
    Serial.print(hour, DEC);
    lcd.setCursor(0,0);
    lcd.print(hour, DEC);
    Serial.print(":");
    lcd.print(":");
    Serial.print(minute, DEC);
    lcd.print(minute, DEC);
    Serial.print(":");
    lcd.print(":");
    Serial.print(second, DEC);
    lcd.print(second, DEC);
    Serial.print(" ");
    Serial.print(month, DEC);
    Serial.print("/");
    Serial.print(dayOfMonth, DEC);
    Serial.print("/");
    Serial.print(year, DEC);
    Serial.print(" Day_of_week:");
    Serial.println(dayOfWeek, DEC);
 
    /*  CONSTRAINTS */
 
    if((hour==8 && minute ==10 &&second >=10) && (hour==8 && minute ==10 &&second <=50))
    digitalWrite(14,HIGH);
    else if((hour==8 && minute ==30 &&second >=00) && (hour==8 && minute ==30 &&second <=20))
    digitalWrite(14,HIGH);
    else if((hour==9 && minute ==30 &&second >=00) && (hour==9 && minute ==30 &&second <=20))
    digitalWrite(14,HIGH);
    else if((hour==10 && minute ==30 &&second >=00) && (hour==10 && minute ==30 &&second <=20))
    digitalWrite(14,HIGH); else if((hour==11 && minute ==30 &&second >=00) && (hour==11 && minute ==30 &&second <=20))
    digitalWrite(14,HIGH);
    else if((hour==12 && minute ==10 &&second >=00) && (hour==12 && minute ==10 &&second <=20))
    digitalWrite(14,HIGH);
    else if((hour==1 && minute ==10 &&second >=00) && (hour==1 && minute ==10 &&second <=20))
    digitalWrite(14,HIGH);
    else if((hour==2 && minute ==10 &&second >=00) && (hour==2&& minute ==10 &&second <=20))
    digitalWrite(14,HIGH);
    else if((hour==2&& minute ==30 &&second >=00) && (hour==2 && minute ==30 &&second <=20))
    digitalWrite(14,HIGH);
    else if((hour==3 && minute ==30 &&second >=00) && (hour==3 && minute ==30 &&second <=20))
    digitalWrite(14,HIGH);
    else if((hour==4 && minute ==30 &&second >=00) && (hour==4 && minute ==30 &&second <=20))
    digitalWrite(14,HIGH);
 
    else
    digitalWrite(14,LOW);
    delay(1000);
  }
