// 指定类型，必须写到第一行
//#define BLINKER_WIFI

// 数据接口，接的是IO0就是0，接的是IO2就是2
#define D 2


#include <ESP8266WiFi.h>   // wifi模块
//#include <Blinker.h>  //点灯
#include <ESP8266HTTPClient.h> 
//#include <WiFi.h>  
#include "DHT.h"   // 温控模块



// WiFi设置  这里需要连上一个WiFi 热点都可以
const char* ssid = "Redmi Note 12 Turbo";  
const char* password = "12345678";  

//点灯设置 这里需要填写刚才生成的密钥
//const char* auth = "aaaa";

//BlinkerNumber HUMI("humi");  // 填写绑定的组件名
//BlinkerNumber TEMP("temp");

    //温控设置 温控初始化
DHT dht(D,DHT11);



HTTPClient http;
WiFiClient wifiClient;  


  
void setup() {  
  Serial.begin(9600);  



  dht.begin();  // 温控启动

  
  //链接WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);  

  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);  
    Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  Serial.print("IP Address: ");  
  Serial.println(WiFi.localIP()); 

 

 


  
}  
  
void loop() {  
  delay(1000); // 延时2s
  //获取温度和湿度
  float h = dht.readHumidity();
  float t = dht.readTemperature();


    // 将变量转换为字符串并构建URL  
  String url = "http://154.12.26.163:5000/addt?temp=";  
  url += String(t); // 添加temp参数和值  
  url += "&humi="; // 添加humi参数和等号  
  url += String(h); // 添加humi的值 


  Serial.println(url);

  // 使用 WiFiClient 和 URL 字符串开始 HTTP 连接  
  http.begin(wifiClient, url.c_str());  
  int httpCode = http.GET();  


  Serial.println(httpCode);

  
  

  // //将温度湿度渲染到前端
  // HUMI.print(h);
  // TEMP.print(t);

  // //启动点灯服务
  // Blinker.run();
}
