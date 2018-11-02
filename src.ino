// =============================================================
// ==                   DEFINE VARIABLES                      ==
// =============================================================
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 8, d5 = 6, d6 = 5, d7 = 1;//
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int enablePin=10;//Питание мотора
const int controlPin1=2;//Мотор провод 1
const int controlPin2=9;//Мотор провод 2
//const int secondMotorPin1 = 21;// Мотор 2 провод 1
//const int secondMotorPin2 = 23;// Мотор 2 провод 2
const int potPin=A0;//PIN LEFT(Подключение потенциометра скорости)
const int potDir=A1; //DIR RIGHT(Подключение потенциометра направления)
int RC1;//Данные с потенциометра для "Переменное движение тележки"
int switchStateForLeft = 0;//Левая кнопка
int switchStateForRight = 0;//Правая кнопка
const int switchPinLeft = 4;//Пин для левой кнопки
const int switchPinRight = 13;//Пин для правой кнопки
int motorSpeed=0;//Скорость мотора
int motorDirection=1;//Направление мотора
int motorEnabled = 1;//Вкл/выкл мотора
int stateNum = 0;//Номер режима
int stateButtonAction = 0;//Переменная для переключения режима
const int stateButton1 = 3;//Кнопка для переключения режимов
int Direction = 0;//Направление мотора
int stopper = 0;//Стоппер для задания "Движения к краю"
int stopperFour = 0;//Стоппер для задания "Движение к ближайшему краю"
int stopperFive = 0;//Стоппер для задания "Центровка"
int difference;//НЕНУЖНАЯ ПЕРЕМЕННАЯ
int differenceFor12;//Различие переменных для "Индикации направления движения"
int differenceFor13;//Различие переменных для "Индикации ускорения тележки"
int value;//Данные потенциометра для "Движение к краю"
int valueFor9First;//Данные потенциометра для "Переменное движение тележки"
int valueFor12First;//Первые данные потенциометра для "Индикация направления движения"
int valueFor12Second;//Вторые данные потенциометра для "Индикация направления движения"
int valueFor13First;//Первые данные потенциометра для "Индикация ускорения тележки"
int valueFor13Second;//Вторые данные потенциометра для "Индикация ускорения тележки"
int valueFor15First;//Данные потенциометра для "Тестирование подвижной части"
int valueFor16First;//Данные потенциометра для "Тестирование датчиков"
int stopperSecond;//Стоппер для задания "Движение от края до края"
int stopperForSecond = 0;//Стоппер для задания "Движение от края до края"
int stopperSeventh = 0;//Стоппер для задания "Разгон"
int stopperEight = 0;//Стоппер для задания "Торможение"
int stopperForFifth = 0;//Стоппер для задания "Центровка"
int fatalStopperForFifth = 0;//Окончательный стоппер для задания "Центровка"
int errorStateForFifteen = 0;//Ошибка для задания "Тестирование подвижной части"
float speedValueSeventh = 50;//Скорость мотора для задания "Разгон"
float speedValueEight = 120;//Скорость мотора для задания "Торможение"
int stopperForSixth = 0;//Стоппер для задания "Дельта"
int testRightForFifteen = 0;//Переменная для проверки нажатия правой кнопки для задания "Тестирование подвижной части"
int testLeftForFifteen = 0;//Переменная для проверки нажатия левой кнопки для задания "Тестирование подвижной части"
int testRightForSixteen = 0;//Переменная для проверки нажатия правой кнопки для задания "Тестирование датчиков"
int testLeftForSixteen = 0;//Переменная для проверки нажатия левой кнопки для задания "Тестирование датчиков"
int errorStateForSixteen = 0;//Ошибка для задания "Тестирование датчков"
int progress = 0;
int soundStopperForFirst = 0;
int soundStopperForSecond = 0;
int soundStopperForThird = 0;
int soundStopperForFourth = 0;
int soundStopperForFifth = 0;
int soundStopperForSixth = 0;
int soundStopperForSeventh = 0;
int soundStopperForEight = 0;
int soundStopperForNineth = 0;
int soundStopperForTenth = 0;
int soundStopperForEleventh = 0;
int soundStopperForTwelfth = 0;
int soundStopperForThirdteenth = 0;
int soundStopperForFourthteenth = 0;
int soundStopperForFifthteenth = 0;
int soundStopperForSixteenth = 0;
const int buttonRowFirstBtn = 15;
const int buttonRowSecondBtn = 16;
const int buttonRowThirdBtn = 17;
const int buttonRowFourthBtn = 18;
const int buttonRowFifthBtn = 19;
const int buttonRowSixthBtn = 22;

const int buzzer = 7; //Speaker pin
// =============================================================
// ==                            SETUP                        ==
// =============================================================
void setup() {
  
  pinMode(potDir, INPUT);
  pinMode(buzzer, OUTPUT);
  
  pinMode(enablePin, OUTPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  
  //pinMode(secondMotorPin1, OUTPUT);
  //pinMode(secondMotorPin2, OUTPUT);
  
  pinMode(stateButton1, INPUT);  
  digitalWrite(enablePin,HIGH);
 
   // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  digitalWrite(controlPin1, LOW);
  digitalWrite(controlPin2, LOW);
  analogWrite(enablePin,0);
  
}
// =============================================================
// ==                        MAIN LOOP                        ==
// =============================================================
void loop() {

// =============================================================
// ==                   CHANGE MENU ITEM                      ==
// =============================================================
  if(digitalRead(stateButton1) == HIGH && stateButtonAction == 0){
    stateButtonAction = 1;
    stateNum++;
    if(stateNum > 16){stateNum = 0;}
  }
  if(digitalRead(stateButton1) == LOW && stateButtonAction == 1){
    stateButtonAction = 0;
  }
// =============================================================
// ==                 Остановка всех режимов                  ==
// =============================================================
if(stateNum == 0){

  if(soundStopperForFirst == 0){
    soundStopperForFirst++;
    tone(buzzer, 950, 50);
    delay(50);
    noTone(buzzer);
  }
  if(digitalRead(buttonRowFirstBtn) == HIGH){
      tone(buzzer, 950, 50);
      delay(50);
      noTone(buzzer);
  }
  if(digitalRead(buttonRowSecondBtn) == HIGH){
      tone(buzzer, 1050, 100);
      delay(100);
      noTone(buzzer);
  }
  if(digitalRead(buttonRowThirdBtn) == HIGH){
      tone(buzzer, 1150, 100);
      delay(100);
      noTone(buzzer);
  }
  if(digitalRead(buttonRowFourthBtn) == HIGH){
      tone(buzzer, 1250, 100);
      delay(100);
      noTone(buzzer);
  }
  if(digitalRead(buttonRowFifthBtn) == HIGH){
      tone(buzzer, 1350, 100);
      delay(100);
      noTone(buzzer);
  }
  if(digitalRead(buttonRowSixthBtn) == HIGH){
      tone(buzzer, 1450, 100);
      delay(100);
      noTone(buzzer);
  }
  analogWrite(enablePin,0);
  digitalWrite(controlPin1, LOW);
  digitalWrite(controlPin2, LOW);

  //digitalWrite(secondMotorPin1 , HIGH);
  //digitalWrite(secondMotorPin2 , LOW);
}
// =============================================================
// ==                 Задача 1.  Движение к краю              ==
// =============================================================
if(stateNum == 1){
  int controlPin1Side;
  int controlPin2Side;
  int direction = 1;
  //1=LEFT 0=RIGHT
  if(direction == 1){ 
    controlPin1Side = HIGH;
    controlPin2Side = LOW;
  }else{
    controlPin1Side = LOW;
    controlPin2Side = HIGH;
  }
  switchStateForLeft = digitalRead(switchPinLeft);
  switchStateForRight = digitalRead(switchPinRight);
  
  if(stopper == 0){
    value = map(400, 0, 500, 0, 104); //Map value 0-1023 to 0-255 (PWM)
    analogWrite(enablePin, value);
    digitalWrite(controlPin1, controlPin1Side);
    digitalWrite(controlPin2, controlPin2Side);
    if(switchStateForLeft == HIGH || switchStateForRight == HIGH){
      digitalWrite(controlPin1, LOW);
      digitalWrite(controlPin2, LOW);
      stopper = 1;
    }
  }else{
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, LOW);
    
  }

}
// =============================================================
// ==             Задача 2. Движение от края до края          ==
// =============================================================
if(stateNum == 2){
  if(stopperForSecond < 1){
     stopperForSecond++;
     analogWrite(enablePin,0);
     digitalWrite(controlPin1, LOW);
     digitalWrite(controlPin2, LOW);
  }
  switchStateForLeft = digitalRead(switchPinLeft);
  switchStateForRight = digitalRead(switchPinRight);
  int controlPin1Side;
  int controlPin2Side;
  int valuePotPin;
  int valuePotDir;
  lcd.setCursor(0, 1);
  lcd.print("                 ");
  valuePotPin = analogRead(potPin);
  valuePotPin = map(valuePotPin, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
  valuePotDir = analogRead(potDir);
  valuePotDir = map(valuePotDir, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
  analogWrite(enablePin, valuePotPin);
  lcd.setCursor(0, 1);
  if(valuePotDir < 5){
    valuePotDir = 0;
  }else if(valuePotDir > 95){
    valuePotDir = 100;
  }
  if(stopperSecond == 0){
    if(valuePotDir == 100){
        digitalWrite(controlPin1, HIGH);
        digitalWrite(controlPin2, LOW);
        if(switchStateForLeft == HIGH){
          digitalWrite(controlPin1, LOW);
          digitalWrite(controlPin2, LOW);
          stopperSecond = 1;
        }
     }else if(valuePotDir == 0){
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, HIGH);
        if(switchStateForRight == HIGH){
          digitalWrite(controlPin1, LOW);
          digitalWrite(controlPin2, LOW);
          stopperSecond = 1;
        }
     }
  }
  lcd.setCursor(0, 1);
  lcd.print(valuePotDir);
}
// =============================================================
// ==                 Задача 3. “Пинг-понг”                   ==
// =============================================================
if(stateNum == 3){
  int controlPin1Side;
  int controlPin2Side;
  int valuePotPin;
  int valuePotDir;
  lcd.setCursor(0, 1);
  lcd.print("                 ");
  valuePotPin = analogRead(potPin);
  valuePotPin = map(valuePotPin, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
  valuePotDir = analogRead(potDir);
  valuePotDir = map(valuePotDir, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
  analogWrite(enablePin, valuePotPin);
  lcd.setCursor(0, 1);
  if(valuePotDir < 5){
    valuePotDir = 0;
  }else if(valuePotDir > 95){
    valuePotDir = 100;
  }
  if(valuePotDir>49){
      digitalWrite(controlPin1, LOW);
      digitalWrite(controlPin2, HIGH);
   }else{
      digitalWrite(controlPin1, HIGH);
      digitalWrite(controlPin2, LOW);
   }
  lcd.setCursor(0, 1);
  lcd.print(valuePotDir);
}
// =============================================================
// ==           Задача 4. Движение к ближайшему краю          ==
// =============================================================
if(stateNum == 4){
  switchStateForLeft = digitalRead(switchPinLeft);
  switchStateForRight = digitalRead(switchPinRight);
  int controlPin1Side;
  int controlPin2Side;
  int valuePotPin;
  int valuePotDir;
  lcd.setCursor(0, 1);
  lcd.print("                 ");
  valuePotPin = analogRead(potPin);
  valuePotPin = map(valuePotPin, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
  valuePotDir = analogRead(potDir);
  valuePotDir = map(valuePotDir, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
  analogWrite(enablePin, valuePotPin);
  lcd.setCursor(0, 1);
  if(valuePotDir < 5){
    valuePotDir = 0;
  }else if(valuePotDir > 95){
    valuePotDir = 100;
  }
  if(stopperFour == 0){
    if(valuePotDir > 49){
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, HIGH);
        if(switchStateForLeft == HIGH){
          digitalWrite(controlPin1, LOW);
          digitalWrite(controlPin2, LOW);
          stopperFour = 1;
        }
     }else{
        digitalWrite(controlPin1, HIGH);
        digitalWrite(controlPin2, LOW);
        if(switchStateForRight == HIGH){
          digitalWrite(controlPin1, LOW);
          digitalWrite(controlPin2, LOW);
          stopperFour = 1;
        }
     }
  }
  lcd.setCursor(0, 1);
  lcd.print(valuePotDir);
}
// =============================================================
// ==                   Задача 5. Центровка                   ==
// =============================================================
if(stateNum == 5){
    int controlPin1Side;
    int controlPin2Side;
    int valuePotPinFive;
    int valuePotDirFive;
    if(stopperForFifth < 1){
     stopperForFifth++;
     analogWrite(enablePin,0);
     digitalWrite(controlPin1, LOW);
     digitalWrite(controlPin2, LOW);
    }
  switchStateForLeft = digitalRead(switchPinLeft);
  switchStateForRight = digitalRead(switchPinRight);
  if(switchStateForLeft == HIGH || switchStateForRight == HIGH){
       analogWrite(enablePin,0);
       digitalWrite(controlPin1, LOW);
       digitalWrite(controlPin2, LOW);
       fatalStopperForFifth = 1;
   }
  if(fatalStopperForFifth != 1){
    lcd.setCursor(0, 1);
    lcd.print("                 ");
    valuePotPinFive = analogRead(potPin);
    valuePotPinFive = map(valuePotPinFive, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
    valuePotDirFive = analogRead(potDir);
    valuePotDirFive = map(valuePotDirFive, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
    analogWrite(enablePin, valuePotPinFive);
    lcd.setCursor(0, 1);
    if(valuePotDirFive < 5){
      valuePotDirFive = 0;
    }else if(valuePotDirFive > 95){
      valuePotDirFive = 100;
    }
  
    if(valuePotDirFive == 49 || valuePotDirFive == 50 || valuePotDirFive == 51){
      digitalWrite(controlPin1, LOW);
      digitalWrite(controlPin2, LOW);
    }else{
      if(valuePotDirFive > 48){
          digitalWrite(controlPin1, HIGH);
          digitalWrite(controlPin2, LOW);
      }else{
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, HIGH);
      }    
    }
  }

  lcd.setCursor(0, 1);
  lcd.print(valuePotDirFive);
}
// =============================================================
// ==                    Задача 7. Разгон                     ==
// =============================================================
if(stateNum == 7){
  float coefficientA =1.005; 
  switchStateForLeft = digitalRead(switchPinLeft);
  switchStateForRight = digitalRead(switchPinRight);
  int controlPin1Side;
  int controlPin2Side;
  int valuePotDirForSeventh;

  //valuePotPin = analogRead(potPin);
  //valuePotPin = map(valuePotPin, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
  valuePotDirForSeventh = analogRead(potDir);
  valuePotDirForSeventh = map(valuePotDirForSeventh, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("                 ");
  if(stopperSeventh != 1){
  speedValueSeventh = speedValueSeventh * coefficientA;
  analogWrite(enablePin, speedValueSeventh);
  }
  if(valuePotDirForSeventh < 5){
    valuePotDirForSeventh = 0;
  }else if(valuePotDirForSeventh > 95){
    valuePotDirForSeventh = 100;
  }
  if(stopperSeventh == 0){
    if(valuePotDirForSeventh==100){
        digitalWrite(controlPin1, HIGH);
        digitalWrite(controlPin2, LOW);
        if(switchStateForLeft == HIGH){
          digitalWrite(controlPin1, LOW);
          digitalWrite(controlPin2, LOW);
          stopperSeventh = 1;
        }
     }else if(valuePotDirForSeventh==0){
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, HIGH);
        if(switchStateForRight == HIGH){
          digitalWrite(controlPin1, LOW);
          digitalWrite(controlPin2, LOW);
          stopperSeventh = 1;
        }
     }
  }
  lcd.setCursor(0, 1);
  lcd.print("P: "+String(valuePotDirForSeventh)+" S: "+String(speedValueSeventh));
}
// =============================================================
// ==                    Задача 8. Торможение                 ==
// =============================================================
if(stateNum == 8){
  float coefficientA = 3; 
  switchStateForLeft = digitalRead(switchPinLeft);
  switchStateForRight = digitalRead(switchPinRight);
  int controlPin1Side;
  int controlPin2Side;
  int valuePotDirForEight;

  //valuePotPin = analogRead(potPin);
  //valuePotPin = map(valuePotPin, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
  valuePotDirForEight = analogRead(potDir);
  valuePotDirForEight = map(valuePotDirForEight, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("                 ");
  if(stopperEight != 1){
    speedValueEight = speedValueEight - coefficientA;
    analogWrite(enablePin, speedValueEight);
  }

  if(speedValueEight == 0){
      digitalWrite(controlPin1, LOW);
      digitalWrite(controlPin2, LOW);
      stopperEight = 1;
  }
  
  if(valuePotDirForEight < 5){
    valuePotDirForEight = 0;
  }else if(valuePotDirForEight > 95){
    valuePotDirForEight = 100;
  }
  if(stopperEight == 0){
    if(valuePotDirForEight == 100){
        digitalWrite(controlPin1, HIGH);
        digitalWrite(controlPin2, LOW);
        if(switchStateForLeft == HIGH){
          digitalWrite(controlPin1, LOW);
          digitalWrite(controlPin2, LOW);
          stopperEight = 1;
        }
     }else if(valuePotDirForEight == 0){
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, HIGH);
        if(switchStateForRight == HIGH){
          digitalWrite(controlPin1, LOW);
          digitalWrite(controlPin2, LOW);
          stopperEight = 1;
        }
     }
  }
  lcd.setCursor(0, 1);
  lcd.print("P: "+String(valuePotDirForEight)+" S: "+String(speedValueEight));
}
// =============================================================
// ==       Задача 9. Переменное движение тележки             ==
// =============================================================
if(stateNum == 9){
  lcd.setCursor(0, 1);
  lcd.print("                 ");
  RC1 = analogRead(potPin);
  RC1 = map(RC1, 0, 1023, -104, 104); //Map value 0-1023 to 0-255 (PWM)
  valueFor9First = analogRead(potPin);
  valueFor9First = map(valueFor9First, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
  if(RC1 < -92){
    RC1 = -100;
  }else if(RC1 > 92){
    RC1 = 100;
  }
  if(valueFor9First < 5){
    valueFor9First = 0;
  }else if(valueFor9First > 92){
    valueFor9First = 100;
  }
  
  if(RC1 == -100){
    valueFor9First = 100; 
    analogWrite(enablePin, 100);
  }else if(RC1 < -90){
    valueFor9First = 90;
    analogWrite(enablePin, 90);
  }else if(RC1 < -80){
    valueFor9First = 80;
    analogWrite(enablePin, 80);
  }else if(RC1 < -70){
    valueFor9First = 70;
    analogWrite(enablePin, 70);
  }else if(RC1 < -60){
    valueFor9First = 60;
    analogWrite(enablePin, 60);
  }else if(RC1 < -50){
    valueFor9First = 50;
    analogWrite(enablePin, 50);
  }else if(RC1 < -40){
    valueFor9First = 40;
    analogWrite(enablePin, 40);
  }else if(RC1 < -30){
    valueFor9First = 30;
    analogWrite(enablePin, 30);
  }else if(RC1 < -20){
    valueFor9First = 20;
    analogWrite(enablePin, 20);
  }else if(RC1 < -10){
    valueFor9First = 10;
    analogWrite(enablePin, 10);
  }
  analogWrite(enablePin, valueFor9First);
  //analogWrite(enablePin, valueFor9First);
  if(RC1 >= -5 && RC1 <= 5){
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, LOW);
  }else if(RC1 < -6){ //-13 < -6
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
  }else if(RC1 > 6){ //20 >= 6
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }
  lcd.setCursor(0, 1);
  lcd.print(RC1);
}
// =============================================================
// ==       Задача 10. Индикация скорости движения тележки    ==
// =============================================================
if(stateNum == 10){
   motorSpeed=analogRead(potPin);
   motorSpeed = map(motorSpeed, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
   if(motorSpeed < 5){
    motorSpeed = 0;
   }else if(motorSpeed > 95){
    motorSpeed = 100;
   }
   delay(200);
   lcd.setCursor(0, 1);
   lcd.print("                  ");
   lcd.setCursor(0, 1);
   lcd.print("V= ");
   lcd.setCursor(3, 1);
   lcd.print(motorSpeed);
}
// =============================================================
// ==        Задача 11. Индикация положения тележки           ==
// =============================================================
if(stateNum == 11){
   lcd.setCursor(0, 1);
   lcd.print("                 ");
   value = analogRead(potDir);          //Read and save analog value from potentiometer
   value = map(value, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
   lcd.setCursor(0, 1);
   if(value < 0){
    value = 0;
   }else if(value > 100){
    value = 100;
   }
   lcd.setCursor(0, 1);
   lcd.print("X= ");
   lcd.setCursor(3, 1);
   lcd.print(value);

}
// =============================================================
// ==      Задача 12. Индикация направления движения          ==
// =============================================================
if(stateNum == 12){
   valueFor12First = analogRead(potDir);          //Read and save analog value from potentiometer
   valueFor12First = map(valueFor12First, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
   delay(200);
   lcd.setCursor(0, 1);
   lcd.print("                  ");
   valueFor12Second = analogRead(potDir);          //Read and save analog value from potentiometer
   valueFor12Second = map(valueFor12Second, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)

   differenceFor12 = valueFor12First-valueFor12Second;
   //Закоментированы строчки которые, крутят мотор в ту сторону которая показана
   //analogWrite(enablePin, 50);
   if(differenceFor12 > 1){
    //digitalWrite(controlPin1, HIGH);
    //digitalWrite(controlPin2, LOW);
    lcd.setCursor(0, 1);
    lcd.print("<<");
   }else if(differenceFor12 < -1){
    //digitalWrite(controlPin1, LOW);
    //digitalWrite(controlPin2, HIGH);
    lcd.setCursor(0, 1);
    lcd.print(">>");
   }else{
    lcd.setCursor(0, 1);
    lcd.print("||");
   }
}
// =============================================================
// ==      Задача 13. Индикация ускорения тележки            ==
// =============================================================
if(stateNum == 13){
   valueFor13First = analogRead(potPin);          //Read and save analog value from potentiometer
   valueFor13First = map(valueFor13First, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
   if(valueFor13First < 5){
    valueFor13First = 0;
   }else if(valueFor13First > 95){
    valueFor13First = 100;
   }
   delay(200);
   lcd.setCursor(0, 1);
   lcd.print("                  ");
   valueFor13Second = analogRead(potPin);          //Read and save analog value from potentiometer
   valueFor13Second = map(valueFor13Second, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
   if(valueFor13Second < 5){
    valueFor13Second = 0;
   }else if(valueFor13Second > 95){
    valueFor13Second = 100;
   }
    analogWrite(enablePin, valueFor13Second);
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
    differenceFor13 = valueFor13First-valueFor13Second;
    if(differenceFor13 > 1){
     lcd.setCursor(0, 1);
     lcd.print("A: Down S: "+String(valueFor13Second));
     //lcd.print(valueFor13Second);
    }else if(differenceFor13 < 0){
     lcd.setCursor(0, 1);
     lcd.print("A: Up S: "+String(valueFor13Second));
    }else{
     lcd.setCursor(0, 1);
     lcd.print("A: 0 S: "+String(valueFor13Second));
    }
}
// =============================================================
// ==      Задача 15. Тестирование подвижной части            ==
// =============================================================
if(stateNum == 14){
  switchStateForLeft = digitalRead(switchPinLeft);
  switchStateForRight = digitalRead(switchPinRight);
  if(errorStateForFifteen != 1){
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(valueFor15First);
   valueFor15First = analogRead(potDir);          //Read and save analog value from potentiometer
   valueFor15First = map(valueFor15First, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
   if(valueFor15First < 8){
    valueFor15First = 0;
   }else if(valueFor15First > 92){
    valueFor15First = 100;
   }
   if(testRightForFifteen != 1){
    //RIGHT || 1 LOW | 2 HIGH
   analogWrite(enablePin, 300);
   digitalWrite(controlPin1, LOW);
   digitalWrite(controlPin2, HIGH);
   if(switchStateForRight == HIGH){
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, LOW);
    if(valueFor15First == 100){
      testRightForFifteen = 1;
    }else{
      lcd.setCursor(0, 1);
      lcd.print("MotionTestError");
      errorStateForFifteen = 1;
      testRightForFifteen = 0;
    }
   }
   }
   
   if(testRightForFifteen == 1){
       analogWrite(enablePin, 300);
       digitalWrite(controlPin1, HIGH);
       digitalWrite(controlPin2, LOW);
       if(switchStateForLeft == HIGH){
        lcd.setCursor(0, 1);
        lcd.print("BtnPressed");
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, LOW);
        if(valueFor15First == 0){

          testLeftForFifteen = 1;
        }else{
          lcd.setCursor(0, 1);
          lcd.print("MotionTestError");
          errorStateForFifteen = 1;
          testLeftForFifteen = 0;
        }
       }
   }
   if(testLeftForFifteen == 1 && testRightForFifteen ==1){
          lcd.setCursor(0, 1);
          lcd.print("MotionTestOk");  
          errorStateForFifteen = 1;
   }
  }
}
// =============================================================
// ==      Задача 16. Тестирование датчиков                   ==
// =============================================================
if(stateNum == 15){
  //int testRightForSixteen = 0;//Переменная для проверки нажатия правой кнопки для задания "Тестирование датчиков"
  //int testLeftForSixteen = 0;//Переменная для проверки нажатия левой кнопки для задания "Тестирование датчиков"
  //int errorStateForSixteen = 0;//Ошибка для задания "Тестирование датчков"
  switchStateForLeft = digitalRead(switchPinLeft);
  switchStateForRight = digitalRead(switchPinRight);
  valueFor16First = analogRead(potDir);          //Read and save analog value from potentiometer
  valueFor16First = map(valueFor16First, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
  if(valueFor16First < 3){
    valueFor16First = 0;
  }else if(valueFor16First > 99){
    valueFor16First = 100;
  }
  if(errorStateForSixteen != 1){
    //RIGHT || 1 LOW | 2 HIGH
   if(testRightForSixteen != 1){
    analogWrite(enablePin, 300);
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(valueFor16First);
    if(valueFor16First < 100 && valueFor16First > 95 && switchStateForRight == HIGH){
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, LOW);
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print("RightButtonOk");
        testRightForSixteen = 1;
        delay(5000);
    }
    if(valueFor16First == 100){
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, LOW);
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print("RightButtonErr"); 
        errorStateForSixteen = 1;
    }
   }
   if(testLeftForSixteen != 1){
    analogWrite(enablePin, 300);
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(valueFor16First);
    if(valueFor16First < 6 && valueFor16First > 0 && switchStateForLeft == HIGH){
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, LOW);
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print("All Done");
        testLeftForSixteen = 1;
        delay(5000);
        errorStateForSixteen = 1;
    }else if(valueFor16First == 0){
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, LOW);
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print("LeftButtonErr"); 
        errorStateForSixteen = 1;
    }
   }
  }else{
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, LOW);
  }

}
// =============================================================
// ==                    Задача 6. Дельта                     ==
// =============================================================
if(stateNum == 16){

    int D = 20;
    int V1 = 50;
    int V2 = 55;
    int valuePotDirSix;
    valuePotDirSix = analogRead(potDir);
    valuePotDirSix = map(valuePotDirSix, 0, 1023, -5.5, 104); //Map value 0-1023 to 0-255 (PWM)
    if(valuePotDirSix < 5){
      valuePotDirSix = 0;
    }else if(valuePotDirSix > 95){
      valuePotDirSix = 100;
    }
    if(progress == 0){
     analogWrite(enablePin,0);
     digitalWrite(controlPin1, LOW);
     digitalWrite(controlPin2, LOW);
    }
    if(valuePotDirSix == 50 && progress !=2 && progress !=3 && progress !=4){
      progress = 1;  
    }
    if(progress == 1){
       analogWrite(enablePin, V1);
       digitalWrite(controlPin1, HIGH);
       digitalWrite(controlPin2, LOW);
       lcd.setCursor(0, 1);
       lcd.print("                ");
       lcd.setCursor(0, 1);
       lcd.print(valuePotDirSix);
       if(valuePotDirSix == 50-D){
          progress = 2;
       }
    }
    if(progress == 2){
       analogWrite(enablePin, V2);
       digitalWrite(controlPin1, LOW);
       digitalWrite(controlPin2, HIGH);
       lcd.setCursor(0, 1);
       lcd.print("                ");
       lcd.setCursor(0, 1);
       lcd.print(valuePotDirSix);
       if(valuePotDirSix == 50+D){
          progress = 3;
       }
    }
    if(progress == 3){
       analogWrite(enablePin, V1);
       digitalWrite(controlPin1, HIGH);
       digitalWrite(controlPin2, LOW);
       lcd.setCursor(0, 1);
       lcd.print("                ");
       lcd.setCursor(0, 1);
       lcd.print(valuePotDirSix);
       if(valuePotDirSix == 50){
          progress = 4;
       }
    }
    if(progress == 4){
     analogWrite(enablePin,0);
     digitalWrite(controlPin1, LOW);
     digitalWrite(controlPin2, LOW);
     lcd.setCursor(0, 1);
     lcd.print("                ");
     lcd.setCursor(0, 1);
     lcd.print(valuePotDirSix);
    }
    
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(valuePotDirSix);    


}
// =============================================================
// ==                        MAIN MENU                        ==
// =============================================================
if(stateNum == 0){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:Off");
  lcd.setCursor(0, 1);
  lcd.print("                ");
 }else if(stateNum == 1){
  lcd.setCursor(0, 0);
  //lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:MoveToTheEdge");
  lcd.setCursor(0, 1);
  //lcd.print("                ");
 }else if(stateNum == 2){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:FromEdgeToEdge");
  lcd.setCursor(0, 1);
  //lcd.print("                ");
 }else if(stateNum == 3){
    lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:PingPong");
  lcd.setCursor(0, 1);
  lcd.print("");
 }else if(stateNum == 4){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:ToNearestEdge");
  //lcd.setCursor(0, 1);
  //lcd.print("                ");
 }else if(stateNum == 5){
   lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:Aligment");
  //lcd.setCursor(0, 1);
  //lcd.print("                ");
 }else if(stateNum == 7){
  lcd.setCursor(0, 0);
  lcd.print("R:Acceleration");
  //lcd.setCursor(0, 1);
  //lcd.print("                ");  
 }else if(stateNum == 8){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:Breaking");
  lcd.setCursor(0, 1);
  //lcd.print("                ");
 }else if(stateNum == 9){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:VariableMovement");
  lcd.setCursor(0, 1);
  //lcd.print("                ");
 }else if(stateNum == 10){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:SpeedIndication");
  //lcd.setCursor(0, 1);
  //lcd.print("");  
 }else if(stateNum == 11){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:TrollPosition");
  lcd.setCursor(0, 1);
  //lcd.print("");
 }else if(stateNum == 12){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:MoveDirection");
  //lcd.setCursor(0, 1);
  //lcd.print("                ");
 }else if(stateNum == 13){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:IndAccel/tion");
  lcd.setCursor(0, 1);
 // lcd.print("                ");
 }else if(stateNum == 14){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:MovementTest");
  lcd.setCursor(0, 1);
  //lcd.print("                ");
 }else if(stateNum == 15){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:SensorTest");
  lcd.setCursor(0, 1);
  //lcd.print("                ");
 }else if(stateNum == 16){
   lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:Delta");
  lcd.setCursor(0, 1);
  //lcd.print("                ");
 }else{
 
 }
 
//  lcd.setCursor(0, 1);
//  lcd.print("          ");
//    lcd.setCursor(3, 0);
//  lcd.print("   ");
//  lcd.setCursor(0, 1);
//  // print the number of seconds since reset:
// // lcd.print(millis() / 1000);
//  lcd.print(motorSpeed);
//  lcd.setCursor(0, 0);
//  lcd.print("R:");
//  lcd.setCursor(3, 0);
//  lcd.print(stateNum);
  delay(100);
}
