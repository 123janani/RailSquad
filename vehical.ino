#include<RH_ASK.h>
#include<SPI.h>
#include<SoftwareSerial.h>

RH_ASK Radio(2000,2);
void setup() {
  Serial.begin(9600);
  if (!Radio.init());
}

void loop() {
     String gid,Time;

  
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
    Serial.print(text);
    Serial.print("\n");
    gid=text.substring(0,8);
    Time=text.substring(8);
    if(gid == '12345678')
    {
    Serial.print(gid);
    Serial.print("\n");
    Serial.print(Time);
    Serial.print("\n");
    }
    
 }
}
