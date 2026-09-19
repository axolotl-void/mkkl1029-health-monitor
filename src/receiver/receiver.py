#!/usr/bin/env python3
"""Penerima data dari dua node nirkabel sekaligus.

Jalur 1: BLE  — Node 1 (pergelangan, MAX30102) mengirim detak jantung + SpO2.
Jalur 2: MQTT — Node 2 (dada, MLX90614) mengirim suhu tubuh.

Setiap paket dicatat waktu tibanya (t_terima) untuk menghitung:
  latency_ms  = (t_terima - t_kirim) * 1000
  jitter_ms   = |latency[i] - latency[i-1]|
  packet_loss = 1 - (jumlah seq unik / jumlah seq seharusnya)
  throughput  = jumlah paket diterima / durasi

Format payload dari node (JSON):
  {"node_id": "wrist01", "seq": 42, "t_kirim": 1699999999.123,
   "bpm": 72, "spo2": 97, "suhu": 36.5}

TODO(minggu 5): implementasi perhitungan QoS dan penulisan CSV.
"""
from __future__ import annotations

import argparse
import asyncio


async def ble_listener(out_dir: str) -> None:
    """Mendengarkan paket dari Node 1 (BLE)."""
    # TODO(minggu 4): pakai bleak untuk scan + subscribe karakteristik.
    raise NotImplementedError


async def mqtt_listener(out_dir: str) -> None:
    """Mendengarkan paket dari Node 2 (MQTT)."""
    # TODO(minggu 4): pakai paho-mqtt, topik klinik/#.
    raise NotImplementedError


async def main() -> None:
    ap = argparse.ArgumentParser(description="Penerima data dua node nirkabel")
    ap.add_argument("--out", default="data/", help="folder keluaran CSV")
    ap.add_argument("--mqtt-host", default="localhost")
    args = ap.parse_args()
    print(f"Menyimpan hasil ke {args.out}")
    await asyncio.gather(ble_listener(args.out), mqtt_listener(args.out))


if __name__ == "__main__":
    asyncio.run(main())
