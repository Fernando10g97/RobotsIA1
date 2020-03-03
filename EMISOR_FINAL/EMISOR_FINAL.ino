#include <VirtualWire.h>
#include <AFMotor.h>

const int dataPin = 9;

//Varaiables del motor
AF_DCMotor M1(1);
AF_DCMotor M2(3);
//Variables de distancia
int Trig = 15;
int Echo = 14;

int cont = 0;
int aux = 0;

char tipo[] = "          ";

void setup()
{
  Serial.begin(9600);
  vw_setup(2000);
  vw_set_tx_pin(dataPin);
  //Varaiables del motor
  M1.setSpeed(180);
  M2.setSpeed(180);
  //Sensor de distancua
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
}

void loop()
{
  //Movimientos
  long duracion;
  long distancia;

  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  duracion = pulseIn(Echo, HIGH);
  distancia = (duracion / 2) / 29;

  //Serial.println(distancia);
  if (distancia > 10)
  {
    //Avanzar
    //tipo = 'a';
    strcpy(tipo, "aaaaaaaaaa");
    M1.run(FORWARD);
    M2.run(FORWARD);
  }
  else if (distancia < 4)
  {
    //tipo = 'r';
    strcpy(tipo, "rrrrrrrrrr");
    //Detener
    M1.run(RELEASE);
    M2.run(RELEASE);
    delay(400);
    //Retroceder
    M1.run(BACKWARD);
    M2.run(BACKWARD);
    delay(400);
    cont++;
  }
  else
  {
    if (aux == 0)
    {
      //Gira a la izquierda
      //tipo = 'i';
      strcpy(tipo, "iiiiiiiiii");
      M1.run(FORWARD);
      M2.run(BACKWARD);
    }
    else
    {
      //Gira a la derecha
      //tipo = 'd';
      strcpy(tipo, "dddddddddd");
      M1.run(BACKWARD);
      M2.run(FORWARD);
    }

    while (distancia < 20 && distancia > 3)
    {
      digitalWrite(Trig, LOW);
      delayMicroseconds(2);
      digitalWrite(Trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(Trig, LOW);

      duracion = pulseIn(Echo, HIGH);
      distancia = (duracion / 2) / 29;
      delay(100);
    }

    if (cont == 2 && aux == 0)
    {
      aux = 1;
      cont = 0;
    }
    else if (cont == 2)
    {
      aux = 0;
      cont = 0;
    }
  }
  //Radiofrecuencia
  //while (Serial.available() > 0)
    while (tipo[0] != ' ')
    {
    char data[] = " ";
    strcpy(data, tipo);
    //char data[1];
    //data[0] = Serial.read();
    vw_send((uint8_t*)data, sizeof(data));
    vw_wait_tx();
    Serial.println(data);
    strcpy(tipo, "          ");
    }
    delay(200);
}
