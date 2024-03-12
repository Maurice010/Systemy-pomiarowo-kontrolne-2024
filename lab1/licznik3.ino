// #############################
// Wyswietlacz 8-segmentowy:
//
//     A
//    F B
//     G
//    E C
//     D .dot(dp)
//
// binary - dpGFE DCBA
// swiecenie, wybor cyfry = LOW
// #############################

void setup() {
  DDRB = 255;
  DDRA = 255;
  DDRC = 0;
  PORTA = 0;
  PORTB = 0;
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
}

const int button = 16;

const byte nums[] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10011000};
const byte numsDot[] = {0b01000000, 0b01111001, 0b00100100, 0b00110000, 0b00011001, 0b00010010, 0b00000010, 0b01111000, 0b00000000, 0b00011000};

unsigned long t1;
unsigned long t2;
bool buttonPressed = false;

void loop() {
    byte button = PINC & 1;
    int num = Serial.parseInt();

    Serial.println(num);
  
    int cyfra[] = {num / 1000, (num / 100) % 10, (num / 10) % 10, num % 10};

    Serial.println(cyfra[0]);
    Serial.println(cyfra[1]);
    Serial.println(cyfra[2]);
    Serial.println(cyfra[3]);

    if(button == LOW) {
      t1 = millis();
      buttonPressed = true;
    }

    while(Serial.available() <= 0) {
      for(int i = 0; i < 4; i++) {
        if(i == 1) {
          PORTB = numsDot[cyfra[i]];
        }
        else {
          PORTB = nums[cyfra[i]];
        }
        PORTA = ~(1 << i);
        delay(1); // diody nie sa w stanie tak szybko sie swiecic gdyby nie bylo
      }
      t2 = millis();

      if((t2 - t1) >= 1000 && num > 0 && buttonPressed == true) {
        num--;
        cyfra[0] = num / 1000;
        cyfra[1] = (num / 100) % 10;
        cyfra[2] = (num / 10) % 10;
        cyfra[3] = num % 10;
        t1 = millis();
      }
    }

    PORTA = 255;
    buttonPressed = false;
}








