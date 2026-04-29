# Tugas Project Sistem Mikrokontroler

### Wiring diagram dan Skematic View

<img width="591" height="426" alt="image" src="https://github.com/user-attachments/assets/25df3e4b-44a5-4639-a274-046b01c0e3a5" />
<img width="839" height="647" alt="image" src="https://github.com/user-attachments/assets/91f2afe3-c25a-40a9-9ed9-70aefd0ab112" />

## ##Kode Lengkapnya

```cpp
#include <LiquidCrystal_I2C.h>

//Inisialisasi semua pin yang masuk
const int   PIN_SENSOR     = A0;
const int   PIN_LED_HIJAU  = 8;
const int   PIN_LED_KUNING = 9;
const int   PIN_LED_MERAH  = 10;
const float BATAS_DINGIN   = 25.0;
const float BATAS_PANAS    = 30.0;

//Inisialisasi tipe LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//fungsi untuk rumus untuk menghitung suhu dalam bentuk celcius sekaligus membaca analog dari TMP
float bacaSuhu() {
  float tegangan = analogRead(PIN_SENSOR) * (5.0 / 1023.0);
  return (tegangan - 0.5) * 100.0;
}

//Aturan percabangan untuk suhunya
const char* tentukanKategori(float suhu) {
  if (suhu < BATAS_DINGIN)  return "Dingin ";
  if (suhu <= BATAS_PANAS)  return "Normal ";
  return "Panas!  ";
}

//Untuk menyalakan LED Berdasarkan aturan percabangan yang telah dibuat di atas
void aturLED(float suhu) {
  digitalWrite(PIN_LED_HIJAU,  suhu < BATAS_DINGIN                          ? HIGH : LOW);
  digitalWrite(PIN_LED_KUNING, suhu >= BATAS_DINGIN && suhu <= BATAS_PANAS   ? HIGH : LOW);
  digitalWrite(PIN_LED_MERAH,  suhu > BATAS_PANAS                            ? HIGH : LOW);
}

// Fungsi untuk menampilkan informasi suhu dan status ke layar LCD fisik
void tampilLCD(float suhu, const char* kategori) {
  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(suhu, 1);
  lcd.print("C   ");
  lcd.setCursor(0, 1);
  lcd.print("Status: ");
  lcd.print(kategori);
}

// Fungsi untuk mengirim data suhu ke Serial Monitor untuk keperluan debugging/monitoring di PC
void kirimSerial(float suhu, const char* kategori) {
  Serial.print("Suhu: ");
  Serial.print(suhu, 1);
  Serial.print(" C | Status: ");
  Serial.println(kategori);
}

//Setup semua untuk digunakan
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

//Loop Utama
void loop() {
  float       suhu     = bacaSuhu(); //mengatur suhu melalui TMP
  const char* kategori = tentukanKategori(suhu); //menilai suhu masuk dalam kategori yang mana
  aturLED(suhu); //nyalain LED sesuai dengan keadaan suhu
  tampilLCD(suhu, kategori); //tampilkan statusnya melalui LCD
  kirimSerial(suhu, kategori); //mengirimkan perubahan suhu ke dalam serial monitor
}
```
