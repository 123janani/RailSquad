#include <math.h>
#include<RH_ASK.h>
#include<SPI.h>


RH_ASK Radio(2000, 2);
const float gate_Long = 80.502838;
const float gate_Lati = 8.353941;
const float r = 6371;
const float pi = 3.14;
float rece_Long,rece_Lati,rece_Speed,Distance;

float gate_longCal = 6371*gate_Long*pi/180;
float gate_latiCal = 6371*gate_Lati*pi/180;

void setup() {
  Serial.begin(9600);
  if (!Radio.init());
 
}

void loop() {
  String Tid,Long,Lati,Speed;
  
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (Radio.recv(buf, &buflen))
  {
    int i;
    String text = "";
    int j;

    for (int j = 0; j < buflen; j++)
    {
      text += (char)buf[j];
    }

    //divide incoming text acording to its data (id,longi length,lati length,longi value,lati value,speed)
    Tid=text.substring(0,8);
    String len_Long=text.substring(8,9);
    String len_Lati=text.substring(9,10);
   
    int len_Lon=len_Long.toInt();
    int len_Lti=len_Lati.toInt();
   
    Long=text.substring(10,10+len_Lon);
    Lati=text.substring(10+len_Lon,10+len_Lon+len_Lti);
    Speed=text.substring(10+len_Lon+len_Lti);

    rece_Long=Long.toInt();//convert string to ing 
    rece_Long=float(rece_Long);//convert ing to float
    rece_Lati=Lati.toInt(); 
    rece_Lati=float(rece_Lati);
    rece_Speed=Speed.toInt(); 
    rece_Speed=float(rece_Speed);
    rece_Speed=rece_Speed/100;//set to 2 decimals

    float speedCal = rece_Speed*5/18;

    float rece_longCal = 6371*rece_Long/1000000*pi/180;//calculate longitude latitite to calculatable format
    float rece_latiCal = 6371*rece_Lati/1000000*pi/180;
    
   //should calculate distance & arrival time
    float long_Dif = gate_longCal-rece_longCal;//difernt of longitute
    float long_pow = long_Dif*long_Dif;//longitute difernt power
 
    float lati_Dif = gate_latiCal-rece_latiCal;//difernt of latitude
    float lati_pow = lati_Dif*lati_Dif;//latitude ifernt power
  
    float lon_lat_sum = long_pow + lati_pow;
    Distance =  (sqrt(lon_lat_sum))*1000;
    int Time = Distance/speedCal;
     
    
    Serial.print(Distance);
    Serial.print("\n");
    Serial.print(Time);
    Serial.print("\n");
    
   
  }
  
}
