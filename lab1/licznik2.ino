// 1. Serial.println("test") (w przykladzie ReadASCIIString sluzyc do debugowania (patrzymy co sie dzieje na porcie klikajac lupee po prawej stronie)
// 2. Wpisujemy liczbe 4-cyfrowa - procesor ma ja ustawic na wyswietlaczu 7-segmentowym
// Najpierw wyswietlamy cyfry 0 - 9 na wyswietlaczu:
// Wybieramy port 8-bitowy i podpinamy (zeby zaświecić to dajemy LOW na SEGMENT i CYFRA)
// Potem robimy odliczanie jak w kuchence mikrofalowej 1. 2 starsze cyfry to liczba min, 2 mlodsze to sekundy, tam gdzie podzial kropka

// A
//F B
// G
//E C
// D dot(dp)
//
//binary - dpGFE DCBA
//swiecenie, wybor cyfry = LOW

void setup() {
  DDRB = 255;
  DDRA = 255;
  PORTA = 0;
  PORTB = 0;
  Serial.begin(9600);
}

const byte nums[] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10011000};

void loop() {
    int num = Serial.parseInt();
    Serial.println(num);
  
    int cyfra[] = {num / 1000, (num / 100) % 10, (num / 10) % 10, num % 10};
    Serial.println(cyfra[0]);
    Serial.println(cyfra[1]);
    Serial.println(cyfra[2]);
    Serial.println(cyfra[3]);

    while(Serial.available() <= 0) {
      for(int i = 0; i < 4; i++) {
        PORTB = nums[cyfra[i]];
        PORTA = ~(1 << i);
        delay(1); // potrzebny, diody nie sa w stanie tak szybko sie swiecic gdyby nie bylo
      }
    }
    PORTA = 255;
}








