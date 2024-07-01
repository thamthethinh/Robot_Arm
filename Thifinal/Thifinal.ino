#include <Servo.h>
#include <EEPROM.h>

const int joyX1 = A0;
const int joyY1 = A2;
const int joyX2 = A1;
const int joyY2 = A3;
//const int nutPin = 2;
const int servoPin1 = 8; 
const int servoPin2 = 9;
const int servoPin3 = 10;
const int servoPin4 = 11; 
const int saveButtonPin = 3;  // Nút để lưu góc servo
const int returnButtonPin = 4; // Nút để quay về góc đã lưu
const int selectSaveSlotPin = 5; // Nút để chuyển đổi giữa các bộ góc lưu trữ

//int solandem = 0;
int saveSlot = 1; // Biến để chọn bộ góc lưu trữ
Servo myServo1;  
Servo myServo2;
Servo myServo3;
Servo myServo4;

unsigned long previousMillis1 = 0;  
unsigned long previousMillis2 = 0;  
unsigned long previousMillis3 = 0;  
unsigned long previousMillis4 = 0;  
int currentServo1 = 90; 
int currentServo2 = 90;
int currentServo3 = 90;
int currentServo4 = 90;

void setup() {
  pinMode(joyX1, INPUT);
  pinMode(joyY1, INPUT);
  pinMode(joyX2, INPUT);
  pinMode(joyY2, INPUT);
  pinMode(saveButtonPin, INPUT_PULLUP);
  pinMode(returnButtonPin, INPUT_PULLUP);
  pinMode(selectSaveSlotPin, INPUT_PULLUP);

  myServo1.attach(servoPin1);
  myServo2.attach(servoPin2);
  myServo3.attach(servoPin3);
  myServo4.attach(servoPin4);  
  myServo1.write(currentServo1); 
  myServo2.write(currentServo2);
  myServo3.write(currentServo3); 
  myServo4.write(currentServo4);  
  Serial.begin(9600); 
}

void loop() {
  int gtJoyX1 = analogRead(joyX1);
  int gtJoyY1 = analogRead(joyY1);
  int gtJoyX2 = analogRead(joyX2);
  int gtJoyY2 = analogRead(joyY2);
  int interval1 = map(gtJoyX1, 0, 1023, 10, 20);
  int interval2 = map(gtJoyY1, 0, 1023, 10, 20);
  int interval3 = map(gtJoyX2, 0, 1023, 10, 20);
  int interval4 = map(gtJoyY2, 0, 1023, 10, 20);
  unsigned long currentMillis1 = millis();
  unsigned long currentMillis2 = millis();
  unsigned long currentMillis3 = millis();
  unsigned long currentMillis4 = millis();
  //int trangthainut = digitalRead(nutpin);
  int saveButtonState = digitalRead(saveButtonPin);
  int returnButtonState = digitalRead(returnButtonPin);
  int selectSaveSlotState = digitalRead(selectSaveSlotPin);
  /*if (trangthainut == HIGH) { 
    delay(200);
    trangthainut = digitalRead(nutPin);
    if(trangthainut == LOW) {
      solandem++;
      Serial.print("so lan dem: ");
      Serial.println(solandem);
      if (solandem >= 5) {
        solandem = 1;*/
      //}
    //}
  //}

  // Kiểm tra nút chuyển đổi giữa các bộ góc lưu trữ
  if (selectSaveSlotState == LOW) {
    delay(200); // delay khử nhiễu
    if (digitalRead(selectSaveSlotPin) == LOW) {
      saveSlot = (saveSlot % 3) + 1; // Chuyển đổi giữa 1, 2, và 3
      Serial.print("Selected save slot: ");
      Serial.println(saveSlot);
    }
  }

  // Kiểm tra nút lưu góc servo
  if (saveButtonState == LOW) {
    delay(200); // delay khử nhiễu
    if (digitalRead(saveButtonPin) == LOW) {
      saveServoAngles(saveSlot);
    }
  }

  // Kiểm tra nút quay lại góc đã lưu
  if (returnButtonState == LOW) {
    delay(200); // delay khử nhiễu
    if (digitalRead(returnButtonPin) == LOW) {
      returnToSavedAngles(saveSlot);
    }
  }

  // Điều khiển servo 1 với trục X của joystick 1
  if (gtJoyX1 < 492) {
    if (currentMillis1 - previousMillis1 >= interval1) {
      previousMillis1 = currentMillis1;
      if (currentServo1 > 0) {  
        currentServo1--;
        myServo1.write(currentServo1); 
        Serial.print(" gtJoyX1: ");
        Serial.print(gtJoyX1);
        Serial.print(" Goc Servo1: ");
        Serial.println(currentServo1);
      }
    }
  } else if (gtJoyX1 > 542) {
    if (currentMillis1 - previousMillis1 >= interval1) {
      previousMillis1 = currentMillis1;
      if (currentServo1 < 180) {  
        currentServo1++;
        myServo1.write(currentServo1);
        Serial.print(" gtJoyX1: ");
        Serial.println(gtJoyX1);
        Serial.print(" Goc Servo1: ");
        Serial.println(currentServo1);
      }
    }
  }

  // Điều khiển servo 2 với trục Y của joystick 1
  if (gtJoyY1 < 492) {
    if (currentMillis2 - previousMillis2 >= interval2) {
      previousMillis2 = currentMillis2;
      if (currentServo2 > 0) {  
        currentServo2--;
        myServo2.write(currentServo2); 
        Serial.print(" gtJoyY1: ");
        Serial.print(gtJoyY1);
        Serial.print(" Goc Servo2: ");
        Serial.println(currentServo2);
      }
    }
  } else if (gtJoyY1 > 542) {
    if (currentMillis2 - previousMillis2 >= interval2) {
      previousMillis2 = currentMillis2;
      if (currentServo2 < 180) {  
        currentServo2++;
        myServo2.write(currentServo2);
        Serial.print(" gtJoyY1: ");
        Serial.println(gtJoyY1);
        Serial.print(" Goc Servo2: ");
        Serial.println(currentServo2);
      }
    }
  }

  // Điều khiển servo 3 với trục X của joystick 2
  if (gtJoyX2 < 492) {
    if (currentMillis3 - previousMillis3 >= interval3) {
      previousMillis3 = currentMillis3;
      if (currentServo3 > 0) {  
        currentServo3--;
        myServo3.write(currentServo3); 
        Serial.print(" gtJoyX2: ");
        Serial.print(gtJoyX2);
        Serial.print(" Goc Servo3: ");
        Serial.println(currentServo3);
      }
    }
  } else if (gtJoyX2 > 542) {
    if (currentMillis3 - previousMillis3 >= interval3) {
      previousMillis3 = currentMillis3;
      if (currentServo3 < 180) {  
        currentServo3++;
        myServo3.write(currentServo3);
        Serial.print(" gtJoyX2: ");
        Serial.println(gtJoyX2);
        Serial.print(" Goc Servo3: ");
        Serial.println(currentServo3);
      }
    }
  }

  // Điều khiển servo 4 với trục Y của joystick 2
  if (gtJoyY2 < 492) {
    if (currentMillis4 - previousMillis4 >= interval4) {
      previousMillis4 = currentMillis4;
      if (currentServo4 > 0) {  
        currentServo4--;
        myServo4.write(currentServo4); 
        Serial.print(" gtJoyY2: ");
        Serial.print(gtJoyY2);
        Serial.print(" Goc Servo4: ");
        Serial.println(currentServo4);
      }
    }
  } else if (gtJoyY2 > 542) {
    if (currentMillis4 - previousMillis4 >= interval4) {
      previousMillis4 = currentMillis4;
      if (currentServo4 < 180) {  
        currentServo4++;
        myServo4.write(currentServo4);
        Serial.print(" gtJoyY2: ");
        Serial.println(gtJoyY2);
        Serial.print(" Goc Servo4: ");
        Serial.println(currentServo4);
      }
    }
  }
}

void saveServoAngles(int slot) {
  int addr = (slot - 1) * 4; // Tính địa chỉ bắt đầu cho slot
  EEPROM.write(addr, currentServo1);
  EEPROM.write(addr + 1, currentServo2);
  EEPROM.write(addr + 2, currentServo3);
  EEPROM.write(addr + 3, currentServo4);
  Serial.print("goc Servo duoc luu trong EEPROM:  ");
  Serial.println(slot);
}

void returnToSavedAngles(int slot) {
  int addr = (slot - 1) * 4; // Tính địa chỉ bắt đầu cho slot
  currentServo1 = EEPROM.read(addr);
  currentServo2 = EEPROM.read(addr + 1);
  currentServo3 = EEPROM.read(addr + 2);
  currentServo4 = EEPROM.read(addr + 3);
  myServo1.write(currentServo1);
  myServo2.write(currentServo2);
  myServo3.write(currentServo3);
  myServo4.write(currentServo4);

  Serial.print("góc Servo quay trở về góc :  ");
  Serial.println(slot);
}
  

