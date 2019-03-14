#include<RH_ASK.h>
#include<SPI.h>

RH_ASK Radio(2000, "", 2);

void setup() {

  pinMode(13, OUTPUT);
  Serial.begin(9600);
  if (!Radio.init())
    Serial.println("init failed");
}

void loop() {
  long int Tid,lng_Long,lng_Lati,lng_Speed;
  float GPS_long,GPS_lati,GPS_Speed;
  
  Tid=45815472;
  GPS_long=80.502861;
  GPS_lati=8.357985;
  GPS_Speed=456.32;
  
  GPS_long=GPS_long*1000000;
  GPS_lati=GPS_lati*1000000;
  GPS_Speed=GPS_Speed*100;
  lng_Long=(long int)GPS_long;
  lng_Lati=(long int)GPS_lati;
  lng_Speed=(long int)GPS_Speed;
  
  String Snd_id=String(Tid);
  
  String Snd_long=String(lng_Long);
  int len_lng=Snd_long.length();
  String Snd_Longlen=String(len_lng);
  
  String Snd_lati=String(lng_Lati);
  int len_lati=Snd_lati.length();
  String Snd_Latilen=String(len_lati);
 
  String Snd_speed=String(lng_Speed);
  
  String Snd_msg=Snd_id+Snd_Longlen+Snd_Latilen+Snd_long+Snd_lati+Snd_speed;
 
  const char *msg=Snd_msg.c_str();
 
  Radio.send((uint8_t *)msg, strlen(msg));
  Radio.waitPacketSent();
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
}

