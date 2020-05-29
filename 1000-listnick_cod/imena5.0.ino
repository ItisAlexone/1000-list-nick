#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);
/*uidCard1[4] = {0x20, 0x58, 0x5D, 0x9C};
  uidCard2[4] = {0x4D, 0xD6, 0x5A, 0xC4};*/
#define card1 0x20
#define card2 0x4D
int newCard[4]={0x00, 0x00, 0x00, 0x00};

void setup() {
  lcd.backlight();
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  Serial.println("Готово к использованию!");
  lcd.setCursor(0, 0);
  lcd.print("Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  for (int i = 0; i < 1; i++) {
    newCard[i] = mfrc522.uid.uidByte[i];
    switch (newCard[i]) {
      case card1:
        Serial.println("Иванов Иван");
        lcd.setCursor(0, 0);
        lcd.print("Ivanov");
        lcd.setCursor(0, 1);
        lcd.print("Ivan");
        digitalWrite(8, HIGH);
        delay (2000);
        digitalWrite(8, LOW);
        lcd.clear();
        break;

      case card2:
        Serial.println("Смирнова Виктория");
        lcd.setCursor(0, 0);
        lcd.print("Smirnova");
        lcd.setCursor(0, 1);
        lcd.print("Viktoriy");
        digitalWrite(8, HIGH);
        delay (2000);
        digitalWrite(8, LOW);
        lcd.clear();
        break;
      default:
        Serial.println("Неизвестная карта");
        lcd.setCursor(0, 0);
        lcd.print("Unknow Card");
        digitalWrite(7, HIGH);
        delay(2000);
        digitalWrite(7, LOW);
        lcd.clear();
        break;
    }
  }
}
