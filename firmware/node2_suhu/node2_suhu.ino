/*
 * Node 2 — Wearable di dada / ketiak.
 * ESP32 + MLX90614 (suhu tubuh tanpa sentuh) -> kirim via WiFi + MQTT.
 *
 * Payload JSON:
 *   {"node_id":"chest01","seq":N,"t_kirim":<epoch_ms>,"suhu":36.5}
 *
 * TODO(minggu 3): baca sensor dan uji keluaran serial.
 * TODO(minggu 4): sambungkan ke WiFi dan publikasikan ke topik MQTT.
 */
#include <Wire.h>
#include <Adafruit_MLX90614.h>

const char* NODE_ID = "chest01";
const char* MQTT_TOPIC = "klinik/suhu/chest01";
unsigned long seq = 0;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(115200);
  mlx.begin();
  // TODO(minggu 4): sambungkan ke WiFi dan setel broker MQTT.
}

void loop() {
  float suhu = mlx.readObjectTempC();
  Serial.printf("suhu=%.2f C\n", suhu);
  // TODO(minggu 4): publikasikan payload JSON ke MQTT_TOPIC.
  delay(1000);
}
