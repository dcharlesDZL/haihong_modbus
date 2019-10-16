/*-----------------headers------------------*/
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include "parameter.h"
/*------------------define-----------------*/
#define BasicAuth()  do{if(!httpserver.authenticate(authname, authpasswd)){ return httpserver.requestAuthentication();}}while(0);


/*------------------init-----------------*/
//初始化服务器
ESP8266WebServer  httpserver(80);
ESP8266HTTPUpdateServer httpUpdater;
SoftwareSerial RS485;
char htmltext[1500];
//声明配网参数
const char* clientID = "hhlabhardware";
//WiFi初始化
const char* apssid ="hhlab";
const char* appassword="hhlab123456";
int isDhcp = 1;
const char* nickname = "hhlab_abc";
char* stassid;
char* stapasswd ;
char* authname = "admin";
char* authpasswd = "123456";
//enum WIFI_MODE {WIFI_AP, WIFI_STA, WIFI_AP_STA, WIFI_OFF};
int wifi_mode = WIFI_AP_STA;
/*-------------------function----------------*/
void home()//ap模式下，进入主页进行配网
{
sprintf(htmltext, "<html><head><meta charset='utf-8'><title>网页配置</title></head><body><form action='/' method='POST'><fieldset><legend align='center'>网页配置</legend><table align='center'><tr><td>设备SN号</td><td><p>%s</p></td></tr><tr><td>设备名字</td><td><input type='text' name='name' value=%s></td></tr><tr><td>路由器热点SSID:</td><td><input type='text' name='ssid' value=%s></td></tr><tr><td>路由器密码:</td><td><input type='text' name='pwd' value=%s></td></tr><tr><td colspan='2' align='center'><button type='submit'>更新配置</button></td></tr></table></fieldset></form><fieldset><legend align='center'>固件更新</legend><table align='center'> <tr> <td colspan='2' align='center'> <button onclick='window.location.href=&quot/update&quot;'>固件升级</button></td></tr></table></fieldset></body></html>", clientID, stassid, stapasswd);
httpserver.send(200,"text/html",htmltext);
}
void HttpServerInit()
{
  httpserver.on("/", HTTP_GET, []() {
    BasicAuth();
    home();
  });
  httpserver.on("/", HTTP_POST, []() {
    BasicAuth();
    String name = httpserver.arg("name");
    String stassid = httpserver.arg("ssid");
    String stapasswd = httpserver.arg("pwd");
    String authname = httpserver.arg("authname");
    String authpasswd = httpserver.arg("authpasswd");
    
    name.trim();
    stassid.trim();
    stapasswd.trim();
    authname.trim();
    authpasswd.trim();
    home();
  });
  httpserver.onNotFound([]() {
    home();
  });
  httpUpdater.setup(&httpserver);
  httpserver.begin();
}
//设置ap热点
void setAP()
{
    IPAddress softLocalIP(192,168,128,1);
    IPAddress softGateway(192,168,128,1);
    IPAddress softSubnet(255,255,255,0);
    WiFi.softAPConfig(softLocalIP, softGateway, softSubnet);
    WiFi.softAP(apssid, appassword);
    Serial.println("ap is ok!");
}
//设置sta模式
void setSta()
{
    if (isDhcp == 0)
    {

    }
    WiFi.hostname(nickname);
    WiFi.begin(stassid, stapasswd);
}
//启动WiFi
void StartWiFi()
{
    WiFi.disconnect();
    switch(wifi_mode)
    {
        case WIFI_OFF:
        {
            WiFi.mode(WIFI_OFF);
            break;
        }
        case WIFI_AP:
        {
            WiFi.mode(WIFI_AP);
            setAP();
            break;
        }
        case WIFI_STA:
        {
            WiFi.mode(WIFI_STA);
            setSta();
            break;
        }
        case WIFI_AP_STA:
        {
            WiFi.mode(WIFI_AP_STA);
            setAP();
            setSta();
            break;
        }
    }
}
/*------------------setup-----------------*/
void setup()
{
    RS485.begin(9600);
    RS485.setPin(13,15);
    Serial.begin(9600);
    HttpServerInit();
    StartWiFi();
    while(1)
    {
        //监听请求
        httpserver.handleClient();
    }
}
/*------------------loop-----------------*/
void loop()
{
    //向设备请求参数信息
    int message[8] = {0x01,0x03,0x00,0x00,0x00,0x0f,0x05,0xce};
    for(int i=0; i<8; i++)     RS485.write(message[i]);
    delay(1000);
    }
/*-----------------------------------*/
