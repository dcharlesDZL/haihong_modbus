#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

SoftwareSerial RS485;
void setup()
{
    RS485.begin(9600);
    RS485.setPin(13,15);
    Serial.begin(9600);
    //WiFi初始化
    String wifiname="Charles";
    String wifipassword="douzhengli123";
    String APName="hhlab";
    String APpassword="123456";
    const char* softAPName=APName.c_str();
    const char* softAPPassword=APpassword.c_str();

    //配置ap模式
    {
        IPAddress softLocal(192,168,128,1);
        IPAddress softGateway(192,168,128,1);
        IPAddress softSubnet(255,255,255,0);
        WiFi.softAPConfig(softLocal, softGateway, softSubnet);
        
        WiFi.softAP(softAPName,softAPpassword);

    }
    //配置sta模式
    {
        WiFi.begin(wifiname, wifipassword);
    }
    //配置ap+sta模式
    {
        WiFi.softAP(softAPName,softAPpassword);
        //静态配网
        WiFi.config(ip, gateway, subnet, dns1, dns2);
        WiFi.hostname(mSavePara.Para.nickname);
        WiFi.begin(wifiname, wifipassword);
    }

}
void loop()
{
    //向设备请求参数信息
    int message[8] = {0x01,0x03,0x00,0x00,0x00,0x0f,0x05,0xce}; 
    for(int i=0; i<8; i++)     RS485.write(message[i]);
    delay(1000);

}