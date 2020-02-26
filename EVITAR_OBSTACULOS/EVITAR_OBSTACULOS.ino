#include <AFMotor.h>

AF_DCMotor M1(1);
AF_DCMotor M2(3);

int Trig = 15;
int Echo = 14;

int cont = 0;
int aux = 0;

void setup() 
{
  //Serial.begin (9600);
  M1.setSpeed(180);
  M2.setSpeed(180);
  
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
}

void loop() 
{
  long duracion;
  long distancia;
  
  digitalWrite(Trig,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig,LOW);
  
  duracion = pulseIn(Echo,HIGH);
  distancia = (duracion/2)/29;

  //Serial.println(distancia);
  if(distancia > 10)
  {
    M1.run(FORWARD);
    M2.run(FORWARD);
  }
  else if(distancia < 4)
  {
    M1.run(RELEASE);
    M2.run(RELEASE);
    delay(400);
    M1.run(BACKWARD);
    M2.run(BACKWARD);
    delay(400);
    cont++;
  }
  else
  {
    if(aux == 0)
    {
      M1.run(FORWARD);
      M2.run(BACKWARD);
    }
    else
    {
      M1.run(BACKWARD);
      M2.run(FORWARD);
    }

    while(distancia < 20 && distancia > 3)
    {
      digitalWrite(Trig,LOW);
      delayMicroseconds(2);
      digitalWrite(Trig,HIGH);
      delayMicroseconds(10);
      digitalWrite(Trig,LOW);
  
      duracion = pulseIn(Echo,HIGH);
      distancia = (duracion/2)/29;
      delay(100);
    }

    if(cont == 2 && aux == 0)
    {
      aux = 1;
      cont = 0;
    }
    else if(cont == 2)
    {
      aux = 0;
      cont = 0;
    }
  }
  delay(100);
}
