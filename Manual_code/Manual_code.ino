#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <IRremote.hpp>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define MOTORA_DIR1   6 //change the pins
#define MOTORA_DIR2   10
#define MOTORB_DIR1   9
#define MOTORB_DIR2   5

int myspeed = 255;
int speedd=80;
const int IR_RECEIVE_PIN = 3;

//const int redPin = 10;

void PV_MOTOR_FORWARD(){
     while (IrReceiver.decode()==1){
      IrReceiver.decode();
      analogWrite( MOTORA_DIR1, speedd);
       analogWrite( MOTORA_DIR2, LOW);
       IrReceiver.resume();
       delay(200);
       IrReceiver.decode();
     }
}

void PV_MOTOR_BACKWARD(){
     while (IrReceiver.decode()==1){
      IrReceiver.decode();
      analogWrite(MOTORA_DIR1, LOW);
       analogWrite( MOTORA_DIR2, speedd);
       IrReceiver.resume();
       delay(200);
       IrReceiver.decode();
     }
}

void BASE_MOTOR_FORWARD(){
     while (IrReceiver.decode()==1){
      IrReceiver.decode();
      analogWrite(MOTORB_DIR1, speedd);
       analogWrite(MOTORB_DIR2, LOW);
       IrReceiver.resume();
       delay(200);
       IrReceiver.decode();
     }
}

void BASE_MOTOR_BACKWARD(){
     while (IrReceiver.decode()==1){
      IrReceiver.decode();
      analogWrite(MOTORB_DIR1, LOW);
       analogWrite(MOTORB_DIR2 , speedd);
       IrReceiver.resume();
       delay(200);
       IrReceiver.decode();
     }
}

void DisplayR() {
    lcd.clear(); // Clear the LCD
    lcd.setCursor(0, 0);
    lcd.print("Moving Right"); 
}

void DisplayL() {
    lcd.clear(); // Clear the LCD
    lcd.setCursor(0, 0);
    lcd.print("Moving Left"); 
}

void Displayup() {
    lcd.clear(); // Clear the LCD
    lcd.setCursor(0, 0);
    lcd.print("Moving Up"); 
}

void DisplayD() {
     lcd.clear(); // Clear the LCD
    lcd.setCursor(0, 0);
    lcd.print("Moving Down"); 
}

void setup()

{
  pinMode(MOTORA_DIR1, OUTPUT);
  pinMode(MOTORA_DIR2, OUTPUT);
  pinMode(MOTORB_DIR1, OUTPUT);
  pinMode(MOTORB_DIR2, OUTPUT);
  Serial.begin(9600);
lcd.init();
lcd.backlight();
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver

  //pinMode(redPin, OUTPUT);

}
 
void loop(){
  
  if (IrReceiver.decode()){
     Serial.println("pressd button:");
     Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    
   if(IrReceiver.decodedIRData.decodedRawData== 0xE619BF40 ){
    Serial.println("PV motor moving up");
     IrReceiver.resume(); IrReceiver.decode();
     delay(300);
    IrReceiver.decode();
    analogWrite( MOTORA_DIR1, myspeed);
    PV_MOTOR_FORWARD();
    Displayup();
   
  }
       digitalWrite(MOTORA_DIR1, LOW);
       digitalWrite(MOTORA_DIR2, LOW);
       IrReceiver.resume();

    
       
   if(IrReceiver.decodedIRData.decodedRawData== 0xE21DBF40 ){
    Serial.println("PV motor moving down");
     IrReceiver.resume(); IrReceiver.decode();
     delay(300);
    IrReceiver.decode();
    analogWrite( MOTORA_DIR2, myspeed);
   PV_MOTOR_BACKWARD();
   DisplayD();
   
  }
       digitalWrite(MOTORA_DIR1, LOW);
       digitalWrite(MOTORA_DIR2, LOW);
       IrReceiver.resume();

       
   if(IrReceiver.decodedIRData.decodedRawData== 0xBF40BF40 ){
     Serial.println("Base motor moving right");
     IrReceiver.resume(); IrReceiver.decode();
     delay(300);
    IrReceiver.decode();
    analogWrite(MOTORB_DIR1, myspeed);
    BASE_MOTOR_FORWARD();
    DisplayR();
   
  }
       digitalWrite(MOTORB_DIR1, LOW);
       digitalWrite(MOTORB_DIR2, LOW);
       IrReceiver.resume();

       
   if(IrReceiver.decodedIRData.decodedRawData== 0xBD42BF40 ){
    Serial.println("Base motor moving left");
     IrReceiver.resume(); IrReceiver.decode();
     delay(300);
    IrReceiver.decode();
    analogWrite(MOTORB_DIR2 , myspeed); 
   BASE_MOTOR_BACKWARD();
   DisplayL();
   
  }
       digitalWrite(MOTORB_DIR1, LOW);
       digitalWrite(MOTORB_DIR2, LOW);
       IrReceiver.resume();

  }

}
