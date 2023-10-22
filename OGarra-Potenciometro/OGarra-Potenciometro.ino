#include <Servo.h>

#define rotacaoPin 8
#define rotacaoPot A0
#define ROTMIN 544
#define ROTMAX 2400

#define bracoPin 9
#define bracoPot A1
#define BRAMIN 1060
#define BRAMAX 2400

#define antebracoPin 10
#define antebracoPot A2
#define ANTMIN 957
#define ANTMAX 2400

#define garraPin 11
#define garraPot A3
#define GARMIN 1266
#define GARMAX 2297

Servo rotacao, braco, antebraco, garra;

int rotacaoVal, bracoVal, antebracoVal, garraVal;

void setup()
{
  rotacao.attach(rotacaoPin);
  braco.attach(bracoPin);
  antebraco.attach(antebracoPin);
  garra.attach(garraPin);
}

void loop()
{
  //conversões de sinal analógico dos potenciômetros para os microsegundos correspondentes no servo
  rotacaoVal = map(analogRead(rotacaoPot), 0, 1023, ROTMIN, ROTMAX);
  bracoVal = map(analogRead(antebracoPot), 0, 1023, BRAMIN, BRAMAX);
  antebracoVal = map(analogRead(bracoPot), 0, 1023, ANTMIN, ANTMAX);
  garraVal = map(analogRead(garraPot), 0, 1023, GARMIN, GARMAX);

  rotacao.writeMicroseconds(rotacaoVal);
  braco.writeMicroseconds(bracoVal);
  antebraco.writeMicroseconds(antebracoVal);
  garra.writeMicroseconds(garraVal);
}