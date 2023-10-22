#include <Ultrasonic.h>
#include <Servo.h>

#define PI 3.14159265359

#define trig 13
#define echo 12

#define rotacaoPin 8
#define bracoPin 9
#define antebracoPin 10

Ultrasonic sensor(trig, echo);
Servo braco, antebraco, rotacao;
bool ready = true;
int distQnt = 10;

void turnTo(Servo&, int, int);
void returnToMiddle(void);

void setup()
{
  braco.attach(bracoPin);
  antebraco.attach(antebracoPin);
  rotacao.attach(rotacaoPin);

  rotacao.write(60);
  braco.write(90);
  antebraco.write(100);
}

void loop()
{
  //verifica que o sinal do sensor ultrassonico está consistente no intervalo
  if(ready && sensor.read() <= 150) distQnt--;
  else if(!ready && sensor.read() > 150) distQnt--;
  else distQnt = 10;

  //realiza o movimento se o sensor estiver estável abaixo de 150cm e se o braço não se movimentou até o valor ficar acima de 150cm de novo
  if(ready && !distQnt){
    turnTo(braco, 180, 350);
    turnTo(antebraco, 80, 250);
    turnTo(rotacao, 30, 500);
    turnTo(rotacao, 90, 700);
    turnTo(rotacao, 30, 700);
    turnTo(rotacao, 90, 700);
    returnToMiddle();

    ready = false; //indica que o braço deve aguardar o sensor ler uma distância maior de novo
    distQnt = 10; //reinicia a contagem de leituras do sensor
  }
  else if(!ready && !distQnt){
    ready = true; //indica que o braço já pode se movimentar
  }
}

//função de interpolação senoidal
void turnTo(Servo& servo, int pos, int ms)
{
  //converte a posição atual e desejada para microsegundos
  int aux = map(servo.read(), 0, 180, 544, 2400);
  pos = map(pos, 0, 180, 544, 2400);

  //ajusta os coeficientes
  double a = (pos - aux)/2;
  double h = (aux < pos ? aux : pos) + abs(a);
  double b = PI/ms;

  //define o tempo de início da função
  unsigned long start = millis();
  unsigned long time = start;

  while(time - start < ms){
    time = millis();
    aux = h + (a*sin((b*(time-start)) - (PI/2))); //define o angulo em microsegundos para o tempo atual por meio da função seno
    servo.writeMicroseconds(aux);
  }
  servo.write(pos); //ajusta o servo ao fim do movimento para conseguir usar read() depois
}

//retorna o braço para a posição de descanso (ângulos obtidos por experimentação)
void returnToMiddle()
{
  turnTo(rotacao, 60, 1000);
  turnTo(braco, 90, 500);
  turnTo(antebraco, 100, 500);
}