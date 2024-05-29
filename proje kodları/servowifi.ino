
#include <ESP32_S2_ISR_Servo.h>
#include <ESP32_S2_ISR_Servo_Debug.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <deneyap.h>

ISR_Servo_t servo1 = {
  -1, D5
};

const char* ssid = "";
const char* password = "*";

void setup() {
  Serial.begin(115200);
  WİFİ.begin(80);

  Serial.print("Bağlanılıyor...");
  while (WİFİ.status() != WL_CONNECTED) {
    Serial.print("Bağlanılıyor...");
    delay(300);
  }
  
  Serial.print("IP ADRESİ: ");
  Serial.println(WİFİ.localIP());
  
  server.begin();
  Serial.println("Sunucu başlatıldı");
  
  ESP32_S2_ISR_Servos.useTimer(USE_ESP32_S2_TIMER_NO);
  ESP32_S2_ISR_Servos.setPosition(servo1.servoIndex, 0);
}

void loop() {
  WİFİClient client = server.available();
  
  if (client) {
    Serial.println("Yeni istemci talebi geldi");
    String currentLine = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<!DOCTYPE html>");
            client.println("<html lang=\"en\">");
            client.println("<head>");
            client.println("<meta charset=\"UTF-8\">");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
            client.println("<title>Document</title>");
            client.println("<style>");
            client.println(".body {");
            client.println("  background-color: yellow;");
            client.println("  background-image: url(\"grupsimgesi.png\");");
            client.println("  background-position: 50%;");
            client.println("  background-repeat: no-repeat};");
            client.println(".div1{");
client.println("    position: relative;");
client.println("    top: 6cm;");
client.println("    text-align:center;");
client.println("    margin: 20px;");
client.println("    text-decoration: none;");
client.println("}");
client.println(".button1{");
client.println("    background-color: #4CAF50; /* Yeşil arka plan */");
client.println("    position: relative;");
client.println("    right: 7cm;");
client.println("    border: none;");
client.println("    color: white; /* Beyaz yazı */");
client.println("    padding: 15px 32px; /* Padding ayarları */");
client.println("    text-decoration: none;");
client.println("    display: inline-block;");
client.println("    font-size: 16px;");
client.println("    margin: 4px 2px;");
client.println("    cursor: pointer;");
client.println("    border-radius: 10px; /* Kenar yuvarlaklığı */");
client.println("    transition-duration: 0.4s; /* Geçiş süresi */");
client.println("}");
client.println(".button2{");
client.println("    position: relative;");
client.println("    left: 7cm;");
client.println("    font-size: 16px;");
client.println("    background-color: red;");
client.println("    color: white;");
client.println("    border: none;");
client.println("    text-decoration: none;");
client.println("    display:inline-block ;");
client.println("    border-radius: 10px;");
client.println("    cursor: pointer;");
client.println("    margin: 4px 2px;");
client.println("    padding: 15px 32px;");
client.println("    transition-duration: 0.4s;");
client.println("}");
client.println(".button1:hover{");
client.println("    color:black;");
client.println("    scale: 1.05;");
client.println("}");
client.println(".button2:hover{");
client.println("    color:black;");
client.println("    scale: 1.05;");
client.println("}");
client.println(".resim{");
client.println("    display: block;");
client.println("    margin-left: auto;");
client.println("    margin-right: auto;");
client.println("}");
client.println(".a1{");
client.println("    text-decoration: none;");
client.println("    color: white;");
client.println("}");
client.println(".a2{");
client.println("    text-decoration: none;");
client.println("    color:white;");
client.println("}");
client.println(".a1:hover{");
client.println("    scale: 1.1;");
client.println("    color:black;");
client.println("}");
client.println(".a2:hover{");
client.println("    scale: 1.1;");
client.println("    color:black;");
client.println("}");
client.println("</style>");

            client.println("</style>");
            client.println("</head>");
            client.println("<body class=\"body\">");
            client.println("<div class=\"div1\">");
            client.println("<button class=\"button1\"><a href=\"/H\" class=\"a1\">Kapağı Aç</a></button>");
            client.println("<button class=\"button2\"><a href=\"/L\" class=\"a2\">Kapağı Kapat</a></button>");
            client.println("</div>");
            client.println("</body>");
            client.println("</html>");
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        
        if (currentLine.endsWith("GET /H")) {
          ESP32_ISR_Servos.setPosition(servo1.servoIndex, -45);
          delay(1000);
          ESP32_ISR_Servos.setPosition(servo1.servoIndex, 0);
        }
        
        if (currentLine.endsWith("GET /L")) {
          ESP32_ISR_Servos.setPosition(servo1.servoIndex, 90);
          delay(1000);
          ESP32_ISR_Servos.setPosition(servo1.servoIndex, 0);
        }
      }
    }
    
    client.stop();
    Serial.println("İstemci Bağlantısı Kesildi.");
  }
}
