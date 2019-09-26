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
    const char* apssid ="hhlab";
    const char* appassword="hhlab123456";
    //声明配网参数
    ESP8266WebServer  httpserver(80);
    char* clientID, nickname, stassid, stapassword;
    char* htmltext;

    //配置ap模式
    {
        IPAddress softLocal(192,168,128,1);
        IPAddress softGateway(192,168,128,1);
        IPAddress softSubnet(255,255,255,0);
        WiFi.softAPConfig(softLocal, softGateway, softSubnet);        
        WiFi.softAP(ssid, password);
        
    }
    //进入配网
    clientID = "hhlabhardware";
    const char* indexhtml = "<html><head><meta charset='utf-8'><title>网页配置</title></head><body><form action='/' method='POST'><fieldset><legend align='center'>网页配置</legend><table align='center'><tr><td>设备SN号</td><td><p>%s</p></td></tr><tr><td>设备名字</td><td><input type='text' name='name' value='%s'></td></tr><tr><td>路由器热点SSID:</td><td><input type='text' name='ssid' value='%s'></td></tr><tr><td>路由器密码:</td><td><input type='text' name='pwd' value='%s'></td></tr><tr><td colspan='2' align='center'><button type='submit'>更新配置</button></td></tr></table></fieldset></form><fieldset><legend align='center'>固件更新</legend><table align='center'> <tr> <td colspan='2' align='center'> <button onclick='window.location.href=&quot/update&quot;'>固件升级</button></td></tr></table></fieldset></body></html>"
    sprintf(htmltext, indexhtml, clientID, nickname, stassid, stapassword);
    httpserver(softLocal);
    httpserver.send(200,"text/html",htmltext);

    //配置sta模式
    {
        WiFi.begin(wifissid, wifipassword);
    }
    // //配置ap+sta模式
    // {
    //     WiFi.softAP(softAPName,softAPpassword);
    //     //静态配网
    //     WiFi.config(ip, gateway, subnet, dns1, dns2);
    //     WiFi.hostname(mSavePara.Para.nickname);
    //     WiFi.begin(wifiname, wifipassword);
    // }

}
void loop()
{
    //向设备请求参数信息
    int message[8] = {0x01,0x03,0x00,0x00,0x00,0x0f,0x05,0xce}; 
    for(int i=0; i<8; i++)     RS485.write(message[i]);
    delay(1000);

}