#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Gpsneo.h>

Gpsneo gps(3,4);
SoftwareSerial mySerial(9, 10);

const int buzzer = 13; 
const int rs = 12, en = 11, d4 = 5, d5 = 7, d6 = 6, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char msg;
char call;

char link[70];
char latitud[15];
char latitudHemisphere[2];
char longitud[15];
char longitudMeridiano[15];

void  setup()
{ 
  mySerial.begin(11520);
  Serial.begin(9600);  
   // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
      lcd.print("EMERGENCY!"); 
      pinMode(buzzer, OUTPUT); 

}

void loop()
{
    gps.getDataGPRMC(latitud,latitudHemisphere,longitud,longitudMeridiano);
    gps.Google(link);
    Serial.println(link);
    Serial.println(latitud);
    Serial.println(latitudHemisphere);
    Serial.println(longitud);
    Serial.println(longitudMeridiano);
    
      
  mySerial.println("AT+CMGF=1");   
  delay(1000);  
  mySerial.println("AT+CMGS=\"+919658975923\"\r"); 
  delay(1000);

  mySerial.println("HELP NEEDED At this Location:");
  mySerial.println(link);
  delay(100);
  mySerial.println((char)26);
  delay(1000);
     lcd.print("contacting..");
      tone(buzzer, 1000); 
  delay(1000);        
  noTone(buzzer);     
  delay(1000);        
}
