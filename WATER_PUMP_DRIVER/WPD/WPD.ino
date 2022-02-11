#define fullSensor1 7//датчик наполнения колодца 1 СИНИЙ (ВП)БЕЛЫЙ
#define fullSensor2 6//датчик верхнего уровня, колодец 2 ЗЕЛЕНЫЙ (ВП)/КОРИЧНЕВЫЙ
#define emptySensor2 5//датчик нижнего уровня, колодец 2 КОРИЧНЕВЫЙ (ВП)/ЖЕЛТЫЙ
#define relay 10//реле
#define led 13
#define btnStart 4// Кнопка ручного запуска насоса

bool fSens1 = LOW;
bool fSens2 = LOW;
bool eSens2 = LOW;
bool pumpStatus = LOW;
bool btn = LOW;
void pumpOn() 
  {
  Serial.println("Pump Activated");
  Serial.println(digitalRead(fullSensor1)); 
  Serial.println(digitalRead(emptySensor2));
  digitalWrite (relay, HIGH);
  digitalWrite(led, HIGH);
  pumpStatus = HIGH;
  }
void pumpOff()
  {
  Serial.println("Pump stop!");
  digitalWrite (relay, LOW);
  digitalWrite(led, LOW);
  pumpStatus = LOW; 
  }

void setup() {

Serial.begin(9600);
pinMode(relay, OUTPUT);//relay pin initialisation
pinMode(led, OUTPUT);
digitalWrite(relay, LOW);
}

void loop() {
//*********************************************************************************************************
// проверяем статус переменной "насос", обнуляем при необходимости:
//*********************************************************************************************************
if (pumpStatus == HIGH)
{pumpStatus = LOW;
  }
//*********************************************************************************************************
// Рабочий цикл:
//*********************************************************************************************************

//опрос датчиков и запись в переменные:
fSens1 = digitalRead(fullSensor1); 
fSens2 = digitalRead(fullSensor2);
eSens2 = digitalRead(emptySensor2);
btn = digitalRead(btnStart);

//Блок проверки условий
if (fSens1 == LOW && eSens2 == LOW)
{
  if (fSens2 == HIGH || btn == HIGH)
  {
    do
    {
    pumpOn();
    } 
    while  (digitalRead(emptySensor2) == LOW && digitalRead(fullSensor1) == LOW);
  }
  pumpOff();
}

//***********************************************************************************************************
// отладочные сообщения в монитор порта:

Serial.print("Верхний датчик колодца №1: ");
Serial.println(digitalRead(fullSensor1));

Serial.print("Верхний датчик колодца №2: ");
Serial.println(digitalRead(fullSensor2));

Serial.print("Нижний датчик колодца №2: ");
Serial.println(digitalRead(emptySensor2));

Serial.print("Кнопка нажата: ");
Serial.println(digitalRead(btnStart));

Serial.print("Статус реле: ");
Serial.println(relay);

Serial.print("Состояние переменной статуса насоса: ");
Serial.println(pumpStatus);

Serial.println("Цикл завершен.");

//delay(5000);

}
