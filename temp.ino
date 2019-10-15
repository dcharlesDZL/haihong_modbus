void StartSta() {
  if (mSavePara.Para.isDhcp == 0) {
    IPAddress ip(mSavePara.Para.ip[0], mSavePara.Para.ip[1], mSavePara.Para.ip[2], mSavePara.Para.ip[3]);
    IPAddress dns(mSavePara.Para.dns[0], mSavePara.Para.dns[1], mSavePara.Para.dns[2], mSavePara.Para.dns[3]);
    IPAddress gateway(mSavePara.Para.gateway[0], mSavePara.Para.gateway[1], mSavePara.Para.gateway[2], mSavePara.Para.gateway[3]);
    IPAddress subnet(mSavePara.Para.subnet[0], mSavePara.Para.subnet[1], mSavePara.Para.subnet[2], mSavePara.Para.subnet[3]);
    WiFi.config(ip, gateway, subnet, dns, dns);
  }  
  WiFi.hostname(mSavePara.Para.nickname);
  WiFi.begin(mSavePara.Para.stassid, mSavePara.Para.stapasswd);
}
void StartAP() {
  sprintf(mSavePara.Para.apssid, "ht_%02X%02X%02X", mac[0], mac[1], mac[2]);
  WiFi.softAP(mSavePara.Para.apssid, mSavePara.Para.appasswd);
}
void StartWiFi() {
  WiFi.disconnect(); 
  if (mSavePara.Para.wifiMode == WIFI_OFF) {
    WiFi.mode(WIFI_OFF);
  } else if (mSavePara.Para.wifiMode == WIFI_AP) {
    WiFi.mode(WIFI_AP);
    StartAP();
  } else if (mSavePara.Para.wifiMode == WIFI_AP_STA) {
    WiFi.mode(WIFI_AP_STA);
    StartAP();
    StartSta();
  } else {
    WiFi.mode(WIFI_STA);
    StartSta();
  }
}