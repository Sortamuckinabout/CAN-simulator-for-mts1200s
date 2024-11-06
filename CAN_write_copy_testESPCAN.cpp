#include <SPI.h>
#include "mcp2515.h"
int cantps =0;
int canrpmth =0;
int canrpmMin =0;
const int chipSelect = 10;  
struct can_frame canMsg1;
struct can_frame canMsg2;
struct can_frame canMsg3;
struct can_frame canMsg4;
struct can_frame canMsg5;
struct can_frame canMsg6;
struct can_frame canMsg7;
struct can_frame canMsg8;
struct can_frame canMsg9;
struct can_frame canMsg10;
struct can_frame canMsg11;
struct can_frame canMsg12;
struct can_frame canMsg13;
struct can_frame canMsg14;
struct can_frame canMsg15;
MCP2515 mcp2515(10);

void setup() {

  
  canMsg1.can_id  = 0x18;// gear and rear wheel speed
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x00;
  canMsg1.data[1] = 0x1E;//changes with TPS
  canMsg1.data[2] = 0x56;//pulses with engineand stops at off 
  canMsg1.data[3] = 0x00;
  canMsg1.data[4] = 0x60;  //first digit after gear
  /**      1 HEX = N
           2 HEX = 1
          4 HEX = 2
           6 HEX = 3
            8 HEX = 4
        A(10) HEX = 5
        C(12) HEX = 6 **/ //second digit wheel speed
  canMsg1.data[5] = 0x52;//Wheel speed first digit
  canMsg1.data[6] = 0x51; //fuel level
  canMsg1.data[7] = 0x5C;
//**************************************************************************************
  //cantps=15 + random (15);
  canMsg2.can_id  = 0x80;//throttle position and rpm
  canMsg2.can_dlc = 8;
  canMsg2.data[0] = 0x0C;//follows TPS sub throttle function
  canMsg2.data[1] = 0x07;// follows TPS agian sub function different value
  canMsg2.data[2] = 0x00;//zero at this test
  canMsg2.data[3] = 0x00;// zero through garage test
  canMsg2.data[4] = 0xC8;//constant at dec 200
  canMsg2.data[5] = 0x11;//rpm{5}*256 + {6}
  canMsg2.data[6] = 0x21;// zero through garage test
  canMsg2.data[7] = 0x11;//tps 100% in hex 0x64, 1% in hex 0x01 cantps=4 + random (60);
//****************************************************************************************
  canMsg3.can_id  = 0x100; //id 100 for slow messagebatt and temps 
  canMsg3.can_dlc = 8;
  canMsg3.data[0] = 0xE0;//erratic on test 0-220 dec*****
  canMsg3.data[1] = 0x03;// constant value
  canMsg3.data[2] = 0x70;//on -off with engine 
  canMsg3.data[3] = 0x61;//Engine Temp -40
  canMsg3.data[4] = 0x80;//Battery volts /10
  canMsg3.data[5] = 0x66;//Ambient temp -40
  canMsg3.data[6] = 0xE0;//high value with ticks?
  canMsg3.data[7] = 0x04;//zero value at test

  

  canMsg4.can_id  = 0x300; 
  canMsg4.can_dlc = 8;
  canMsg4.data[0] = 0x65;//erratic on test 0-220 dec*****
  canMsg4.data[1] = 0x05;//steady low value
  canMsg4.data[2] = 0x84;//steady high value
  canMsg4.data[3] = 0x3E;//clock mins?? up and down
  canMsg4.data[4] = 0x7B;//ODO1(thousands)        
  canMsg4.data[5] = 0x02;//ODO2 0-256
  canMsg4.data[6] = 0xB2;//engine mode%16//Clock hours
  canMsg4.data[7] = 0x00;

  canMsg5.can_id  = 0x150; 
  canMsg5.can_dlc = 8;
  canMsg5.data[0] = 0x02;//Idle tps??
  canMsg5.data[1] = 0x9E;//Oxygen sens1
  canMsg5.data[2] = 0x9D;//Oxygen sens2
  canMsg5.data[3] = 0x44;// constant number at idle
  canMsg5.data[4] = 0x7C;// constant number at idle
  canMsg5.data[5] = 0x7C;//drops when engine stops
  canMsg5.data[6] = 0x02;//map%16
  canMsg5.data[7] = 0x02;//MAP //Erratic histogram but constant value!

  canMsg6.can_id  = 0x310; // all constant values maybe settings
  canMsg6.can_dlc = 8;
  canMsg6.data[0] = 0x12;
  canMsg6.data[1] = 0xAE;
  canMsg6.data[2] = 0xbd;
  canMsg6.data[3] = 0x11;
  canMsg6.data[4] = 0x5C;
  canMsg6.data[5] = 0x4C;
  canMsg6.data[6] = 0x02;
  canMsg6.data[7] = 0x39;

  canMsg7.can_id  = 0x320; // all constant values maybe settings
  canMsg7.can_dlc = 8;
  canMsg7.data[0] = 0x20;
  canMsg7.data[1] = 0x2c;
  canMsg7.data[2] = 0x58;
  canMsg7.data[3] = 0x04;
  canMsg7.data[4] = 0x40;
  canMsg7.data[5] = 0x00;
  canMsg7.data[6] = 0x0E;
  canMsg7.data[7] = 0x20;

  canMsg8.can_id  = 0x160; 
  canMsg8.can_dlc = 8;
  canMsg8.data[0] = 0x15;
  canMsg8.data[1] = 0x3a;
  canMsg8.data[2] = 0x9D;
  canMsg8.data[3] = 0x22;
  canMsg8.data[4] = 0xae;
  canMsg8.data[5] = 0x7d;
  canMsg8.data[6] = 0x02;//map%16
  canMsg8.data[7] = 0x02;//MAP //Erratic histogram but constant value!


  canMsg9.can_id  = 0x20; 
  canMsg9.can_dlc = 8;
  canMsg9.data[0] = 0x00;
  canMsg9.data[1] = 0x02;//Front wheel speed
  canMsg9.data[2] = 0x9F;//Front wheel speed
  canMsg9.data[3] = 0x4C;//immob key present
  canMsg9.data[4] = 0xEE;//immob key present
  canMsg9.data[5] = 0xD0;//immob key present
  canMsg9.data[6] = 0x00;
  canMsg9.data[7] = 0x00;
/**
  canMsg10.can_id  = 0x500; //oil reset //map and A/F reset
  canMsg10.can_dlc = 8;//oil //MAP //A_F //FAN on
     canMsg10.data[0] = 0x6C;//6D//01//6d or 6C
     canMsg10.data[1] = 0x00;//00//00//00
     canMsg10.data[2] = 0x00;//00//00//00
     canMsg10.data[3] = 0x21;//00//20//20
     canMsg10.data[4] = 0x00;//00//40//00
     canMsg10.data[5] = 0x00;//00//00//00
     canMsg10.data[6] = 0x00;//00//00//00
     canMsg10.data[7] = 0x00;//00//00//00

  canMsg11.can_id  = 0x7E3; //DESMO reset 
  canMsg11.can_dlc = 8;
     canMsg11.data[0] = 0x01;
     canMsg11.data[1] = 0x20;
     canMsg11.data[2] = 0x00;
     canMsg11.data[3] = 0x00;
     canMsg11.data[4] = 0x00;
     canMsg11.data[5] = 0x00;
     canMsg11.data[6] = 0x00;
     canMsg11.data[7] = 0x00;

**/
  Serial.begin(9600);
 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
   
  Serial.println("Example: Write to CAN");
}

void loop() {    
 //***********************************

 int canfuel =1 + random (99);
  canMsg1.can_id  = 0x18;// gear and rear wheel speed
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x00;
  canMsg1.data[1] = 0x1E;//changes with TPS
  canMsg1.data[2] = 0x56;//pulses with engineand stops at off 
  canMsg1.data[3] = 0x00;
  canMsg1.data[4] = 0xA1;  //first digit after gear
  /**      1 HEX = N
           2 HEX = 1
          4 HEX = 2
           6 HEX = 3
            8 HEX = 4
        A(10) HEX = 5
        C(12) HEX = 6 **/ //second digit wheel speed
  canMsg1.data[5] = 0x21;//Wheel speed first digit
  canMsg1.data[6] = canfuel; //fuel level 0 - 
  canMsg1.data[7] = 0x5C;

  mcp2515.sendMessage(&canMsg1);
  delayMicroseconds(3000);

  //***************************
   cantps=4 + random (60);
   canrpmth = 4 + random(38);
   canrpmMin = 1 + random (38);
 canMsg2.can_id  = 0x80;//throttle position and rpm
  canMsg2.can_dlc = 8;
  canMsg2.data[0] = 0x0C;//follows TPS sub throttle function
  canMsg2.data[1] = 0x07;// follows TPS agian sub function different value
  canMsg2.data[2] = 0x00;//zero at this test
  canMsg2.data[3] = 0x00;// zero through garage test
  canMsg2.data[4] = 0xC8;//constant at dec 200
  canMsg2.data[5] = canrpmth;//rpm{5}*256 + {6}
  canMsg2.data[6] = canrpmMin;// zero through garage test
  canMsg2.data[7] = cantps;//tps 100% in hex 0x64, 1% in hex 0x01
  //*************************
 mcp2515.sendMessage(&canMsg2);
  delayMicroseconds(30000);
  mcp2515.sendMessage(&canMsg3);
  delayMicroseconds(30000);
  mcp2515.sendMessage(&canMsg4);
  delayMicroseconds(30000);
  mcp2515.sendMessage(&canMsg5);
  delayMicroseconds(30000);
  mcp2515.sendMessage(&canMsg6);
  delayMicroseconds(30000);
  mcp2515.sendMessage(&canMsg7);
  delayMicroseconds(50000);
  mcp2515.sendMessage(&canMsg8);
  delayMicroseconds(50000);
  mcp2515.sendMessage(&canMsg9);
 delayMicroseconds(10000);


  Serial.println("Messages sent");

   delay(100);

}
