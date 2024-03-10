// 'ping pong' diodami - swiatelko odbija sie od jednej strony do drugiej

void setup() {
  DDRB = 255;
  PORTB = 1;
}

void loop() {
  delay(1000);
  for(int i = 1; i <= 7; i++) {
    PORTB = ~(1 << i);
    delay(1000);
  }
  for(int i = 7; i > 0; i--) {
    PORTB = ~(1 << i);
    delay(1000);
  }
}
