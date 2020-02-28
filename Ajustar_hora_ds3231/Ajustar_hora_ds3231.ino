//Ajustar fecha y hora con la hora en la que se subio el programa.
#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>

RTC_DS3231 RTC;

void setup () {
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  //Comentar linea una vez que la hora y la fecha sean las correctas, luego subir el programa de nuevo
  RTC.adjust(DateTime(__DATE__, __TIME__));

}

void loop () {
  DateTime now = RTC.now();
  print_date(now);
  delay(1000);

}
void print_date(DateTime now)
{
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}
