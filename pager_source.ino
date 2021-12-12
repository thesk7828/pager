// include the library code:
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9

int n=1;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(7,6,5,4,3,2);

void setup() {
  Serial.begin(9600);   // Initiate a Serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();
  lcd.setCursor(0,0);
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  lcd.print("wave the credential");
}

void loop() {
if(n%16==0)
lcd.setCursor(0,1);
if (Serial.available())
  {
   // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent()) 
  {
    if ( mfrc522.PICC_ReadCardSerial())
      {
      //Checking for valid RFID Tag
      if (mfrc522.uid.uidByte[0] == 0x8E && mfrc522.uid.uidByte[1] == 0x56 && mfrc522.uid.uidByte[2] == 0xAA && mfrc522.uid.uidByte[3] == 0x59)//you can paste your own RFID Number
      {
        char ch=Serial.read();
        lcd.print(ch);
        n=n+1;
        delay(1000);
      }
     else if (mfrc522.uid.uidByte[0] == 0x16 && mfrc522.uid.uidByte[1] == 0x55 && mfrc522.uid.uidByte[2] == 0x3B && mfrc522.uid.uidByte[3] == 0xD9)
      {
        char ch=Serial.read();
        lcd.print(ch);
        n=n+1;
        delay(1000);
      }
     else if (mfrc522.uid.uidByte[0] == 0x04 && mfrc522.uid.uidByte[1] == 0xDD && mfrc522.uid.uidByte[2] == 0xF7 && mfrc522.uid.uidByte[3] == 0xC1 && mfrc522.uid.uidByte[4] == 0xE0 && mfrc522.uid.uidByte[5] == 0x02 && mfrc522.uid.uidByte[6] == 0x80)
      {
        char ch=Serial.read();
        lcd.print(ch);
        n=n+1;
        delay(1000);
      }
     else
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Unknown ID");
        lcd.setCursor(0,1);
        lcd.print("wave again!");
        delay(1000);
      }
    }
  }
 }
}
