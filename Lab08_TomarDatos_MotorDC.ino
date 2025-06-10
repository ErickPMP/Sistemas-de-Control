#define CHA   27
#define CHB   26
#define PWM   25
#define DIR1  33
#define DIR2  32
#define STBY  12
#include "INA226.h"
INA226 INA(0x40);

/*
  MOTOR 37D     0.0333
	MOTOR 25D     0.0470
*/
int DIR;
double theta_n = 0, theta_n1 = 0;
double omega_n = 0;
double crrnt_n = 0;

double enAcc = 0;

unsigned long timeold,timeOld2 = 0;
unsigned long timeNow;
const unsigned long Ts = 10000;
float t;
float value;
float u_n;

typedef union {
  float number;
  uint8_t bytes[4];
} valor;
valor theta_s_ML, omega_s_ML, crrnt_s_ML,Tiempo_ML, u_n_s_ML;

void IRAM_ATTR CHA_ISR(){
  DIR = (digitalRead(CHA)==digitalRead(CHB))?-1:1;
  enAcc += DIR;
}

void IRAM_ATTR CHB_ISR(){
  DIR = (digitalRead(CHA)==digitalRead(CHB))?1:-1;
  enAcc += DIR; 
}

void setup()
{
  Serial.begin(115200);
  pinMode(CHA, INPUT_PULLUP);
  pinMode(CHB, INPUT_PULLUP);
  pinMode(STBY,OUTPUT);
  pinMode(PWM,OUTPUT);
  pinMode(DIR1,OUTPUT);
  pinMode(DIR2,OUTPUT);
  digitalWrite(STBY,HIGH);
  digitalWrite(DIR1,LOW);
  digitalWrite(DIR2,HIGH); 
  attachInterrupt(digitalPinToInterrupt(CHA), CHA_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(CHB), CHB_ISR, RISING);

  Wire.begin(21,22);
  if (!INA.begin() ){
    Serial.println("could not connect. Fix and Reboot");
  }

  INA.setMaxCurrentShunt(0.8, 0.1);
  timeOld2 = micros();
}

void loop(){
  if(Serial.available() > 0){value = recepcion();}
  if (value == 1){
    if(t>=0 && t<10) {u_n = 0.0;}
    else if(t>=10 && t<20) {u_n = 3.0;}
    else if(t>=20 && t<30) {u_n = 0.0;}  
    else if(t>=30 && t<40) {u_n = 6.0;}   
    else if(t>=40 && t<50) {u_n = 0.0;}     
    else if(t>=50 && t<60) {u_n = 9.0;}   
    else if(t>=60 && t<70) {u_n = 0.0;}     
    else if(t>=70 && t<80) {u_n = 12.0;}    
    else if(t>=80 && t<90) {u_n = 0.0;}      
    else if(t>=90) {t = 0;}
    else{t=0.0;}
    analogWrite(PWM,round((u_n/12.0)*255.0));

    timeNow = micros();
    if (timeNow - timeOld2 >= Ts){
        timeOld2 = timeNow;
        t = t + (Ts / 1e6);  // Suma Ts en segundos (puedes usar Ts/1000.0 si lo quieres en milisegundos)
    }

    if (millis()-timeold >= 10){
      theta_n = ((enAcc/22.0) * 0.0470)*2*3.1416; //Delgado
      //theta_n = ((enAcc/22.0) * 0.0333)*2*3.1416;  //Gordo
      omega_n = (theta_n - theta_n1)/0.01;
      crrnt_n = INA.getCurrent_mA()/1000.0;
      theta_n1 = theta_n;

      theta_s_ML.number = theta_n;    
      omega_s_ML.number = omega_n;    
      crrnt_s_ML.number = crrnt_n;
      u_n_s_ML.number = u_n;

      Serial.write('V');
      for (int i = 0; i < 4; i++) Serial.write(theta_s_ML.bytes[i]);
      for (int i = 0; i < 4; i++) Serial.write(omega_s_ML.bytes[i]);
      for (int i = 0; i < 4; i++) Serial.write(crrnt_s_ML.bytes[i]);
      for (int i = 0; i < 4; i++) Serial.write(u_n_s_ML.bytes[i]);
      Serial.write('\n');
      timeold = millis();
    }
  }
  else {
    t = 0.0;
  }
}

//Recibir Flotante
float recepcion(){
  int i;
  valor buf;
  for(i=0; i<4; i++)
    buf.bytes[i] = Serial.read();  
  return buf.number;
}
