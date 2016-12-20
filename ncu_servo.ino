#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>
Servo myservo;

int val;

#define SSID "IOTCourse"                                   
#define PASS ""     

ESP8266WebServer server(80);

String webSite;

void buildWeb(){
    webSite += "<html>";
    webSite+="<head>\n";
    webSite+="<meta charset='UTF-8'/>\n";
    webSite+="<title>Form Control SERVO_TURN</title>\n";
    webSite+="<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>";
    webSite+="<script>";
    webSite+="$(document).ready(function(){";
    webSite+="$(\"[type = range]\").change(function(){";
    webSite+="var redval = $(\"#red\").val();";
    webSite+="$(\"#red-text\").text(redval);";

    webSite+="});";
    webSite+="});";
    webSite+="</script>";
    webSite+="</head>\n";
    webSite += "<body>";
    webSite += "<h1>Servo Control form</h1>";
    webSite += "<form action=\"/form1\">";
    webSite += "<p>Angle : <span id = \"red-text\">0</span></p>";
    webSite += "<input type=\"range\" id=\"red\" name=\"R-led\" min=\"0\" max=\"180\" value=\"0\">";

webSite += "<br><br><input type=\"submit\" value=\"submit\"></form>";
webSite += "</body></html>";
}

void handleRoot(){
server.send(200,"text/html",webSite);
}

void AnglePicker(){
int val = server.arg("R-led").toInt();
    myservo.write(val);                  // 設定 Servo 旋轉角度
    delay(15);                           // 等待 Servo 旋轉指定的位置
    server.send(200,"text/html",webSite);
}
void handleNotFound(){
server.send(404,"text/html","404 Error!");
}

void setup() {  
Serial.begin(115200);

myservo.attach(5);  // Servo 接在 pin 9

buildWeb();
WiFi.begin(SSID, PASS); 

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}

server.on("/",handleRoot);
server.on("/form1",AnglePicker);
server.onNotFound(handleNotFound);

server.begin();
Serial.println(WiFi.localIP());  
}
void loop() {
server.handleClient();  
}

