void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 5; i++){
    Serial.println(i);
    delay(500);
  }
  Serial.println("goodnight");
  ESP.deepSleep(0);
}
