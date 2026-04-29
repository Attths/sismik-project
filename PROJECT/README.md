# Sistem Monitoring Suhu Berbasis Arduino UNO

## Sistem pemantauan suhu real-time menggunakan sensor TMP, LCD I2C 16×2, dan indikator LED tiga warna Berbasis Arduino UNO.

---

## Tentang Proyek

Proyek ini merupakan implementasi **Sistem Monitoring Suhu** berbasis Arduino UNO yang dirancang untuk mata kuliah **Sistem Mikrokontroler** di Program Studi Teknik Komputer, Fakultas Teknik, Universitas Jenderal Soedirman.

Kemampuan Sitem:
- Membaca suhu lingkungan secara real-time menggunakan sensor TMP36 (ADC)
- Menampilkan nilai suhu dan status pada LCD 16×2 melalui protokol **I2C**
- Memberikan indikator visual dengan **3 LED** (Hijau / Kuning / Merah)
- Mengirimkan data monitoring ke komputer melalui **UART Serial**

## Kategori Suhu

| Kondisi | Rentang | LED Aktif |
|---------|---------|-----------|
| 🟢 Dingin | < 25°C | Hijau |
| 🟡 Normal | 25°C – 30°C | Kuning |
| 🔴 Panas | > 30°C | Merah |

---

## Schematic Sistem

<img width="839" height="647" alt="image" src="https://github.com/user-attachments/assets/91f2afe3-c25a-40a9-9ed9-70aefd0ab112">

---

## Komponen yang Digunakan

| No. | Komponen | Fungsi |
|-----|----------|--------|
| 1 | Arduino UNO | Mikrokontroler utama sebagai otak pemrosesan sistem |
| 2 | Sensor TMP36 | Membaca suhu lingkungan secara analog dan mengonversinya ke tegangan |
| 3 | LCD 16×2 + Modul I2C | Menampilkan nilai suhu dan status secara real-time via I2C |
| 4 | LED Merah | Indikator visual kondisi suhu tinggi (> 30°C) |
| 5 | LED Kuning | Indikator visual kondisi suhu sedang (25°C – 30°C) |
| 6 | LED Hijau | Indikator visual kondisi suhu normal / dingin (< 25°C) |
| 7 | Resistor 220Ω | Pembatas arus untuk masing-masing LED |
| 8 | Breadboard | Media penghubung antar komponen tanpa solder |
| 9 | Kabel Jumper | Menghubungkan komponen satu dengan lainnya |
| 10 | Kabel USB Tipe B | Menghubungkan Arduino ke Laptop dan sebagai sumber daya |

---

## Koneksi Pin

| Komponen | Pin Arduino UNO |
|----------|-----------------|
| Sensor TMP36 | A0 |
| LED Hijau + Resistor 220Ω | D8 |
| LED Kuning + Resistor 220Ω | D9 |
| LED Merah + Resistor 220Ω | D10 |
| LCD I2C – SDA | A4 |
| LCD I2C – SCL | A5 |
| VCC semua komponen | 5V |
| GND semua komponen | GND |

---

## Cara Kerja Sistem

1. **Inisialisasi** — Arduino menginisialisasi Serial (9600 bps), mengatur pin LED sebagai OUTPUT, menginisialisasi LCD, dan menampilkan pesan `"Monitoring Suhu - Sistem Aktif..."` selama 1,5 detik.

2. **Infinite Loop** — Program memasuki fungsi `loop()` yang berjalan secara terus-menerus.

3. **Baca Suhu** — Fungsi `bacaSuhu()` membaca nilai analog dari pin A0, mengonversinya ke tegangan (0–5V), kemudian ke derajat Celsius menggunakan rumus TMP36:
   ```
   suhu = (tegangan - 0.5) × 100
   ```

4. **Klasifikasi Suhu** — Fungsi `tentukanKategori()` menggunakan logika `if-else` untuk menentukan kategori: *Dingin*, *Normal*, atau *Panas*.

5. **Kontrol LED** — Fungsi `aturLED()` menyalakan satu LED yang sesuai dan mematikan dua lainnya.

6. **Tampil LCD** — Fungsi `tampilLCD()` menampilkan nilai suhu di baris 1 dan kategori di baris 2 via I2C.

7. **Kirim Serial** — Fungsi `kirimSerial()` mengirimkan data suhu dan kategori ke Serial Monitor via UART.

---

## Source Code

```cpp

```

---

## Penjelasan Fungsi

| Fungsi | Deskripsi |
|--------|-----------|
| `bacaSuhu()` | Membaca nilai ADC dari pin A0 dan mengonversinya ke °C menggunakan rumus TMP36 |
| `tentukanKategori(suhu)` | Mengklasifikasikan suhu dengan logika `if-else` menjadi Dingin / Normal / Panas |
| `aturLED(suhu)` | Mengontrol 3 pin GPIO output; hanya satu LED yang HIGH sesuai kategori |
| `tampilLCD(suhu, kategori)` | Menampilkan suhu (baris 1) dan status (baris 2) ke LCD via I2C (0x27) |
| `kirimSerial(suhu, kategori)` | Mengirim data suhu + kategori ke Serial Monitor via UART 9600 bps |
| `setup()` | Inisialisasi Serial, pin LED, dan LCD — dijalankan sekali saat boot |
| `loop()` | Fungsi utama yang berjalan secara infinite loop — memanggil semua fungsi di atas |

---

## Simulasi Sistem

<img width="591" height="426" alt="image" src="https://github.com/user-attachments/assets/25df3e4b-44a5-4639-a274-046b01c0e3a5">

---

## Nama Partisipan

**Kelompok 3 — Sistem Mikrokontroler 2026**
Program Studi Teknik Komputer, Fakultas Teknik, Universitas Jenderal Soedirman

| Nama | NIM |
|------|-----|
| Wendy Virtus | H1H024048 |
| Abyan Devadi | H1H024049 |
| Muhammad Aziz Ihza F. S. | H1H024050 |
| Muhammad Faiz M. | H1H024051 |
| Hafish Athallah | H1H024052 |
| Rasta Listiadi | H1H024053 |

### **Dosen Pengampu:** Ucky Pradestha Novettralita, S.Pd., M.Kom.

---

## Referensi

- BINUS University. (2019). *Mengenal Mikrokontroler*. https://binus.ac.id/bandung/2019/11/mengenal-mikrokontroler/
- Eraspace. (2024). *Apa Itu CPU? Ketahui Pengertian, Fungsi, dan Kegunaannya*. https://eraspace.com/artikel/post/apa-itu-cpu
- BINUS University. (2024). *Mengenal Interrupt pada Mikrokontroler*. https://comp-eng.binus.ac.id/2024/12/09/mengenal-interrupt-pada-mikrokontroler
- Kabar Harian. (2022). *Pengertian Peripheral, Fungsi, dan Contoh-Contoh Komponennya*. https://kumparan.com/kabar-harian

---