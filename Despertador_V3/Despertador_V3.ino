/*
 * Rafael Lozano Rolon
 * soporte@taloselectronics.com
*/
#include <Keypad.h>
#include <RTClib.h>
#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>

RTC_DS3231 RTC;
LiquidCrystal_I2C lcd(0x27, 20, 4);

const byte buzzer = A3;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

char keys[ROWS][COLS] = {
  {1, 2, 3},
  {4, 5, 6},
  {7, 8, 9},
  {'*', 'z', '#'}
};

byte icono_alarma[] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B00000,
  B00100,
  B00000
};

byte rowPins[ROWS] = {7, 2, 3, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 8, 4}; //connect to the column pinouts of the keypad

int date_hour = 5;
int date_min = 50;
bool alarm = true;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, icono_alarma);

  Wire.begin();
  RTC.begin();
  RTC.setAlarm1Simple(date_hour, date_min);

  digitalWrite(buzzer, HIGH);
  //RTC.adjust(DateTime(__DATE__, __TIME__));

  pinMode(buzzer, OUTPUT);
}

void loop() {
  DateTime now = RTC.now();
  char key = keypad.getKey();
  lcd.setCursor(5, 0);
  lcd.print("Bienvenido");
  Time(now);
  switch (key)
  {
    case '#':
      alarm = !alarm;
      if (alarm) {
        Serial.println("Alarma activada");
        RTC.turnOnAlarm(1);
        digitalWrite(buzzer, LOW);
        delay(100);
        digitalWrite(buzzer, HIGH);
      }
      else {
        Serial.println("Alarma desactivada");
        RTC.turnOnAlarm(0);
      }
      break;

    case '*':
      Serial.println("Configurando alarma");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" Configurar alarma");

      lcd.setCursor(0, 2);
      lcd.print(date_hour);
      lcd.print(":");
      lcd.print(date_min);

      update_alarma();

      break;
  }
  if (RTC.checkIfAlarm(1)) {
    Serial.println("Alarm Triggered");
    alarma_on();
    lcd.backlight();
  }
}
void update_alarma()
{
  char key = keypad.getKey();
  int digito = 0;
  lcd.setCursor(0, 1);
  lcd.blink();

  //Configurar horas
  key = keypad.waitForKey();
  date_hour = int(key) * 10;
  lcd.print(int(key));

  key = keypad.waitForKey();
  if (key == '*')
  {
    date_hour = date_hour / 10;
    lcd.print(":");
  }
  else if (key == 'z')
  {
    lcd.print(0);
    lcd.print(":");
  }
  else
  {
    date_hour = date_hour + int(key);
    lcd.print(int(key));
    lcd.print(":");
  }

  //configurar minutos
  key = keypad.waitForKey();
  if (key == 'z')
  {
    lcd.print(0);
    lcd.print(":");
  }
  else
  {
    date_min = int(key) * 10;
    lcd.print(int(key));
  }


  key = keypad.waitForKey();

  if (key == '*')
  {
    date_min = date_min / 10;
  }
  else if (key == 'z')
  {
    lcd.print(0);

  }
  else
  {
    date_min = date_min + int(key);
    lcd.print(int(key));
  }
  RTC.setAlarm1Simple(date_hour, date_min);
  RTC.turnOnAlarm(1);


  lcd.noBlink();
  delay(500);
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Guardado!");
  delay(500);
  lcd.clear();

}
void alarma_on()
{
  char Tecla;
  while (1)
  {
    lcd.backlight();
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    lcd.noBacklight();
    Tecla = keypad.getKey();
    if (Tecla != NO_KEY)
    {
      digitalWrite(buzzer, HIGH);
      return 0;
    }
  }
}

void Time(DateTime now)
{
  String date = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());
  String Time = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + " ";
  String AL = String(date_hour) + ":" + String(date_min);
  lcd.setCursor(0, 2);
  lcd.print(Time);
  lcd.setCursor(0, 3);
  lcd.print(date);
  lcd.setCursor(11, 2);
  lcd.print("A1=");
  lcd.print(AL);
  if (alarm)
  {
    lcd.setCursor(19, 2);
    lcd.write(0);
  }
  else {
    lcd.setCursor(19, 2);
    lcd.print(" ");
  }

}
