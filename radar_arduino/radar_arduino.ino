
#include <Servo.h>
#include <SPI.h>
#include <WiFi101.h>
int Echo = A4;  
int Trig = A5;
char ssid[] = "";   //  your network SSID (name) 
char pass[] = "";   // your network password
int status = WL_IDLE_STATUS;

WiFiServer server(80);
Servo myservo;
int i = 0;
void setup() {
  //servo pin here uses 5
  myservo.attach(5);
  Serial.begin(9600);
  //when drgree is 2, my servo points 0
  myservo.write(2);
  status = WiFi.begin(ssid, pass);
  if ( status == WL_CONNECTED) {
    server.begin();
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
  }
}
int Distance_test(){
  //return distance as interger
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance/58;       
  return (int)Fdistance;
}
int scale(int i){
  //my servo doesn't turn to designated angle
  //so I need this mapping function to correct the error
  //you may not need it depending on the quality of your servo. 
  if (i<=45){
    return map(i, 0, 45, 2, 25);
  }
  else if (i>45 && i<=90){
    return map(i, 45, 90, 25, 52);
  }
  else{
    return map(i, 90, 270, 52, 172);
  }
}
void loop() {
  //sending data to client
  //create a server
  WiFiClient client = server.available();
  for (int i = 5; i <176; i = i+10){
    myservo.write(scale(i));
    int dis = Distance_test();
    server.print(String(i)+"d"+String(dis)+"E");
    int r = client.read();
    client.flush();
    if (r == -1){
      Serial.print("s");
    }
    else{
      Serial.print(char(r));
    }
  }
  
}
