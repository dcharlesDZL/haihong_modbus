/*
初始化参数
*/
void ResetConfig()
{
    strcpy(mSavePara.Para.clientID, "hhlabhardware");
    strcpy(mSavePara.Para.apssid, "hhlab");
    strcpy(mSavePara.Para.appasswd, "hhlab123456");
    strcpy(mSavePara.Para.nickname, "hhlab_abc");
    strcpy(mSavePara.Para.authname, "admin");
    strcpy(mSavePara.Para.authpasswd, "123456");
    mSavePara.Para.isDhcp = 1;
    mSavePara.Para.wifiMode = WIFI_AP_STA;
    //服务器host和port 配置未写
    mSavePara.Para.ip[0] = 192;
    mSavePara.Para.ip[1] = 168;
    mSavePara.Para.ip[2] = 128;
    mSavePara.Para.ip[3] = 11;
    mSavePara.Para.dns[0] = 114;
    mSavePara.Para.dns[1] = 114;
    mSavePara.Para.dns[2] = 114;
    mSavePara.Para.dns[3] = 114;
    mSavePara.Para.gateway[0] = 192;
    mSavePara.Para.gateway[1] = 168;
    mSavePara.Para.gateway[2] = 128;
    mSavePara.Para.gateway[3] = 1;
    mSavePara.Para.subnet[0] = 255;
    mSavePara.Para.subnet[1] = 255;
    mSavePara.Para.subnet[2] = 255;
    mSavePara.Para.subnet[3] = 0;
}

