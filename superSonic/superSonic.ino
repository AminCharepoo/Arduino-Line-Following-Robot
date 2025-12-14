const int Trig = 13;
const int Echo = 12;

void setup() {
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10); // standard pulse
  digitalWrite(Trig, LOW);
  
  long duration = pulseIn(Echo, HIGH, 30000); // timeout 30ms
  if(duration == 0){
    Serial.println("No pulse detected");
  } else {
    int distance = duration / 58;
    Serial.print("Distance: ");
    Serial.println(distance);
  }
  delay(500);
}
