#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial bluetooth(10,11);

Servo myservo; 
char b;
int echo1=8;
int trig1=7;

int motor1c=3;
int motor1a=5;
int motor2c=6;
int motor2a=A2;

int duration1;
int distance1;

int initial=0;
 int after=0;

 
 
void forward(){
  digitalWrite(motor1a,HIGH);
  digitalWrite(motor1c,LOW);
  digitalWrite(motor2a,HIGH);
  digitalWrite(motor2c,LOW);
  }
void backward(){
  digitalWrite(motor1a,LOW);
  digitalWrite(motor1c,HIGH);
  digitalWrite(motor2a,LOW);
  digitalWrite(motor2c,HIGH);
  }
void left(){
   digitalWrite(motor1a,LOW);
  digitalWrite(motor1c,HIGH);
  digitalWrite(motor2a,HIGH);
   digitalWrite(motor2c,LOW);
  }  
void right(){
   digitalWrite(motor1a,HIGH);
  digitalWrite(motor1c,LOW);
  digitalWrite(motor2a,LOW);
   digitalWrite(motor2c,HIGH);
  }  
void stopping(){
    digitalWrite(motor1c,LOW);
    digitalWrite(motor1a,LOW);
    digitalWrite(motor2c,LOW);
    digitalWrite(motor2a,LOW);
    }
void sen1(){
digitalWrite(trig1,LOW);
delay(2);
digitalWrite(trig1,HIGH);
delay(20);
digitalWrite(trig1,LOW);
duration1=pulseIn(echo1,HIGH);
initial=duration1/58.7;  

  }  
void sen2(){
digitalWrite(trig1,LOW);
delay(2);
digitalWrite(trig1,HIGH);
delay(20);
digitalWrite(trig1,LOW);
duration1=pulseIn(echo1,HIGH);
after=duration1/58.7;  
  }  
    
 int pos = 0;
 
void setup() {
  myservo.attach(A4); 
   
  pinMode(echo1,INPUT);
  pinMode(trig1,OUTPUT);
  
  pinMode(motor1c,OUTPUT);
  pinMode(motor1a,OUTPUT);
  pinMode(motor2c,OUTPUT);
  pinMode(motor2a,OUTPUT);
  
bluetooth.begin(9600);
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  
digitalWrite(trig1,LOW);
delay(2);
digitalWrite(trig1,HIGH);
delay(20);
digitalWrite(trig1,LOW);
duration1=pulseIn(echo1,HIGH);
distance1=duration1/58.7;

// sen1();  
 Serial.print("dist1===");
Serial.println(distance1);
//forward();

  if (bluetooth.available()){
  b=bluetooth.read();
  Serial.println(b);
  switch(b){
    case'F':forward();
   
    break;
  case'B':backward();
  
    break;  
  case'L':left();
  
    break;   
  case'R':right();
  
    break;   
   case'S':stopping();
    break;  
    }
  
}

if (distance1==25||distance1==24||distance1==23||distance1==22||distance1==21||distance1==20){
myservo.write(10);
sen1();
delay(1000);
myservo.write(170);
sen2();
delay(1000);
myservo.write(90);
delay(200);

if(after>initial){
right();
delay(200);
stopping();
}

if(after<initial){
left();
delay(200);
stopping();
}

if(after==initial){
backward();
delay(200);
stopping();
}


  }


 }  

  
