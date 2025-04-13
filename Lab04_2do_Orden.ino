#define ADC 34
hw_timer_t * timer = NULL;
int timer_flag = 0;
float u_n = 0,u_n1 = 0, u_n2 = 0 ,y_n = 0,y_n1 = 0, y_n2 = 0;
/*Constantes y varialbes de filtro*/
float a = 0.3599, b = 0.2735, c = -0.8159, d = 0.4493;
/**/
float Ts = 0.1;

void IRAM_ATTR timer_ISR() 
{
  timer_flag = 1;
}

void setup()
{
  Serial.begin(115200);
  delay(1000);
} 
void loop()
{
  if(timer_flag == 1)
  {
    u_n = (analogRead(ADC)/4095.0);
    y_n = a*u_n1 + b*u_n2 - c*y_n1 - d*y_n2;    // y[n] = a*u[n-1] + b*u[n-2] - c*y[n-1] - d*[y-2]
    u_n2 = u_n1;
    y_n2 = y_n1;
    u_n1 = u_n;
    y_n1 = y_n;
    Serial.print(u_n);
    Serial.print(',');
    Serial.println(y_n);
    timer_flag = 0;
  } 
}

char inChar;

void serialEvent()
{
  while (Serial.available())
  {
    inChar = Serial.read();
    if(inChar == 'b')
    {
      timer =timerBegin(1000000);
      timerAttachInterrupt(timer, &timer_ISR);
      timerAlarm(timer, round(Ts*1000000), true,0);
    }
    else if(inChar == 'e')
    {
      timerStop(timer);
      timerDetachInterrupt(timer);
      timerEnd(timer);
      u_n = 0,u_n1 = 0,y_n = 0,y_n1 = 0;
    }
  }
}
