#include <VirtualWire.h>
#include <AFMotor.h>

const int dataPin = 9;
const int ledPin = 16;

//Varaiables del motor
AF_DCMotor M1(1);
AF_DCMotor M2(3);

// Agregue
int Trig = 15;
int Echo = 14;

int cont = 0;
int aux = 0;

void setup()
{
  // Agregue
  //Serial.begin (9600);
  M1.setSpeed(180);
  M2.setSpeed(180);

  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  //

  vw_setup(2000);
  vw_set_rx_pin(dataPin);
  vw_rx_start();

  //Varaiables del motor
  M1.setSpeed(180);
  M2.setSpeed(180);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, true);
  delay(300);
  digitalWrite(ledPin, false);

  M1.run(FORWARD);
  M2.run(FORWARD);
}

void loop()
{
  uint8_t data;
  uint8_t dataLength = 1;

  if (vw_get_message(&data, &dataLength))
  {
    /*if ((char)data == 'a')
      {
      digitalWrite(ledPin, true);
      delay(300);
      digitalWrite(ledPin, false);
      //Avanzar
      M1.run(FORWARD);
      M2.run(FORWARD);
      }*/
    if ((char)data == 'r')
    {
      digitalWrite(ledPin, true);
      delay(300);
      digitalWrite(ledPin, false);
      //Detener
      M1.run(RELEASE);
      M2.run(RELEASE);
      delay(400);
      //Retroceder
      M1.run(BACKWARD);
      M2.run(BACKWARD);
      delay(400);
    }
    else if ((char)data == 'i')
    {
      digitalWrite(ledPin, true);
      delay(300);
      digitalWrite(ledPin, false);
      //Gira a la izquierda
      M1.run(FORWARD);
      M2.run(BACKWARD);
    }
    else if ((char)data == 'd')
    {
      digitalWrite(ledPin, true);
      delay(300);
      digitalWrite(ledPin, false);
      //Gira a la derecha
      M1.run(BACKWARD);
      M2.run(FORWARD);
    }/*
    else if ((char)data == 's')
    {
      digitalWrite(ledPin, true);
      delay(300);
      digitalWrite(ledPin, false);
      //Detener
      M1.run(RELEASE);
      M2.run(RELEASE);
      delay(400);
    }*/
    else {
      digitalWrite(ledPin, true);
      delay(300);
      digitalWrite(ledPin, false);
      //Avanzar
      M1.run(FORWARD);
      M2.run(FORWARD);
    }
  }
  delay(100);
}
