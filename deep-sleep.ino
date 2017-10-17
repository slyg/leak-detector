#define SLEEP_DELAY_IN_SECONDS 20

void setup() {
  Serial.begin(115200);
  Serial.println("---");
  Serial.println("Wake up for 10s");
  for (int i = 10; i >= 0; i--){
    Serial.println(String(i) + "s");
    delay(1000);
  }
}

void loop() {
  Serial.println("Entering deep sleep mode for 20s");
  ESP.deepSleep(SLEEP_DELAY_IN_SECONDS * 1000000, WAKE_RF_DEFAULT);
  delay(500); // wait for deep sleep
}