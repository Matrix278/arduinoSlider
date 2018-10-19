// =============================================================
// ==                   ОПРЕДЕЛЕНИЕ ПЕРЕМЕННЫХ                ==
// =============================================================
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 8, d5 = 6, d6 = 5, d7 = 1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int enablePin=10;
const int controlPin1=2;
const int controlPin2=9;
const int potPin=A0;
const int potDir=A1;
int RC1;
int switchStateForLeft = 0;
int switchStateForRight = 0;
const int switchPinLeft = 4;
const int switchPinRight = 13;
int motorSpeed=0;
int motorDirection=1;
int motorEnabled = 1;
int stateNum = 0;
int stateButtonAction = 0;
const int stateButton1 = 3;
int Direction = 0;
int stopper = 0;
int stopperFour = 0;
int stopperFive = 0;
int differenceFor12;
int differenceFor13;
int value;
int valueFor9First;
int valueFor12First;
int valueFor12Second;
int valueFor13First;
int valueFor13Second;
int valueFor15First;
int valueFor16First;
int stopperSecond;
int stopperForSecond = 0;
int stopperSeventh = 0;
int stopperEight = 0;
int stopperForFifth = 0;
int fatalStopperForFifth = 0;
int errorStateForFifteen = 0;
float speedValueSeventh = 50;
float speedValueEight = 120;
int stopperForSixth = 0;
int testRightForFifteen = 0;
int testLeftForFifteen = 0;
int testRightForSixteen = 0;
int testLeftForSixteen = 0;
int errorStateForSixteen = 0;
int progress = 0;
// =============================================================
// ==                         НАСТРОЙКА                       ==
// =============================================================
void setup() {
  pinMode(potDir, INPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(stateButton1, INPUT);  
  digitalWrite(enablePin,HIGH);
  lcd.begin(16, 2);
  digitalWrite(controlPin1, LOW);
  digitalWrite(controlPin2, LOW);
  analogWrite(enablePin,0);
}
// =============================================================
// ==                     ОСНОВНОЙ ЦИКЛ                       ==
// =============================================================
void loop() {
// =============================================================
// ==                 ПЕРЕКЛЮЧЕНИЕ РЕЖИМОВ (МЕНЮ)             ==
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
  analogWrite(enablePin,0);
  digitalWrite(controlPin1, LOW);
  digitalWrite(controlPin2, LOW);
}
// =============================================================
// ==                 Задача 1.  Движение к краю              ==
// =============================================================
if(stateNum == 1){
  int controlPin1Side;
  int controlPin2Side;
  int direction = 1;
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
    value = map(400, 0, 500, 0, 104);
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
  valuePotPin = map(valuePotPin, 0, 1023, -5.5, 104);
  valuePotDir = analogRead(potDir);
  valuePotDir = map(valuePotDir, 0, 1023, -5.5, 104);
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
  valuePotPin = map(valuePotPin, 0, 1023, -5.5, 104);
  valuePotDir = analogRead(potDir);
  valuePotDir = map(valuePotDir, 0, 1023, -5.5, 104);
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
  valuePotPin = map(valuePotPin, 0, 1023, -5.5, 104);
  valuePotDir = analogRead(potDir);
  valuePotDir = map(valuePotDir, 0, 1023, -5.5, 104);
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
    valuePotPinFive = map(valuePotPinFive, 0, 1023, -5.5, 104);
    valuePotDirFive = analogRead(potDir);
    valuePotDirFive = map(valuePotDirFive, 0, 1023, -5.5, 104);
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
  valuePotDirForSeventh = analogRead(potDir);
  valuePotDirForSeventh = map(valuePotDirForSeventh, 0, 1023, -5.5, 104);
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
  valuePotDirForEight = analogRead(potDir);
  valuePotDirForEight = map(valuePotDirForEight, 0, 1023, -5.5, 104);
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
  RC1 = map(RC1, 0, 1023, -104, 104);
  valueFor9First = analogRead(potPin);
  valueFor9First = map(valueFor9First, 0, 1023, -5.5, 104);
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
  if(RC1 >= -5 && RC1 <= 5){
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, LOW);
  }else if(RC1 < -6){
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
  }else if(RC1 > 6){
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
   motorSpeed = map(motorSpeed, 0, 1023, -5.5, 104);
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
   value = analogRead(potDir);
   value = map(value, 0, 1023, -5.5, 104);
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
   valueFor12First = analogRead(potDir);
   valueFor12First = map(valueFor12First, 0, 1023, -5.5, 104);
   delay(200);
   lcd.setCursor(0, 1);
   lcd.print("                  ");
   valueFor12Second = analogRead(potDir);
   valueFor12Second = map(valueFor12Second, 0, 1023, -5.5, 104);
   differenceFor12 = valueFor12First-valueFor12Second;
   if(differenceFor12 > 1){
    lcd.setCursor(0, 1);
    lcd.print("<<");
   }else if(differenceFor12 < -1){
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
   valueFor13First = analogRead(potPin);
   valueFor13First = map(valueFor13First, 0, 1023, -5.5, 104);
   if(valueFor13First < 5){
    valueFor13First = 0;
   }else if(valueFor13First > 95){
    valueFor13First = 100;
   }
   delay(200);
   lcd.setCursor(0, 1);
   lcd.print("                  ");
   valueFor13Second = analogRead(potPin);
   valueFor13Second = map(valueFor13Second, 0, 1023, -5.5, 104);
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
   valueFor15First = analogRead(potDir);
   valueFor15First = map(valueFor15First, 0, 1023, -5.5, 104);
    valueFor15First = 0;
   }else if(valueFor15First > 92){
    valueFor15First = 100;
   }
   if(testRightForFifteen != 1){
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
  switchStateForLeft = digitalRead(switchPinLeft);
  switchStateForRight = digitalRead(switchPinRight);
  valueFor16First = analogRead(potDir);
  valueFor16First = map(valueFor16First, 0, 1023, -5.5, 104);
  if(valueFor16First < 3){
    valueFor16First = 0;
  }else if(valueFor16First > 99){
    valueFor16First = 100;
  }
  if(errorStateForSixteen != 1){
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
    valuePotDirSix = map(valuePotDirSix, 0, 1023, -5.5, 104);
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
// ==                        ГЛАВНОЕ МЕНЮ                     ==
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
  lcd.setCursor(0, 0);
  lcd.print("R:MoveToTheEdge");
  lcd.setCursor(0, 1);
 }else if(stateNum == 2){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:FromEdgeToEdge");
  lcd.setCursor(0, 1);
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
 }else if(stateNum == 5){
   lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:Aligment");
 }else if(stateNum == 7){
  lcd.setCursor(0, 0);
  lcd.print("R:Acceleration"); 
 }else if(stateNum == 8){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:Breaking");
  lcd.setCursor(0, 1);
 }else if(stateNum == 9){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:VariableMovement");
  lcd.setCursor(0, 1);
 }else if(stateNum == 10){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:SpeedIndication");
 }else if(stateNum == 11){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:TrollPosition");
  lcd.setCursor(0, 1);
 }else if(stateNum == 12){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:MoveDirection");
 }else if(stateNum == 13){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:IndAccel/tion");
  lcd.setCursor(0, 1);
 }else if(stateNum == 14){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:MovementTest");
  lcd.setCursor(0, 1);
 }else if(stateNum == 15){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:SensorTest");
  lcd.setCursor(0, 1);
 }else if(stateNum == 16){
   lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("R:Delta");
  lcd.setCursor(0, 1);
 }else{
 
 }
  delay(100);
}
