#include <Arduino.h>
int trigR = 11;
int echoR = 9;
int pinkanon = 53;

int trigB = 12;
int echoB = 13;

int trigL = 10;
int echoL = 8;

int green = 52;
int yellow = 50;
int red = 48;

int ena = 7;
const int in4 = 6;
const int in3 = 5;
int in2 = 4;
int in1 = 3;
int ena1 = 2;
int SPEED_Right;
int SPEED_Left;
int SPEED_Right_Revers;

int SPEED_Left_Revers;
int SPEED;
float durationR, distanceR, distanceL, durationL, durationB, distanceB;


//#include<Servo.h>
//Servo servo1;
//Servo servo2;
//int pos =0;
//int pos1 = 0;

void setup() {
  // put your setup code here, to run once:
   pinMode(trigR, OUTPUT);
   pinMode(echoR, INPUT);
   pinMode(trigB, OUTPUT);
   pinMode(echoB, INPUT);
   pinMode(trigL, OUTPUT);
   pinMode(echoL, INPUT);
   
   pinMode(green, OUTPUT);
   pinMode(yellow, OUTPUT);
   pinMode(red, OUTPUT);
   
   pinMode(ena, OUTPUT);
   pinMode(in4, OUTPUT);
   pinMode(in3, OUTPUT);
   pinMode(ena1, OUTPUT);
   pinMode(in2, OUTPUT);
   pinMode(in1, OUTPUT);


//  servo1.attach(34);
//  servo2.attach(36);
//  pinMode(pinkanon, OUTPUT);
//  servo();

  Serial.begin(9600);
}

 void color(int R, int G, int Y){
  analogWrite(red, R);
  analogWrite(green, G);
  analogWrite(yellow, Y);
 }
void loop() {

  // put your main code here, to run repeatedly:
  // Front Right
  digitalWrite(trigR, LOW);
  delayMicroseconds(1);
  digitalWrite(trigR, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigR, LOW);
  durationR = pulseIn(echoR, HIGH);
  distanceR = (durationR/2)* 0.0343;

// Front LEFT
  digitalWrite(trigL, LOW);
  delayMicroseconds(1);
  digitalWrite(trigL, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigL, LOW);
  durationL = pulseIn(echoL, HIGH);
  distanceL = (durationL/2)* 0.0343;
  
// REVERS
  digitalWrite(trigB, LOW);
  delayMicroseconds(1);
  digitalWrite(trigB, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigB, LOW);
  durationB = pulseIn(echoB, HIGH);
  distanceB = (durationB/2)* 0.0343;

     
  if(distanceR >=400 && distanceR < 4 && distanceL >=400 && distanceL < 4 && distanceB>=400 && distanceB<4){
    Serial.println("Out of range");

    color(255,0,0);       //    RED
   
    color(255,255,0);       //YELLOW
    color(0,255,0);       //  LIME
  //  servo();

   }else if(distanceR >=360 || distanceR < 4){
    Serial.println("Out of range RIGHT");
    color(0, 0, 255);       //  BLUE
    color(255, 140, 0);     // DARKORANGE
    }else if(distanceL >=360 || distanceL < 4){
    Serial.println("Out of range LEFT");
     color(0, 0, 255);       //  BLUE
    color(255, 140, 0);     // DARKORANGE
    }else if(distanceB>=360 || distanceB<4){
     Serial.println("Out of range REVRS");
    color(0, 191, 255);       //  DEEPSKYBLUE
    color(128, 0, 128);     // PURPLE
    }
     else{
     Serial.print("Distance Front LEET = ");
     Serial.print(distanceL);
     Serial.println(" cm");
     
     Serial.print("Distnace Front RIGHT = ");
     Serial.print(distanceR);
     Serial.println(" cm");

     Serial.print("Distance Revers = ");
     Serial.print(distanceB);
     Serial.println(" cm");
     
     delayMicroseconds(1);
     if(distanceR >=350 && distanceL >=350){
      if(distanceR > distanceL ){
      
        SPEED_Right = 200;
        SPEED_Left = 150;

        color(124, 252, 0);         //LAWNGREEN
        digitalWrite(in3, HIGH);      // FORWARD    RIGHT
        digitalWrite(in4, HIGH);
        digitalWrite(in2, LOW);       // REVERS 
        digitalWrite(in1, LOW);        // RIGHT
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);
        
        Serial.print('350 LEFT Velocity range (R>L) = ');
        Serial.println(SPEED_Left);
        Serial.print('350 RIGHT Velocity range (R>L) = ');
        Serial.println(SPEED_Right);
        
      }else if(distanceL > distanceR){
        SPEED_Right = 150;
        SPEED_Left = 200;
      

        color(124, 252, 0);         //LAWNGREEN

        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in1, LOW);
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);

        Serial.print('350 LEFT Velocity range (R<L) = ');
        Serial.println(SPEED_Left);
        Serial.print('350 RIGHT Velocity range (R<L) = ');
        Serial.println(SPEED_Right);
        }
        else
        {

        SPEED_Right = 150;
        SPEED_Left = 150;
       

        color(124, 252, 0);         //LAWNGREEN

        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in1, LOW);
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);
        Serial.print('350 LEFT Velocity range (DR==DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('350 RIGHT Velocity range (DR==DL) = ');
        Serial.println(SPEED_Right);
      }
    }else if(distanceR >=200 && distanceL >=200){
      if(distanceR > distanceL ){
      
        SPEED_Right = 170;
        SPEED_Left = 140;

        color(255,255,0);           //YELLOW
        color(0, 255, 0);            // LIME
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in1, LOW);
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);

        Serial.print('>=200 LEFT Velocity range (DR>DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('>=200 RIGHT Velocity range (DR>DL) = ');
        Serial.println(SPEED_Right);
        
      }else if(distanceL > distanceR){
        SPEED_Right = 140;
        SPEED_Left = 170;
      
        color(255,255,0);           //YELLOW
        color(0, 255, 0);           //LIME
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in1, LOW);
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);
        Serial.print('>=200 LEFT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('>=200 RIGHT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Right);
        }else{
        SPEED_Right = 140;
        SPEED_Left = 140;
       
        color(0, 255, 0);         // LIME
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in1, LOW);
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);
        Serial.print('>=200 LEFT Velocity range (R==L) = ');
        Serial.println(SPEED_Left);
        Serial.print('>=200 RIGHT Velocity range (R==L) =');
        Serial.println(SPEED_Right);
      }
    }
    else if(distanceR>100 && distanceL >100){
      if(distanceR > distanceL){
        SPEED_Right = 160;
        SPEED_Left = 130;

        color(0, 128, 0);         //GREEN
        color(255,255,0);         //YELLOW
        digitalWrite(in3, HIGH); // FORWARD RIGHT
        digitalWrite(in4,HIGH); //  FORWARD LEFT
        digitalWrite(in2, LOW);  // GOES REVERS LEFT
        digitalWrite(in1, LOW); // GOES REVERS RIGHT
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);

        Serial.print('100 LEFT Velocity range (DR>DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('100 RIGHT Velocity range (DR>DL) = ');
        Serial.println(SPEED_Right);
      }else if(distanceL > distanceR){
        SPEED_Right = 130;
        SPEED_Left = 160;

        color(0, 128, 0);         //GREEN

        color(255,255,0);         //YELLOW
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        digitalWrite(in2, LOW); // REVERS
        digitalWrite(in1, LOW);
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);
        
        Serial.print('100 LEFT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('100 RIGHT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Right);
        }
      else{
        SPEED_Right = 130;
        SPEED_Left = 130;
        color(255, 215, 0);         //GOLD    

        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH); // GOES LEFT
        digitalWrite(in2, LOW);
        digitalWrite(in1, LOW);
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);
        
        Serial.print('100 LEFT Velocity range (DR==DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('100 RIGHT Velocity range (DR>==DL) = ');
        Serial.println(SPEED_Right);
      }
    }else if(distanceR>50 && distanceL >50){
      if(distanceR > distanceL){
        SPEED_Right = 250;
        SPEED_Left = 100;
        
        color(255,0,0);         //RED
        color(255,255,0);       // YELLOW
        digitalWrite(in3, HIGH);     // GOES FORWARD RIGHT
        digitalWrite(in4, HIGH);      // FORWARD LEFT
        digitalWrite(in2, LOW);      // REVERS LEFT 
        digitalWrite(in1, LOW);     // GOES REVERS RIGHT
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);

        Serial.print('30 LEFT Velocity range (DR>DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('30 RIGHT Velocity range (DR>DL) = ');
        Serial.println(SPEED_Right);

      }else if(distanceL > distanceR){
        SPEED_Right = 100;
        SPEED_Left = 250;

        color(255,0,0);         //RED
        color(255,255,0);       // YELLOW
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in1, LOW);
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);

        Serial.print('30 LEFT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('30 RIGHT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Right);
        }
      else{
        SPEED_Right = 100;
        SPEED_Left = 100;

        color(128, 0, 0);         //Maroon
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in1, LOW);
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);

        Serial.print('30 LEFT Velocity range (DR==DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('30 RIGHT Velocity range (DR==DL) = ');
        Serial.println(SPEED_Right);
      }
    }else if(distanceR >=25 && distanceR <50 && distanceL  >=25 && distanceL<50){
      if(distanceR > distanceL ){
        SPEED_Right = 100;
        SPEED_Left = 250;

        color(255,0,0);         //RED
        color(255,255,0);       // YELLOW
        digitalWrite(in3, LOW);  // FORWARD RIGHT
        digitalWrite(in4, HIGH);     // FORWARD LEFT
        digitalWrite(in2, LOW);  // REVERS LEFT
        digitalWrite(in1, HIGH);   // REVERS RIGHT
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);

        Serial.print('30 LEFT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('30 RIGHT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Right);
    }else if(distanceL > distanceR){
        SPEED_Right = 250;
        SPEED_Left = 100;

        color(255,0,0);         //RED
        color(255,255,0);       // YELLOW
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in1, LOW);
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);

        Serial.print('30 LEFT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('30 RIGHT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Right);
    }else{
        SPEED_Right = 80;
        SPEED_Left = 80;

        color(255,0,0);         //RED
        color(255,255,0);       // YELLOW
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in1, LOW);
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);

        Serial.print('30 LEFT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('30 RIGHT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Right);
    }
    }else{ 
      // REVERS                                                         RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
      
      if (distanceB>=100 && distanceB<390){
        SPEED_Right_Revers = 150;
        SPEED_Left_Revers = 150;

        color(255, 20, 147);        // DeepPink
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        digitalWrite(in2, HIGH);   // REVERS LEFT   
        digitalWrite(in1, HIGH); // // GOES REVERS RIGHT
        analogWrite(ena1, SPEED_Right_Revers);
        analogWrite(ena, SPEED_Left_Revers);
        Serial.print('REVERS LEFT Velocity range (B>100 B<350) = ');
        Serial.println(SPEED_Right_Revers);
        Serial.print('REVERS RIGHT Velocity range (B>100 B<350) = ');
        Serial.println(SPEED_Left_Revers);
      }else if(distanceB>=50 && distanceB<100){
        SPEED_Right_Revers = 130;
        SPEED_Left_Revers = 130;

        color(255,0,255);         // Fuchsia
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in1, HIGH);
        analogWrite(ena1, SPEED_Right_Revers);
        analogWrite(ena, SPEED_Left_Revers);

        Serial.print('REVERS LEFT Velocity range (B>50 B<100) = ');
        Serial.println(SPEED_Right_Revers);
        Serial.print('REVERS RIGHT Velocity range (B>50 B<100) = ');
        Serial.println(SPEED_Left_Revers);
        
      }else if(distanceB>=4 && distanceB<50){
        if(distanceR > distanceL){
        SPEED_Right_Revers = 100;
        SPEED_Left_Revers = 255;
        
        color(75,0,130);          // INDIGO
        digitalWrite(in3, LOW);   // forward Right
        digitalWrite(in4, HIGH);   // forward Left
        digitalWrite(in2, LOW);    // revers Left
        digitalWrite(in1, HIGH);    // REVERs RIGHT
        analogWrite(ena1, SPEED_Right_Revers);
        analogWrite(ena, SPEED_Left_Revers);

        Serial.print('REVERS LEFT Velocity range (B>10 B<50) = ');
        Serial.println(SPEED_Right_Revers);
        Serial.print('REVERS RIGHT Velocity range (B>10 B<50) = ');
        Serial.println(SPEED_Left_Revers);
        }else if(distanceL > distanceR){
        SPEED_Right_Revers = 100;
        SPEED_Left_Revers = 255;
        
        color(75,0,130);          // INDIGO
        digitalWrite(in3, LOW);   // forward Right
        digitalWrite(in4, HIGH);   // forward Left
        digitalWrite(in2, LOW);    // revers Left
        digitalWrite(in1, HIGH);    // REVERs RIGHT
        analogWrite(ena1, SPEED_Right_Revers);
        analogWrite(ena, SPEED_Left_Revers);

        Serial.print('REVERS LEFT Velocity range (B>10 B<50) = ');
        Serial.println(SPEED_Right_Revers);
        Serial.print('REVERS RIGHT Velocity range (B>10 B<50) = ');
        Serial.println(SPEED_Left_Revers);
        }
        SPEED_Right_Revers = 100;
        SPEED_Left_Revers = 100;
        
        color(75,0,130);          // INDIGO
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in1, HIGH);
        analogWrite(ena1, SPEED_Right_Revers);
        analogWrite(ena, SPEED_Left_Revers);

        Serial.print('REVERS LEFT Velocity range (B>10 B<50) = ');
        Serial.println(SPEED_Right_Revers);
        Serial.print('REVERS RIGHT Velocity range (B>10 B<50) = ');
        Serial.println(SPEED_Left_Revers);
      }
      
      else{
        SPEED = 0;

        color(0,255,255);          // CYAN
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in1, LOW);
        analogWrite(ena, SPEED);
        analogWrite(ena1, SPEED);
//        servo();

      }
    }
  }
}


// 
// void servo(){
//   // put your main code here, to run repeatedly:
//  for(pos = 0; pos<=105; pos++){
//    servo1.write(pos);
// delayMicroseconds(4000);
//  }
//  
//  for(pos = 105; pos<=0; pos--){
//    servo1.write(pos);
// delayMicroseconds(4000);
//  }
// 
////     for(pos1 = 40; pos1<=0; pos1--){
////    servo2.write(pos1);
////     delay(2);
////
////  }
////    digitalWrite(pinkanon, HIGH);
////    delay(2);
////    digitalWrite(pinkanon, LOW);
////    
////   for(pos1 = 0; pos1<=40; pos1++){
////   servo2.write(pos1);
////   delay(2);
////
////}
////  for(pos = 75; pos<=105; pos++){
////    servo1.write(pos);
////   delay(2); 
////  }
//
////  for(pos = 105; pos<=75; pos--){
////    servo1.write(pos);
////    delay(2);
////  }
//   
//     for(pos1 = 40; pos1<=0; pos1--){
//    servo2.write(pos1);
// delayMicroseconds(4000);
//
//
//  }
//   for(pos1 = 0; pos1<=40; pos1++){
//   servo2.write(pos1);
// delayMicroseconds(4000);
//
//}
//for(pos = 105; pos<=130; pos++){
//    servo1.write(pos);
// delayMicroseconds(4000);
//
//  }
//  
//  for(pos = 130; pos<=105; pos--){
//    servo1.write(pos);
//  delayMicroseconds(4000);
//  }
////     for(pos1 = 40; pos1<=0; pos1--){
////    servo2.write(pos1);
////     delay(2);
////
////  }
////    digitalWrite(pinkanon, HIGH);
////    delay(2);
////    digitalWrite(pinkanon, LOW);
////    
////   for(pos1 = 0; pos1<=40; pos1++){
////   servo2.write(pos1);
////   delay(2);
////
////}
////
////for(pos = 135; pos<=150; pos++){
////    servo1.write(pos);
////   delay(2); 
////  }
////  
////  for(pos = 150; pos<=135; pos--){
////    servo1.write(pos);
////    delay(2);
////  }
//
// }