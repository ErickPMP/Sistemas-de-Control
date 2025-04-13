#define ADC 34
hw_timer_t * timer = NULL; //Objeto disponible para configurar timer    * Puntero
int timer_flag = 0; //Bandera Timer
float u_n = 0,u_n1 = 0,y_n = 0,y_n1 = 0;
/*Constantes y varialbes de filtro*/
float a = 0.07688, b = -0.9231;
void IRAM_ATTR timer_ISR() //Rutina de Interrupción cada 10 ms
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
    u_n = (analogRead(ADC)/4095.0);  //ADC 12 bits -> 4095 resolución de 0 a 3.3V
    // y[n] = a*u[n-1] - b*y[n-1]
    y_n = a*u_n1 - b*y_n1;         
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
    if(inChar == 'b')  //begin
    {
      timer =timerBegin(1000000); //Frecuencia del timer 1 Mhz ciclos por seg (ciclo de trabajo ->1us), límite el oscilador del ESP 32
      timerAttachInterrupt(timer, &timer_ISR); //Enlace Funcion ISR con objeto Timer
      timerAlarm(timer, 10000, true,0); // 10 ms (objeto,Ts(us->1e-6),autoreload, ) Interrupción cada 10000 ciclos de trabajo
    }
    else if(inChar == 'e') //end
    {
      timerStop(timer);
      timerDetachInterrupt(timer);
      timerEnd(timer);
      u_n = 0,u_n1 = 0,y_n = 0,y_n1 = 0;
    }
  }
}
