void setup() {
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  delay(1000);
  Serial.println("HIGH");
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  delay(1000);
  Serial.println("Low");
}
