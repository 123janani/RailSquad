#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial serial_connection(1,0);//RX=9,TX=8
TinyGPSPlus gps;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  serial_connection.begin(9600);
  Serial.println("GPS Start");
}

void loop() {
  float Long,Lti,Speed;
  // put your main code here, to run repeatedly:
  while(serial_connection.available())
  {
    gps.encode(serial_connection.read());
    }
    if(gps.location.isUpdated())
    {
       Long=gps.location.lng();
       Lati=gps.location.lat();
       Speed=gps.speed.kmph();
    }  
      
      
      
      
      
      
      Serial.println("Satalite Count");
      Serial.println(gps.satellites.value());
      Serial.println("Latitude:");
      Serial.println(gps.location.lat(),6);
      Serial.println("Longitude:");
      Serial.println(gps.location.lng(),6);
      Serial.println("Speed MPH:");
      Serial.println(gps.speed.mph());
      }
}
