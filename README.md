# LoRaWan Antares
<img width="500" height="300" alt="Lora4 pptx" src="https://github.com/user-attachments/assets/5aadb0a8-3778-4ee4-8a72-6adcda04dc1b" />

# Selayang Pandang

Belajar LoRaWan dan Telkom Antares melalui praktek langsung<br>
Saya bagikan ilmu LoRa dan LoRaWan yang saya sudah geluti sejak 2021<br>
Melalui praktek yang sudah saya lakukan bersama TRSE - Undiksha di 2025<br>
4 Modul ini semoga dapat membantu siapapun yang sedang belajar komunikasi LoRa<br><br>
Part 1 : https://github.com/ahocool-aisi555/LoRa_1<br>
Part 2 : https://github.com/ahocool-aisi555/LoRa_2<br>
Part 3 : https://github.com/ahocool-aisi555/LoRa_IOT_GW_DIY

# Bahan-Bahan

1. LiLyGo/TTGO - LoRa- ESP32 Modul <br>
2. DHT11 / DHT22 <br>
3. Kabel Jumper <br> <br>

<img width="400" height="225" alt="lora_ttgo" src="https://github.com/user-attachments/assets/e273fa06-9df8-479d-9233-c9802d3cc0c8" />

Jika mau belajar dasar pengiriman data suhu TTGO ke Antares bisa baca di : https://www.aisi555.com/2024/05/lorawan-ttgo-esp32-telkom-antares.html

# Library

Uncomplete But Working library from Ricaun : https://github.com/ricaun/LoRaWanPacket <br>
jangan gunakan library Antares yg sudah tidak di maintenis lagi


# Teori LoRaWan

<img width="500" height="300" alt="Lora4 pptx (1)" src="https://github.com/user-attachments/assets/7dc2f584-2f4a-4d68-a2e7-b8387c4065f2" />

# Regulasi LoRaWan di Indonesia

- Frekuensi band AS 923-2 (921.2 Mhz  - 922.6Mhz) - 200khz spacing per channel<br>
- Class A dan C <br>
- SF : 7-12 <br>
- Bandwidth : 125 khz <br>
- Panjang pesan : max 80 karakter <br>
- Lebih tepat digunakan untuk monitoring / meter,  bukan untuk kontrol perangkat

# Antares - LoRaWan

<img width="400" height="268" alt="lora_kebalen" src="https://github.com/user-attachments/assets/7f7fc858-26b8-4f1b-a36b-a7173dcb1101" />

Silahkan menuju ke blog saya karena sepertinya saya yg pertama kali mengoprek LoRaWan nya antares sampe bisa jalan : https://www.aisi555.com/2022/05/lorawan-antares-id-pengolahan-data.html

# LoRaWanPacket Master

Script disini penggalan dari script yg sukses kirim LoRaWan ke Antares di semua frekuensi<br>

```c++
struct LoRa_config
{
  long Frequency;
  int SpreadingFactor;
  long SignalBandwidth;
  int CodingRate4;
  bool enableCrc;
  bool invertIQ;
  int SyncWord;
  int PreambleLength;
};

long LoRa_frek_INA_923_start = 921200000 ; 
long LoRa_frek_INA_923_end   = 922600000 ;
long LoRa_frek_step = 200000;

static LoRa_config txLoRa = {LoRa_frek_INA_923, 12, 125000, 5, true, false, 0x34, 8};


```

<img width="500" height="300" alt="Lora4 pptx (2)" src="https://github.com/user-attachments/assets/9fab3b19-7960-416a-b3d8-f216997fbbf2" />

Silahkan menuju ke : https://www.aisi555.com/2024/05/lorawan-antares-menampilkan-grafik-di.html


# Praktek

<img width="500" height="300" alt="Lora4 pptx (3)" src="https://github.com/user-attachments/assets/e5cfdc56-36f3-482b-b528-7d0a80e6e3d2" />

<img width="500" height="300" alt="Lora4 pptx (4)" src="https://github.com/user-attachments/assets/31160031-47b5-40ac-8754-09bbed819e54" />

<img width="500" height="300" alt="Lora4 pptx (5)" src="https://github.com/user-attachments/assets/8b3b6490-fc4e-4594-84f3-d9550e2f56ad" />


# Acknowledgement

Bapak Ketut Udy Ariawan ST. MT. - Koordinator Prodi Teknik Rekayasa Sistem Elektronika - Fakultas Teknik Dan Kejuruan - Universitas Pendidikan Ganesha - Singaraja Bali 
