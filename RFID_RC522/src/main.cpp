/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the ID/UID, type and any data blocks it can read. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * If your reader supports it, this sketch/program will read all the PICCs presented (that is: multiple tag reading).
 * So if you stack two or more PICCs on top of each other and present them to the reader, it will first output all
 * details of the first and then the next PICC. Note that this may take some time as all data blocks are dumped, so
 * keep the PICCs at reading distance until complete.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */
#include <Arduino.h>
#include<SPI.h>
#include<MFRC522.h>
#define RST_PIN 49
#define SS_PIN  53
MFRC522 mfrc522(SS_PIN, RST_PIN); // CREATING MFRC522 instance
String read_rfid;
String start_tank  = "6d6ae2e3";
#define led 42
#define trigR 11
#define echoR 9
#define pinkanon 42
#define trigB 12
#define echoB 13
#define trigL 10
#define echoL 8
#define Green 46
#define Yellow 48
#define Red 46
#define ena 7
#define in4 6
#define in3 5
#define in2 4
#define in1 3
#define ena1 2
int SPEED_Right;
int SPEED_Left;
int SPEED_Right_Revers;
int SPEED_Left_Revers;
float durationR, distanceR, distanceL, durationL, durationB, distanceB;
  //------------------------------------------------------------------------
void setup(){
  Serial.begin(9600);
  SPI.begin(); // initialize SPI bus
  mfrc522.PCD_Init(); // initilize MFRC522 card
  pinMode(led, OUTPUT);
  //------------------------------------------------------------------------
   pinMode(trigR, OUTPUT);
   pinMode(echoR, INPUT);
   pinMode(trigB, OUTPUT);
   pinMode(echoB, INPUT);
   pinMode(trigL, OUTPUT);
   pinMode(echoL, INPUT);
   pinMode(Green, OUTPUT);
   pinMode(Yellow, OUTPUT);
   pinMode(Red, OUTPUT);
   pinMode(ena, OUTPUT);
   pinMode(in4, OUTPUT);
   pinMode(in3, OUTPUT);
   pinMode(ena1, OUTPUT);
   pinMode(in2, OUTPUT);
   pinMode(in1, OUTPUT);
   //color(0,0,255);

}
 //------------------------------------------------------------------------

 void color(int R, int G, int Y){
  analogWrite(Red, R);
  analogWrite(Green, G);
  analogWrite(Yellow, Y);
 }
  //------------------------------------------------------------------------
 

void byte_array(byte * buff, byte buff_size){
  read_rfid="";
  for (byte i = 0; i<buff_size; i++){
    read_rfid = read_rfid + String(buff[i], HEX);
    
  }
}

  //------------------------------------------------------------------------

void READ_CARD_AND_START_TANK(){
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
  //------------------------------------------------------------------------

     
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

    }   //------------------------------------------------------------------------

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
	   //------------------------------------------------------------------------

     if(distanceR >=350 && distanceL >=350){
      if(distanceR > distanceL ){
      
        SPEED_Right = 170;
        SPEED_Left = 165;
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
        SPEED_Right = 165;
        SPEED_Left = 170;
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

        SPEED_Right = 160;
        SPEED_Left = 160;
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
	    //------------------------------------------------------------------------

    }else if(distanceR >=200 && distanceL >=200){
      if(distanceR > distanceL ){
      
        SPEED_Right = 160;
        SPEED_Left = 155;

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
        SPEED_Right = 155;
        SPEED_Left = 160;
      
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
	  //------------------------------------------------------------------------

    else if(distanceR>100 && distanceL >100){
      if(distanceR > distanceL){
        SPEED_Right = 140;
        SPEED_Left = 135;

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
        SPEED_Right = 135;
        SPEED_Left = 140;
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
        SPEED_Right = 120;
        SPEED_Left = 120;
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
	    //------------------------------------------------------------------------

    }else if(distanceR>70 && distanceL >70){
      if(distanceR > distanceL){
        SPEED_Right = 110;
        SPEED_Left = 105;
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
        SPEED_Right = 105;
        SPEED_Left = 110;
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
	    //------------------------------------------------------------------------

    }else if(distanceR >50&& distanceL  >50){
      if(distanceR > distanceL ){
        SPEED_Right = 90;
        SPEED_Left = 100;
        color(255,0,0);         //RED
        color(255,255,0);       // YELLOW
        digitalWrite(in3, HIGH);  // FORWARD RIGHT / svinger mot venstre
        digitalWrite(in4, HIGH);     // FORWARD LEFT
        digitalWrite(in2, LOW);  // REVERS LEFT
        digitalWrite(in1, LOW);   // REVERS RIGHT
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);
        Serial.print('30 LEFT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('30 RIGHT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Right);
    }else if(distanceL > distanceR){
        SPEED_Right = 100;
        SPEED_Left = 90;
        color(255,0,0);         //RED
        color(255,255,0);       // YELLOW
        digitalWrite(in3, HIGH);   // FORWARD RIGHT
        digitalWrite(in4, HIGH); // NÅR DEN HIGH vil vinge mot høyre
        //delay(500);
        digitalWrite(in2, LOW);
        digitalWrite(in1, LOW); // REVERS RIGHT
        analogWrite(ena,  SPEED_Left );
        analogWrite(ena1, SPEED_Right);
        Serial.print('30 LEFT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('30 RIGHT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Right);
    }else{
        SPEED_Right = 100;
        SPEED_Left = 100;
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
	  //------------------------------------------------------------------------

    }else{ 
       
        if(distanceR < 50 && distanceL < 50 && distanceB>=4 && distanceB<350){
          if(distanceR > distanceL){
            
        SPEED_Right = 100;
        SPEED_Left = 150;
        color(255,0,0);         //RED
        color(255,255,0);       // YELLOW
        digitalWrite(in2, LOW);   // LEFt REVERS
        digitalWrite(in1, HIGH); // RIGHT REVERS
        analogWrite(ena1, SPEED_Right);
        delay(500);
        digitalWrite(in3, LOW);   // RIGHT Forward
        digitalWrite(in4, HIGH); // NÅR DEN HIGH vil vinge mot høyre
        analogWrite(ena,  SPEED_Left );
        delay(500);
        Serial.print('30 RIGHT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Right);
        Serial.print('30 LEFT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Left);
          }else if(distanceL > distanceR){
        SPEED_Right = 150;
        SPEED_Left = 100;
        color(255,0,0);         //RED
        color(255,255,0);       // YELLOW
        digitalWrite(in2, HIGH); // LEFt REVERS      // LOW
        digitalWrite(in1, LOW);
        analogWrite(ena,  SPEED_Left );
        delay(500);
        digitalWrite(in3, HIGH);   //
        digitalWrite(in4, LOW); // NÅR DEN HIGH vil vinge mot høyre
        analogWrite(ena1, SPEED_Right);
        delay(500);
        Serial.print('30 LEFT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('30 RIGHT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Right);
    }else{
        SPEED_Right = 90;
        SPEED_Left = 90;
        color(255,0,0);         //RED
        color(255,255,0);       // YELLOW
        digitalWrite(in2, HIGH); // LEFt REVERS
        digitalWrite(in1, HIGH);
        analogWrite(ena,  SPEED_Left );
        digitalWrite(in3, LOW);   //
        digitalWrite(in4, LOW); // NÅR DEN ER HIGH vil vinge mot høyre
        analogWrite(ena1, SPEED_Right);
        Serial.print('30 LEFT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Left);
        Serial.print('30 RIGHT Velocity range (DR<DL) = ');
        Serial.println(SPEED_Right);
    }
    
    }
    }}}
  //------------------------------------------------------------------------



void loop(){
  // check for new cards
  if(! mfrc522.PICC_IsNewCardPresent())
    return;
    // Read the card
  if(! mfrc522.PICC_ReadCardSerial())
    return;

  byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);

  if(read_rfid ==start_tank){
    READ_CARD_AND_START_TANK();
    Serial.println(start_tank);
  }else{
//----------------------------------
// Front Right
  digitalWrite(trigR, LOW);
// Front LEFT
  
  digitalWrite(trigL, LOW);  
// REVERS
  digitalWrite(trigB, LOW);
//----------------------------------

    	color(0,0,255);
        SPEED_Right = 0;
        SPEED_Left = 0;
        digitalWrite(in2, LOW); // LEFt REVERS
        digitalWrite(in1, LOW);
        analogWrite(ena,  SPEED_Left );
        digitalWrite(in3, LOW);   //
        digitalWrite(in4, LOW); // NÅR DEN ER HIGH vil vinge mot høyre
        analogWrite(ena1, SPEED_Right);

  }
}
 