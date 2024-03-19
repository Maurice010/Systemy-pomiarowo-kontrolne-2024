// 1. Serial.println("test") (w przykladzie ReadASCIIString sluzyc do debugowania (patrzymy co sie dzieje na porcie klikajac lupee po prawej stronie)
// 2. Wpisujemy liczbe 4-cyfrowa - procesor ma ja ustawic na wyswietlaczu 7-segmentowym
// Najpierw wyswietlamy cyfry 0 - 9 na wyswietlaczu:
// Wybieramy port 8-bitowy i podpinamy (zeby zaświecić to dajemy LOW na SEGMENT i CYFRA)
// Potem robimy odliczanie jak w kuchence mikrofalowej 1. 2 starsze cyfry to liczba min, 2 mlodsze to sekundy, tam gdzie podzial kropka
// Potem odliczanie dopiero po nacisnieciu przycisku

// A
//F B
// G
//E C
// D dot(dp)
//
//binary - dpGFE DCBA
//swiecenie, wybor cyfry = LOW
const int button = 16;
void setup() {
  DDRB = 255;
  DDRA = 255;
  PORTA = 0;
  PORTB = 0;
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
}

const byte nums[] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10011000};
const byte numsDot[] = {0b01000000, 0b01111001, 0b00100100, 0b00110000, 0b00011001, 0b00010010, 0b00000010, 0b01111000, 0b00000000, 0b00011000};

unsigned long t1 = 0;
unsigned long t2 = 0;

byte buttonPressed = false;

void loop() {
    byte button = PINC & 1;
    int num = 0;
    num = Serial.parseInt();
  
    int cyfra[] = {num / 1000, (num / 100) % 10, (num / 10) % 10, num % 10};

    while(Serial.available() > 0) {
        button = PINC & 1;
        if(button == LOW && buttonPressed == false) {
          t1 = millis();
          buttonPressed = true;
        }
        for(int i = 0; i < 4; i++) {
          if(i == 1) {
            PORTB = numsDot[cyfra[i]];
          }
          else {
            PORTB = nums[cyfra[i]];
          }
          PORTA = ~(1 << i);
          delay(1); // potrzebny, diody nie sa w stanie tak szybko sie swiecic gdyby nie bylo
        }
        t2 = millis();
        
        if((t2 - t1) >= 1000 && num > 0 && buttonPressed == true) {
          int sec = num % 100;
          int mins = num / 100;
          if(sec <= 0 && mins > 0) {
            mins--;
            num = mins * 100 + 59;
          }
          else if(sec > 0) {
            sec--;
            num = mins * 100 + sec;
          }
            
          cyfra[0] = num / 1000;
          cyfra[1] = (num / 100) % 10;
          cyfra[2] = (num / 10) % 10;
          cyfra[3] = num % 10;
          t1 = t2;
          
        }
      }

    PORTA = 255;
    buttonPressed == false;
}








