/*
 * rosserial PubSub Example
 * Prints "hello world!" and toggles led
 */
#include<Servo.h>
#include <ros.h>
#include <std_msgs/String.h>
byte servoPin1 = 7;
byte servoPin2 = 8;
byte servoPin3 = 9;
byte servoPin4 = 10;
byte servoPin5 = 11;
byte servoPin6 = 12;
Servo servo1;
Servo servo2;Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
char* start_Bit;
char* stop_Bit;
int start_bit_comp,stop_bit_comp;
String value = " ";
char str[35];
const int maximumStep = 10 ;
char* steps[maximumStep];
ros::NodeHandle  nh;
int thr1=0 ,thr2=0 ,thr3=0  ,thr4=0  , thr5=0  ,thr6=0  ;

void messagecb(const std_msgs::String& toggle_msg){
  
  value = toggle_msg.data;
  if(value.length()>0)
  {
    value.toCharArray(str,35);
    char* ptr = strtok(str,",");
    ptr = str;
    int i = 0;
    while(ptr != NULL){
      steps[i] =ptr;
      ptr = strtok(NULL , ",");
      i++;
    }
    start_Bit = steps[0]; 
      thr1 = atoi(steps[1]);
      Serial.println(thr1);
      thr2 = atoi(steps[2]);
      Serial.println(thr2);
      thr3 = atoi(steps[3]);
      Serial.println(thr3);
      thr4 = atoi(steps[4]);
      Serial.println(thr4);
      thr5 = atoi(steps[5]);
      //Serial.println(thr5);
      thr6 = atoi(steps[6]);
      //Serial.println(thr6);
      stop_Bit = steps[7];
      Serial.println(start_Bit);
      Serial.println(stop_Bit);    
      start_bit_comp = strcmp(start_Bit,"$");
      stop_bit_comp = strcmp(stop_Bit,"#");
     if(start_bit_comp==0 && stop_bit_comp==0) 
      {
        if((thr1>=1100 && thr1<=1900) && (thr2>=1100 && thr2<=1900) && (thr3>=1100 && thr3<=1900) && (thr4>=1100 && thr4<=1900) && (thr5>=1100 && thr5<=1900) && (thr6>=1100 && thr6<=1900))
        {
          servo1.writeMicroseconds(thr1);
          servo2.writeMicroseconds(thr2);
          servo3.writeMicroseconds(thr3);
          servo4.writeMicroseconds(thr4);
          servo5.writeMicroseconds(thr5);
          servo6.writeMicroseconds(thr6);
        }
        
    }
  
  }
}
std_msgs::String str_msg;
ros::Subscriber<std_msgs::String> sub("Thrust_values", &messagecb);


void setup()
{
  Serial.begin(57600);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);
  servo5.attach(servoPin5);
  servo6.attach(servoPin6);
  servo1.writeMicroseconds(1500);
  servo2.writeMicroseconds(1500);
  servo3.writeMicroseconds(1500);
  servo4.writeMicroseconds(1500);
  servo5.writeMicroseconds(1500);
  servo6.writeMicroseconds(1500);
  delay(3000);
  
  nh.initNode();
  nh.subscribe(sub);
  
}

void loop()
{
  nh.spinOnce();
  delay(200);
}
