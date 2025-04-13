hw_timer_t * timer = NULL;
int timer_flag = 0;
float t;
float Ts = 0.01;
float y_n = 0;
/*Constantes y varialbes de filtro*/
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
    t = t + Ts;                 // Cada vez que timerFlag sea igual a 1 entonces la variable de tiempo t
    y_n = sin(2*3.1416*4*t);    // se actualiza e incrementa su valor en Ts, con la ayuda de esto podemos
    Serial.println(y_n);        // generar la y(t), que es una señal senoidal simple de frecuencia 2 Hz.
     
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
      timerAlarm(timer, 10000, true,0);
    }
    else if(inChar == 'e')
    {
      timerStop(timer);
      timerDetachInterrupt(timer);
      timerEnd(timer);
