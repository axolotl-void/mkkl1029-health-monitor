# Arsitektur Sistem

![Diagram arsitektur](diagrams/arsitektur-mkkl1029.png)

## Komponen

| Komponen | Fungsi | Titik ukur |
|---|---|---|
| Node 1 — pergelangan | ESP32 + MAX30102 membaca detak jantung dan SpO2 | Waktu kirim (`t_kirim`), nomor urut (`seq`), nilai bpm/SpO2 |
| Node 2 — dada/ketiak | ESP32 + MLX90614 membaca suhu tubuh tanpa sentuh | Waktu kirim (`t_kirim`), nomor urut (`seq`), nilai suhu |
| Broker MQTT | Meneruskan pesan dari Node 2 menuju penerima | Waktu terima di broker |
| Penerima (laptop) | Mendengarkan BLE dan MQTT, menghitung parameter QoS | Waktu terima (`t_terima`), jumlah byte |
| Dashboard | Menampilkan grafik tanda vital dan hasil pengukuran | — |

## Alur Data

1. Node 1 dan Node 2 membentuk payload `{node_id, seq, t_kirim, nilai}`.
2. Node 1 mengirim melalui BLE; Node 2 mengirim melalui WiFi ke topik MQTT.
3. Penerima mencatat `t_terima` setiap paket tiba, lalu menghitung `latency = t_terima - t_kirim`.
4. Nomor urut dipakai mendeteksi paket hilang; selisih latency antar paket berurutan menjadi jitter.
5. Hasil disimpan sebagai CSV per sesi dan dikirim ke dashboard untuk ditampilkan sebagai grafik.

## Rumus

| Parameter | Rumus | Satuan |
|---|---|---|
| Latency | `(t_terima - t_kirim) x 1000` | milidetik |
| Jitter | `abs(latency[i] - latency[i-1])` | milidetik |
| Packet loss | `1 - (seq unik diterima / seq seharusnya)` | persen |
| Throughput | `jumlah paket diterima / durasi` | paket per detik |

## Protokol

- **BLE (Bluetooth Low Energy)** — jalur Node 1, dipilih karena hemat daya dan cocok untuk perangkat yang dikenakan.
- **MQTT di atas WiFi 2,4 GHz** — jalur Node 2, dipilih karena ringan dan mendukung banyak node.
- **TCP** — lapisan pengangkut untuk MQTT. Untuk pengukuran packet loss, catat juga jumlah pesan yang tidak sampai sebagai pembanding.
- **HTTP/WebSocket** — jalur tampilan dashboard.

## Catatan Perancangan

Waktu kirim diambil dari jam masing-masing node. Agar latency yang dihitung tidak
terpengaruh selisih jam node dan laptop, penerima mengestimasi selisih jam itu
sebagai **nilai terkecil** dari `t_terima − t_kirim` sepanjang sesi: paket
tercepat dianggap hampir tanpa antrean, sehingga selisihnya mendekati selisih
jam murni.

Akibatnya angka latency yang dilaporkan adalah **delay relatif terhadap paket
tercepat**, bukan delay absolut — dan itu wajib disebutkan saat melaporkan
hasil. Nilai selisih jam yang dipakai (`offset_jam_detik`) serta keterangan
metodenya (`catatan_latency`) ditulis ke berkas ringkasan setiap sesi supaya
dapat diperiksa. Penerima menyediakan `--metode-offset minimum|awal|tanpa`
untuk membandingkan ketiga cara.

Node 1 (BLE) memakai waktu sejak menyala karena tidak tersambung internet,
sedangkan Node 2 (WiFi) dapat mengambil waktu dari NTP. Keduanya tetap berjalan
dengan penyelarasan di sisi penerima, dan menghidupkan NTP pada Node 1 hanya
membuat selisihnya lebih kecil — bukan syarat agar latency terhitung.
