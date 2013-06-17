#include <SoftwareSerial.h>
#include <serLCD.h>

serLCD lcd(SERIAL_LCD_PIN);

void setupLCD() {
  lcd.setCursor(1, 1);
  lcd.print("Temp:    ---.-");
  lcd.write(0xDF); // degree symbol
  lcd.print(fahrenheit ? "F" : "C");
  lcd.print("Compressor: ----");
}

void updateLCD() {
  if (temp == -1000) {
    lcd.setCursor(1, 10);
    lcd.print("---.-");
  } else {
    int pos;
    if (temp >= 100.0 || temp <= -10.0) {
      pos = 10;
    } else if (temp >= 10.0 || temp < 0.0) {
      pos = 11;
    } else {
      pos = 12;
    }
    lcd.setCursor(1, 10);
    lcd.print("     ");
    lcd.setCursor(1, pos);
    lcd.print(temp, 1); // 1 decimal place
  }

  lcd.setCursor(2, 13);
  lcd.write(compressor ? "  ON" : (compressorDelayed ? "WAIT" : " OFF"));
}
