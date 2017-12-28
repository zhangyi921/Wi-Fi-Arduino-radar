// this client receive the data from arduino

import processing.net.*; 
Client myClient; 
String inString;
byte interesting = 10;

void setup() { 
  size (800, 800);
  background(0);
  draw_radar();
  //enter of local IP address of your arduino, this IP address won't work
  //on your wifi environment. 
  myClient = new Client(this, "192.168.0.27", 80); 
} 

void draw() { 
  // draw the radar diagram
  if (myClient.available() > 0) { 
    String deg = myClient.readStringUntil(100);
    String dist = myClient.readStringUntil(69);
    int degree = int(deg.substring(0, deg.length()-1));
    float distance = float(dist.substring(0, dist.length()-1));
    
    if (distance >100){
      distance = 0;}
    distance = distance/100;
    draw_bar((degree-5)/10, distance);
    println("degree: ", degree);
    println("distance: ", distance);
  }
}
void draw_radar(){
  background(0);
  stroke(0, 255, 0);
  for (int i = 0; i<18; i++){
    fill(0, 255, 0);
    arc(400, 400, 490, 490, PI+i*PI/18+PI/180, PI+(i+1)*PI/18-PI/180, PIE);   
  }
  noFill();
  arc(400, 400, 500, 500, PI, 2*PI, PIE); 
}
void draw_bar(int i, float per){
  i = 17 - i;
  stroke(255, 0, 0);
  fill(255, 0, 0);
  arc(400, 400, 490, 490, PI+i*PI/18+PI/180, PI+(i+1)*PI/18-PI/180, PIE);
  stroke(0, 255, 0);
  fill(0, 255, 0);
  arc(400, 400, 490*per, 490*per, PI+i*PI/18+PI/180, PI+(i+1)*PI/18-PI/180, PIE);
}