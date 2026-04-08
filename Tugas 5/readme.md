# Source Code
```cpp
const int ledMerahKendaraan = 8;
const int ledKuningKendaraan = 9;
const int ledHijauKendaraan = 10;

const int ledMerahPed = 6;
const int ledHijauPed = 7;

const int tombol = 2;

volatile bool tombolDitekan = false;

// ISR (Interrupt Service Routine)
void tekanTombol() {
  tombolDitekan = true;
}

void setup() {
  pinMode(ledMerahKendaraan, OUTPUT);
  pinMode(ledKuningKendaraan, OUTPUT);
  pinMode(ledHijauKendaraan, OUTPUT);

  pinMode(ledMerahPed, OUTPUT);
  pinMode(ledHijauPed, OUTPUT);

  pinMode(tombol, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(tombol), tekanTombol, FALLING);

  // Kondisi awal
  digitalWrite(ledHijauKendaraan, HIGH);
  digitalWrite(ledMerahPed, HIGH);
}

void loop() {

  if (tombolDitekan) {
    tombolDitekan = false;

    // 1. Kendaraan merah, pedestrian hijau
    digitalWrite(ledHijauKendaraan, LOW);
    digitalWrite(ledMerahKendaraan, HIGH);

    digitalWrite(ledMerahPed, LOW);
    digitalWrite(ledHijauPed, HIGH);

    delay(5000); // waktu nyebrang

    // 2. Pedestrian merah lagi
    digitalWrite(ledHijauPed, LOW);
    digitalWrite(ledMerahPed, HIGH);

    // Kendaraan kuning
    digitalWrite(ledMerahKendaraan, LOW);
    digitalWrite(ledKuningKendaraan, HIGH);

    delay(2000); // transisi

    // 3. Kembali ke awal
    digitalWrite(ledKuningKendaraan, LOW);
    digitalWrite(ledHijauKendaraan, HIGH);
  }
}

```
## Penjelasan singkat
Program ini menggunakan interrupt untuk mendeteksi tombol pedestrian.
Ketika tombol ditekan, sistem langsung merespons tanpa menunggu loop selesai.

Alur kerjanya:

Awalnya kendaraan hijau, pedestrian merah
Saat tombol ditekan → interrupt aktif
Kendaraan berhenti (merah), pedestrian jalan (hijau)
Setelah beberapa detik → pedestrian berhenti
Kendaraan masuk fase kuning lalu kembali hijau

Dengan interrupt, sistem jadi lebih responsif dibanding polling biasa
