# Pengujian

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
