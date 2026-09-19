/*
 * Node 1 — Wearable di pergelangan tangan.
 * ESP32 + MAX30102 (detak jantung + SpO2) -> kirim via BLE.
 *
 * Payload JSON:
 *   {"node_id":"wrist01","seq":N,"t_kirim":<epoch_ms>,"bpm":..,"spo2":..}
 *
 * TODO(minggu 3): baca sensor dan uji keluaran serial.
 * TODO(minggu 4): aktifkan BLE dan kirim payload berkala.
 */
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

const char* NODE_ID = "wrist01";
unsigned long seq = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  // TODO(minggu 3): inisialisasi sensor dan cek koneksi I2C.
}

void loop() {
  // TODO(minggu 3): baca BPM + SpO2, cetak ke Serial.
  // TODO(minggu 4): bentuk payload JSON dan kirim melalui BLE.
  delay(1000);
}
