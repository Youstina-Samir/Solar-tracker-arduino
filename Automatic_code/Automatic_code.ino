#define ldr_b_l     A0
#define ldr_b_r     A1
#define ldr_u_l     A2
#define ldr_u_r     A3

#define RECV_PIN 11

// base motor 
#define base_motor_speed 3
#define base_motor_clockwise 4
#define base_motor_Anti_clockwise 5

// PV cell motor
#define pv_motor_speed 9
#define pv_motor_clockwise 7
#define pv_motor_Anti_clockwise 6

void base_clockwise();
void base_Anti_clockwise();
void pv_clockwise();
void pv_Anti_clockwise();
void Stop_pv();
void Stop_base();
void Error(void);
void PID_control ();
void track();
void manual();
float e_1,e_2,u_1,up_1,ud_1,e1,e2,e_old_1,u_2,up_2,ud_2,e_old_2;
                                                                //e1 Horizontal
                                                                // e2 vertical
                                                            
float Kp_1 = 0.8; 
float Kd_1 = 0.5;

float Kp_2 = 0.8;
float Kd_2 = 0.5;

int Speed_base = 0;
int Speed_pv = 0;
float Error_arr[2]={0};

void setup() {
  Serial.begin(9600);
  pinMode(base_motor_speed, OUTPUT);
  pinMode(base_motor_clockwise, OUTPUT);
}

void loop() {  
  track();
}


void Error(void)
{
Error_arr[0]=(analogRead(ldr_b_l)-analogRead(ldr_u_r)); // Horizontal LDRs
Error_arr[1]=(analogRead(ldr_b_r)-analogRead(ldr_u_l)); // Vertical
 
}

void PID_control  ()
{
  Error();
 e_1 = Error_arr[0];
 e_2 = Error_arr[1];
 up_1=Kp_1*e_1;
 ud_1=Kd_1*(e_1-e_old_1);
 u_1=up_1+ud_1;
 e_old_1=e_1; 

 up_2=Kp_2*e_2;
 ud_2=Kd_2*(e_2-e_old_2);
 u_2=up_2+ud_2;
 e_old_2=e_2; 
}

void track()
{
 PID_control ();
 if(u_1<0 && abs(u_1)>100)
 {
  Speed_base = map(abs(u_1), 0, 1023, 0, 255);
 base_clockwise ();
 Serial.println("cw");
 Serial.println("speed_base");
 Serial.println(Speed_base);
 delay(300);
 }
 else if(u_1>0 && abs(u_1)>100)
 {
 Speed_base = map(abs(u_1), 0, 1023, 0, 255);
 base_Anti_clockwise ();
 Serial.println("ccw");
 Serial.println("speed_base");
 Serial.println(Speed_base);
 delay(300);
 }
 else if(abs(u_1)<100)
 {
 Stop_base();
 Serial.println("stop");
  Serial.println("BASE");
  Serial.println(u_1);
  // delay(3000);
 }
 if(u_2>0 && abs(u_2)>100)
 {
    Speed_pv=map(abs(u_2),0,1023,0,255); 
    pv_Anti_clockwise();
    Serial.println("Acw");
 Serial.println("speed_pv");
 Serial.println(Speed_pv);
 delay(300);
    Serial.println("up");
 }
 else if(u_2<0 && abs(u_2)>100)
 {
     Speed_pv=map(abs(u_2),0,1023,0,255); 
     pv_clockwise ();
     Serial.println("cw");
    Serial.println("speed_pv");
    Serial.println(Speed_pv);
      delay(300);
     Serial.println("down");
 }
 else if(abs(u_2)<100)
 {

     Stop_pv();
     Serial.println("pv");
 }
 }

 void base_clockwise () 
{
analogWrite(base_motor_speed, Speed_base);
digitalWrite(base_motor_clockwise, HIGH);
digitalWrite(base_motor_Anti_clockwise, LOW);
}

void base_Anti_clockwise () 
{
analogWrite(base_motor_speed, Speed_base);
digitalWrite(base_motor_clockwise, LOW);
digitalWrite(base_motor_Anti_clockwise, HIGH);
}

void Stop_base()
{ 
digitalWrite(base_motor_clockwise,LOW); 
digitalWrite(base_motor_Anti_clockwise,LOW);
}

void pv_clockwise () 
{
 analogWrite (pv_motor_speed, Speed_pv);
 digitalWrite(pv_motor_clockwise, HIGH);
 digitalWrite(pv_motor_Anti_clockwise,LOW);
}

void pv_Anti_clockwise () 
{
analogWrite (pv_motor_speed, Speed_pv);
digitalWrite(pv_motor_clockwise, LOW);
digitalWrite(pv_motor_Anti_clockwise, HIGH);
}

void Stop_pv()
{
digitalWrite(pv_motor_clockwise,LOW);
digitalWrite(pv_motor_Anti_clockwise,LOW); 
}
