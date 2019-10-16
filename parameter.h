/*
定义了RS485、机器参数、运行参数、存储参数数据结构。
*/
//u8:unsigned8
//u16：unsigned16
//s16：signed16
//#include <stdint.h>
typedef struct _RS485_TYPE
{
  union     //UN1  主机向从机写数据
  {
    struct masterBuf
    {
      u8 devnum;            //设备号
      u8 funcode;           //功能码(0x10写)
      u8 idhigh;            //起始地址高八位
      u8 idlow;             //起始地址低八位
      u8 numhigh;           //寄存器数高八位
      u8 numlow;            //寄存器数低八位
      u8 datalen;           //数据字节长度
      s16 setTemp;          //设定温度
      s16 setSpeed;         //设定速度
      s16 setTimeHour;      //设定时间（小时）
      s16 setTimeMinute;    //设定时间（分钟）
      u16 tempMin;          //设定温度量程最小值
      u16 tempMax;          //设定温度量程最大值
      u16 speedMin;         //设定温度最小值
      u16 speedMax;         //设定温度最大值
      u16 setStatus;        //设置运行状态
      s16 setCurrentMode;   //设置当前模式（1/2/3）
      u16  setPwrOffMem;    //设置掉电记忆(0/1)
    }__attribute__((packed)); //__attribute__((packed)) 设置对齐
    u8 masterPtr[40];
  } UN1;
  
  union       //UN2  当主机发送读取指令后从机向主机返回的参数
  {
    struct slaveBuf{
      u8 devnum;           //地址码
      u8 funcode;          //功能码
      u8 datalen;          //返回的数据长度
      u16 type;            //机器类型（全部两字节）
      u16 temp;            //当前温度
      u16 setTemp;         //温度设定值
      u16 speed;           //当前速度
      u16 setSpeed;        //速度设定值
      u16 setTimeHour;     //小时设定值
      u16 setTimeMinute;   //分钟设定值
      u16 timeHour;        //当前小时值
      u16 timeMinute;      //当前分钟值
      u16 tempRangeMin;    //温度量程最小值
      u16 tempRangeMax;    //温度量程最大值
      u16 speedMin;        //速度最小值
      u16 speedMax;        //速度最大值
      u16 alarm;           //故障报警（使用0-9位）
      u16 status;          //运行状态（到此处一共15个数据，共30字节）
      s16 currentMode;     //当前模式（协议2.2添加的）
      u16 powerOffMem;     //掉电记忆（协议2.2添加的）
      u16 checkcode;             //校验码
    };                 //从机缓冲 modbus
    u8 slavePtr[40];             //从机返回的数据
  } UN2;
} RS485_TYPE;

typedef struct _MachinePara       //机器参数
{                   
  s16 machineType = 0;
  s16 paraTemp = 0;
  s16 setTemp = 50.0;     //缺省值为50
  s16 paraSpeed = 0;
  s16 setSpeed = 100;     //速度设定缺省值为100
  s16 setTimeHour = 0;
  s16 setTimeMinute = 0;
  s16 paraTimeHour = 0;
  s16 paraTimeMinute = 0;
  // s16 paraTempRangeMin = 0;
  // s16 paraTempRangeMax = 0;
  s16 setTempRangeMin = 0.0;
  s16 setTempRangeMax = 320.0;    //最大设定温度为320
  s16 paraSpeedMin = 0; 
  s16 paraSpeedMax = 0;
  s16 setSpeedMin = 100;     //最小设定速度缺省值为100
  s16 setSpeedMax = 1500;    //最大设定速度缺省值为1500
  u16 alarm;                 //报警值，位操作
  u16 paraRunStatus = 0;
  u16 paraCurrentMode = 0;     //（协议2.2添加）
  u16 paraPwrOffMem = 0;
  u16 setCurrentMode = 0;
  u16 setPwrOffMem = 0;
}MachinePara;

typedef struct _RunningPara{
  time_t cpuTime;//CPU UNIX时间
  time_t startupTime;
  byte wifiPwrOnAlm;
  int mqttState;
  byte rs485Triged;
  byte startSmartconfig;
  byte alarm; 
  byte sosAlarm;
  byte paraRestore; 
  byte yunUpload;
  byte portMode;

  byte tempRemote;
  byte remoteSetReply;
  byte firstAlarmCount;  
  int controlDelayWIFI;
  byte wifisConnected;
} RunningPara;

typedef union _SavePara 
{
  struct _Para
  {
    byte wifiMode;  //0STA 1AP 2STA+AP
    byte isDhcp;
    byte ip[4];
    byte dns[4];
    byte gateway[4];
    byte subnet[4];

    char* clientID;
    char stassid[20];
    char stapasswd[20];
    char apssid[20];
    char appasswd[20];
    char authname[20];
    char authpasswd[20];
    char nickname[20];
    char* tcp_server_host;
    u16 tcp_server_port;

  }Para;
  byte bytes[100];
} SavePara;
