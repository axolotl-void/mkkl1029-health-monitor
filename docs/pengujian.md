# Pengujian

## Cara Menjalankan Penerima

```bash
pip install -r src/receiver/requirements.txt

# Uji coba tanpa perangkat keras (dua node tiruan, 60 detik):
python src/receiver/receiver.py --source sim --durasi 60 --skenario uji

# Pengukuran sesungguhnya:
python src/receiver/receiver.py --source ble       # Node 1
python src/receiver/receiver.py --source mqtt --mqtt-host 192.168.1.10
python src/receiver/receiver.py --source dua       # keduanya sekaligus

# Simpan grafik ke docs/grafik/:
python src/dashboard/app.py --plot
```

Hasil tiap sesi: satu CSV per paket dan satu `.ringkasan.json` berisi keempat
parameter QoS pada folder `data/`.

> [!warning] Angka simulasi bukan hasil pengukuran
> Mode `--source sim` memakai dua node tiruan dengan jejak delay buatan. Gunanya
> menguji perhitungan QoS dan dashboard **sebelum** perangkat keras selesai
> dirakit, bukan menghasilkan data untuk laporan. Tabel di bawah hanya boleh
> diisi dari sesi `--source ble` atau `--source mqtt` dengan perangkat
> sesungguhnya.

### Catatan penting: latency yang dilaporkan adalah delay relatif

Jam pada node dan jam pada laptop penerima tidak sama, sehingga
`t_terima − t_kirim` bukan latency, melainkan latency ditambah selisih jam.
Penerima mengestimasi selisih jam itu sebagai nilai **terkecil** dari
`t_terima − t_kirim` sepanjang sesi (paket tercepat dianggap hampir tanpa
antrean). Akibatnya angka latency adalah **delay relatif terhadap paket
tercepat**, bukan delay absolut. Nilai selisih jam yang dipakai dicatat pada
berkas ringkasan (`offset_jam_detik` dan `catatan_latency`) supaya dapat
diperiksa, dan hal ini wajib disebutkan saat melaporkan hasil.

Cara membandingkan metode penyelarasan jam:

```bash
python src/receiver/receiver.py --source mqtt --metode-offset minimum   # bawaan
python src/receiver/receiver.py --source mqtt --metode-offset awal
python src/receiver/receiver.py --source mqtt --metode-offset tanpa
```

## Skenario yang Diuji

| # | Skenario | Yang divariasikan | Parameter yang diamati |
|---|---|---|---|
| 1 | Jarak dekat | Node pada 1 m dari penerima | Keempat parameter QoS |
| 2 | Jarak sedang | Node pada 4 m dari penerima | Keempat parameter QoS |
| 3 | Jarak jauh | Node pada 8 m dari penerima | Keempat parameter QoS |
| 4 | Penghalang | Dinding atau tubuh di antara node dan penerima | Packet loss, jitter |
| 5 | Interferensi | Ruangan padat perangkat 2,4 GHz vs kosong | Latency, jitter |
| 6 | Koneksi terputus | Salah satu node dimatikan saat pengiriman | Perilaku penyambungan ulang |
| 7 | Daya | Pengiriman terus-menerus sampai baterai habis | Lama pemakaian |

## Cara Mencatat Hasil

Setiap sesi pengukuran menghasilkan satu berkas CSV pada folder `data/` dengan
penamaan `sesi-<skenario>-<tanggal>-<jam>.csv`. Setiap berkas dicatat pula pada
tabel di bawah beserta kondisi ruangan saat pengukuran berlangsung.

Hal yang wajib dicatat pada setiap sesi:

- Waktu dan tanggal pengukuran.
- Jarak node ke penerima.
- Kondisi ruangan: jumlah orang dan perkiraan jumlah perangkat WiFi aktif.
- Node mana yang dipakai (dan posisi pemasangan sensornya).
- Pembanding: hasil pembacaan oximeter jari dan termometer digital.

## Tabel Hasil Sementara

| Skenario | Waktu | Latency rata-rata (ms) | Packet loss (%) | Jitter (ms) | Throughput (paket/s) | Catatan |
|---|---|---|---|---|---|---|
| Jarak 1 m | Belum diukur | — | — | — | — | — |
| Jarak 4 m | Belum diukur | — | — | — | — | — |
| Jarak 8 m | Belum diukur | — | — | — | — | — |
| Penghalang | Belum diukur | — | — | — | — | — |
| Interferensi | Belum diukur | — | — | — | — | — |
| Koneksi terputus | Belum diukur | — | — | — | — | — |
| Daya | Belum diukur | — | — | — | — | — |

## Perbandingan dengan Alat Pembanding

| Sesi | Pembacaan sensor | Pembacaan alat pembanding | Selisih |
|---|---|---|---|
| Detak jantung | Belum diukur | — | — |
| SpO2 | Belum diukur | — | — |
| Suhu tubuh | Belum diukur | — | — |

## Catatan

Tabel di halaman ini diisi setelah pengukuran pertama dilakukan (minggu ke-6).
Hasil lengkap beserta grafiknya disusun pada laporan akhir menjelang UAS.
