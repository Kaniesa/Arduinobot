int x = 0;

void setup() {
  //runs once
  Serial.begin(115200);
  Serial.setTimeout(1);
}

void loop() {
    //run repeatedly
  Serial.println(x);
  x++;
  delay(0.1);
}
