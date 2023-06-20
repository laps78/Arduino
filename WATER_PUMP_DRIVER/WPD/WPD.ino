#define barrel_2_has_water 8//  датчик НАЛИЧИЯ ВОДЫ колодца 2  - СИНИЙ/БЕЛО-СИНИНЙ
#define barrel_1_is_full 6//    датчик ВЕРХНЕГО УРОВНЯ, колодец 2 КОРИЧНЕЫЙ/БЕЛО-КОРИЧНЕВЫЙ
#define barrel_1_has_space 5//  датчик НИЖНЕГО УРОВНЯ, колодец 2 ЗЕЛЕНЫЙ/БЕЛО-ЗЕЛЕНЫЙ 
#define pump_relay 10//         реле
#define led 13
#define button_start 4//       Кнопка ручного запуска насоса

bool bar_2_sens_downer = LOW;
bool bar_1_sens_upper = LOW;
bool bar_1_sens_downer = LOW;
bool pump_status = LOW;
bool button = LOW;

void pumpOn() {
  Serial.println("Pump Activated");
  digitalWrite (pump_relay, HIGH);
  digitalWrite(led, HIGH);
  pump_status = HIGH;
}

void pumpOff() {
  Serial.println("Pump stop!");
  digitalWrite (pump_relay, LOW);
  digitalWrite(led, LOW);
  pump_status = LOW; 
}


void setup() {
  //open port monitoring
  Serial.begin(9600);

  //pin initialization
  pinMode(pump_relay, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(button_start, INPUT);
  pinMode(barrel_2_has_water, INPUT);
  pinMode(barrel_1_is_full, INPUT);
  pinMode(barrel_1_has_space, INPUT);


  digitalWrite(pump_relay, LOW);
}

void loop() {
  // проверяем статус переменной "насос", обнуляем при необходимости:
  if (pump_status == HIGH) {
    pump_status = LOW;
    }

  // Рабочий цикл:
  // опрос датчиков и запись в переменные:
  bar_2_sens_downer = digitalRead(barrel_2_has_water); 
  bar_1_sens_upper = digitalRead(barrel_1_is_full);
  bar_1_sens_downer = digitalRead(barrel_1_has_space);
  button = digitalRead(button_start);

  // Блок проверки условий
  if(bar_2_sens_downer == HIGH && bar_1_sens_upper == LOW) {
    if (bar_1_sens_downer == HIGH || button == HIGH){
      do {
        pumpOn();
        } while (bar_1_sens_upper == LOW || bar_2_sens_downer == HIGH);
      }
    }

  // отладочные сообщения в монитор порта:
  Serial.print("Нижний датчик колодца №2: ");
  Serial.println(bar_2_sens_downer);

  Serial.print("Верхний датчик колодца №1: ");
  Serial.println(bar_1_sens_upper);

  Serial.print("Нижний датчик колодца №1: ");
  Serial.println(bar_1_sens_downer);

  Serial.print("Кнопка нажата: ");
  Serial.println(button);

  Serial.print("Статус реле: ");
  Serial.println(pump_relay);

  Serial.print("Состояние переменной статуса насоса: ");
  Serial.println(pump_status);
  
  Serial.println("Цикл завершен.");

  //delay(3000);

}
