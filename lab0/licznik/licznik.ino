//  - diody to reprezentacja licznika bitowego
//  - przycisk jest źródłem informacji dla procesora
//  - klikajac przyciskiem inkrementujemy licznik o 1
//  - drugi przycisk inkrementuje o 10

const int buttonPinOne = 24;
const int buttonPinTen = 25;
int ans = 0;

void setup() {
  DDRB = 255;
  DDRA = 0;
  
  pinMode(buttonPinOne, INPUT_PULLUP);
  pinMode(buttonPinTen, INPUT_PULLUP);
}

void loop() {
  byte buttonPinOne = PINA & 1;
  byte buttonPinTen = PINA & 2;
  PORTB = ~ans;

  if(buttonPinOne == LOW) {
    ans++;
    delay(100);
  }
  if(buttonPinOne == LOW && buttonPinTen == HIGH) {
    ans++;
    delay(100);
  }
  if(buttonPinOne == HIGH && buttonPinTen == LOW) {
    ans += 10;
    delay(100);
  }
}
