#include <Wire.h>
#include<SoftwareSerial.h>
#include <Adafruit_MLX90614.h>
SoftwareSerial gsm(2,3);

int xpin = A3;                
int ypin = A2;                
int zpin = A1; 
int xvalue;
int yvalue;
int zvalue;
int count=0;
const String PHONE = "+918667316311";
 Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup()
{
  Serial.begin(115200);          // initialize the serial communications:
  mlx.begin();
  delay(1000);
  Serial.begin(9600);
  gsm.begin(9600);
  delay(1000);
  gsm.println("AT");
  delay(1000);
}


void loop()
{
    delay(1000);
    xvalue = analogRead(xpin);                              //reads values from x-pin & measures acceleration in X direction 
   int x = map(xvalue, 257, 389, -100, 100);               //maps the extreme ends analog values from -100 to 100 for our understanding
   float xg = (float)x/(-100.00);                          //converts the mapped value into  acceleration in terms of "g"
    Serial.print(xg);                                       //prints value of acceleration in X direction
    //Serial.print("g   ");                                   //prints "g"
     
    yvalue = analogRead(ypin);
    int y = map(yvalue, 257, 389, -100, 100);
    float yg = (float)y/(-100.00);
    Serial.print("\t");
    Serial.print(yg);
    //Serial.print("g   "); 
 
    zvalue = analogRead(zpin);
    int z = map(zvalue, 266, 394, -100, 100);
    float zg = (float)z/(100.00);
    Serial.print("\t"); 
    Serial.println(zg);
  //Serial.println("g   ");
  
    Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
    Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
    Serial.println();
      delay(400);
    float temp= 30.5;
    int lol=0;
    Serial.print("Ambient zzzzzzzzzzzzz ");
     delay(400);
    if(xg>=-1.60 && xg<=2.09)
    {
      Serial.print("xxxxxxxxxxx");
      delay(400);
      if(yg>=-1.90 && yg<=2.07)
      {
        Serial.print("yyyyyyyyyyyyy");
        delay(400);
        if(zg>=-1.12 && zg<=1.16)
        {  
          Serial.print("zzzzzzzzzzzzzzzzz");
          delay(400);
          if(temp>=30)
          {
            Serial.print("temppppppp");
            delay(400);
              count=count+1;
              
  Serial.print(count);
    delay(400); 
         }else{lol=1; Serial.print("Nope xxxxxxxxxxx");delay(400);}
      }else{lol=1;Serial.print("Nope yyyyyyyyyyyyy");delay(400);}
    }else{lol=1; Serial.print("Nope zzzzzzzzzzzzzzzzz");delay(400);}
  }else{lol=1;Serial.print("Nope temppppppppp");delay(400);}
if (lol==1){count=0;}
   
     if (count==5)
     {

      gsm.println("ATD"+PHONE+";");
     delay(20000);
     gsm.println("ATH");
  
    delay(1500);
    gsm.println("AT+CMGF=1\r");
    delay(500);
    gsm.println("AT+CMGS=\"+918667316311\"\r");
    delay(500);
    gsm.println("HI farmer! You cow is about to calve in an hour.");
    delay(500);
    gsm.println((char)26);
    delay(500);
    count=0;
  }

}
