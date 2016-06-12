#include <Servo.h>

Servo servo;
int pos;
int keskeytys = 0;
#define trigPin D6
#define echoPin D5
void setup() {
  // put your setup code here, to run once:
  servo.attach(D1);
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(D7, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println("Rotating servo");
  while (keskeytys == 0) {
    digitalWrite(D7, HIGH);
    for (pos = 0; pos <= 180; pos += 1) {
      servo.write(pos);
      if(sensorData() == 1){
        digitalWrite(D7, LOW);
        keskeytys = 1;
        Serial.println("Keskeytys commencing");
        break;
      }
      delay(15);
    }
    for (pos = 180; pos >= 0; pos -= 1) {
      servo.write(pos);
      if(sensorData() == 1){
        digitalWrite(D7, LOW);
        keskeytys = 1;
        Serial.println("Keskeytys commencing");
        break;
      }
      delay(15);
    }
    break;
  }

  delay(5000);
  keskeytys = 0; 
}


int sensorData(){
  int palautus = 0;
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else if(distance <= 30) {
    Serial.print(distance);
    Serial.println(" cm");
    palautus = 1;
  }
  return palautus;
}

