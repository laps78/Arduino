/*
                  SITUATION CHEMATIC DIAGRAM
   _______________                          _______________
   |             |                          |             |
www|             |WWWWwwwwWwwwWWwwwwWwwwWwww|             |WwW
---|             |--------------------------|~~~~~~~~~~~~~|---
   |             |                  sensor +|             |
   |~~~~~~~~~~~~~|                          |             |
   |             |                  sensor +|             |
   |             |==========================|             |
   |             |           tube           |             |
   |            +|sensor                    |             |
   |=============|                          |=============|
       BARREL 2                                 BARREL 1
                     SENSOR CONTROL TABLE
  ========================================================
  |                              |   КОНТРОЛЬ СЕНСОРОВ   |
  | НАИМЕНОВАНИЕ ОБЪЕКТА/СЕНСОРА |-----------------------|
  |                              | ЕСТЬ ВОДА | НЕТ ВОДЫ  |
  |------------------------------------------------------|
  | КОЛОДЕЦ 2 (малый, источник)  |           |           |
  |              синий/бело-синий|      1    |     0     |
  |------------------------------------------------------|
  | КОЛОДЕЦ 1 (большой, приемник)|           |           |
  |    коричневый/бело-коричневый|      1    |     0     |
  |------------------------------------------------------|
  | КОЛОДЕЦ 1 (большой, приемник)|           |           |
  |          зеленый/бело-зеоеный|      1    |     0     |
  ========================================================
*/

// определение функций портов ввода-вывода
#define barrel_2_has_water 8  // датчик НАЛИЧИЯ ВОДЫ колодца 2  - СИНИЙ/БЕЛО-СИНИНЙ
#define barrel_1_is_full 6    // датчик ВЕРХНЕГО УРОВНЯ, колодец 1 КОРИЧНЕЫЙ/БЕЛО-КОРИЧНЕВЫЙ
#define barrel_1_has_space 5  // датчик НИЖНЕГО УРОВНЯ, колодец 1 ЗЕЛЕНЫЙ/БЕЛО-ЗЕЛЕНЫЙ 
#define pump_relay 10         // реле
#define led 13                // индикация на плате управления
#define button_start 4        // Кнопка ручного запуска насоса

// определение переменных
bool barrel_2_sens_downer = LOW;
bool barrel_1_sens_upper = LOW;
bool barrel_1_sens_downer = LOW;
bool pump_status = LOW;
bool button = LOW;

// определение рабочих функций
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

void normalCycle() {
  do {
    pumpOn();
  } while (barrel_2_sens_downer == HIGH && barrel_1_sens_upper == LOW);
}

// установки скетча
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
  
  // гарантируем, что реле насоса отключено на момент старта программы
  digitalWrite(pump_relay, LOW);
}

// рабочий цикл
void loop() {
  // проверяем статус переменной "насос", обнуляем при необходимости:
  if (pump_status == HIGH) {
    pump_status = LOW;
  }

  // Рабочий цикл:
  // опрос датчиков и запись в переменные:
  barrel_2_sens_downer = digitalRead(barrel_2_has_water);
  barrel_1_sens_upper = digitalRead(barrel_1_is_full);
  barrel_1_sens_downer = digitalRead(barrel_1_has_space);
  button = digitalRead(button_start);
  
  // Блок проверки условий рабочего цикла
  if (barrel_2_sens_downer == HIGH) { // определяем наличие воды для перекачки
    if (barrel_1_sens_upper == LOW) { // определяем наличие места для перекачки
      normalCycle();
    }
  }

  // отладочные сообщения в монитор порта:
  Serial.print("Нижний датчик колодца №2: ");
  Serial.println(barrel_2_sens_downer);

  Serial.print("Верхний датчик колодца №1: ");
  Serial.println(barrel_1_sens_upper);

  Serial.print("Нижний датчик колодца №1: ");
  Serial.println(barrel_1_sens_downer);

  Serial.print("Кнопка нажата: ");
  Serial.println(button);

  Serial.print("Статус реле: ");
  Serial.println(pump_relay);

  Serial.print("Состояние переменной статуса насоса: ");
  Serial.println(pump_status);

  Serial.println("Цикл завершен.");
  
  /* Раскомментируй следующую строку чтобы включить задержку вывода сообщений в серийный порт для отладки */
  // delay(3000);
}
