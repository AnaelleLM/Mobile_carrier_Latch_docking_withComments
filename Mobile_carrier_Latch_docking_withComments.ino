// MOBILE CARRIER PROJECT
// Latch Docking
// Date 22/07/2014
// Writen by Anaelle LE MENTEC

//Rossifying by Malcolm Mielle

#include <ros.h>
#include <std_msgs/Bool.h>

void messageCb( const std_msgs::Bool& msg);

ros::NodeHandle nh;
ros::Subscriber<std_msgs::Bool> sub("lift", &messageCb );

// Declaration of variables
int  enablePin = 11;
int  in1Pin = 10;
int  in2Pin = 9;
int  switch1Pin = 7;
int  switch2Pin = 2;
int speed = 200;


void setup()
{
pinMode(in1Pin, OUTPUT);
pinMode(in2Pin, OUTPUT);
pinMode(enablePin, OUTPUT);
pinMode(switch1Pin, INPUT);
pinMode(switch2Pin, INPUT);

  //Switch M12V DC motor on
  initial();
}

void initial(){
  analogWrite(enablePin, speed);
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  
}

void messageCb( const std_msgs::Bool& msg){
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  
  if (msg.data==true){
    int stateSwitch1 = digitalRead(switch1Pin);
    int stateSwitch2 = digitalRead(switch2Pin);
  
    //Open arms while there are not in opened position (= switch 1 on)
    while(!(stateSwitch1!=HIGH &&  stateSwitch2!=LOW))
    {
      stateSwitch1 = digitalRead(switch1Pin);
      stateSwitch2 = digitalRead(switch2Pin);
      analogWrite(enablePin, speed);
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, HIGH);
    }
  }
  else{
    int stateSwitch1 = digitalRead(switch1Pin);
    int stateSwitch2 = digitalRead(switch2Pin);
  
    //Latch arms while there are not in closed position (= switch 2 on)
    while(!(stateSwitch1!=LOW && stateSwitch2!=HIGH))
    {
      stateSwitch1 = digitalRead(switch1Pin);
      stateSwitch2 = digitalRead(switch2Pin);
      analogWrite(enablePin, speed);
      digitalWrite(in1Pin, HIGH);
      digitalWrite(in2Pin, LOW);
    }
  }
  
  
}

// Main Loop
void loop()
{


  nh.subscribe(sub);
  nh.spinOnce();
  delay(1);

}
