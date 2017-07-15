#define DS    2
#define ST_CP 4
#define SH_CP 5

#define DELAY 200 //4 is not noticable

byte bitMap[] = {
  0b11111100, // 0
  0b01100000, // 1
  0b11011010, // 2...
  0b11110010,
  0b01100110,
  0b10110110,
  0b10111110,
  0b11100000,
  0b11111110,
  0b11100110,
  0b11101110,
  0b00111110,
  0b10011100,
  0b01111010,
  0b10011110,
  0b10001110
};

void setup() {
  // put your setup code here, to run once:
  pinMode(DS, OUTPUT);
  pinMode(SH_CP, OUTPUT);
  pinMode(ST_CP, OUTPUT);

  digitalWrite(DS, LOW);
  digitalWrite(SH_CP, LOW);
  digitalWrite(ST_CP, LOW);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(DELAY);

  _setInvisible();
  writeByte(0);
  _setVisible();

  _setInvisible();
  writeByte(255);
  _setVisible();
}

void _setBit(int state) {
  digitalWrite(DS, state);
}

void _clockBit() {
  digitalWrite(SH_CP, HIGH);
  digitalWrite(SH_CP, LOW);
}

void _writeBit(int state) {
  _setBit(state);
  _clockBit();
}

void _setVisible() {
  digitalWrite(ST_CP, HIGH);
}

void _setInvisible() {
  digitalWrite(ST_CP, LOW);
}

void writeByte(byte number) {
  // 0-255
  // clock least significant bit first using >> operators
 // Serial.println(number);
 // Serial.println("\n");
  for(int i = 0; i < 8; i++) {
    //Serial.print(number % 2);
    //Serial.print("\n");
    _writeBit(number % 2);
    number >>= 1;
  }
  //Serial.println("\n\n-------------\n");
}
