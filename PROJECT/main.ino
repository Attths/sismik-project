#include <LiquidCrystal_I2C.h>

const int   PIN_SENSOR     = A0;
const int   PIN_LED_HIJAU  = 8;
const int   PIN_LED_KUNING = 9;
const int   PIN_LED_MERAH  = 10;
const float BATAS_DINGIN   = 25.0;
const float BATAS_PANAS    = 30.0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

float bacaSuhu() {
  float tegangan = analogRead(PIN_SENSOR) * (5.0 / 1023.0);
  return (tegangan - 0.5) * 100.0;
}

const char* tentukanKategori(float suhu) {
  if (suhu < BATAS_DINGIN)  return "Dingin ";
  if (suhu <= BATAS_PANAS)  return "Normal ";
  return "Panas!  ";
}

void aturLED(float suhu) {
  digitalWrite(PIN_LED_HIJAU,  suhu < BATAS_DINGIN                          ? HIGH : LOW);
  digitalWrite(PIN_LED_KUNING, suhu >= BATAS_DINGIN && suhu <= BATAS_PANAS   ? HIGH : LOW);
  digitalWrite(PIN_LED_MERAH,  suhu > BATAS_PANAS                            ? HIGH : LOW);
}

void tampilLCD(float suhu, const char* kategori) {
  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(suhu, 1);
  lcd.print("C   ");
  lcd.setCursor(0, 1);
  lcd.print("Status: ");
  lcd.print(kategori);
}

void kirimSerial(float suhu, const char* kategori) {
  Serial.print("Suhu: ");
  Serial.print(suhu, 1);
  Serial.print(" C | Status: ");
  Serial.println(kategori);
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED_HIJAU,  OUTPUT);
  pinMode(PIN_LED_KUNING, OUTPUT);
  pinMode(PIN_LED_MERAH,  OUTPUT);
  digitalWrite(PIN_LED_HIJAU,  LOW);
  digitalWrite(PIN_LED_KUNING, LOW);
  digitalWrite(PIN_LED_MERAH,  LOW);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Monitoring Suhu");
  lcd.setCursor(0, 1);
  lcd.print("Sistem Aktif...");
  delay(1500);
  lcd.clear();
}

void loop() {
  float       suhu     = bacaSuhu();
  const char* kategori = tentukanKategori(suhu);
  aturLED(suhu);
  tampilLCD(suhu, kategori);
  kirimSerial(suhu, kategori);
}
