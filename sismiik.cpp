// Definisi Pin
int lampu[4][3] = {
  {13, 12, 11}, // Utara: Hijau, Kuning, Merah
  {10, 9, 8},   // Timur: Hijau, Kuning, Merah
  {7, 6, 5},    // Selatan: Hijau, Kuning, Merah
  {4, 3, 2}     // Barat: Hijau, Kuning, Merah
};

void setup() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      pinMode(lampu[i][j], OUTPUT);
    }
  }
  semuaMerah(); // Kondisi default
}

void loop() {
  // Urutan: Utara -> Timur -> Selatan -> Barat
  for (int i = 0; i < 4; i++) {
    aktifkanSimpang(i);
  }
}

// Fungsi Kondisi Default: Semua Merah
void semuaMerah() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(lampu[i][0], LOW);  // Hijau mati
    digitalWrite(lampu[i][1], LOW);  // Kuning mati
    digitalWrite(lampu[i][2], HIGH); // Merah nyala
  }
}

// Fungsi Modular untuk mengaktifkan satu sisi
void aktifkanSimpang(int index) {
  // 1. Hijau Nyala (Sisi ini hijau, yang lain tetap merah)
  digitalWrite(lampu[index][2], LOW);  // Merah sisi ini mati
  digitalWrite(lampu[index][0], HIGH); // Hijau sisi ini nyala
  delay(5000); 

  // 2. Kuning Berkedip 3 kali (Durasi total 2 detik)
  digitalWrite(lampu[index][0], LOW);  // Hijau mati
  for (int k = 0; k < 3; k++) {
    digitalWrite(lampu[index][1], HIGH); // Kuning nyala
    delay(333);
    digitalWrite(lampu[index][1], LOW);  // Kuning mati
    delay(333);
  }

  // 3. Kembali ke Merah
  digitalWrite(lampu[index][2], HIGH);
}
