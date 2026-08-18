#define ENA 5
#define ENB 6

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 7

#define BUZZER 8

#define TRIG 9
#define ECHO 10

#define METAL_SENSOR 13

#define RED_LED A1
#define GREEN_LED A4

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(METAL_SENSOR, INPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
}

void loop() {

  // Metal detected
  if (digitalRead(METAL_SENSOR) == LOW) {

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    tone(BUZZER, 1000);

    return;
  }

  noTone(BUZZER);

  long distance = getDistance();

  // Obstacle detected
  if (distance < 25) {

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    digitalWrite(GREEN_LED, LOW);

    for (int i = 0; i < 4; i++) {
      digitalWrite(RED_LED, HIGH);
      delay(100);
      digitalWrite(RED_LED, LOW);
      delay(100);
    }

    // Turn right
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    delay(700);
  }
  else {

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    // Forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
}

long getDistance() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);

  if (duration == 0)
    return 999;

  return duration * 0.034 / 2;
}