hw_timer_t * timer = NULL;
volatile bool timer_flag = false;

int trig = 2;
int eco = 4;
long duracion;
int distancia;
int w = 0;
float In = 0, Out = 0;
typedef union {
  float number;
  uint8_t bytes[4];
} valor;

valor Out_ML;
valor In_ML;

void IRAM_ATTR timer_ISR() {
  timer_flag = true;  // Solo cambia una bandera, ISR debe ser rápida
}

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(eco, INPUT);
  timer =timerBegin(1000000); //Frecuencia del timer 1 Mhz ciclos por seg (ciclo de trabajo ->1us), límite el oscilador del ESP 32
  timerAttachInterrupt(timer, &timer_ISR); //Enlace Funcion ISR con objeto Timer
  timerAlarm(timer, 10000, true,0); // 10 ms (objeto,Ts(us->1e-6),autoreload, ) Interrupción cada 10000 ciclos de trabajo
}

void loop() {
  if (timer_flag) {
    timer_flag = false;

    // Enviar pulso ultrasónico
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    // Medir duración del eco
    duracion = pulseIn(eco, HIGH); // Timeout opcional de 30 000 us (30 ms)
    distancia = duracion / 58.2;

    // Mostrar distancia
    //Serial.print("Distancia: ");
    //Serial.print(distancia);
    //Serial.println(" cm");
    w = w + 1;
  }
  In = distancia;
  Out = Out; 
  if (w==5){
    w = 0;
    Out_ML.number = Out;
    In_ML.number = In;
    Serial.write('V');
      for (int i = 0; i < 4; i++) { Serial.write(Out_ML.bytes[i]); }
      for (int i = 0; i < 4; i++) { Serial.write(In_ML.bytes[i]); }
    Serial.write('\n');
  }
}
/*
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
    }
  }
}*/
